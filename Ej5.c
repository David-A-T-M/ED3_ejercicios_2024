/*Escribir un programa en C que permita realizar un promedio movil con los últimos
8 datos ingresados por el puerto 1. Considerar que cada dato es un entero
signado y está formado por los 16 bits menos significativos de dicho puerto. El
resultado, también de 16 bits, debe ser sacado por los pines P0.0 al P0.11 y
P0.15 al P0.18. Recordar que en un promedio movil primero se descarta el dato
mas viejo de los 8 datos guardados, se ingresa un nuevo dato proveniente del
puerto y se realiza la nueva operación de promedio con esos 8 datos disponibles,
así sucesivamente. Considerar el uso de un retardo antes de tomar una nueva
muestra por el puerto.*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

int data[8];

void confGPIO(){
  LPC_PINCON->PINSEL2 &= ~(0xFFFFFFFF);  //P1.0 al P1.15 como GPIO
  LPC_PINCON->PINSEL0 &= ~(0xC0FFFFFF); //P0.0 al P0.11 como GPIO
  LPC_PINCON->PINSEL1 &= ~(0x3F); //P0.15 al P0.18 como GPIO
  LPC_GPIO1->FIODIR &= ~(0xFFFF); //P1.0 al P1.15 como entrada
  LPC_PINCON->PINMODE2 |= 0xFFFFFFFF; //P1.0 al P1.15 con pull-down
  LPC_GPIO0->FIODIR |= 0x78FFF; //P0.0 al P0.11 y P0.15 al P0.18 como salida
}

int mean(){
  int mean = 0;
  for(int i=0; i<8; i++){  //sumo los datos
    mean += data[i];
  }
  mean = mean/8;    //divido por la cantidad de datos
  return mean;    //retorno el promedio
}

int main(){
  confGPIO();    //configuro los pines como GPIO
  for(int i=0; i<8; i++){
    data[i] = 0;
  }

  int j=0;
  while(1){
    data[j%8] = LPC_GPIO1->FIOPIN & 0xFFFF;    //Guardo el dato en el arreglo
    int prom = mean();          // Calculo el promedio
    LPC_GPIO0->FIOCLR = 0x78FFF;    //Limpio el puerto
    LPC_GPIO0->FIOSET |= ((prom & 0xF000) << 3);  //P0.15 al P0.18
    LPC_GPIO0->FIOSET |= (prom & 0x0FFF);  //P0.0 al P0.11
    j++;
  }

  return 0;
}