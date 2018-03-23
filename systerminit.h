#define CPU_F ((double)8000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
/*************������ն˿ڶ���**************/

#define   HW_I     P1DIR &=~BIT3
#define   HW_O     P1DIR |= BIT3
#define   HW_L     P1OUT &=~BIT3
#define   HW_H     P1OUT |= BIT3
#define   HW_Q     (P1IN & BIT3)


#define   BUZ_OFF  P6OUT|=BIT2
#define   BUZ_ON   P6OUT&=~BIT2


unsigned char temp;
unsigned char second,minute,hour,day,month,year,week;
unsigned char achour,acminute,acmonth,acday,acmusic;
unsigned char flag=0;
unsigned int temperature;
unsigned char setflag=0;//״̬��־��ͨ���ı�˱�־���벻ͬ�Ĺ��ܻ���
unsigned char key_value;//��ż�ֵ

unsigned char week_table[8][4]={{"SUN"},{"MON"},{"TUE"},{"WED"},{"THU"},{"FRI"},{"SAT"},{"SUN"}};
unsigned char accontrol[2][4]={{"OFF"},{" ON"}};
unsigned char table_lcd[]={48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70};//Һ����ʾ���ֶ�ӦASIIC

unsigned char *dat2={"Tem"};
unsigned char set_table_1[]={"next   ok   back "};
unsigned char set_table_2[]={"ok          back "};
unsigned char set_table_3[]={" DAT:   /   M:"};//gai
unsigned char set_table_4[]={"    ʱ������ "};
unsigned char set_table_5[]={" TIME:  :       "};
unsigned char set_table_6[]={" DAT:   /   /   "};
unsigned char set_table_7[]={"       :"};



/*ʱ�������µı���*/
unsigned char table_time[5]={0,0,0,0,0};
unsigned char table_dat[6]={0,0,0,0,0,0};
unsigned char table_ac1[4]={0,0,0,0};
unsigned char table_ac2[6]={0,0,0,0,0,0};
unsigned char move=0;//�����û����������ʱ����ָ���������һλ
unsigned char zxflag=0;//������ҳ������Ļ������ʾ�������ݣ��˱�־���������޸���һ��
                     //0��ѡ���޸ĵ�һ������    1��ѡ���޸ĵڶ�������
unsigned char lastplay=0;//���������Ƿ���ʾ����Ԫ�أ�һ���л�һ��ҳ�棬ֻ��Ҫ��һ�ΰ�
                     //һЩ����Ԫ����ʾһ�Σ��´ν���ֻ��Ҫˢ������

unsigned char keydownflag=0;//�м����±�־ 0���޼����£�1���м�����

unsigned char ac_num;//�ճ̹ر�־    0���ر� ��1������
unsigned char ac[30][6]={{0,0},{0,0}};

