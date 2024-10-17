# Registros de los Timers

## LPC_SC->PCONP
`Power para los Timers`
- **1 PCTIM0 [0]**: Habilita el Timer 0.
- **2 PCTIM1 [0]**: Habilita el Timer 1.
- **22 PCTIM2 [0]**: Habilita el Timer 2.
- **23 PCTIM3 [0]**: Habilita el Timer 3.

## LPC_SC->PCLKSEL0
`Clock para los Timers 0 y 1`
- **3:2 PCLK_TIMER0 [0]**:
    - `00 = CCLK/4`
    - `01 = CCLK`
    - `10 = CCLK/2`
    - `11 = CCLK/8`
- **5:4 PCLK_TIMER1 [0]**

## LPC_SC->PCLKSEL1
`Clock para los Timers 2 y 3`
- **13:12 PCLK_TIMER2 [0]**
- **15:14 PCLK_TIMER3 [0]**

## LPC_TIMx->IR
`Flags de interrupción del timer LPC_TIMx`
- **0 MR0 [0]**: Interrupción por coincidencia con MR0.
- **1 MR1 [0]**: Interrupción por coincidencia con MR1.
- **2 MR2 [0]**: Interrupción por coincidencia con MR2.
- **3 MR3 [0]**: Interrupción por coincidencia con MR3.
- **4 CR0 [0]**: Interrupción por evento de captura en CR0.
- **5 CR1 [0]**: Interrupción por evento de captura en CR1.

## LPC_TIMx->TCR
`Control del Timer LPC_TIMx`
- **0 CE [0]**: Habilita el contador.
- **1 CR [0]**: Resetea el TC y PC en el próximo flanco de PCLK. Debe ser limpiado por software para seguir contando.

## LPC_TIMx->CTCR
`Control de modo del timer LPC_TIMx`
- **1:0 CTM [0]**:
    - `00 = Timer Mode`
    - `01 = Counter Mode, captura en flanco de subida`
    - `10 = Counter Mode, captura en flanco de bajada`
    - `11 = Counter Mode, captura en flanco de subida y bajada`
- **3:2 CIS [0]**:
    - `00 = CAPx.0`
    - `01 = CAPx.1`
En modo contador, los 3 bits del CAP seleccionado como captura de evento se ponen en 0 (CCR);
sin embargo, el otro CAP se puede seguir usando para interrumpir o capturar el TC

## LPC_TIMx->CCR
`Control de captura del timer LPC_TIMx`
- **0 CAP0RE [0]**: CAP0 en RE causa que TC se copie a CR0.
- **1 CAP0FE [0]**: CAP0 en FE causa que TC se copie a CR0.
- **2 CAP0I [0]**: Interrumpe en el flanco habilitado (pueden ser ambos).
- **3 CAP1RE [0]**: CAP1 en RE causa que TC se copie a CR1.
- **4 CAP1FE [0]**: CAP1 en FE causa que TC se copie a CR1.
- **5 CAP1I [0]**: Interrumpe en el flanco habilitado (pueden ser ambos).

## LPC_TIMx->CR0
## LPC_TIMx->CR1
`Registros de captura del timer LPC_TIMx`
- **31:0 CR [0]**: Copia el valor de TC cuando ocurre el evento habilitado en CCR.

## LPC_TIMx->TC
- **31:0 TC [0]**: Incrementa cada que PC alcanza el valor de PR, si no se reinicia cuenta hasta
  0xFFFF FFFF y regresa a 0 sin interrumpir (se puede interrumpir con un match si se necesita)

## LPC_TIMx->PR
`Prescaler del timer LPC_TIMx`
- **31:0 PR [0]**: Cada que PC alcanza PR, TC incrementa en 1, si  PR=0, TC++ cada ciclo de reloj.
  En modo contador, se pone en 0 para contar todos los eventos.

## LPC_TIMx->PC
`Prescaler counter del timer LPC_TIMx`
- **31:0 PC [0]**: Cuenta cada ciclo de reloj, si PC=PR, TC incrementa en 1.

## LPC_TIMx->MR0
## LPC_TIMx->MR1
## LPC_TIMx->MR2
## LPC_TIMx->MR3
`Registros de match del timer LPC_TIMx`
- **31:0 MR [0]**: Se comparan continuamente con TC, si son iguales se dispara el evento controlado por MCR.

