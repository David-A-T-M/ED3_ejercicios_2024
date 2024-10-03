/*Una famosa empresa de calzados a incorporado a sus zapatillas 10 luces leds comandadas por un microcontrolador
LPC1769 y ha pedido a su grupo de ingenieros que diseñen 2 secuencias de luces que cada cierto tiempo se vayan
intercalando (secuencia A - secuencia B- secuencia A- ... ). Como todavía no se ha definido la frecuencia a la cual va a
funcionar el CPU del microcontrolador, las funciones de retardos que se incorporen deben tener como parametros de
entrada variables que permitan modificar el tiempo de retardo que se vaya a utilizar finalmente. Se pide escribir el código
que resuelva este pedido, considerando que los leds se encuentran conectados en los puertos P0,0 al P0.9. Adjuntar el
archivo .c bajo el nombre "eje1ApellidoDelEstudiante.c”*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

void confGPIO(){
  LPC_PINCON->PINSEL0 &= ~(0xFFFF);  //P0.0 al P0.9 como GPIO
  LPC_GPIO0->FIODIR |= 0x3FF; //P0.0 al P0.9 como salida
  LPC_GPIO0->FIOCLR = 0x3FF; //Inicio con los leds apagados
}
void secA(){
  int led = 0x200;
  for(int i=0; i<10; i++){
    LPC_GPIO0->FIOSET = (led >> i); //Enciendo desde el led 9 al led 0
    for(int j=0; j<1000000; j++); //Retardo
    LPC_GPIO0->FIOCLR = (led >> i); //Apago desde el led 9 al led 0
  }
}
void secB(){
  int led = 0x1;
  for(int i=0; i<10; i++){
    LPC_GPIO0->FIOSET = (led << i); //Enciendo desde el led 0 al led 9
    for(int j=0; j<1000000; j++); //Retardo
    LPC_GPIO0->FIOCLR = (led << i); //Apago desde el led 0 al led 9
  }
}

int main(){
  confGPIO();  //Configuro los pines como GPIO, salidas y apagados
  int i=0;      //Variable para intercalar las secuencias
  int delay=10;  //Variable para modificar el tiempo de retardo
  while(1){      //Bucle infinito
    int j=0;    //Variable para el retardo
    while(j<delay){
      if(i%2==0){
        secA();
        j++;
      }else{
        secB();
        j++;
      }
    }
    i++;    //Incremento la variable para intercalar las secuencias
  }
  return 0;
}