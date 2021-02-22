#include <16LF1518.h>
#fuses XT,NOWDT, MCLR,NOPROTECT, NOBROWNOUT,NODEBUG, LVP, NOVCAP,NOFCMEN,NOIESO 
#device ADC=10
//#use delay(internal=8MHz)
#use delay(internal=16MHz)
//#use delay(internal=1MHz)
#use FIXED_IO( C_outputs=PIN_C2 )
#define led   PIN_C2

#use rs232(DISABLE_INTS,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=ublox)
//#use rs232(baud=9600,parity=N,xmit=PIN_B1,rcv=PIN_B2,bits=8,stream=user,FORCE_SW)

