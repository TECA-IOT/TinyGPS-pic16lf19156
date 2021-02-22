#include <16LF19156.h>
#device ADC=12
#fuses NOCLKOUT, NOLCDPEN, MCLR, PUT_64MS, NOLPBOR, NOBROWNOUT, NOZCDDIS,STVREN, NODEBUG, NOWDT, LVP
//#use delay(internal=16000000)
#use delay(internal=1000000)



#pin_select U1TX = PIN_C6
#pin_select U1RX = PIN_C7

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=ublox)
#use rs232(DISABLE_INTS,baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=ublox)
