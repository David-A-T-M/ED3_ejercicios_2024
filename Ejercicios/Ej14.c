/*Utilizando el Timer 1, escribir un código en C para que por cada presión de un pulsador, la frecuencia de parpadeo
de un led disminuya a la mitad debido a la modificación del reloj que llega al periférico. El pulsador debe producir una
interrupción por GPIO0 con flanco descendente.*/

#include "C:\Users\David\Desktop/Facu/ED 3/CMSISv2p00_LPC17xx/inc/LPC17xx.h"

void confPIN();
void confInt();
void confTimer();

int main(){
  confPIN();
  confInt();
  confTimer();

  while(1);

  return 0;
}

void confPIN() {
  PINSEL_CFG_Type pin_cfg;
  pin_cfg.Portnum = PINSEL_PORT_1;
  pin_cfg.Pinnum = PINSEL_PIN_22;
  pin_cfg.Funcnum = PINSEL_FUNC_3;
  PINSEL_ConfigPin(&pin_cfg);   // Se configura como MAT1.0 para el led
  pin_cfg.Portnum = PINSEL_PORT_0;
  pin_cfg.Pinnum = PINSEL_PIN_0;
  pin_cfg.Funcnum = PINSEL_FUNC_0;
  pin_cfg.Pinmode = PINSEL_PINMODE_PULLDOWN;
  PINSEL_ConfigPin(&pin_cfg);   // Se configura como P0.0 (in) para el pulsador, con PD.
}

void confInt() {
  GPIO_IntCmd(0, 1, 1);   // Habilito interrupción de P0.0 por flanco de bajada
  GPIO_ClearInt(0, 1);    // Limpio interrupción de P0.0
  NVIC_EnableIRQ(EINT3_IRQn);  // Habilito la interrupción en el NVIC
}
void confTimer() {
  TIM_TIMERCFG_Type timer_cfg;
  timer_cfg.PrescaleOption = TIM_PRESCALE_USVAL;
  timer_cfg.PrescaleValue = 1000000;  // timer con TC cada segundo
  TIM_Init(LPC_TIM1, TIM_TIMER_MODE , &timer_cfg);  // Inicializo el timer
  TIM_MATCHCFG_Type match_cfg;
  match_cfg.MatchChannel = 0;
  match_cfg.IntOnMatch = DISABLE;
  match_cfg.StopOnMatch = DISABLE;
  match_cfg.ResetOnMatch = ENABLE;
  match_cfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
  match_cfg.MatchValue = 10;
  TIM_ConfigMatch(LPC_TIM1, &match_cfg);  // Configuro el match
}

void EINT3_IRQHandler() {
  static uint8_t clk_sel[4]={0x03, 0x01, 0x02, 0x00};
  static uint8_t i=0;
  LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & 0xFFFFFFCF) | (clk_sel[i % 4] << 4); // Modifica secuencialmente el clock del timer
  i++;
  EXTI_ClearEXTIFlag(EXTI_EINT3);
}