#define CPU_F ((double)8000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
/*************红外接收端口定义**************/

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
unsigned char setflag=0;//状态标志，通过改变此标志进入不同的功能画面
unsigned char key_value;//存放键值

unsigned char week_table[8][4]={{"SUN"},{"MON"},{"TUE"},{"WED"},{"THU"},{"FRI"},{"SAT"},{"SUN"}};
unsigned char accontrol[2][4]={{"OFF"},{" ON"}};
unsigned char table_lcd[]={48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70};//液晶显示数字对应ASIIC

unsigned char *dat2={"Tem"};
unsigned char set_table_1[]={"next   ok   back "};
unsigned char set_table_2[]={"ok          back "};
unsigned char set_table_3[]={" DAT:   /   M:"};//gai
unsigned char set_table_4[]={"    时间设置 "};
unsigned char set_table_5[]={" TIME:  :       "};
unsigned char set_table_6[]={" DAT:   /   /   "};
unsigned char set_table_7[]={"       :"};



/*时间设置下的变量*/
unsigned char table_time[5]={0,0,0,0,0};
unsigned char table_dat[6]={0,0,0,0,0,0};
unsigned char table_ac1[4]={0,0,0,0};
unsigned char table_ac2[6]={0,0,0,0,0,0};
unsigned char move=0;//接收用户输入的数据时用来指向数码的下一位
unsigned char zxflag=0;//在设置页面下屏幕可以显示两行数据，此标志用来控制修改哪一行
                     //0：选择修改第一行数据    1：选择修改第二行数据
unsigned char lastplay=0;//用来控制是否显示基本元素，一般切换一个页面，只需要第一次把
                     //一些基本元素显示一次，下次进入只需要刷新数据

unsigned char keydownflag=0;//有键按下标志 0：无键按下，1：有键按下

unsigned char ac_num;//日程关标志    0：关闭 ，1：开启
unsigned char ac[30][6]={{0,0},{0,0}};

