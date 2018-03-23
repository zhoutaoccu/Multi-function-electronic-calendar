
/*************������պ���***************/

unsigned char infrared(void)
{
    unsigned char k;
    unsigned char table_IR[32];//������Ž��յĺ����źű���
    //uchar ir=0;
    unsigned char j=0;
    unsigned char value;//��Ų�����
    unsigned char keydat=99;
    for(k=0;k<19;k++)
    { 
      delay_us(400);
      if(HW_Q){ return keydat;}  //����Ƿ���9ms�ĵ͵�ƽ�����򷵻����¼��
    }
    while(!HW_Q);//�ȴ�9ms�͵�ƽ��ȥ
    for(k=0;k<5;k++)
    {
      delay_us(500);
      if(!HW_Q){return keydat;}//�����2.5ms���е͵�ƽ������Ϊ�Ǹ��ţ������˳����¼��
    }
    while(HW_Q);//�ȴ�4.5ms�ߵ�ƽ��ȥ
    
    for(k=0;k<32;k++)
    {     
      while(!HW_Q);   //�ȴ�0.565ms�ĵ͵�ƽ��ȥ  
      while(HW_Q)    //����ߵ�ƽ�Ŀ�ȣ��жϽ��յ�Ϊ"0"����"1"
      {
        delay_us(100);
        j++;
        if(j>22){break;}    //����ߵ�ƽʱ�����������ѭ��������ִ������ĳ���   
      }
      if(j>=7)//����ߵ�ƽ�Ŀ�ȴ���0.7ms,����յ�Ϊ1,ͬʱ��������
      {
        table_IR[k]=1;
      }
      else  table_IR[k]=0;//����ߵ�ƽ���С��0.7ms������յ�Ϊ"0"��ͬʱ��������
      j=0;
    } 
    for(k=16;k<24;k++)//�ѵ�3���ֽڵ���λ����value_L�ڣ�������Һ������ʾ
    {
      value<<=1;
      if(table_IR[k])
      value|=0x01;
      
    }
    switch(value)
    {
    case 0x02:keydat=12;break;//���ܣ��������ӵĿ��أ���Ӧң�����ϵ���һ��
    case 0xa2:keydat=13;break;//���ܣ������˳�                   ��Ӧң�����ϵ�CH-
    case 0x62:keydat=14;break;//���ܣ������ƶ�      ��Ӧң�����ϵ�CH
    case 0xe2:keydat=15;break;//���ܣ�  ����                  ��Ӧң�����ϵ�CH+
    case 0xa8:keydat=16;break;//���ܣ������ƶ�        ��Ӧң�����ϵ�����+
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
    P6DIR|=BIT2;//�������˿���Ϊ���ģʽ
    BUZ_ON;
    delay_ms(50);   
    BUZ_OFF;
    P6DIR&=~BIT2;//�������˿���Ϊ����ģʽ
    return keydat;
}

/******************
�������ܣ�����м����£�����ϵͳ��ǰ״̬������Ӧ�ļ�ֵ����ģ�飬Ȼ����ݼ�ִֵ����Ӧ����
����˵�����������й�������״̬��1.��ҳ��ʱ����ʾ(setflag==0)
                                2.���˵���1��(setflag==1)
                                3.���˵���2��(setflag==2)
                                4.ʱ������ (setflag==3)
                                5.��������  (setflag==4) 
         ÿ���м�����ʱ���setflag��־�����ݼ�ִֵ����Ӧ����

*****************/
void keyvalue_const(void)
{
  if(setflag==0)//��ҳ��1״̬�µļ�ֵ����
  {   
  key_value=infrared();//������ֵ
  switch(key_value)
  {
  case 13: setflag=1;timeread(table_time,table_dat);break;//�����ֵΪ13������2״̬.���˵���1��
  default :break;//�����ֵΪ����ֵ��ֱ�ӷ��ء�
  }
  return ;
 
  }
  else if(setflag==1)//2״̬�����µļ�ֵ����
  {
  key_value=infrared();//������ֵ
  switch(key_value)
  {
  case 13:setflag=2;break;//��ֵ13������3״̬.���˵���2��
  case 14:setflag=3;break;//��ֵ14������4״̬.ʱ������ 
  case 15:setflag=0;LCD_CLEAR();IE1|=WDTIE;break;//��ֵ15������1״̬.��ҳ��
  default :break;
  }
  return ;
  }
  else if(setflag==2)//3״̬.���˵������������µļ�ֵ����
  {
  key_value=infrared();//������ֵ
  switch(key_value)
  {
  case 13:setflag=1;break;//��ֵ13������2״̬.���˵���1��
  case 14:setflag=4;break;//��ֵ14������5״̬.�������� 
  case 15:setflag=0;LCD_CLEAR();IE1|=WDTIE;break;//��ֵ15������1״̬.��ҳ��
  default :break;
  }
  P2OUT&=~0x01;
  delay_ms(50);
  P2OUT|=0x01;
  delay_ms(50);
  return ;
  }
  else if(setflag==3)//4״̬.ʱ�����û����µļ�ֵ����
  {
  key_value=infrared();//������ֵ
  switch(key_value)
  {
  case 13:setflag=1;timeset(table_time,table_dat);lastplay=0;move=0;break;
        /*********��ֵ13������2״̬.���˵���1��,�������ú��ʱ��д��DS1302,
              ���lastplay,move��־*********/
  case 14:zxflag=0;move=0;break;//��ֵ14��ѡ������ʱ�䣬ָ���־����
  case 15:setflag=1;lastplay=0;move=0;break;//��ֵ15�����������ݣ�ֱ�ӷ���2״̬.���˵���1��
  case 16:zxflag=1;move=0;break;//��ֵ16��ѡ���������ڣ�ָ���־��1
  }
  if(key_value<10)
  {
   if(zxflag==0&&move<5) {table_time[move]=key_value; move++;}//���ָ���־Ϊ0���Ѽ�ֵд��ʱ��������
   else if(zxflag==1&&move<6){table_dat[move]=key_value;move++;} //���ָ���־Ϊ1���Ѽ�ֵд������������
  } 
  P2OUT&=~0x01;
  delay_ms(50);
  P2OUT|=0x01;
  delay_ms(50);
  return ;
  }
  /*
  else if(setflag==4)//5״̬.�����������û����µļ�ֵ����
  {
  key_value=infrared();//������ֵ
  switch(key_value)
  {
  case 12://��ֵ12���������ӵĿ����͹ر�
          acflag^=0x01; break;//���ָ���־Ϊ0����������1�Ŀ����͹ر�
  case 13:break;//��ֵnext��ѡ�����õ�һ�����ӣ�ָ���־����
  case 14://��ֵok�������˳�
    setflag=1;//����2״̬.���˵���1��
    lastplay=0;move=0;//���lastplay,move��־
    achour=table_ac1[0]*10+table_ac1[1];//�����û����������
    acminute=table_ac1[2]*10+table_ac1[3];
    acmonth=table_ac2[0]*10+table_ac2[1];
    acday=table_ac2[2]*10+table_ac2[3];
    acmusic=table_ac2[4];
    _DINT();//�ر����ж�
    write_segA();//�����ú����������д��flash
    break;//�����˳�
  
  case 15:setflag=1;lastplay=0;move=0;break;//��ֵback���˳������棬ֱ�ӷ���2״̬.���˵���1��
  case 16:if(zxflag==0){zxflag=1;move=0;}
          else{zxflag=0;move=0;}break;//��ֵ16��ѡ�����õڶ������ӣ�ָ���־��1
  }
  if(key_value<10)
  {
   if(zxflag==0&&move<4) {table_ac1[move]=key_value; move++;}//���ָ���־Ϊ0���Ѽ�ֵд��������������1��
   else if(zxflag==1&&move<5){table_ac2[move]=key_value;move++;} //���ָ���־Ϊ1���Ѽ�ֵд��������������2��
  } 
  P2OUT&=~0x01;
  delay_ms(50);
  P2OUT|=0x01;
  delay_ms(50);
  return ;
  }
  */
  else if(setflag==4)//4״̬.�ճ��������û����µļ�ֵ����
  {
     key_value=infrared();//������ֵ
     switch(key_value)
     {
     case 12://��ֵ12���������ӵĿ����͹رգ���ϵͳ�û����������������ӣ�
              ac[ac_num][5]^=0x01; break;//���ָ���־Ϊ0����������1�Ŀ����͹ر�
     case 13:
             move=0;//���lastplay,move��־
             ac[ac_num][0]=table_ac1[0]*10+table_ac1[1];//�����û����������
             ac[ac_num][1]=table_ac1[2]*10+table_ac1[3];
             ac[ac_num][2]=table_ac2[0]*10+table_ac2[1];
             ac[ac_num][3]=table_ac2[2]*10+table_ac2[3];
             ac[ac_num][4]=table_ac2[4];
             _DINT();//�ر����ж�
             write_segA();//�����ú���ճ�����д��flash
             ac_num++;
             show_read();
             break;//��ֵ13(next)��������һ���ճ�     LCD_CLEAR();IE1|=WDTIE;   
     case 14://��ֵ14(ok)�������˳�
             setflag=1;//����2״̬.���˵���1��
             lastplay=0;move=0;//���lastplay,move��־
             ac[ac_num][3]=table_ac1[0]*10+table_ac1[1];//�����û����������
             ac[ac_num][4]=table_ac1[2]*10+table_ac1[3];
             ac[ac_num][1]=table_ac2[0]*10+table_ac2[1];
             ac[ac_num][2]=table_ac2[2]*10+table_ac2[3];
             ac[ac_num][6]=table_ac2[4];
             _DINT();//�ر����ж�
             write_segA();//�����ú���ճ�����д��flash
             break;//�����˳�
     
     case 15:setflag=1;lastplay=0;move=0;break;//��ֵ15���˳������棬ֱ�ӷ���2״̬.���˵���1��
     case 16:if(zxflag) {zxflag=1;move=0;break;}
                 else {zxflag=0;move=0;break;}//��ֵ16��ѡ�����õڶ��У�ָ���־��1
     }
     if(key_value<10)
    {
       if(zxflag==0&&move<4) {table_ac1[move]=key_value; move++;}//���ָ���־Ϊ0���Ѽ�ֵд���һ������������
       else if(zxflag==1&&move<5){table_ac2[move]=key_value;move++;} //���ָ���־Ϊ1���Ѽ�ֵд��ڶ�����������2��
    } 
  /*   P2OUT&=~0x01;
     delay_ms(50);
     P2OUT|=0x01;
     delay_ms(50);*/
     return ;
  }
}

