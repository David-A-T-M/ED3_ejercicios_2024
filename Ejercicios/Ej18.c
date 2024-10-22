/*Utilizando los 4 registros match del Timer 0 y las salidas P0.0, P0.1, P0.2 y P0.3,
realizar un programa en C que permita obtener las formas de ondas adjuntas, donde los
pulsos en alto tienen una duración de 5 mseg. Un pulsador conectado a la entrada EINT3,
permitirá elegir entre las dos secuencias mediante una rutina de servicio a la interrupción.
La prioridad de la interrupción del Timer tiene que ser mayor que la del pulsador.*/

#include <stdint.h>

void confPin();     // Configurar los 4 pines de salida y el pulsador
void confTimer0();  //Configurar timer0 y con 4 match y TC 2,5ms
void confEint3();     //Configurar interrupción del pulsador

uint8_t secA[8] = {1, 1, 2, 2, 4, 4, 8, 8};   // Asumiendo salida A en P0.0, B en P0.1, A' en P0.2 y B' en P0.3
uint8_t secB[4] = {9, 3, 6, 12};
uint8_t i = 0;
uint8_t flag = 0;

int main(){
    confPin();
    confTimer0();
    confEint3();
    while(1);
}

void confPin() {
    PINSEL_CFG_Type cnfPin;
    cnfPin.Portnum = 1;
    cnfPin.Pinnum = 13;
    cnfPin.Funcnum = 1;
    cnfPin.Pinmode = PINSEL_PINMODE_PULLDOWN;
    cnfPin.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&cnfPin);  // Configurar P1.13 como EINT3 para el pulsador
    GPIO_SetDir(0, 0xf, 1);     // Configurar P0.0, P0.1, P0.2 y P0.3 como salidas
}

void confTimer0() {
    TIM_TIMERCFG_Type confTim;
    confTim.TIM_PRESCALE_USVAL = TIM_PRESCALE_USVAL;
    confTim.PrescaleValue = 2500;   // TC cada 2,5ms
    TIM_Init(LPC_TIM0, TimerCounterMode, TIM_ConfigStruct);
    TIM_MATCHCFG_Type confMat;
    confMat.MatchChannel = 0;
    confMat.IntOnMatch = ENABLE;
    confMat.StopOnMatch = DISABLE;
    confMat.ResetOnMatch = ENABLE;
    confMat.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
    confMat.MatchValue = 1;
    TIM_ConfigMatch(LPC_TIM0, &confMat);    // configuro match 0 para que interrumpa cada 5ms y reinicia
    NVIC_SetPriority(EINTx_IRQn, 1);
    NVIC_EnableIRQ(TIMER0_IRQn);
}
void confEint3() {
    EXTI_InitTypeDef confEint;
    confEint.EXTI_Line = EXTI_EINT3;
    confEint.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
    confEint.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE;
    EXTI_Init();
    EXTI_Config(&confEint);
    NVIC_SetPriority(EINTx_IRQn, 2);
    NVIC_EnableIRQ(EINTx_IRQn);
}
TIMER0_IRQHandler() {
    if (flag) {
        LPC_GPIO0->FIOPIN = (LPC_GPIO0->FIOPIN & 0xf) | secA[i % 8];
    } else {
        LPC_GPIO0->FIOPIN = (LPC_GPIO0->FIOPIN & 0xf) | secB[i % 4];
    }
    i++;
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
EINT3_IRQHandler() {
    flag = !flag;
    EXTI_ClearEXTIFlag(EXTI_EINT3);
}