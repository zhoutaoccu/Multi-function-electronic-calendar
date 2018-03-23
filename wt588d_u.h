

#define RST_0 P3OUT &=~BIT4
#define RST_1 P3OUT|=BIT4 /*P2.2ΪP3�ڵĵ�4λ*/ 
#define SDA_0 P3OUT&=~BIT0
#define SDA_1 P3OUT|=BIT0/*P2,4ΪP3�ڵĵ�5λ*/
#define CS_0 P3OUT &=~BIT1
#define CS_1 P3OUT|=BIT1/*P3_1ΪP3�ڵĵ�3λ*/ 
#define SCL_0 P3OUT &=~BIT2
#define SCL_1 P3OUT|=BIT2/*P3_2ΪP3�ڵĵ�4λ*/ 

void delay1ms(unsigned char count) 
{ 
     unsigned char i,j,k; 
      for(k=count;k>0;k--) 
        for(i=2;i>0;i--)  
          for(j=248;j>0;j--); 
} 

 
void delay100us(unsigned char count)  //100US��ʱ�ӳ��� 
{ 
     unsigned char j;
          for(j=count*50;j>0;j--);   
} 
 
 
void Send_threelines(unsigned char addr) //���߷����ӳ��� 
    { 
      unsigned char i;
      RST_0;
      delay1ms(5);
      RST_1;
      delay1ms(17);
      CS_0;  
      delay1ms(2); 
      for(i=0;i<8;i++)  
       {
         SCL_0;  
         if(addr & 1)SDA_1;  
         else SDA_0;  

         addr>>=1;  
         delay100us(3);  /* 300us */  
         SCL_1;  
         delay100us(3);   
         }  
        CS_1; 
     } 
 











