
#include <msp430x14x.h>
#include "systerminit.h"
#include "led.c"
#include "ds1302.c"
#include "ds18b20.c"
#include "flash.h"
#include "display.h"
#include "keyhandle.h"

void main(void)
{
  unsigned char i;
  WDTCTL=WDT_ADLY_250;              //定时器模式，250ms中断一次
  IE1|=WDTIE;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
  BCSCTL2|=SELM1;                    //MCLK为8MHZ，SMCLK时钟源选择DCO 800khz
  do{
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);          //如果标志位1，则继续循环等待
  IFG1&=~OFIFG;  
  //Close_LED();//关数码管
  delay_ms(5);
  P5DIR|=BIT7+BIT6+BIT5+BIT0+BIT1;//将液晶相关控制位设为输出
  LCDDATOUT;//液晶数据口设置输出
  P4OUT=0xff;//初始化液晶数据口为高电平
  LCD_INIT();//初始化液晶
  delay_ms(500);
  P1DIR=0xf7;//键盘端口初始化
  P1OUT=0xFF;
  P1IE|=BIT3;//允许中断
  P1IES=0xff;//下降沿中断
  P2DIR=0xff;
  P2OUT=0xff;
  /********初始化flash********/
  FCTL2=FWKEY+FSSEL1+FN0;
 
  /********初始化定时器*********/
  TACTL|=TASSEL_1+MC_2+TACLR;
  TACCR0=1;
  TACCR1=1;  
  wellcomplay();//显示欢迎画面
  read_segA(); //读取flash闹钟数据 
  LCD_CLEAR();//清屏
  P3DIR |=BIT1+BIT2+BIT0+BIT4;//初始化语音使用的引脚
  DS1302_INIT();//初始化DS1302
  GET_TIME();//读取一次时间
 // lunar_calendar(year,month,day);//进行一次阴历的转换
  display();  //显示时间画面
 
  DS_INIT(); //初始化18B20
  DS_write(0xcc);  //跳过ROM指令
  DS_write(0x44);//启动转换
  _BIS_SR(GIE);//开总中断
  while(1)
  {
   _BIS_SR(LPM2_bits);//进入低功耗
   if( (minute==0||minute==30) && (second==3))
   { 
      sj=hour+minute/30;
      Send_threelines(sj);
     // delay_ms(25);
   }
    if( (minute==acminute)&&(hour==achour)&&(second==10))
   { 
    // sj=2*hour+minute/30;
      Send_threelines(acmusic+48);
      //Send_threelines();
   }
    if(keydownflag)//如果有按键按下，进入键值分析处理函数
    {
      
      keydownflag=0;//清除标志
      keyvalue_const();//键值分析处理
    }
    if(flag&&(setflag==0))//1s刷新一次数据
    {
      flag=0;        
      GET_TIME();//读取时间
      temperature=GET_TEMP();//获取温度    
      display(); //刷新屏幕
    }
    switch(setflag)//根据状态标志的值显示相应的画面
    {
    case 1:play_menu_1();IE1&=~WDTIE;  _EINT();break;//主菜单（一）
    case 2:play_menu_2();IE1&=~WDTIE;   _EINT();break;//主菜单（二）
    case 3:play_menu_1_0();lastplay=1;IE1&=~WDTIE;   _EINT();break;//时间设置画面
    case 4:play_menu_2_0();lastplay=1;IE1&=~WDTIE;   _EINT();break;//闹钟设置画面
    default :break;
    }

  }
}
//中断说明
#pragma vector=WDT_VECTOR
__interrupt void wdt_time(void)
{
 _DINT();
  temp=second;
  second=READ_DS1302(READ_SECOND);
  if(second!=temp)
  {
   flag=1;
   _EINT();
  _BIC_SR_IRQ(LPM2_bits);
  }
  
}
#pragma vector=PORT1_VECTOR
__interrupt void port1(void)
{
  P1IFG&=~BIT3;
  keydownflag=1;
  _DINT();//关闭总中断
  _BIC_SR_IRQ(LPM2_bits);
}
/*
#pragma vector=TIMERA0_VECTOR
__interrupt void time_A0(void)

{
    _DINT();
   if( minute==acminute&&hour==achour&&month==acmonth&&day==acday&&second==10)
   { 

      Send_threelines(0x00);
      
 
   }
   TACCTL0&=~CCIFG;
   TACCTL0&=~CCIE;
   _EINT();
   _BIS_SR(LPM2_bits);//进入低功耗
}*/

#pragma vector=TIMERA1_VECTOR
__interrupt void time_A1(void)
{
    _DINT(); 
    
    if( (minute==acminute)&&(hour==achour)&&(second==10))
   { 
    // sj=2*hour+minute/30;
      Send_threelines(0x03);
      //Send_threelines();
   }
   
   if( (minute==0||minute==30) && (second==3))
   { 
      sj=2*hour+minute/30;
      Send_threelines(sj);
   }
   

   TACCTL1&=~CCIFG;
   TACCTL1&=~CCIE;
   _EINT();
   _BIS_SR(LPM2_bits);//进入低功耗
  // TACCTL0&=~CCIE;//P2OUT|=BIT2;
 }