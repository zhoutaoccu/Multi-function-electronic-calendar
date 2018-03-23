#include"ds18b20.h"

unsigned int GET_TEMP(void)
{
  unsigned char datbuff[9];//�������18B20  RAM�е�9�ֽ�����
  unsigned int temp,temp_low;//����¶�ֵ
  unsigned char i;
  
  DS_INIT(); //��ʼ��18B20
  DS_write(0xcc);  //����ROMָ��
  DS_write(0xbe); //��ʼ��ȡRAM����(�¶�)
  for(i=0;i<9;i++)
  {
    datbuff[i]=DS_read();//��RAM��9�ֽ����ݣ�����datbuff[]
  }
  //��������
  temp_low=datbuff[0];//���¶�ֵ��8λ
  temp=datbuff[1];//���¶�ֵ��8λ
  temp=temp<<8;
  temp|=temp_low;//�ϲ��¶�ֵ�ĸ�8λ�͵�8λ
  temp=(unsigned int)((float)(temp)*0.625);//���ݹ�ʽ�����¶�
  DS_INIT(); //��ʼ��18B20
  DS_write(0xcc);  //����ROMָ��
  DS_write(0x44);//����ת��
  return temp;
}

/**********DS18B20��ʼ��***********/
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
/*********��DS18B20дһ�ֽ�����***********/
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
/**********��DS18B20�ж�һ�ֽ�����***********/
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
