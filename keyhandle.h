
/*************红外接收函数***************/

unsigned char infrared(void)
{
    unsigned char k;
    unsigned char table_IR[32];//用来存放接收的红外信号编码
    //uchar ir=0;
    unsigned char j=0;
    unsigned char value;//存放操作码
    unsigned char keydat=99;
    for(k=0;k<19;k++)
    { 
      delay_us(400);
      if(HW_Q){ return keydat;}  //检测是否有9ms的低电平，否则返回重新检测
    }
    while(!HW_Q);//等待9ms低电平过去
    for(k=0;k<5;k++)
    {
      delay_us(500);
      if(!HW_Q){return keydat;}//如果在2.5ms内有低电平，则认为是干扰，并且退出重新检测
    }
    while(HW_Q);//等待4.5ms高电平过去
    
    for(k=0;k<32;k++)
    {     
      while(!HW_Q);   //等待0.565ms的低电平过去  
      while(HW_Q)    //计算高电平的宽度，判断接收的为"0"还是"1"
      {
        delay_us(100);
        j++;
        if(j>22){break;}    //如果高电平时间过长，跳出循环，继续执行下面的程序   
      }
      if(j>=7)//如果高电平的宽度大于0.7ms,则接收的为1,同时存入数组
      {
        table_IR[k]=1;
      }
      else  table_IR[k]=0;//如果高电平宽度小于0.7ms，则接收的为"0"，同时存入数组
      j=0;
    } 
    for(k=16;k<24;k++)//把第3个字节低四位存入value_L内，便于在液晶上显示
    {
      value<<=1;
      if(table_IR[k])
      value|=0x01;
      
    }
    switch(value)
    {
    case 0x02:keydat=12;break;//功能：控制闹钟的开关，对应遥控器上的下一曲
    case 0xa2:keydat=13;break;//功能：保存退出                   对应遥控器上的CH-
    case 0x62:keydat=14;break;//功能：向上移动      对应遥控器上的CH
    case 0xe2:keydat=15;break;//功能：  返回                  对应遥控器上的CH+
    case 0xa8:keydat=16;break;//功能：向下移动        对应遥控器上的音量+
    case 0x68:keydat=0;break;
    case 0x30:keydat=1;break;
    case 0x18:keydat=2;break;
    case 0x7a:keydat=3;break;
    case 0x10:keydat=4;break;
    case 0x38:keydat=5;break;
    case 0x5a:keydat=6;break;
    case 0x42:keydat=7;break;
    case 0x4a:keydat=8;break;
    case 0x52:keydat=9;break;
    }
    P6DIR|=BIT2;//蜂鸣器端口设为输出模式
    BUZ_ON;
    delay_ms(50);   
    BUZ_OFF;
    P6DIR&=~BIT2;//蜂鸣器端口设为输入模式
    return keydat;
}

