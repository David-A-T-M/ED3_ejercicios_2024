/*Un estacionamiento automatizado utiliza una barrera que se abre y cierra en función de la validación de un ticket de acceso
utilizando una LPC1769 Rev. D trabajando a una frecuencia de CCLK a 70 [MHz]
Cuando el sistema detecta que un automóvil se ha posicionado frente a la barrera, se debe activar un sensor conectado
al pin P2[4] mediante una interrupción externa (EINT). Una vez validado el ticket, el sistema activa un motor que abre
la barrera usando el pin P0[15]. El motor debe estar activado por X segundos y luego apagarse, utilizando el temporizador Systick
para contar el tiempo. Si el ticket es inválido, se encenderá un LED rojo conectado al pin P1[5].
Para gestionar el tiempo de apertura de la barrera, existe un switch conectado al pin P3[4] que dispone de una ventana
de configuración de 3 segundos gestionada por el temporizador Systick.
Durante dicha ventana, se debe contar cuantas veces se presiona el switch y en función de dicha cantidad, establecer el
tiempo de la barrera.
*/

/**
 *   Transcripción literal de mi parcial.
 *   - Error en la forma de limpiar los flags de interrupción
 *   - Variable global tiempo no declarada. línea 71
 */

// Configura la interrupción EINT0 y el pin 2[4] donde está el sensor que interrumpe cuando un auto se posiciona frente a la barrera
void confEINT0() {
  LPC_PINCON->PINSEL4 |= 0x100000; // P2[4] como EINT0
  LPC_SC->EXTMODE |= 1; // EINT0 por flanco
  LPC_SC->EXTPOLAR |= 1; // EINT0 por flanco de subida
  NVIC_ClearPendingIRQ(EINT0_IRQn); // debió ser LPC_SC->EXTINT |= 1;
  NVIC_EnableIRQ(EINT0_IRQn); // Habilita interrupción EINT0
}

// Configuración de GPIO del led, del motor (salidas) y del validador de ticket y switch (entradas)
// El switch es un botón que se configura en P0[1] porque P3[4] no existe
// El validador de ticket en P0[0] que se pone en 1 cuando el ticket es válido
void confGPIO() {
  //Todos los pines son GPIO por defecto
  LPC_GPIO0->FIODIR |= 1<<15; // P0[15] como salida para el motor
  LPC_GPIO1->FIODIR |= 1<<5; // P1[5] como salida para el LED rojo
  //P0[0] y P0[1] son entradas por defecto
  LPC_PINCON->PINMODE0 |= 0xF; // P0[0] y P0[1] con pull-down
}

void confInt() {
  LPC_GPIOINT->IO0IntEnR |= 2; // Habilito interrupción por flanco de subida en P0[1] para el switch
  NVIC_ClearPendingIRQ(EINT3_IRQn); // debió ser LPC_SC->EXTINT |= 8;
  NVIC_EnableIRQ(EINT3_IRQn); // Habilita interrupción EINT3
}

// Interrupción de sensor de auto
EINT0_IRQHandler() {
  if (LPC_GPIO0->FIOPIN&1)
    LPC_GPIO0->FIOSET = 1<<15; // Abre la barrera
  else
    LPC_GPIO1->FIOSET = 1<<5; // Enciende el LED rojo

  contx = 0; // Reinicia el contador de tiempo
  NVIC_ClearPendingIRQ(EINT0_IRQn); // debió ser LPC_SC->EXTINT |= 1;
}

// Interrupción de switch para configurar el tiempo de la barrera
EINT3_IRQHandler() {
  if (flag) {   // Si es la primera vez que se presiona el switch
    contador = 0;   // Reinicio el contador de veces que se presiona
    flag = 0; // Bajo el flag de switch
  } else
    contador ++;  // Si ya se presionó el switch, incrementa el contador de veces que se presiona
  NVIC_ClearPendingIRQ(EINT3_IRQn); // debió ser LPC_SC->EXTINT |= 8;
}

// Variables globales
int contx = 0; // Contador de tiempo
int cont3 = 0; // Contador de tiempo de la ventana de configuración
int contador = 0; // Contador de veces que se presiona el switch
int flag = 1; // Flag para saber si se presionó el switch, 1 si no se presionó, 0 si se presionó y estoy en la ventana de configuración
/*int tiempo = 25;*/  // Tiempo de la barrera inicial, olvidé declararla

// Interrupción de SysTick cada 0,2 segundos
SysTick_Handler() {
  if (flag == 0) {    // Si se presionó el switch
    cont3++;    // Incremento el contador la ventana de configuración
    if (cont3 == 15) {  // Si se termina el tiempo de la ventana de configuración
      flag = 1;   // Reinicio el flag de switch
      cont3 = 0;  // Reinicio el contador de la ventana de configuración
      switch (contador) {   // Establece el tiempo de la barrera en función de la cantidad de veces que se presiona el switch
        case 1:
          tiempo = 50;  // Tiempo de 10 segundos
          break;
        case 2:
          tiempo = 100;   // Tiempo de 20 segundos
          break;
        case 3:
          tiempo = 200;   // Tiempo de 40 segundos
          break;
        default:
          tiempo = 25;    // Tiempo de 5 segundos
      }
    }
  }
  contx++;  // Contador de tiempo de barrera
  if (contx == tiempo) {  // Si se cumple el tiempo de la barrera
    LPC_GPIO0->FIOCLR |= 1<<15; // Cierra la barrera
    LPC_GPIO1->FIOCLR |= 1<<5; // Apaga el LED rojo
  }
  NVIC_ClearPendingIRQ(SysTick_IRQn); // debió ser SysTick->CTRL &= SysTick->CTRL;
}

int main() {
  confEINT0();
  confGPIO();
  confInt();
  SysTick_Config(14000000); // SysTick cada 0.2 segundos
  while (1);
  return 0;
}