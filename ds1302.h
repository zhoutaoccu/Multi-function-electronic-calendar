

#define  DS_SCLK_H   P6OUT|=BIT5
#define  DS_IO_H     P6OUT|=BIT6
#define  DS_RST_H    P6OUT|=BIT7
#define  DS_SCLK_L   P6OUT&=~BIT5
#define  DS_IO_L     P6OUT&=~BIT6
#define  DS_RST_L    P6OUT&=~BIT7
#define  DS_SCLK_O   P6DIR|=BIT5
#define  DS_IO_O     P6DIR|=BIT6
#define  DS_RST_O    P6DIR|=BIT7
#define  DS_SCLK_I   P6DIR&=~BIT5
#define  DS_IO_I     P6DIR&=~BIT6
#define  DS_RST_I    P6DIR&=~BIT7
#define  DS_IO_Q     P6IN & 0x40

#define  WRITE_SECOND    0X80
#define  READ_SECOND     0x81
#define  WRITE_MINUTE    0x82
#define  READ_MINUTE     0x83
#define  WRITE_HOUR      0x84
#define  READ_HOUR       0x85
#define  WRITE_DAY       0x86
#define  READ_DAY        0x87
#define  WRITE_MONTH     0x88
#define  READ_MONTH      0x89
#define  WRITE_YEAR      0x8c
#define  READ_YEAR       0x8d
#define  WRITE_WEEK      0x8a
#define  READ_WEEK       0x8b
#define  WRITE_PROTECT   0x8e
#define  READ_PROTECT    0x8f


void WRITE_DS1302(unsigned char add,unsigned char dat);
unsigned char READ_DS1302(unsigned char add);
void DS1302_INIT(void);
void GET_TIME(void);

unsigned char sj=0x00;