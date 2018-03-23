#include"ds18b20.h"

unsigned int GET_TEMP(void)
{
  unsigned char datbuff[9];//用来存放18B20  RAM中的9字节数据
  unsigned int temp,temp_low;//存放温度值
  unsigned char i;
  
  DS_INIT(); //初始化18B20
  DS_write(0xcc);  //跳过ROM指令
  DS_write(0xbe); //开始读取RAM数据(温度)
  for(i=0;i<9;i++)
  {
    datbuff[i]=DS_read();//读RAM中9字节数据，存入datbuff[]
  }
  //处理数据
  temp_low=datbuff[0];//读温度值低8位
  temp=datbuff[1];//读温度值高8位
  temp=temp<<8;
  temp|=temp_low;//合并温度值的高8位和低8位
  temp=(unsigned int)((float)(temp)*0.625);//根据公式计算温度
  DS_INIT(); //初始化18B20
  DS_write(0xcc);  //跳过ROM指令
  DS_write(0x44);//启动转换
  return temp;
}

/**********DS18B20初始化***********/
char DS_INIT(void)
{
  unsigned char i;
  DSDATOUT;
  DSDAT1;
  DSDAT0;
  delay_us(750);
  DSDAT1;
  DSDATIN;
  delay_us(80);
  if(DS_Q)i=1;
  delay_us(480);
  DSDATOUT;
  DSDAT1;
  return i;
}
/*********向DS18B20写一字节数据***********/
void DS_write(unsigned char dat)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
  DSDAT0;
  delay_us(15);
  if(dat & 0x01)DSDAT1;
  delay_us(45);
  DSDAT1;
  dat=dat>>1;
  delay_us(2);
  }
}
/**********从DS18B20中读一字节数据***********/
unsigned char DS_read(void)
{
  unsigned char i;
  unsigned char read_dat;
  for(i=0;i<8;i++)
  {
    read_dat=read_dat>>1;
  DSDATOUT;
  DSDAT1;
  delay_us(2);
  DSDAT0;
  delay_us(6);
  DSDAT1;
  delay_us(4);
  DSDATIN;
  if(DS_Q) read_dat |=0x80;
  DSDATOUT;
  delay_us(30);    
  }
  return read_dat;
}
