/*Utilizando el modo Capture, escribir un código en C para que guarde en una variable, llamada "shooter", el tiempo
(en milisegundos) que le lleva a una persona presionar dos pulsadores con un único dedo. Adjuntar el archivo .c del
código. Nombre de los archivos*/

#include <stdint.h>

void confPIN();
void confTIM0();

uint32_t shooter;

int main() {
    confPIN();
    confTIM0();

    while (1);
}

void confPIN() {
    PINSEL_CFG_Type confPin;
    confPin.Portnum = PINSEL_PORT_1;
    confPin.Pinnum = PINSEL_PIN_26;
    confPin.Funcnum = PINSEL_FUNC_3;
    confPin.Pinmode = PINSEL_PINMODE_PULLDOWN;
    confPin.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&confPin); // P1.26 como CAP0.0, se conecta el primer botón
    confPin.Pinnum = PINSEL_PIN_27;
    PINSEL_ConfigPin(&confPin); // P1.27 como CAP0.1, se conecta el segundo botón

}
void confTIM0() {
    TIM_TIMERCFG_Type confTim;
    confTim.PrescaleOption = TIM_PRESCALE_USVAL;
    confTim.PrescaleValue = 1000;   // Cada TC = 1ms
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &confTim);   // Inicializa el timer0
    TIM_CAPTURECFG_Type confCap;
    confCap.CaptureChannel = 0;
    confCap.RisingEdge = DISABLE;
    confCap.FallingEdge = ENABLE;
    confCap.IntOnCaption = ENABLE;
    TIM_ConfigCapture(LPC_TIM0, &confCap);  // Configura el canal 0 para captura FE, Interrumpe
    confCap.CaptureChannel = 1;
    TIM_ConfigCapture(LPC_TIM0, &confCap);  // Configura el canal 1 para captura FE, Interrumpe
    TIM_ClearIntPending(LPC_TIM0, TIM_CR0_INT);
    TIM_ClearIntPending(LPC_TIM0, InTIM_CR1_INT);
    NVIC_EnableIRQ(TIMER0_IRQn);
}
TIMER0_IRQHandler() {
    static uint8_t i = 0;
    static uint32_t prev = 0;
    if(!i % 2) {
        prev = TIM_GetCaptureValue(LPC_TIM0, TIM_COUNTER_INCAP0);
    } else {
        shooter = TIM_GetCaptureValue(LPC_TIM0, TIM_COUNTER_INCAP0) - prev;
    }
}