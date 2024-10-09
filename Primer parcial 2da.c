/*En una fábrica, hay un sistema de alarma utilizando una LPC1769 Rev. D trabajando a una frecuencia de CCLK a 100 [MHz],
conectado a un sensor de puerta que se activa cuando la puerta se abre.
El sensor está conectado al pin P0[6], el cual genera una interrupción externa (EINT) cuando se detecta una apertura
(cambio de estado). Al detectar que la puerta se ha abierto, el sistema debe iniciar un temporizador utilizando el Systick
para contar un período de 30 segundos.
Durante estos 30 segundos, el usuario deberá introducir un código de desactivación mediante un DIP switch de 4 entradas
conectado a los pines P2[0] - P2[3]. El código correcto es 0xAA (1010 en binario). El usuario tiene dos intentos para
introducir el código correcto. Si después de dos intentos el código ingresado es incorrecto, la alarma se activará,
encendiendo un buzzer conectado al pin P1[11]
*/

#include "C:\Users\David\Documents\MCUXpressoIDE_11.7.1_9221\TP\CMSISv2p00_LPC17xx\inc\LPC17xx.h"

// Configura la interrupción EINT0 y el pin 2[4] para el botón de confirmación de contraseña
void confEINT0() {
    LPC_PINCON->PINSEL4 |= 0x100000; // P2[4] como EINT0
    LPC_SC->EXTMODE |= 1; // EINT0 por flanco
    LPC_SC->EXTPOLAR |= 1; // EINT0 por flanco de subida
    NVIC_ClearPendingIRQ(EINT0_IRQn);   // debió ser LPC_SC->EXTINT |= 1;
    NVIC_EnableIRQ(EINT0_IRQn); // Habilita interrupción EINT0
}

// Configuración de GPIO del buzzer y del DIP switch, y uso P0[6] para interrumpir por GPIO, ya que no tiene EINT
void confGPIO() {
    // Todos los pines son GPIO por defecto, entradas por defecto
    LPC_PINCON->PINMODE0 |= 3<<13; // debió ser 3<<12, P0[6] con pull-down para sensor de puerta
    LPC_PINCON->PINMODE4 |= 0xFF; // P2[0] - P2[3] con pull-down (DIP switch)
    LPC_GPIO1->FIODIR |= 1<<11; // P1[11] como salida para el buzzer
}

// La interupción por GPIO activa el flag0 cuando se abrió la puerta
EINT3_IRQHandler() {
    flag0 = 1;
    NVIC_ClearPendingIRQ(EINT3_IRQn); // debió ser LPC_SC->EXTINT |= 8;
}

// La interrupción por EINT0 activa el flag_lec cuando se presiona el botón de confirmación de contraseña
EINT0_IRQHandler() {
    flag_lec = 1;
    NVIC_ClearPendingIRQ(EINT0_IRQn); // debió ser LPC_SC->EXTINT |= 1;
}

SysTick_Handler() {
    if (flag0) {    // Si se detectó la apertura de la puerta
        cont++;     // Incrementa el contador de tiempo de los 30 segundos
        if (cont == 300)    // Si pasaron los 30 segundos
            LPC_GPIO1->FIOSET |= 1<<11; // Enciende el buzzer
    }
    if (flag_lec) { // Si se presionó el botón para confirmar la contraseña
        if ((LPC_GPIO2->FIOPIN & 0xF) == 0b1010) {  // Si la contraseña es correcta
            flag_lec = 0;   // Bajo el flag de confirmación de contraseña
            flag0 = 0;      // Bajo el flag de apertura de puerta para que deje de contar los 30 segundos
            cont = 0;       // Reinicio el contador de tiempo de los 30 segundos
            error = 0;      // Reinicio el contador de errores
        } else {    // Si la contraseña es incorrecta
            error++;    // Incremento el contador de errores
            flag_lec = 0;   // Bajo el flag de confirmación de contraseña
            if (error == 2) {   // Si ya se ingresó dos veces la contraseña incorrecta
                LPC_GPIO1->FIOSET |= 1<<11; // Enciende el buzzer
            }
        }
    }
}

// Habilitación de interrupción por flanco de subida en P0[6] para el sensor de puerta, literalmente la misma función que
// el ejercicio anterior, pero con otro puerto
void confGPIOInt() {
    //LPC_GPIOINT->IO0IntEnR |= 1<<6; // Habilito interrupción por flanco de subida en P0[1] para el switch
    //NVIC_ClearPendingIRQ(EINT3_IRQn); // debió ser LPC_SC->EXTINT |= 8;
    //NVIC_EnableIRQ(EINT3_IRQn); // Habilita interrupción EINT3
}

// Variables globales
int cont = 0;       // Contador de tiempo
int flag0 = 0;      // Flag para saber si se detectó la apertura de la puerta
int flag_lec = 0;   // Flag del botón de confirmación de contraseña
int error = 0;      // Contador de errores

int main() {
    confEINT0();
    confGPIO();
    confGPIOInt();
    SysTick_Config(10000000); // 0,1 segundos

    while(1);

    return 0;
}