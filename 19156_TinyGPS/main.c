
#include <main.h>
#include <tinyGPS.h>

char C__;
boolean newData = false;
char buff[1000];
float flat, flon;
unsigned INT32 age;
char a[100] = "";

void decodeString()
{
   INT i=0;

   WHILE (a[i] != '\0')
   {
      putchar (a[i], UBLOX);
      newData = encode (a[i]);
      i++;
   }
}

/*
void main()
{
   setup_lcd (LCD_DISABLED) ;

   WHILE (TRUE)
   {
      putchar (getchar (UBLOX), UBLOX) ;
   }
}*/
/*
void main()
{
   setup_lcd (LCD_DISABLED) ;
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
   fprintf (UBLOX, "BOOT ! \r\n\r\n\r\n") ;
   
   WHILE (TRUE)
   {
      putchar ('+', UBLOX);
      for (INT n = 0; n < 200; n++){ 
      //buff[i] = getchar (UBLOX);  
      C__ = getchar (UBLOX);  
      buff[n] = C__;
      putchar(C__,UBLOX);
      }
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('*', UBLOX);
      delay_ms(100);
      putchar ('@', UBLOX);
      putchar ('\n', UBLOX);
      
      for (INT n = 0; n < 200; n++){       putchar(buff[n],UBLOX);      }
   }
}*/

void main()
{
   setup_lcd (LCD_DISABLED) ;
   //enable_interrupts (INT_RDA) ;
   //enable_interrupts (GLOBAL) ;
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
   fprintf (UBLOX, "BOOT ! \r\n\r\n\r\n") ;
   
   WHILE (TRUE)
   {
      delay_ms(60000);
      
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      putchar ('\n', UBLOX);
      //putchar ('+', UBLOX);
      for (int16 n = 0; n < 500; n++){ 
      //buff[i] = getchar (UBLOX);  
      C__ = getchar (UBLOX);  
      buff[n] = C__;
      putchar(C__,UBLOX);
      }
      //putchar ('*', UBLOX);
      delay_ms(10);
      putchar ('\n', UBLOX);
      putchar ('@', UBLOX);
      putchar ('\n', UBLOX);
      //for (INT i = 0; i < 100; i++){       putchar(buff[i],UBLOX);      }
      
      for (int16 n = 0; n < 500; n++)
      {
         //putchar(buff[n],UBLOX);
         newData = encode ( buff[n] );

         IF (newData)
         {
            //putchar ('1', UBLOX);
            INT sats = satellites ();
            //putchar ('2', UBLOX);
            UNSIGNED int32 hdop__ = hdop ();
            f_get_position (&flat,&flon,&age);
            //putchar ('3', UBLOX);
            IF (flat == GPS_INVALID_F_ANGLE) flat = 0.0;
            IF (flon == GPS_INVALID_F_ANGLE) flon = 0.0;
            IF (satellites () == GPS_INVALID_SATELLITES) sats = 0;
            //putchar ('4', UBLOX);
            IF (hdop () == GPS_INVALID_HDOP) hdop__ =  0;
            fprintf (UBLOX, "La: %.6f Lo: %.6f sat: %d hdop: %ld\r\n", flat, flon, sats, hdop__);
         }
      }
   }
}//*/

/*
void main()
{
   setup_lcd (LCD_DISABLED) ;
   //enable_interrupts (INT_RDA) ;
   //enable_interrupts (GLOBAL) ;
   fprintf (UBLOX, "BOOT ! \r\n\r\n\r\n") ;
   
   //WHILE (TRUE) { putchar (getchar (UBLOX), UBLOX);  }
   
   strcpy (a, "\n$GPRMC, 162740.00, A, 1205.07505, S, 07702.82978, W, 3.773, 246.40, 150221,,, A * 69\n\0"); decodeString ();
   //strcpy (a, "$GPGSV, 4, 1, 15, 01, 18, 225, 34, 03, 32, 290, 41, 04, 11, 339, 25, 08, 57, 198, 25 * 79\n\0"); decodeString ();
   strcpy (a, "$GPRMC,,V,,,,,,,,,,N*53\n\0"); decodeString ();
   strcpy (a, "$GPGGA, 162740.00, 1205.07505, S, 07702.82978, W, 1, 05, 4.87, 44.5, M, 9.0, M,, * 58\n\0"); decodeString ();
   
   //strcpy (a, "$GPGSV, 4, 1, 15, 01, 18, 225, 34, 03, 32, 290, 41, 04, 11, 339, 25, 08, 57, 198, 25 * 79\n\0"); decodeString ();
   //newData = true;

   IF (newData)
   {
      INT sats = satellites ();
      UNSIGNED int32 hdop__ = hdop ();
      f_get_position (&flat,&flon,&age);
      //IF (flat != GPS_INVALID_F_ANGLE) flat = 0.0;//, 6; /////////////////////////////////////////////////////////////////////////////////////
      //IF (flon != GPS_INVALID_F_ANGLE) flon = 0.0;//, 6; ////////////////////////////////////////////////////////////////////////////////////
      IF (satellites () == GPS_INVALID_SATELLITES) sats = 0;
      IF (hdop () == GPS_INVALID_HDOP) hdop__ =  0;
      fprintf (UBLOX, "La: %.6f Lo: %.6f sat: %d hdop: %ld\r\n\r\n\r\n", flat, flon, sats, hdop__);
   }

   WHILE (TRUE)
   {
      putchar ('*', UBLOX);
      //getchar (UBLOX) ;
      //getch (UBLOX) ;
      //getc (UBLOX) ;
      //putchar (' + ', UBLOX);
      //encode (getchar (UBLOX) );
      //putchar (' - ', UBLOX);
      IF (encode  (getchar (UBLOX) ) == true){putchar ('~', UBLOX); }
      ELSE{putchar ('!', UBLOX); }
      putchar ('@', UBLOX);

      //IF (kbhit (UBLOX))
      {
         IF (encode (getchar (UBLOX) ) )
         {
            putchar ('1', UBLOX);
            INT sats = satellites ();
            putchar ('2', UBLOX);
            UNSIGNED int32 hdop__ = hdop ();
            f_get_position (&flat,&flon,&age);
            putchar ('3', UBLOX);
            IF (flat != GPS_INVALID_F_ANGLE) flat = 0.0;
            IF (flon != GPS_INVALID_F_ANGLE) flon = 0.0;
            IF (satellites () == GPS_INVALID_SATELLITES) sats = 0;
            putchar ('4', UBLOX);
            IF (hdop () == GPS_INVALID_HDOP) hdop__ =  0;
            fprintf (UBLOX, "La: %.6f Lo: %.6f sat: %d hdop: %ld\r\n\r\n\r\n", flat, flon, sats, hdop__);
         }
      }
   }
}

//*/


