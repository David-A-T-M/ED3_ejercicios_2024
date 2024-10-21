/*Realizar un programa que configure el puerto P2.0 y P2.1 para que provoquen
una interrupción por flanco de subida para el primer pin y por flanco de bajada
para el segundo. Cuando la interrupción sea por P2.0 se enviará por el pin P0.0 la
secuencia de bits 010011010. Si la interrupción es por P2.1 se enviará por el pin
P0.1 la secuencia 011100110. Las secuencias se envían únicamente cuando se
produce una interrupción, en caso contrario la salida de los pines tienen valores 1
lógicos. ¿que prioridad tienen configuradas por defecto estas interrupciones?*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

void confGPIO(){
  LPC_PINCON->PINSEL4 &= ~(0xF);  //P2.0 y P2.1 como GPIO
  LPC_GPIO2->FIODIR &= ~(0x3); //P2.0 y P2.1 como entrada
  LPC_PINCON->PINMODE4 |= 0x3; //P2.0 con pull-down
  LPC_PINCON->PINMODE4 &= ~(0xC); //P2.1 con pull-up
  LPC_PINCON->PINSEL0 &= ~(0xF); //P0.0 y P0.1 como GPIO
  LPC_GPIO0->FIODIR |= 0x3; //P0.0 y P0.1 como salida
}

void confInt(){
  LPC_GPIOINT->IO2IntEnR |= 0x1; //Interrupción por flanco de subida en P2.0
  LPC_GPIOINT->IO2IntEnF |= 0x2; //Interrupción por flanco de bajada en P2.1
  NVIC_EnableIRQ(EINT3_IRQn); //Habilito la interrupción
}

void sec1(){
  int sec = 0x6A; //010011010
  for(int i=0; i<9; i++){
    int bit = (sec >>i) & 0x1;
    if(bit){
      LPC_GPIO0->FIOSET = 1;
    }else
      LPC_GPIO0->FIOCLR = 1;
    for(int j=0; j<1000000; j++);
  }
  LPC_GPIO0->FIOSET = 1;
}

void sec2(){
  int sec = 0x73; //011100110
  for(int i=0; i<9; i++){
    int bit = (sec >>i) & 0x1;
    if(bit){
      LPC_GPIO0->FIOSET = 2;
    }else
      LPC_GPIO0->FIOCLR = 2;
    for(int j=0; j<1000000; j++);
  }
  LPC_GPIO0->FIOSET = 2;
}

void EINT3_IRQHandler(){
  if(LPC_GPIOINT->IO2IntStatR & 0x1){
    sec1();
    LPC_GPIOINT->IO2IntClr |= 0x1;
  }
  if(LPC_GPIOINT->IO2IntStatF & 0x2){
    sec2();
    LPC_GPIOINT->IO2IntClr |= 0x2;
  }
}

int main(){
  confGPIO();
  confInt();
  while(1);

  return 0;
}