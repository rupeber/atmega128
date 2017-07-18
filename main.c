#define F_CPU 11059200UL
#include <avr/io.h>
#include <util/delay.h>
#include "printNumber.h"


int main (void) {

  //Setup
   DDRC = 0xFF;


   DDRF = (1<<PF3); //sw2
   PORTF = 0x08;

   DDRG = (1<<PG3); //sw3
   PORTG = 0x08;

   DDRG = (1<<PG4); //sw4
   PORTG = 0x10;

   DDRE = (1<<PE7); //sw5
   PORTE = 0x80;

   int num=0;

   //Loop  
   while(1) {


      if (bit_is_clear(PINE,PE7)){

	if (num==9){
	  num=0;
	}
	
	else {
	  num++;
	}
	printNumber(num);


      }
      if(bit_is_clear(PING,PG3)){
	if (num==0){
	  num=9;
	}
	else { 
	  num--;
	}
	printNumber(num);

      }

      if (bit_is_clear(PINF,PF3)){
	num=0;
	printNumber(num);
      }
      
      
   }
     
}
