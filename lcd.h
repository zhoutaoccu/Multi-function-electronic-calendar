
#define    LCDRS0    P5OUT&=~BIT5
#define    LCDRS1    P5OUT|=BIT5
#define    LCDRW0    P5OUT&=~BIT6
#define    LCDRW1    P5OUT|=BIT6
#define    LCDEC0    P5OUT&=~BIT7
#define    LCDEC1    P5OUT|=BIT7
#define    LCDPSB0   P5OUT&=~BIT0 
#define    LCDPSB1   P5OUT|=BIT0
#define    LCDRST0   P5OUT&=~BIT1
#define    LCDRST1   P5OUT|=BIT1
#define    LCDDATIN  P4DIR=0x00
#define    LCDDATOUT P4DIR=0xff;
void LCD_INIT(void);//液晶初始化函数声明
void LCD_WRITE_str(unsigned char add,unsigned char *p);//显示字符串函数声明
unsigned char LCD_BUSY(void);//液晶忙检测函数声明
void WRITE_LCD_COM(unsigned char com);//液晶写指令函数声明
void WRITE_LCD_DATA(unsigned char dat);//液晶写数据函数声明
unsigned char READ_LCD_DATA(void);//液晶读数据函数声明
void LCD_CLEAR(void);//绘图模式下清屏函数声明
void WRITE_LCD_pho_up(const unsigned char *pho);//显示图片函数声明（上半屏）
void WRITE_LCD_pho_down(const unsigned char *pho);//显示图片函数声明（下半屏）
void WRITE_LCD_pho_up2(const unsigned char *pho);//显示自定义格式文字函数声明（上半屏）
void WRITE_LCD_pho_down2(const unsigned char *pho);//显示自定义格式文字函数声明（下半屏）
void WRITE_LCD_point(unsigned char x,unsigned char y);//任意位置打点函数声明
void WRITE_LCD_line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//任意两点间画线函数声明
void WRITE_LCD_pho3(unsigned char bit,unsigned char digit);//显示16*32的字符

