#define F_CPU 11059200UL
#include <avr/io.h>
#include <util/delay.h>




int main (void) {

   DDRC |= (1 << PC0);

   DDRF &= (1<<PF3); 
   PORTF |= 0x08;

   while(1) {

     if (PINF &  0x08){

       PORTC &= ~(1 << PC0);
     }
     else
       PORTC |= (1 << PC0);
   }

}
