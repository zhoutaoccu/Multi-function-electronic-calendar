
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
  WDTCTL=WDT_ADLY_250;              //��ʱ��ģʽ��250ms�ж�һ��
  IE1|=WDTIE;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1;                    //MCLKΪ8MHZ��SMCLKʱ��Դѡ��DCO 800khz
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);          //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG;  
  //Close_LED();//�������
  delay_ms(5);
  P5DIR|=BIT7+BIT6+BIT5+BIT0+BIT1;//��Һ����ؿ���λ��Ϊ���
  LCDDATOUT;//Һ�����ݿ��������
  P4OUT=0xff;//��ʼ��Һ�����ݿ�Ϊ�ߵ�ƽ
  LCD_INIT();//��ʼ��Һ��
  delay_ms(500);
  P1DIR=0xf7;//���̶˿ڳ�ʼ��
  P1OUT=0xFF;
  P1IE|=BIT3;//�����ж�
  P1IES=0xff;//�½����ж�
  P2DIR=0xff;
  P2OUT=0xff;
  /********��ʼ��flash********/
  FCTL2=FWKEY+FSSEL1+FN0;
 
  /********��ʼ����ʱ��*********/
  TACTL|=TASSEL_1+MC_2+TACLR;
  TACCR0=1;
  TACCR1=1;  
  wellcomplay();//��ʾ��ӭ����
  read_segA(); //��ȡflash�������� 
  LCD_CLEAR();//����
  P3DIR |=BIT1+BIT2+BIT0+BIT4;//��ʼ������ʹ�õ�����
  DS1302_INIT();//��ʼ��DS1302
  GET_TIME();//��ȡһ��ʱ��
 // lunar_calendar(year,month,day);//����һ��������ת��
  display();  //��ʾʱ�仭��
 
  DS_INIT(); //��ʼ��18B20
  DS_write(0xcc);  //����ROMָ��
  DS_write(0x44);//����ת��
  _BIS_SR(GIE);//�����ж�
  while(1)
  {
   _BIS_SR(LPM2_bits);//����͹���
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
    if(keydownflag)//����а������£������ֵ����������
    {
      
      keydownflag=0;//�����־
      keyvalue_const();//��ֵ��������
    }
    if(flag&&(setflag==0))//1sˢ��һ������
    {
      flag=0;        
      GET_TIME();//��ȡʱ��
      temperature=GET_TEMP();//��ȡ�¶�    
      display(); //ˢ����Ļ
    }
    switch(setflag)//����״̬��־��ֵ��ʾ��Ӧ�Ļ���
    {
    case 1:play_menu_1();IE1&=~WDTIE;  _EINT();break;//���˵���һ��
    case 2:play_menu_2();IE1&=~WDTIE;   _EINT();break;//���˵�������
    case 3:play_menu_1_0();lastplay=1;IE1&=~WDTIE;   _EINT();break;//ʱ�����û���
    case 4:play_menu_2_0();lastplay=1;IE1&=~WDTIE;   _EINT();break;//�������û���
    default :break;
    }

  }
}
//�ж�˵��
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
  _DINT();//�ر����ж�
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
   _BIS_SR(LPM2_bits);//����͹���
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
   _BIS_SR(LPM2_bits);//����͹���
  // TACCTL0&=~CCIE;//P2OUT|=BIT2;
 }