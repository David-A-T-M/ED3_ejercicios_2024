/*Configurar 4 canales del ADC para que funcionando en modo
burst se obtenga una frecuencia de muestreo en cada
uno de 50Kmuestras/seg. Suponer un cclk = 100 Mhz*/

void confPin();     // Configurar los 4 pines para el ADC
void confADC();     // Modo burst, con 4 canales

int main() {
    confPin();
    confADC();

    while(1);
}

void confPin() {
    PINSEL_CFG_Type cfgPin;
    cfgPin.Portnum = PINSEL_PORT_0;
    cfgPin.Pinnum = PINSEL_PIN_23;
    cfgPin.Funcnum = PINSEL_FUNC_1;
    cfgPin.Pinmode = PINSEL_PINMODE_TRISTATE;
    cfgPin.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&cfgPin);      // Pin 0.23 como AD0.0
    cfgPin.Pinnum = PINSEL_PIN_24;
    PINSEL_ConfigPin(&cfgPin);      // Pin 0.24 como AD0.1
    cfgPin.Pinnum = PINSEL_PIN_25;
    PINSEL_ConfigPin(&cfgPin);      // Pin 0.25 como AD0.2
    cfgPin.Pinnum = PINSEL_PIN_26;
    PINSEL_ConfigPin(&cfgPin);      // Pin 0.26 como AD0.3
}
void confADC() {
    ADC_Init(LPC_ADC, 200000);
    ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
    ADC_ChannelCmd(LPC_ADC, 1, ENABLE);
    ADC_ChannelCmd(LPC_ADC, 2, ENABLE);
    ADC_ChannelCmd(LPC_ADC, 3, ENABLE);
    ADC_BurstCmd(LPC_ADC, ENABLE);
}