## LPC_TIMx->MCR
`Control de match del timer LPC_TIMx`
- **0 MR0I [0]**: Interrumpe cuando MR0=TC.
- **1 MR0R [0]**: Resetea TC cuando MR0=TC.
- **2 MR0S [0]**: Detiene TC y PC cuando MR0=TC, además TCR[0]=0.
- **5:3**: Idem para MR1.
- **8:6**: Idem para MR2.
- **11:9**: Idem para MR3.

## LPC_TIMx->EMR
`Control de salida del match del timer LPC_TIMx`
- **0 EM0 [0]**: Valor de salida para pin MATx.0, comportamiento controlado por EMC0.
- **1 EM1 [0]**: Idem para MATx.1.
- **2 EM2 [0]**: Idem para MATx.2 (solo en timer 2).
- **3 EM3 [0]**: Idem para MATx.3 (solo en timer 2).
- **5:4 EMC0 [0]**: Comportamiento de MATx.0:
    - `00 = No cambia`
    - `01 = Pone a 0 en match`
    - `10 = Pone a 1 en match`
    - `11 = Alterna el valor en match`
- **7:6 EMC1 [0]**: Idem para MATx.1.
- **9:8 EMC2 [0]**: Idem para MATx.2 (solo en timer 2).
- **11:10 EMC3 [0]**: Idem para MATx.3 (solo en timer 2).

---

# Drivers de los Timers
## Estructuras de configuración
- **TIM_TIMERCFG_Type**
  - **uint8_t PrescaleOption**:
    - `TIM_PRESCALE_TICKVAL Valor de prescaler en ticks.`
    - `TIM_PRESCALE_USVAL: Valor de prescaler en microsegundos.`
  - **uint32_t PrescaleValue**:


- **TIM_COUNTERCFG_Type**
  - **uint8_t CounterOption**:
    - `TIM_COUNTER_INCAP0: Captura en pin CAPx.0 para TIMERx.`
    - `TIM_COUNTER_INCAP1: Captura en pin CAPx.1 para TIMERx.`
  - **uint8_t CountInputSelect**:
    - La documentación dice que los argumentos van en el campo CounterOption, pero la función usa CountInputSelect,
    posiblemente mal documentado. No manipular esta estructura de forma directa.


- **TIM_MATCHCFG_Type**
  - **uint8_t MatchChannel**: Canal de match.
    - `0`
    - `1`
    - `2`
    - `3`
  - **uint8_t IntOnMatch**: Habilita interrupción en match.
    - `ENABLE` o `DISABLE`
  - **uint8_t StopOnMatch**: Detiene el timer en match.
    - `ENABLE` o `DISABLE`
  - **uint8_t ResetOnMatch**: Resetea el timer en match.
    - `ENABLE` o `DISABLE`
  - **uint8_t ExtMatchOutputType**: Tipo de salida en match.
    - `TIM_EXTMATCH_NOTHING`
    - `TIM_EXTMATCH_LOW`
    - `TIM_EXTMATCH_HIGH`
    - `TIM_EXTMATCH_TOGGLE`
  - **uint8_t MatchValue**: Valor de match.


- **TIM_CAPTURECFG_Type**
  - **uint8_t CaptureChannel**: Canal de captura.
    - `0`
    - `1`
  - **uint8_t RisingEdge**: Habilita captura en flanco de subida.
    - `ENABLE` o `DISABLE`
  - **uint8_t FallingEdge**: Habilita captura en flanco de bajada.
    - `ENABLE` o `DISABLE`
  - **uint8_t IntOnCaption**: Habilita interrupción en captura.
    - `ENABLE` o `DISABLE`

## TIM_Init(LPC_TIMx, TimerCounterMode, TIM_ConfigStruct)
`Habilita el power para el timer, clock en CCLK/4, setea el prescaler para el rate de la struct, resetea y limpia la interrupción`
- **LPC_TIMx**: Timer a inicializar. `x = [0-3]`
- **TimerCounterMode**: Modo del timer.
  - `TIM_TIMER_MODE` Modo timer
  - `TIM_COUNTER_RISING` Modo contador, captura en flanco de subida
  - `TIM_COUNTER_FALLING` Modo contador, captura en flanco de bajada
  - `TIM_COUNTER_ANY` Modo contador, captura en flanco de subida y bajada
- **TIM_ConfigStruct**: `TIM_TIMERCFG_Type` para timer o `TIM_COUNTERCFG_Type` para contador.

## TIM_DeInit(LPC_TIMx)
`Detiene el timer y deshabilita el power`
- **LPC_TIMx**: Timer a desinicializar. `x = [0-3]`

