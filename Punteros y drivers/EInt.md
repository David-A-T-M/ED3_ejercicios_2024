# INTERRUPCIONES EXTERNAS

## Pines disponibles
- **EINT0**: P2[10]. Func 01.
- **EINT1**: P2[11]. Func 01.
- **EINT2**: P2[12]. Func 01.
- **EINT3**: P2[13]. Func 01.

# Registros de las interrupciones externas

## LPC_SC->EXTINT
`Registros de flag de interrupciones externas [R/W]`
- **0 EINT0 [0]**: Se limpia escribiendo 1. En modo de nivel, solo se puede limpiar si el pin no está en el nivel configurado para interrumpir.
- **1 EINT1 [0]**: Idem.
- **2 EINT2 [0]**: Idem.
- **3 EINT3 [0]**: Idem.

## LPC_SC->EXTMODE
`Registros de configuración de modo de las interrupciones externas [R/W]`
- **0 EXTMODE0 [0]**: Se debe deshabilitar la interrupción antes de cambiar el modo, y limpiar el EXTINT correspondiente antes de habilitarla.
    - `0 = Nivel.`
    - `1 = Flanco.`
- **1 EXTMODE1 [0]**:
- **2 EXTMODE2 [0]**:
- **3 EXTMODE3 [0]**:

## LPC_SC->EXTPOLAR
`Registros de configuración de los flancos de las interrupciones externas [R/W]`
- **0 EXTPOLAR0 [0]**: Se debe deshabilitar la interrupción antes de cambiar el modo, y limpiar el EXTINT correspondiente antes de habilitarla.
    - `0 = Nivel bajo o Flanco de bajada.`
    - `1 = Nivel alto o Flanco de subida.`
- **1 EXTPOLAR1 [0]**:
- **2 EXTPOLAR2 [0]**:
- **3 EXTPOLAR3 [0]**:

---

# Drivers de las interrupciones externas
## Estructuras de configuración
- **EXTI_InitTypeDef**
    - **EXTI_Line**:
        - `EXTI_EINTx` x de 0 a 3.
    - **EXTI_Mode**:
        - `EXTI_MODE_LEVEL_SENSITIVE`
        - `EXTI_MODE_EDGE_SENSITIVE`
    - **EXTI_polarity**:
        - `EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE`
        - `EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE`

## EXTI_Init()
`Limpia los flags de interrupción y configura todo a 0`

## EXTI_DeInit()
`No hace nada`

## EXTI_Config(EXTICfg)
`Configura una interrupción externa`
- **EXTICfg**: Estructura de configuración.

## NVIC_EnableIRQ(EINTx_IRQn)
`Habilita la interrupción extrena x en el NVIC`
- x [0-3].

## EXTI_SetMode(EXTILine, mode)
`Configura el modo de una interrupción externa`
- **EXTILine**: Línea a configurar.
    - `EXTI_EINTx` x de 0 a 3.
- **mode**:
    - `EXTI_MODE_LEVEL_SENSITIVE`
    - `EXTI_MODE_EDGE_SENSITIVE`

## EXTI_SetPolarity(EXTILine, polarity)
`Configura la polaridad de una interrupción externa`
- **EXTILine**: Línea a configurar.
    - `EXTI_EINTx` x de 0 a 3.
- **polarity**:
    - `EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE`
    - `EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE`

## EXTI_ClearEXTIFlag(EXTILine)
`Limpia el flag de una interrupción externa`
- **EXTILine**: Interrupción a limpiar.
    - `EXTI_EINTx` x de 0 a 3.
