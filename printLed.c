#define F_CPU 11059200UL
#include <avr/io.h>
#include <util/delay.h>
#include "waitDelay.h"
#include "printLed.h"


#define zero 0b11111111
#define one 0b11111101
#define two 0b11110101
#define three 0b11010101
#define four 0b10010101
#define five 0b10000101
#define six 0b10000001
#define seven 0b10000000
#define error 0b01111111


void printLed(float number){

   DDRC = 0xFF;

  if(number<=5){
    PORTC = (zero); waitDelay();
  
  } else if(number>5 & number <=10) {
PORTC = (one);  waitDelay();
  
}else if(number>10 & number <=15){
PORTC = (two); waitDelay();

 }else if(number>15 & number <=20){
PORTC = (three);  waitDelay();

 }else if(number>20 & number <=25){
PORTC = (four);  waitDelay();

 }else if(number>25 & number <=30){
PORTC = (five);  waitDelay();

 }else if(number>30 & number <=35){
PORTC = (six);  waitDelay();

 }else if(number>35){
PORTC = (seven); waitDelay();
  
}else {
    PORTC = (error);  waitDelay();
  }

}
