void write_segA(void)
{
  unsigned char i;
  unsigned char *segA;
  segA=(unsigned char *)0x1080;
  FCTL1=FWKEY+ERASE;
  FCTL3=FWKEY;//Çå³ýLOCKÎ»
  *segA=1;
  while(FCTL3&BUSY);
  FCTL1=FWKEY+WRT;
  
  for(i=0;i<6;i++)
  {
    *segA++=ac[ac_num][i];
    while(FCTL3&0x01);
  }
 // *segA++=acflag;
  //for(i=0;i<4;i++)
 // {
 // *segA++=table_ac2[i];
 // while(FCTL3&0x01);
//  }
 // *segA++=acflag2;
  FCTL1=FWKEY;
  FCTL3=FWKEY+LOCK;
  
}
void read_segA(void)
{
  unsigned char i,j;
  unsigned char *segA;
  segA=(unsigned char *)0x1080;
  FCTL3=FWKEY;
  for(i=0;i<ac_num;i++)
  {
    for(j=0;j<4;j++)
     {
      ac[i][j]=*segA++;
     }
     if(ac[ac_num][5]>1)ac[ac_num][5]=0;
  }
 // acflag2=*segA++;
  FCTL3=FWKEY+LOCK;
 
//  if(acflag2>1)acflag2=0;
}

