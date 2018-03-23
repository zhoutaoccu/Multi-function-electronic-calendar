
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
void LCD_INIT(void);//Һ����ʼ����������
void LCD_WRITE_str(unsigned char add,unsigned char *p);//��ʾ�ַ�����������
unsigned char LCD_BUSY(void);//Һ��æ��⺯������
void WRITE_LCD_COM(unsigned char com);//Һ��дָ�������
void WRITE_LCD_DATA(unsigned char dat);//Һ��д���ݺ�������
unsigned char READ_LCD_DATA(void);//Һ�������ݺ�������
void LCD_CLEAR(void);//��ͼģʽ��������������
void WRITE_LCD_pho_up(const unsigned char *pho);//��ʾͼƬ�����������ϰ�����
void WRITE_LCD_pho_down(const unsigned char *pho);//��ʾͼƬ�����������°�����
void WRITE_LCD_pho_up2(const unsigned char *pho);//��ʾ�Զ����ʽ���ֺ����������ϰ�����
void WRITE_LCD_pho_down2(const unsigned char *pho);//��ʾ�Զ����ʽ���ֺ����������°�����
void WRITE_LCD_point(unsigned char x,unsigned char y);//����λ�ô�㺯������
void WRITE_LCD_line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);//��������仭�ߺ�������
void WRITE_LCD_pho3(unsigned char bit,unsigned char digit);//��ʾ16*32���ַ�

