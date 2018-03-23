#define   DSDATIN    P5DIR &=~BIT3
#define   DSDATOUT   P5DIR |=BIT3
#define   DSDAT1   P5OUT|=BIT3
#define   DSDAT0   P5OUT &=~BIT3
#define   DS_Q     (P5IN & DSDAT)
#define   DSDAT     0x08

char DS_INIT(void);
void DS_write(unsigned char dat);
unsigned char DS_read(void);
