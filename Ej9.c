/*Escribir un programa en C que permita sacar por los pines P1.16 al P1.23 el
equivalente en ascii de "a" si la interrupción se ha realizado por interrupción de
EINT1 y no hay interrupción pendiente de EINT0. Para el caso en el cual se
produzca una interrupción por EINT1 y exista una interrupción pendiente de
EINT0 sacar por el puerto el equivalente en ascii de "A". La interrupción de
EINT1 es por el flanco de subida producido por un pulsador identificado como
"tecla a/A", mientras que la interrupción EINT0 es por el nivel alto de un
pulsador etiquetado como "Activación de Mayusculas".
Nota: Valerse de la configuración de los niveles de prioridad para que la
pulsación conjunta de "Activación de Mayúsculas" con "tecla a/A" de como
resultado a la salida el equivalente en ascii "A".*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

int flag = 1;

void confGPIO(){
  LPC_PINCON->PINSEL4 |= 0x500000; //P2.10 y P2.11 como EINT0 y EINT1
  LPC_PINCON->PINMODE4 |= 0xF00000; //EINT0 y EINT1 con pull-down
  LPC_PINCON->PINSEL3 &= ~(0xFF); //P1.16 al P1.23 como GPIO
}

void confInt(){
  LPC_SC->EXTMODE |= 0x2; //EINT1 por flanco
  LPC_SC->EXTPOLAR |= 0x2; //EINT1 por flanco de subida
  NVIC_EnableIRQ(EINT1_IRQn); //Habilito la interrupción
  NVIC_SetPriority(EINT1_IRQn, 0); //Prioridad 0
  LPC_SC->EXTPOLAR |= 0x1; //EINT0 por nivel alto
  NVIC_EnableIRQ(EINT0_IRQn); //Habilito la interrupción
  NVIC_SetPriority(EINT0_IRQn, 1); //Prioridad 1
}

void EINT1_IRQHandler(){
  if(LPC_SC->EXTINT & 0x1){    //
    LPC_GPIO1->FIOCLR = 0xFF0000;
    LPC_GPIO1->FIOSET = 0x610000;
  }else{
    LPC_GPIO1->FIOCLR = 0xFF0000;
    LPC_GPIO1->FIOSET = 0x410000;
  }
  flag = 0;
  LPC_SC->EXTINT |= 0x2; //Limpio la interrupción
}

void EINT0_IRQHandler(){
  while(flag);
  flag = 1;
  LPC_SC->EXTINT |= 0x1; //Limpio la interrupción
}

int main(){
  confGPIO();
  confInt();

  while(1);

  return 0;
}