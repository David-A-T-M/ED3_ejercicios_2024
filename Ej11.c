/*Configure el Systick Timer de modo que genere una forma de onda llamada PWM
tal como la que se muestra en la figura adjunta. Esta señal debe ser sacada por el
pin P0.22 para que controle la intensidad de brillo del led. El periodo de la señal
debe ser de 10 mseg con un duty cycle de 10%. Configure la interrupción externa
EINT0 de modo que cada vez que se entre en una rutina de interrupción externa el
duty cycle incremente en un 10% (1 mseg). Esto se repite hasta llegar al 100%,
luego, si se entra nuevamente a la interrupción externa, el duty cycle volverá al 0%.
b. Modificar los niveles de prioridad para que la interrupción por systick tenga
mayor prioridad que la interrupción externa.*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

int main(){

}

//TODO: