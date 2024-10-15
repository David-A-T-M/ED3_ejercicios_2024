#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"
#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\Drivers\inc\lpc17xx_adc.h"
#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\Drivers\src\lpc17xx_adc.c"

int adc () {
//  Power para el ADC
    LPC_SC->PCONP;
    /*                  12 PCADC [0]: Limpiar PDN antes de deshabilitar, habilitar PCADC antes del PDN*/
//  Clock para el ADC
    LPC_SC->PCLKSEL0;
    /*                  25:24 PCLK_ADC [0]: 00 = CCLK/4, 01 = CCLK, 10 = CCLK/2, 11 = CCLK/8*/
//  Configuración del ADC
    LPC_ADC->ADCR;
    /*                  7:0 SEL [0x1]: Selección de canal, en modo sw se habilita 1 a la vez
                        15:8 CLKDIV [0]: [PCLK_ADC / (CLKDIV + 1)] <= 13 MHz
                        16 BURST [0]: Si se habilita, START=000 y ADINTEN:8=0
                        21 PDN [0]: Habilita el ADC
                        26:24 START [0]:    001 = Inicia la conversión
                                            010 = EINT0 (P2[10])
                                            011 = CAP0.1 (P1[27])
                                            100 = T0MR1
                                            101 = T0MR3
                                            110 = T1MR0
                                            111 = T1MR1
                        27 EDGE [0]: 0 = Subida, 1 = Bajada; decide flanco de 010-111 de START*/
//  Global
    LPC_ADC->ADGDR;
    /*                  15:4 RESULT [X]: Última conversión
                        26:24 CHN [X]: Canal que se convirtió
                        30 OVERRUN [0]: Resultado sobrescrito, siempre 1 en burst, se limpia leyendo
                        31 DONE [0]: Conversión lista, se limpia leyendo ADGDR o ecribiendo ADCR. Si se escribe ADCR
                                    durante una conversión, se pone en 1 y se reinicia la conversión*/
//  Interrupciones
    LPC_ADC->ADINTEN;
    /*                  7:0 ADINTENx [0]: Habilita interrupción por canal x, 1 = habilita
                        8 ADGINTEN [1]: 0 = Interrumpen los canales habilitados, 1 = interrumpe DONE de ADGDR*/
//  Estado de cada canal
    LPC_ADC->ADDR0;
    /*                  15:4 RESULT [X]: Última conversión
                        30 OVERRUN [0]: Resultado sobrescrito, siempre 1 en burst, se limpia leyendo
                        31 DONE [0]: Conversión lista, se limpia leyendo*/
//  Estado global
    LPC_ADC->ADSTAT;
    /*                  7:0 DONE [0]: Repite el DONE de ADDRx
                        15:8 OVERRUN [0]: Repite el OVERRUN de ADDRx
                        16 ADINT [0]: Se pone en 1 cuando hay algún DONE en 1, si no hay ningún DONE se limpia,
                                    por lo que si se interrumpe por sw, se limpia leyendo ADGDR*/
}

