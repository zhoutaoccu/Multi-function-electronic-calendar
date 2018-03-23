#include"lcd.h"
#include"photo.c"

/**************任意两点间画线函数**************/
void WRITE_LCD_line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
  int dx;
  int dy;
  unsigned char x;
  unsigned char y;
  int e;
  unsigned char temp;
  if(x1>x2)//交换坐标 保证x1始终是起点
  {
      temp=x1;x1=x2;x2=temp;
      temp=y1;y1=y2;y2=temp;
  }
  dx=x2-x1;//X轴的坐标增量
  dy=y2-y1;//Y轴的坐标增量
  x=x1;
  y=y1;
  if(dy==0)//斜率为0
  {
    while(x1<=x2)
    {WRITE_LCD_point(x1,y1);x1++;}
  }
  else if(dy>0)
  {
    if(dy<dx)
    {
      e=-dx;
      for(temp=0;temp<dx;temp++)
      {
        WRITE_LCD_point(x,y);
        x++;
        e=e+2*dy;
        if(e>0)
        {
          y++;
          e=e-2*dx;
        }
      }
    }
    if(dy>dx)
    {
      e=-dy;
      for(temp=0;temp<dy;temp++)
      {
       WRITE_LCD_point(x,y);
       y++;
       e=e+2*dx;
       if(e>0)
       {
        x++;
        e=e-2*dy;
       }
      }
    }
  }
  else if(dy<0)
  {
    dy=-dy;
    if(dy<dx)
    {
      e=-dx;
      for(temp=0;temp<dx;temp++)
      {
       WRITE_LCD_point(x,y);
       x++;
       e=e+2*dy;
       if(e>0)
       {
        y--;
        e=e-2*dx;
       }
      }
    }
    else
    {
      e=-dy;
      for(temp=0;temp<dy;temp++)
      {
        WRITE_LCD_point(x,y);
        y--;
        e=e+2*dx;
        if(e>0)
        {
         x++;
         e=e-2*dy;
        }
      }
    }
  }
}
/***********打点函数*************/
void WRITE_LCD_point(unsigned char x,unsigned char y)
{
  unsigned char x_byte,x_bit;
  unsigned char y_byte,y_bit;
  unsigned char temph,templ;
  x&=0x7f;
  y&=0x3f;
  x_byte=x/16;
  x_bit=x&0x0f;
  y_byte=y/32;
  y_bit=y%32;//参考资料上此处是y_bit=y&0x3f;不过经过测试下半屏的点无法显示
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x80+y_bit);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x80+x_byte+y_byte*8);
  while(LCD_BUSY());
  READ_LCD_DATA();
  while(LCD_BUSY());
  temph=READ_LCD_DATA();
  while(LCD_BUSY());
  templ=READ_LCD_DATA();
  while(LCD_BUSY());
  WRITE_LCD_COM(0x80+y_bit);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x80+x_byte+y_byte*8);
  while(LCD_BUSY());
  if(x_bit<8)
  {
    WRITE_LCD_DATA(temph|(0x01<<(7-x_bit)));
    while(LCD_BUSY());
    WRITE_LCD_DATA(templ);
    while(LCD_BUSY());   
  }
  else
  {
    WRITE_LCD_DATA(temph);
    while(LCD_BUSY());
    WRITE_LCD_DATA(templ|(0x01<<(15-x_bit)));
    while(LCD_BUSY());
    
  }
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x30);
  while(LCD_BUSY());

  
}
/**********显示软件提取的字模或图片（上半屏），一次写一行，写32次************/
void WRITE_LCD_pho_up(const unsigned char *pho)
{
  unsigned char i,j;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  for(i=0;i<32;i++)
  {
    
    WRITE_LCD_COM(0x80+i);
    while(LCD_BUSY());
    WRITE_LCD_COM(0x80);
    while(LCD_BUSY());
    for(j=0;j<8;j++)
    {
      WRITE_LCD_DATA(pho[i*16+j*2]);
      delay_us(50);
      WRITE_LCD_DATA(pho[i*16+j*2+1]);
      delay_us(50);
    }
  }

}
/**********显示软件提取的字模或图片（下半屏），一次写一行，写32次************/
void WRITE_LCD_pho_down(const unsigned char *pho)
{
  unsigned char i,j;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  for(i=0;i<32;i++)
  {    
    WRITE_LCD_COM(0x80+i);
    while(LCD_BUSY());
    WRITE_LCD_COM(0x88);
    while(LCD_BUSY());
    for(j=0;j<8;j++)
    {
      WRITE_LCD_DATA(pho[i*16+j*2]);
      delay_us(50);
      WRITE_LCD_DATA(pho[i*16+j*2+1]);
      delay_us(50);
    }
  } 

}
/***********显示字符串函数************/
void LCD_WRITE_str(unsigned char add,unsigned char *p)
{
  while(LCD_BUSY());
  WRITE_LCD_COM(add);
  while(LCD_BUSY());
  while(*p!='\0')
  {
    WRITE_LCD_DATA(*p++);
  }
  while(LCD_BUSY());
}
/*********液晶忙检测函数***********/
unsigned char LCD_BUSY(void)
{
  unsigned char busy;
  LCDDATIN;
  LCDRS0;
  LCDRW1;
  LCDEC1;
  busy=P4IN;
  delay_us(5);
  LCDEC0;
  LCDDATOUT;//////////
  return (busy&0x80);
}
/*************液晶初始化函数**************/
void LCD_INIT(void)
{
  LCDRST1;///////////////
  LCDPSB1;/////////////////
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x30);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x0C);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x01);
  while(LCD_BUSY());

}
/************液晶写指令函数*************/
void WRITE_LCD_COM(unsigned char com)
{
  LCDRS0;
  LCDRW0;
  LCDEC0;
  P4OUT=com;
  delay_us(5);
  LCDEC1; 
  delay_us(5);
  LCDEC0;
}
/************液晶写数据函数**************/
void WRITE_LCD_DATA(unsigned char dat)
{
  LCDRS1;
  LCDRW0;
  LCDEC0;
  P4OUT=dat;
  delay_us(5);
  LCDEC1;  
  delay_us(5);
  LCDEC0;
}
/************液晶读数据函数**************/
unsigned char READ_LCD_DATA(void)
{
  unsigned char data;
  LCDDATIN;
  LCDRS1;
  LCDRW1;
  LCDEC1;
  data=P4IN;
  delay_us(5);
  LCDEC0;  
  LCDDATOUT;
  return data;
}
/************绘图模式清屏函数***************/
void LCD_CLEAR(void)
{
  unsigned char i,j;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x30);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x01);
  while(LCD_BUSY());
 
  for(i=0;i<32;i++)
  {
    WRITE_LCD_COM(0x34);
    while(LCD_BUSY());
    WRITE_LCD_COM(0x80+i);
    while(LCD_BUSY());
    WRITE_LCD_COM(0x80);
    while(LCD_BUSY());
    for(j=0;j<8;j++)
    {
      WRITE_LCD_DATA(0x00);
      while(LCD_BUSY());
      WRITE_LCD_DATA(0x00);
      while(LCD_BUSY());    
    }
  }
  for(i=0;i<32;i++)
  {
    WRITE_LCD_COM(0x34);
    while(LCD_BUSY());
    WRITE_LCD_COM(0x80+i);
    while(LCD_BUSY());
    WRITE_LCD_COM(0x88);
    while(LCD_BUSY());
    for(j=0;j<8;j++)
    {
      WRITE_LCD_DATA(0x00);
      while(LCD_BUSY());
      WRITE_LCD_DATA(0x00);
      while(LCD_BUSY());     
    }
  }
    //WRITE_LCD_COM(0x30);
    //while(LCD_BUSY());
}
/**********显示软件提取的字模或图片（上半屏），从左到右一次写完32*32的点阵************/
void WRITE_LCD_pho_up2(const unsigned char *pho)
{
  unsigned char i,j;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  for(i=4;i<4;i++)
  {   
    for(j=0;j<32;j++)
    {
      WRITE_LCD_COM(0x80+j);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x80+i*2);
      while(LCD_BUSY());
      WRITE_LCD_DATA(pho[i*128+j*4]);
      delay_ms(5);
      WRITE_LCD_DATA(pho[i*128+j*4+1]);
      delay_ms(5);
      WRITE_LCD_COM(0x80+j);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x80+i*2+1);
      while(LCD_BUSY());
      WRITE_LCD_DATA(pho[i*128+j*4+2]);
      delay_ms(5);
      WRITE_LCD_DATA(pho[i*128+j*4+3]);
      delay_ms(5);
    }
  }

}
/**********显示软件提取的字模或图片（下半屏），从左到右一次写完32*32的点阵************/
void WRITE_LCD_pho_down2(const unsigned char *pho)
{
  unsigned char i,j;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY());
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  for(i=0;i<4;i++)
  {
    
    for(j=0;j<32;j++)
    {      
      WRITE_LCD_COM(0x80+j);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x88+i*2);
      while(LCD_BUSY());
      WRITE_LCD_DATA(pho[i*128+j*4]);
      delay_ms(5);
      WRITE_LCD_DATA(pho[i*128+j*4+1]);
      delay_ms(5);
      WRITE_LCD_COM(0x80+j);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x88+i*2+1);
      while(LCD_BUSY());
      WRITE_LCD_DATA(pho[i*128+j*4]);
      delay_ms(5);
      WRITE_LCD_DATA(pho[i*128+j*4+1]);
      delay_ms(5);
    }
  } 

}
/**********显示软件提取的字模，一次写16*32的点阵************/
void WRITE_LCD_pho3(unsigned char bit,unsigned char digit)
{
  unsigned char j;
  unsigned char x,y;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY()); 
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  for(j=0;j<32;j++)
  {
     if(j<16){ y=j+16; x=bit; }
     else { y=j-16;x=bit+8; }
      WRITE_LCD_COM(0x80+y);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x80+x);
      while(LCD_BUSY());
      WRITE_LCD_DATA(digit_photo[digit][j*2]);
      while(LCD_BUSY());
      WRITE_LCD_DATA(digit_photo[digit][j*2+1]);
      while(LCD_BUSY());
  }  
}
/**********显示软件提取的字模，************/
void WRITE_LCD_pho4(unsigned char bit,unsigned char *p)
{
  unsigned char j;
  unsigned char x,y;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY()); 
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  for(j=0;j<32;j++)
  {
     if(j<16){ y=j+16; x=bit; }
     else { y=j-16;x=bit+8; }
      WRITE_LCD_COM(0x80+y);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x80+x);
      while(LCD_BUSY());
      WRITE_LCD_DATA(p[j*2]);
      while(LCD_BUSY());
      WRITE_LCD_DATA(p[j*2+1]);
      while(LCD_BUSY());
  }
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
}
/**********显示软件提取的字模，从左到右一次写完16*16的点阵************/
void WRITE_LCD_char(unsigned char x,unsigned char y,unsigned char *chardat)
{
  unsigned char j;
  WRITE_LCD_COM(0x34);
  while(LCD_BUSY()); 
  WRITE_LCD_COM(0x36);
  while(LCD_BUSY());
  if(y>31){ y=y-32; x=x+8; }
  for(j=0;j<16;j++)
  {    
      WRITE_LCD_COM(0x80+y+j);
      while(LCD_BUSY());
      WRITE_LCD_COM(0x80+x);
      while(LCD_BUSY());
      WRITE_LCD_DATA(chardat[j*2]);
      while(LCD_BUSY());
      WRITE_LCD_DATA(chardat[j*2+1]);
      while(LCD_BUSY());
  }
}
