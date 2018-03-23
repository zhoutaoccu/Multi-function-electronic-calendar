

 /*switch(month2)
    {
    case 1: {if(day2==1){
                      WRITE_LCD_char(6,0,photo_chun);
                      WRITE_LCD_char(7,0,photo_jie);};
             if(day2==15){
                      WRITE_LCD_char(6,0,photo_yuan);
                      WRITE_LCD_char(7,0,photo_xiao);};
             };
             break;
          
    case 5:{if(day2==5){
              WRITE_LCD_char(6,0,photo_duan);
              WRITE_LCD_char(7,0,photo_wuu);};
           };
           break;
           
    case 7: { if(day2==7){
              WRITE_LCD_char(6,0,photo_qi);
              WRITE_LCD_char(7,0,photo_xi);};
            };
            break;
           
    case 8: { if(day2==15){
              WRITE_LCD_char(6,0,photo_zhong);
              WRITE_LCD_char(7,0,photo_qiu);};
            };
               break;
    case 9: { if(day2==9){
              WRITE_LCD_char(6,0,photo_chong);
              WRITE_LCD_char(7,0,photo_yang);};
            } ;
               break;
    case 12: { if(day2==30){
              WRITE_LCD_char(6,0,photo_chu);
              WRITE_LCD_char(7,0,photo_xi);};
            } ;
               break;
    } ;*/
void judge_jieri(void)
{
   if(month==1 && day==1){ WRITE_LCD_char(6,0,photo_yuan);
                          WRITE_LCD_char(7,0,photo_dan1);};
    if(month==3 && day==21){ WRITE_LCD_char(6,0,photo_chun);
                            WRITE_LCD_char(7,0,photo_fen);};
    if(month==5 && day==1){ WRITE_LCD_char(6,0,photo_wu);
                          WRITE_LCD_char(7,0,photo_yi);};
    if(month==6 && day==1){ WRITE_LCD_char(6,0,photo_liu);
                          WRITE_LCD_char(7,0,photo_yi);};
    if(month==6 && day==21){ WRITE_LCD_char(6,0,photo_chun);
                          WRITE_LCD_char(7,0,photo_fen);};
    if(month==8 && day==1){ WRITE_LCD_char(6,0,photo_jian);
                          WRITE_LCD_char(7,0,photo_jun);};
    if(month==9 && day==10){ WRITE_LCD_char(6,0,photo_jiao);
                          WRITE_LCD_char(7,0,photo_shi);};
    if(month==9 && day==23){ WRITE_LCD_char(6,0,photo_xia);
                          WRITE_LCD_char(7,0,photo_zhi1);};
    if(month==10 && day==1){ WRITE_LCD_char(6,0,photo_guo);
                          WRITE_LCD_char(7,0,photo_qing1);};
   if(month==12 && day==22){ WRITE_LCD_char(6,0,photo_dong);
                          WRITE_LCD_char(7,0,photo_zhi);};
} 