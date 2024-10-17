#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"
#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\Drivers\inc\lpc17xx_timer.h"
#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\Drivers\src\lpc17xx_timer.c"

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