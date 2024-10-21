# SYSTICK
# Registros del SysTick

## SysTick->CTRL
`Registro de control del SysTick [R/W]`
- **0 ENABLE [0]**: Habilita el contador.
- **1 TICKINT [0]**: Habilita la interrupción. Interrumpe cuando el contador llega a 0.
- **2 CLKSOURCE [1]**: Selecciona la fuente de clock.
  - `0` Fuente de clock externa (STCLCK).
  - `1` Fuente de clock interna.
- **16 COUNTFLAG [0]**: Bandera de conteo. Se pone en 1 cuando el contador llega a 0. Se limpia leyéndola.

## SysTick->LOAD
`Registro de recarga del SysTick [R/W]`
- **23:0 RELOAD [0]**: Valor de recarga. Cuando el contador llega a 0, vuelve a contar desde este valor.

## SysTick->VAL
`Registro de valor actual del SysTick [R/W]`
- **23:0 CURRENT [0]**: Valor actual del contador.

## SysTick->CALIB
`Registro de calibración del SysTick [R/W]`
- **23:0 TENMS [0x0F 423F]**: Valor de calibración. Contiene el valor de carga necesario para contar 10ms a 100MHz.
- **30 SKEW [0]**: Indica si con el valor de TENMS se puede considerar preciso el conteo de 10ms.
  - `0` El conteo se considera preciso.
  - `1` El conteo no es preciso.
- **31 NOREF [0]**: Indica si existe un reloj externo de referencia.
  - `0` Disponible.
  - `1` No disponible.

---

# Drivers del SysTick
## SYSTICK_InternalInit(time)
`Inicializa el SysTick con el CPU clock y carga (cclk/1000)*time - 1 en LOAD`
- **time**: Tiempo en ms. Tiempo máximo igual a 1/SystemCoreClock * (2<sup>24</sup>) * 1000 (ms)

## SYSTICK_ExternalInit(freq, time)
`Inicializa el SysTick con un clock externo y carga (freq/1000)*time - 1 en LOAD`
- **freq**: Frecuencia del clock externo.
- **time**: Tiempo en ms. Tiempo máximo igual a 1/freq * (2<sup>24</sup>) * 1000 (ms)

## SYSTICK_Cmd(NewState)
`Habilita o deshabilita el contador del SysTick`
- **NewState**: ENABLE o DISABLE

## SYSTICK_IntCmd(NewState)
`Habilita o deshabilita la interrupción del SysTick`
- **NewState**: ENABLE o DISABLE

## SysTick_Handler()
`Handler de la interrupción del SysTick`

## uint32_t SYSTICK_GetCurrentValue()
`Devuelve el valor actual del contador del SysTick (VAL)`

## SYSTICK_ClearCounterFlag()
`Limpia la bandera de conteo del SysTick (COUNTFLAG)`

## SysTick_Config(ticks)
`Configura el SysTick con un valor de recarga, habilita las interrupciones e inicia el contador`
- **ticks**: Valor de recarga. Máximo 2<sup>24</sup> - 1 = 16777215
