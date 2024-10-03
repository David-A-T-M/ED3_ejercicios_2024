/*Configurar la interrupción externa EINT1 para que interrumpa por flanco de
bajada y la interrupción EINT2 para que interrumpa por flanco de subida. En la
interrupción por flanco de bajada configurar el systick para desbordar cada 25
mseg, mientras que en la interrupción por flanco de subida configurarlo para que
desborde cada 60 mseg. Considerar que EINT1 tiene mayor prioridad que EINT2.*/


#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

void confGPIO(){
  LPC_PINCON->PINSEL4 |= 0x2400000; //P2.11 y P2.12 como EINT1 y EINT2
  LPC_PINCON->PINMODE4 |= 0x3000000; //EINT2 con pull-down
}

void confInt(){
  LPC_SC->EXTMODE |= 0x6; //EINT1 y EINT2 por flanco
  LPC_SC->EXTPOLAR |= 0x4; //EINT1 por flanco de bajada y EINT2 por flanco de subida
  NVIC_EnableIRQ(EINT1_IRQn); //Habilito la interrupción
  NVIC_EnableIRQ(EINT2_IRQn); //Habilito la interrupción
}

void EINT1_IRQHandler(){
  if(SysTick_Config(2500000)){
    while(1);
  }
  LPC_SC->EXTINT |= 0x2; //Limpio la interrupción
}

void EINT2_IRQHandler(){
  if(SysTick_Config(6000000)){
    while(1);
  }
  LPC_SC->EXTINT |= 0x4; //Limpio la interrupción
}

void SysTick_Handler(){
  SysTick->CTRL &= SysTick->CTRL; //Limpio el flag
}

int main(){
  confGPIO();
  confInt();

  while(1);

  return 0;
}