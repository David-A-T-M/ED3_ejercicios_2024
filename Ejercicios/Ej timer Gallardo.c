// Generar con timer0 una señal de freq. variable
// Usando el capture “medir” el periodo usando otro timer
// Prender leds tipo vúmetro según la frecuencia
// Con un pulsador cambiar la frecuencia de pasos de 100khz. Actualizar el vúmetro

#include "../../../Desktop/Facu/ED 3/CMSISv2p00_LPC17xx/inc/LPC17xx.h"

uint8_t ticks[5] = {499, 249, 166, 124, 99}; // 100kHz, 200kHz, 300kHz, 400kHz, 500kHz

void confPIN(); // pin para el pulsador y los leds
void confInt(); // Interrupción para el pulsador por flanco descendente
void confTimer0();  // Usar un match para generar una señal
void confTimer1();  // Usar un capture para medir el periodo


int main() {
    confPIN();
    confInt();
    confTimer0();
    confTimer1();

    while (1);
}

void confPIN() {
    PINSEL_CFG_Type pinCfg;
    pinCfg.Portnum = PINSEL_PORT_0;
    pinCfg.Pinnum = PINSEL_PIN_0;
    pinCfg.Funcnum = PINSEL_FUNC_0;
    pinCfg.Pinmode = PINSEL_PINMODE_PULLDOWN;
    pinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&PinCfg);  // P0.0 como GPIO (in) resistencia PD, para el pulsador
    pinCfg.Pinnum = PINSEL_PIN_1;
    pinCfg.Pinmode = PINSEL_PINMODE_TRISTATE;
    PINSEL_ConfigPin(&PinCfg);  // P0.1 como GPIO para el led 0
    pinCfg.Pinnum = PINSEL_PIN_2;
    PINSEL_ConfigPin(&PinCfg);  // P0.2 como GPIO para el led 1
    pinCfg.Pinnum = PINSEL_PIN_3;
    PINSEL_ConfigPin(&PinCfg);  // P0.3 como GPIO para el led 1
    pinCfg.Pinnum = PINSEL_PIN_4;
    PINSEL_ConfigPin(&PinCfg);  // P0.4 como GPIO para el led 1
    pinCfg.Pinnum = PINSEL_PIN_5;
    PINSEL_ConfigPin(&PinCfg);  // P0.5 como GPIO para el led 1
    GPIO_SetDir(0, 0b111110, 1);    // P0.1 a P0.5 como salidas
    pinCfg.Portnum = PINSEL_PORT_1;
    pinCfg.Pinnum = PINSEL_PIN_28;
    pinCfg.Funcnum = PINSEL_FUNC_3;
    PINSEL_ConfigPin(&PinCfg);  // P1.28 como MAT0.0
    pinCfg.Portnum = PINSEL_PORT_1;
    pinCfg.Pinnum = PINSEL_PIN_18;
    pinCfg.Funcnum = PINSEL_FUNC_3;
    pinCfg.Pinmode = PINSEL_PINMODE_PULLDOWN;
    PINSEL_ConfigPin(&PinCfg);  // P1.18 como CAP1.0
}
void confInt() {
    GPIO_IntCmd(0, 1, 1);   // Interrupción en P0.0 por FE
    GPIO_ClearInt(0, 1);    // Limpia la bandera de interrupción de P0.0
    NVIC_EnableIRQ(EINT3_IRQn); // Habilita la interrupción de GPIO
}
void confTimer0() {
    LPC_SC->PCLKSEL0 |= 1<<2;   // PCLK = CCLK/1 = 100Mhz
    TIM_TIMERCFG_Type timerCfg;
    timerCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
    timerCfg.PrescaleValue = 0; // 100Mhz
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timerCfg);
    TIM_MATCHCFG_Type matchCfg;
    matchCfg.MatchChannel = 0;
    matchCfg.IntOnMatch = DISABLE;
    matchCfg.StopOnMatch = DISABLE;
    matchCfg.ResetOnMatch = ENABLE;
    matchCfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
    matchCfg.MatchValue = 499;  // Señal haciendo toggle a 200khz, => f = 100khz
    TIM_ConfigMatch(LPC_TIM0, &matchCfg);
}
void confTimer1() {
    LPC_SC->PCLKSEL0 |= 1<<4;   // PCLK = CCLK/1 = 100Mhz
    TIM_TIMERCFG_Type timerCfg;
    timerCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
    timerCfg.PrescaleValue = 0; // 100Mhz
    TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timerCfg);
    TIM_CAPTURECFG_Type captureCfg;
    captureCfg.CaptureChannel = 0;
    captureCfg.RisingEdge = ENABLE;
    captureCfg.FallingEdge = DISABLE;
    captureCfg.IntOnCaption = ENABLE;
    TIM_ConfigCapture(LPC_TIM1, &captureCfg);   // Captura en el canal 0, RE, interrumpe
    TIM_ClearIntPending(LPC_TIM1, TIM_CR0_INT);
    NVIC_EnableIRQ(TIMER0_IRQn);

}
TIMER1_IRQHandler() {
    static uint32_t lastTime = 0;
    uint32_t time = TIM_GetCaptureValue(LPC_TIM1, TIM_COUNTER_INCAP0);
    uint32_t period = time - lastTime;
    switch (period) {   // Limpio los 5 leds y enciendo según la cantidad de ticks
        case 100:
            GPIO_ClearValue(0, 0b111100);
            GPIO_SetValue(0, 0b10);         // 1 led encendido
            break;
        case 50:
            GPIO_ClearValue(0, 0b111100);
            GPIO_SetValue(0, 0b110);        // 2 leds encendidos
            break;
        case 33:
            GPIO_ClearValue(0, 0b111100);
            GPIO_SetValue(0, 0b1110);       // 3 leds encendidos
            break;
        case 25:
            GPIO_ClearValue(0, 0b111100);
            GPIO_SetValue(0, 0b11110);      // 4 leds encendidos
            break;
        case 20:
            GPIO_ClearValue(0, 0b111100);
            GPIO_SetValue(0, 0b111110);     // 5 leds encendidos
            break;
        default:
            break;
    }
    TIM_ClearIntPending(LPC_TIM1, TIM_CR0_INT);
}
EINT3_IRQHandler() {
    static uint8_t i = 0;
    TIM_UpdateMatchValue(LPC_TIM1, 0, ticks[i % 5]);    // Cambio el match para variar la frecuencia
    EXTI_ClearEXTIFlag(EXTI_EINT3);
}