## TIM_ClearIntPending(LPC_TIMx, IntFlag)
`Limpia la bandera de interrupción de un timer`
- **IntFlag**: Bandera a limpiar.
  - `TIM_MR0_INT` Match 0
  - `TIM_MR1_INT` Match 1
  - `TIM_MR2_INT` Match 2
  - `TIM_MR3_INT` Match 3
  - `TIM_CR0_INT` Captura 0
  - `TIM_CR1_INT` Captura 1

## TIM_ClearIntCapturePending(LPC_TIMx, IntFlag)
`Idem que la anterior, pero para capturas. Función totalmente al pedo IMHO`
- **IntFlag**: Bandera a limpiar.
  - `0` Captura 0 (no pasar TIM_CR0_INT porque la función inicia desplazando 4 bits)
  - `1` Captura 1 (no pasar TIM_CR1_INT porque la función inicia desplazando 4 bits)

## FlagStatus TIM_GetIntStatus(LPC_TIMx, IntFlag)
`Devuelve el estado de la bandera de interrupción de un timer (1 o 0)`
- **IntFlag**: Bandera a leer.
  - `TIM_MR0_INT` Match 0
  - `TIM_MR1_INT` Match 1
  - `TIM_MR2_INT` Match 2
  - `TIM_MR3_INT` Match 3
  - `TIM_CR0_INT` Captura 0
  - `TIM_CR1_INT` Captura 1

## FlagStatus TIM_GetIntCaptureStatus(LPC_TIMx, IntFlag)
`Idem que la anterior, pero para capturas. Función totalmente al pedo IMHO`
- **IntFlag**: Bandera a leer.
  - `0` Captura 0 (no pasar TIM_CR0_INT porque la función inicia desplazando 4 bits)
  - `1` Captura 1 (no pasar TIM_CR1_INT porque la función inicia desplazando 4 bits)

## TIM_ConfigStructInit(TimerCounterMode, TIM_ConfigStruct)
`Inicializa la estructura de configuración TIM_TIMERCFG_Type o TIM_COUNTERCFG_Type`
- **TimerCounterMode**: Modo del timer.
  - `TIM_TIMER_MODE` Modo timer
  - `TIM_COUNTER_RISING` Modo contador, captura en flanco de subida
  - `TIM_COUNTER_FALLING` Modo contador, captura en flanco de bajada
  - `TIM_COUNTER_ANY` Modo contador, captura en flanco de subida y bajada
- **TIM_ConfigStruct**: `TIM_TIMERCFG_Type` para timer o `TIM_COUNTERCFG_Type` para contador.

## TIM_ConfigMatch(LPC_TIMx, TIM_MatchConfigStruct)
`Configura el valor del match, las interrupciones y el comportamiento de la salida`
- **TIM_MatchConfigStruct**: `Estructura de configuración de tipo TIM_MATCHCFG_Type`

## TIM_UpdateMatchValue(LPC_TIMx, MatchChannel, MatchValue)
`Configura el valor de match`
- **MatchChannel**: Canal de match.
  - `0`
  - `1`
  - `2`
  - `3`
- **MatchValue**: Nuevo valor de match.

## TIM_SetMatchExt(LPC_TIMx, ext_match )
`Configura el comportamiento de la salida en match`
- **ext_match**: Comportamiento de la salida en match.
  - `TIM_EXTMATCH_NOTHING`
  - `TIM_EXTMATCH_LOW`
  - `TIM_EXTMATCH_HIGH`
  - `TIM_EXTMATCH_TOGGLE`

## TIM_ConfigCapture(LPC_TIMx, TIM_CaptureConfigStruct)
`Configura el flanco de captura`
- **TIM_CaptureConfigStruct**: `Estructura de configuración de tipo TIM_CAPTURECFG_Type`

## TIM_Cmd(LPC_TIMx, NewState)
`Habilita o deshabilita el contador (TCR[0]), no deshabilita el power`
- **NewState**: `ENABLE` o `DISABLE`

## uint32_t TIM_GetCaptureValue(LPC_TIMx, CaptureChannel)
`Devuelve el valor de TC que se capturó (CRx)`
- **CaptureChannel**: Canal de captura.
  - `TIM_COUNTER_INCAP0`
  - `TIM_COUNTER_INCAP1`

## TIM_ResetCounter(LPC_TIMx)
`Resetea el timer (TCR[1])`