/******************
函数功能：如果有键按下，根据系统当前状态进入相应的键值处理模块，然后根据键值执行相应命令
函数说明：本程序中共有五种状态：1.主页面时间显示(setflag==0)
                                2.主菜单（1）(setflag==1)
                                3.主菜单（2）(setflag==2)
                                4.时间设置 (setflag==3)
                                5.闹钟设置  (setflag==4) 
         每次有键按下时检测setflag标志，根据键值执行相应命令

*****************/
void keyvalue_const(void)
{
  if(setflag==0)//主页面1状态下的键值处理
  {   
  key_value=infrared();//分析键值
  switch(key_value)
  {
  case 13: setflag=1;timeread(table_time,table_dat);break;//如果键值为13：进入2状态.主菜单（1）
  default :break;//如果键值为其它值，直接返回。
  }
  return ;
 
  }
  else if(setflag==1)//2状态画面下的键值处理
  {
  key_value=infrared();//分析键值
  switch(key_value)
  {
  case 13:setflag=2;break;//键值13：进入3状态.主菜单（2）
  case 14:setflag=3;break;//键值14：进入4状态.时间设置 
  case 15:setflag=0;LCD_CLEAR();IE1|=WDTIE;break;//键值15：返回1状态.主页面
  default :break;
  }
  return ;
  }
  else if(setflag==2)//3状态.主菜单（二）画面下的键值处理
  {
  key_value=infrared();//分析键值
  switch(key_value)
  {
  case 13:setflag=1;break;//键值13：返回2状态.主菜单（1）
  case 14:setflag=4;break;//键值14：进入5状态.闹钟设置 
  case 15:setflag=0;LCD_CLEAR();IE1|=WDTIE;break;//键值15：返回1状态.主页面
  default :break;
  }
  P2OUT&=~0x01;
  delay_ms(50);
  P2OUT|=0x01;
  delay_ms(50);
  return ;
  }
  else if(setflag==3)//4状态.时间设置画面下的键值处理
  {
  key_value=infrared();//分析键值
  switch(key_value)
  {
  case 13:setflag=1;timeset(table_time,table_dat);lastplay=0;move=0;break;
        /*********键值13：返回2状态.主菜单（1）,并将设置后的时间写入DS1302,
              清除lastplay,move标志*********/
  case 14:zxflag=0;move=0;break;//键值14：选择设置时间，指向标志清零
  case 15:setflag=1;lastplay=0;move=0;break;//键值15：不保存数据，直接返回2状态.主菜单（1）
  case 16:zxflag=1;move=0;break;//键值16：选择设置日期，指向标志置1
  }
  if(key_value<10)
  {
   if(zxflag==0&&move<5) {table_time[move]=key_value; move++;}//如果指向标志为0，把键值写入时间数组中
   else if(zxflag==1&&move<6){table_dat[move]=key_value;move++;} //如果指向标志为1，把键值写入日期数组中
  } 
  P2OUT&=~0x01;
  delay_ms(50);
  P2OUT|=0x01;
  delay_ms(50);
  return ;
  }
  /*
  else if(setflag==4)//5状态.闹钟设置设置画面下的键值处理
  {
  key_value=infrared();//分析键值
  switch(key_value)
  {
  case 12://键值12：按制闹钟的开启和关闭
          acflag^=0x01; break;//如果指向标志为0：控制闹钟1的开启和关闭
  case 13:break;//键值next：选择设置第一组闹钟，指向标志清零
  case 14://键值ok：保存退出
    setflag=1;//返回2状态.主菜单（1）
    lastplay=0;move=0;//清除lastplay,move标志
    achour=table_ac1[0]*10+table_ac1[1];//处理用户输入的数据
    acminute=table_ac1[2]*10+table_ac1[3];
    acmonth=table_ac2[0]*10+table_ac2[1];
    acday=table_ac2[2]*10+table_ac2[3];
    acmusic=table_ac2[4];
    _DINT();//关闭总中断
    write_segA();//将设置后的闹钟数据写入flash
    break;//保存退出
  
  case 15:setflag=1;lastplay=0;move=0;break;//键值back：退出不保存，直接返回2状态.主菜单（1）
  case 16:if(zxflag==0){zxflag=1;move=0;}
          else{zxflag=0;move=0;}break;//键值16：选择设置第二组闹钟，指向标志置1
  }
  if(key_value<10)
  {
   if(zxflag==0&&move<4) {table_ac1[move]=key_value; move++;}//如果指向标志为0，把键值写入闹钟数据数组1中
   else if(zxflag==1&&move<5){table_ac2[move]=key_value;move++;} //如果指向标志为1，把键值写入闹钟数据数组2中
  } 
  P2OUT&=~0x01;
  delay_ms(50);
  P2OUT|=0x01;
  delay_ms(50);
  return ;
  }
  */
  else if(setflag==4)//4状态.日程设置设置画面下的键值处理
  {
     key_value=infrared();//分析键值
     switch(key_value)
     {
     case 12://键值12：按制闹钟的开启和关闭（本系统用户可以设置两组闹钟）
              ac[ac_num][5]^=0x01; break;//如果指向标志为0：控制闹钟1的开启和关闭
     case 13:
             move=0;//清除lastplay,move标志
             ac[ac_num][0]=table_ac1[0]*10+table_ac1[1];//处理用户输入的数据
             ac[ac_num][1]=table_ac1[2]*10+table_ac1[3];
             ac[ac_num][2]=table_ac2[0]*10+table_ac2[1];
             ac[ac_num][3]=table_ac2[2]*10+table_ac2[3];
             ac[ac_num][4]=table_ac2[4];
             _DINT();//关闭总中断
             write_segA();//将设置后的日程数据写入flash
             ac_num++;
             show_read();
             break;//键值13(next)：进入下一个日程     LCD_CLEAR();IE1|=WDTIE;   
     case 14://键值14(ok)：保存退出
             setflag=1;//返回2状态.主菜单（1）
             lastplay=0;move=0;//清除lastplay,move标志
             ac[ac_num][3]=table_ac1[0]*10+table_ac1[1];//处理用户输入的数据
             ac[ac_num][4]=table_ac1[2]*10+table_ac1[3];
             ac[ac_num][1]=table_ac2[0]*10+table_ac2[1];
             ac[ac_num][2]=table_ac2[2]*10+table_ac2[3];
             ac[ac_num][6]=table_ac2[4];
             _DINT();//关闭总中断
             write_segA();//将设置后的日程数据写入flash
             break;//保存退出
     
     case 15:setflag=1;lastplay=0;move=0;break;//键值15：退出不保存，直接返回2状态.主菜单（1）
     case 16:if(zxflag) {zxflag=1;move=0;break;}
                 else {zxflag=0;move=0;break;}//键值16：选择设置第二行，指向标志置1
     }
     if(key_value<10)
    {
       if(zxflag==0&&move<4) {table_ac1[move]=key_value; move++;}//如果指向标志为0，把键值写入第一行数据数组中
       else if(zxflag==1&&move<5){table_ac2[move]=key_value;move++;} //如果指向标志为1，把键值写入第二行数据数组2中
    } 
  /*   P2OUT&=~0x01;
     delay_ms(50);
     P2OUT|=0x01;
     delay_ms(50);*/
     return ;
  }
}