void adcDrivers () {
//  Activa el Power al adc, setea CLKDIV para tener el rate deseado y habilita el PDN del ADC
    ADC_Init(LPC_ADC, rate);
    /*                  LPC_ADC: ADC a inicializar, es el único que hay
                        rate: Frecuencia de muestreo, máximo 200 kHz*/
//  Habilita o deshabilita modo burst
    ADC_BurstCmd(LPC_ADC, NewState);
    /*                  NewState: ENABLE o DISABLE*/
// Configura la forma de inicio de la conversión
    ADC_StartCmd(LPC_ADC, start_mode);
    /*                  NewState:   ADC_START_CONTINUOUS    -> Para modo burst
                                    ADC_START_NOW           -> Inicia una conversión
                                    ADC_START_ON_EINT0      -> Inicia en flanco de EINT0
                                    ADC_START_ON_CAP01      -> Inicia en flanco de CAP0.1
                                    ADC_START_ON_MAT01      -> Inicia en flanco de T0MR1
                                    ADC_START_ON_MAT03      -> Inicia en flanco de T0MR3
                                    ADC_START_ON_MAT10      -> Inicia en flanco de T1MR0
                                    ADC_START_ON_MAT11      -> Inicia en flanco de T1MR1*/
//  Habilita o deshabilita un canal
    ADC_ChannelCmd(LPC_ADC, channel, NewState);
    /*                  channel: Número de canal
                        NewState: ENABLE o DISABLE*/
//  Elige el flanco para
    ADC_EdgeStartConfig(LPC_ADC, EdgeOption);
    /*                  EdgeOption: ADC_START_ON_RISING     -> Inicia en flanco de subida
                                    ADC_START_ON_FALLING    -> Inicia en flanco de bajada*/
//  Habilita o deshabilita la interrupción de un canal o del bit DONE
    ADC_IntConfig (LPC_ADC, IntType, NewState);
    /*                  IntType:    ADC_ADINTENx            -> Canal x (0-7)
                                    ADC_ADGINTEN
                        NewState: ENABLE o DISABLE*/
//  Habilita o deshabilita el PDN del ADC (Innecesario si se usa ADC_Init)
    ADC_PowerdownCmd(LPC_ADC, NewState);
    /*                  NewState: ENABLE o DISABLE*/
//  Retorna la última conversión (ADGDR)
    ADC_GlobalGetData(LPC_ADC);
//  Retorna el valor leído por el ADC en un canal específico (ADDRx)
    ADC_ChannelGetData(LPC_ADC, channel);
    /*                  channel: Número de canal*/
//  Verifica el estado global (Overrun o Done, según StatusType)
    ADC_GlobalGetStatus(LPC_ADC, StatusType);
    /*                  StatusType: 0       -> Si hubo overrun retorna 1
                                    1       -> Si done es 1 retorna 1*/
//  Verifica el estado de un canal (Overrun o Done, según StatusType)
    ADC_ChannelGetStatus(LPC_ADC, channel, StatusType);
    /*                  channel: Número de canal
                        StatusType: 0       -> Si hubo overrun retorna 1
                                    1       -> Si done es 1 retorna 1*/
}

