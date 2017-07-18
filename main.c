#define F_CPU 11059200UL
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "tcn75.h"
#include "uart.h"
#include "waitDelay.h"
#include "printLed.h"
#include "printNumber.h"
#include "printNumberDot.h"

int main(void)
{
	float temp;
	uint8_t cfg;
	char *string;
	char *string2;
	bool flag;
	flag = 1;
	float lastDigit;


	string = malloc(80);

	/* Initializing LED 7segment*/
	DDRC=0xFF;
	  
	DDRF = (1<<PF3); //sw2
	PORTF = 0x08;

	DDRG = (1<<PG3); //sw3
	PORTG = 0x08;

	DDRG = (1<<PG4); //sw4
	PORTG = 0x10;

	DDRE = (1<<PE7); //sw5
	PORTE = 0x80;
	
	tcn75_init();
	uart_init(0);
	uart_printstrn(0, "\nPress SW5 to manual mode or SW3 automatic mode");

	while(1) {
	  
	  if (bit_is_clear(PING,PG4)){
	    flag = !flag;
	    _delay_ms(250);
	  }

	  if(bit_is_clear(PINE, PE7)) {
		uart_printstrn(0, "\nManual mode");

		cfg = 255;

		if (tcn75_read_config_reg(&cfg)) {
			uart_printstrn(0, " Error reading conf reg!");
		} else {
			uart_printstrn(0, " Config reg in hex ");
			string = itoa(cfg, string, 16);
			uart_printstrn(0, string);
		}

		temp = tcn75_read_temperature();

		if (temp == -99) {
			uart_printstrn(0, " Error reading temp!");
		} else {
			uart_printstrn(0, ". Temperature: ");
			string = dtostrf(temp, 3, 5, string);
			string2= strcat(string," °C");
			uart_printstrn(0, string2);
                        lastDigit=fmod(temp,10);

			if(flag==0){
			printLed(temp);
			}
			else {
			  if (temp >= 30){
                          printNumberDot(lastDigit);
			  }
			  else {
			  printNumber(lastDigit);
			  }
			}
		}
		_delay_ms(250);
	  }

	   if(bit_is_clear(PING, PG3)) {
	     uart_printstrn(0, "\nAutomatic mode starts press and mantain SW2 to stop ");

	     do {
		cfg = 255;

		if (bit_is_clear(PING,PG4)){
		  flag = !flag;
		  _delay_ms(250);
		}

		if (tcn75_read_config_reg(&cfg)) {
			uart_printstrn(0, "Error reading conf reg! ");
		} else {
			uart_printstrn(0, "\nConfig reg in hex ");
			string = itoa(cfg, string, 16);
			uart_printstrn(0, string);
		}

		temp = tcn75_read_temperature();

		if (temp == -99) {
			uart_printstrn(0, "Error reading temp! ");
		} else {
			uart_printstrn(0, ". Temperature: ");
			string = dtostrf(temp, 3, 5, string);
			string2= strcat(string," °C");
			uart_printstrn(0, string2);
                        lastDigit=fmod(temp,10);

			if(flag==0){
			printLed(temp);
			}
			else {
			  if (temp >= 30){
                          printNumberDot(lastDigit);
			  }
			  else {
			  printNumber(lastDigit);
			  }
			}

		}
		_delay_ms(250);
	     }while (!(bit_is_clear(PINF, PF3)));
	   }			 
	}

	free(string);
	return(0);
}
