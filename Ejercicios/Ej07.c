/*Realizar un programa que configure el puerto P0.0 y P2.0 para que provoquen
una interrupción por flanco de subida. Si la interrupción es por P0.0 guardar el
valor binario 100111 en la variable "auxiliar", si es por P2.0 guardar el valor
binario 111001011010110*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

int auxiliar;

void confGPIO(){
  LPC_PINCON->PINSEL0 &= ~(0x3);  //P0.0 como GPIO
  LPC_GPIO0->FIODIR &= ~(0x1); //P0.0 como entrada
  LPC_PINCON->PINMODE0 |= (0x3); //P0.0 con pull-down
  LPC_PINCON->PINSEL4 &= ~(0x3);  //P2.0 como GPIO
  LPC_GPIO2->FIODIR &= ~(0x1); //P2.0 como entrada
  LPC_PINCON->PINMODE4 |= (0x3); //P2.0 con pull-down
}
void confInt(){
  LPC_GPIOINT->IO0IntEnR |= 0x1; //Interrupción por flanco de subida en P0.0
  LPC_GPIOINT->IO2IntEnR |= 0x1; //Interrupción por flanco de subida en P2.0
  NVIC_EnableIRQ(EINT3_IRQn); //Habilito la interrupción
}
void EINT3_IRQHandler(){
  if(LPC_GPIOINT->IO0IntStatR & 0x1){
    auxiliar = 0b100111;
    LPC_GPIOINT->IO0IntClr |= 0x1;
  } else {
    auxiliar = 0b111001011010110;
    LPC_GPIOINT->IO0IntClr |= 0x1;
  }
}

int main(){
  confGPIO();
  confInt();

  while(1);

  return 0;
}