void timers () {
//  Power
    LPC_SC->PCONP;
    /*                  1 PCTIM0 [1]: Habilita el Timer 0
                        2 PCTIM1 [1]: Habilita el Timer 1
                        22 PCTIM2 [0]: Habilita el Timer 2
                        23 PCTIM3 [0]: Habilita el Timer 3*/
//  Clock
    LPC_SC->PCLKSEL0;
    /*                  3:2 PCLK_TIMER0 [0]: 00 = CCLK/4, 01 = CCLK, 10 = CCLK/2, 11 = CCLK/8
                        5:4 PCLK_TIMER1 [0]*/
    LPC_SC->PCLKSEL1;
    /*                  13:12 PCLK_TIMER2 [0]
                        15:14 PCLK_TIMER3 [0]*/
//  Flags de interrupción del timer LPC_TIMx
    LPC_TIM0->IR;
    /*                  0 MR0 [0]: Match 0
                        1 MR1 [0]: Match 1
                        2 MR2 [0]: Match 2
                        3 MR3 [0]: Match 3
                        4 CR0 [0]: Evento en CAP0
                        5 CR1 [0]: Evento en CAP1*/
//  Control del timer LPC_TIMx
    LPC_TIM0->TCR;
    /*                  0 Counter Enable [0]: Habilita el TC y el PC
                        1 Counter Reset [0]: Reinicia el TC y el PC en el siguiente flanco de subida de reloj*/
//  Control de modo del timer LPC_TIMx
    LPC_TIM0->CTCR;
    /*                  1:0 CTM [0]: 00 = Timer, 01 = Counter RE, 10 = FE, 11 = BE
                        3:2 CIS [0]: 00 = CAPx.0, 01 = CAPx.1*, en modo counter los 3 bits del cap seleccionado
                                    se deben poner en 0, sin embargo, el otro CAP se puede seguir usando para
                                    interrumpir o capturar el TC*/
//  Control de captura del timer LPC_TIMx
    LPC_TIM0->CCR;
    /*                  0 CAP0RE [0]: CAP0 en RE causa que TC se copie a CR0
                        1 CAP0FE [0]: CAP0 en FE causa que TC se copie a CR0
                        2 CAP0I [0]: CAP0 interrumpe en el flanco habilitado (pueden ser ambos)
                        3 CAP1RE [0]: CAP1 en RE causa que TC se copie a CR1
                        4 CAP1FE [0]: CAP1 en FE causa que TC se copie a CR1
                        5 CAP1I [0]: CAP1 interrumpe en el flanco habilitado (pueden ser ambos)*/
//  Capturas del timer LPC_TIMx
    LPC_TIM0->CR0;
    LPC_TIM0->CR1;
    /*                  31:0 CRx [0]: Copia el valor de TC cuando ocurre el evento habilitado en CCR*/
//  Contador del timer LPC_TIMx
    LPC_TIM0->TC;
    /*                  31:0 TC [0]: Incrementa cada que PC alcanza el valor de PR, si no se reinicia cuenta hasta
                        0xFFFF FFFF y regresa a 0 sin interrumpir (se puede interrumpir con un match si se necesita)*/
//  Prescaler del timer LPC_TIMx
    LPC_TIM0->PR;
    /*                  31:0 PR [0]: Cada que PC alcanza PR, TC incrementa en 1, si  PR=0, TC++ cada ciclo de reloj*/
//  Prescaler counter del timer LPC_TIMx
    LPC_TIM0->PC;
    /*                  31:0 PC [0]: Cuenta cada ciclo de reloj, si PC=PR, TC incrementa en 1*/
//  Matchs del timer LPC_TIMx
    LPC_TIM0->MR0;
    LPC_TIM0->MR1;
    LPC_TIM0->MR2;
    LPC_TIM0->MR3;
    /*                  Se comparan continuamente con TC, si son iguales se dispara el evento controlado por MCR*/
//  Match Control del timer LPC_TIMx
    LPC_TIM0->MCR;
    /*                  0 MR0I [0]: Interrumpe si MR0=TC
                        1 MR0R [0]: Resetea TC si MR0=TC
                        2 MR0S [0]: Detiene TC y PC si MR0=TC, además TCR[0]=0
                        5:3 Idem para MR1
                        8:6 Idem para MR2
                        11:9 Idem para MR3*/
//  Salida del match del timer LPC_TIMx
    LPC_TIM0->EMR;
    /*                  0 EM0 [0]: Valor de salida para pin MATx.0, comportamiento controlado por EMC0
                        1 EM1 [0]:
                        2 EM2 [0]: (solo timer 2)
                        3 EM3 [0]: (solo timer 2)
                        5:4 EMC0 [0]: 000 = No cambia, 001 = 0, 010 = 1, 011 = Toggle
                        7:6 EMC1 [0]:
                        9:8 EMC2 [0]: (solo timer 2)
                        11:10 EMC3 [0]: (solo timer 2)*/
    }

void timersDrivers () {

}

void dac () {
    // Clock
    LPC_SC->PCLKSEL0;
/*                      23:22 PCLK_DAC [0]: 00 = CCLK/4, 01 = CCLK, 10 = CCLK/2, 11 = CCLK/8*/
    //
    LPC_DAC->DACR;
/*                      15:6 VALUE [0]: Valor de salida del DAC
                        16 BIAS [0]: 0->1MHz, 1->400kHz*/
    //
    LPC_DAC->DACCTRL;
/**/
    //
    LPC_DAC->DACCNTVAL;
/**/
}