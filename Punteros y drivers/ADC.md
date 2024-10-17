# Registros del ADC

## LPC_SC->PCONP
`Power para el ADC`
- **12 PCADC [0]**: Limpiar PDN antes de deshabilitar, habilitar PCADC antes del PDN.

## LPC_SC->PCLKSEL0
`Clock para el ADC`
- **25:24 PCLK_ADC [0]**:
    - `00 = CCLK/4`
    - `01 = CCLK`
    - `10 = CCLK/2`
    - `11 = CCLK/8`

## LPC_ADC->ADCR
`Configuración del ADC`
- **7:0 SEL [0x1]**: Selección de canal, en modo SW se debe habilitar 1 a la vez.
- **15:8 CLKDIV [0]**: `[PCLK_ADC / (CLKDIV + 1)] <= 13 MHz`
- **16 BURST [0]**: Si se habilita, `START=000` y `ADINTEN:8=0`.
- **21 PDN [0]**: Habilita el ADC.
- **26:24 START [0]**:
    - `001` = Inicia la conversión.
    - `010` = EINT0 (P2[10]).
    - `011` = CAP0.1 (P1[27]).
    - `100` = T0MR1.
    - `101` = T0MR3.
    - `110` = T1MR0.
    - `111` = T1MR1.
- **27 EDGE [0]**: `0 = Subida`, `1 = Bajada`; decide flanco de `010-111` de `START`.

## LPC_ADC->ADGDR
`Estado Global`
- **15:4 RESULT [X]**: Última conversión.
- **26:24 CHN [X]**: Canal que se convirtió.
- **30 OVERRUN [0]**: Resultado sobrescrito, siempre `1` en burst, se limpia leyendo.
- **31 DONE [0]**: Conversión lista, se limpia leyendo `ADGDR` o escribiendo `ADCR`. Si se escribe `ADCR` durante una conversión, se pone en `1` y se reinicia la conversión.

## LPC_ADC->ADINTEN
`Interrupciones`
- **7:0 ADINTENx [0]**: Habilita interrupción por canal `x`, `1` = habilita.
- **8 ADGINTEN [1]**: `0` = Interrumpen los canales habilitados, `1` = interrumpe `DONE` de `ADGDR`.

## LPC_ADC->ADDR0
`Estado de cada canal`
- **15:4 RESULT [X]**: Última conversión.
- **30 OVERRUN [0]**: Resultado sobrescrito, siempre `1` en burst, se limpia leyendo.
- **31 DONE [0]**: Conversión lista, se limpia leyendo.

## LPC_ADC->ADSTAT
`Estado Global`
- **7:0 DONE [0]**: Repite el `DONE` de `ADDRx`.
- **15:8 OVERRUN [0]**: Repite el `OVERRUN` de `ADDRx`.
- **16 ADINT [0]**: Se pone en `1` cuando hay algún `DONE` en `1`, si no hay ningún `DONE` se limpia, por lo que si se interrumpe por software, se limpia leyendo `ADGDR`.

---

# Drivers del ADC

## ADC_Init(LPC_ADC, rate)
`Activa el Power al adc, setea CLKDIV para tener el rate deseado y habilita el PDN del ADC`
- **LPC_ADC**: ADC a inicializar, es el único que hay
- **rate**: Frecuencia de muestreo, máximo 200 kHz

## ADC_BurstCmd(LPC_ADC, NewState)
`Habilita o deshabilita el modo burst`
- **NewState**: `ENABLE` o `DISABLE`

## ADC_StartCmd(LPC_ADC, start_mode)
`Configura la forma de inicio de la conversión`
- **start_mode**:
  - `ADC_START_CONTINUOUS`: Para modo burst
  - `ADC_START_NOW`: Inicia una conversión
  - `ADC_START_ON_EINT0`: Inicia en flanco de EINT0
  - `ADC_START_ON_CAP01`: Inicia en flanco de CAP0.1
  - `ADC_START_ON_MAT01`: Inicia en flanco de T0MR1
  - `ADC_START_ON_MAT03`: Inicia en flanco de T0MR3
  - `ADC_START_ON_MAT10`: Inicia en flanco de T1MR0
  - `ADC_START_ON_MAT11`: Inicia en flanco de T1MR1

## ADC_ChannelCmd(LPC_ADC, channel, NewState)
`Habilita o deshabilita un canal`
- **channel**: Canal a habilitar
- **NewState**: `ENABLE` o `DISABLE`

## ADC_EdgeStartConfig(LPC_ADC, EdgeOption)
`Configura el flanco de inicio de la conversión`
- **EdgeOption**:
  - `ADC_START_ON_RISING`: Inicia en flanco de subida
  - `ADC_START_ON_FALLING`: Inicia en flanco de bajada

## ADC_IntConfig(LPC_ADC, IntType, NewState)
`Habilita o deshabilita la interrupción de un canal o del bit DONE de ADGDR`
- **IntType**:
  - `ADC_ADINTENx`: Habilita interrupción por canal `x`
- **NewState**: `ENABLE` o `DISABLE`

## ADC_PowerdownCmd(LPC_ADC, NewState)
`Habilita o deshabilita el PDN del ADC (Innecesario si se usa ADC_Init)`
- **NewState**: `ENABLE` o `DISABLE`

## uint32_t ADC_GlobalGetData(LPC_ADC)
`Devuelve el valor de la última conversión (ADGDR)`

## uint16_t ADC_ChannelGetData(LPC_ADC, channel)
`Devuelve el valor de la última conversión de un canal específico (ADDRx)`
- **channel**: Canal a leer

## FlagStatus ADC_GlobalGetStatus(LPC_ADC, StatusType)
`Verifica el estado global (Overrun o Done, según StatusType)`
- **StatusType**:
  - `0`: Overrun
  - `1`: Done

## FlagStatus ADC_ChannelGetStatus(LPC_ADC, channel, StatusType)
`Verifica el estado de un canal (Overrun o Done, según StatusType)`
- **channel**: Canal a leer
- **StatusType**:
  - `0`: Overrun
  - `1`: Done