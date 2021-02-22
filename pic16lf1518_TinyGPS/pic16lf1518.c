#include <pic16lf1518.h>
#include <tinyGPS.h>

char C__;
boolean newData = false;
float flat, flon;
unsigned INT32 age;
char buff[300];
int index=0;
/*
//#INT_RDA
void  RDA_isr(void) 
{
   //putchar(getchar(UBLOX),UBLOX );
   //return;
   //newData = encode(C_);
   //newData = encode(  getchar(UBLOX)  );
   //if(newData) disable_interrupts(INT_RDA);
   while( kbhit(UBLOX) ){//////////////////////////////////
   //newData = encode(  getchar(UBLOX)  );
   //if(newData) disable_interrupts(INT_RDA);
   C__ = getchar(UBLOX);
   switch(C__){
   case '\r':
      //buff[index] = C__;
      buff[index+1]='\0';
      disable_interrupts(INT_RDA);
      newData = true;
      break;
   case '$':
      index=0;
   }
      buff[index] = C__;
      index++;

   
   
   }
   
   //getchar(UBLOX);
   //output_toggle(pin_c2);
} */

void decodeString()
{

  fprintf(UBLOX,buff);
  putchar('\n',UBLOX);
  for(int i=0 ; buff[i] != '\0' ; i++){
  putchar(buff[i], UBLOX);
    //newData = encode( buff[i] );
    //if(new)
    if( encode( buff[i] ) ){
         float flat, flon;
         unsigned int32 age;
         int sats = satellites();
         unsigned int32 hdop__ = hdop();
         f_get_position(&flat, &flon, &age);    
         if(flat == GPS_INVALID_F_ANGLE )  flat = 0.0;
         if(flon == GPS_INVALID_F_ANGLE )  flon = 0.0;
         if(satellites() == GPS_INVALID_SATELLITES ) sats=0;
         if(hdop() == GPS_INVALID_HDOP) hdop__= 0;
         fprintf(UBLOX,"La: %.6f Lo: %.6f sat: %d hdop: %ld\r\n\r\n\r\n",flat,flon,sats,hdop__);
         }
    }
}


void main()
{
   //enable_interrupts (INT_RDA) ;
   //enable_interrupts (GLOBAL) ;
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
   fprintf (UBLOX, "BOOT ! \r\n\r\n\r\n") ;
   
   WHILE (TRUE)
   {
      
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);      
      for (int16 n = 0; n < 300; n++){ 
      //buff[i] = getchar (UBLOX);  
      C__ = getchar (UBLOX);  
      buff[n] = C__;
      putchar(C__,UBLOX);
      }
      delay_ms(10);
      putchar ('\n', UBLOX);
      putchar ('@', UBLOX);
      putchar ('\n', UBLOX);
      //for (INT i = 0; i < 100; i++){       putchar(buff[i],UBLOX);      }
      
      for (int16 n = 0; n < 300; n++)
      {
         newData = encode ( buff[n] );

         IF (newData)
         {
            INT sats = satellites ();
            UNSIGNED int32 hdop__ = hdop ();
            f_get_position (&flat,&flon,&age);
            IF (flat == GPS_INVALID_F_ANGLE) flat = 0.0;
            IF (flon == GPS_INVALID_F_ANGLE) flon = 0.0;
            IF (satellites () == GPS_INVALID_SATELLITES) sats = 0;
            IF (hdop () == GPS_INVALID_HDOP) hdop__ =  0;
            fprintf (UBLOX, "La: %.6f Lo: %.6f sat: %d hdop: %ld\r\n", flat, flon, sats, hdop__);
         }
      }
   delay_ms(60000);
   }
}

