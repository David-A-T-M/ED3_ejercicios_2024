# DAC

## Pines disponibles
- **AOUT**: P0[26]. Func 10.

# Registros del DAC

## LPC_SC->PCLKSEL0
`Clock para el timer asociado al DAC-DMA [R/W]`
- **23:22 PCLK_DAC [0]**:
    - `00 = CCLK/4`
    - `01 = CCLK`
    - `10 = CCLK/2`
    - `11 = CCLK/8`

## LPC_DAC->DACR
`Configuración del DAC [R/W]`
- **15:6 VALUE [0]**: Valor de salida. (VALUE x (Vrefp - Vrefn) / 1024 + Vrefn)
- **16 BIAS [0]**:
  - `0` Tiempo de establecimiento de 1us y corriente de salida de 700uA. Permite actualización de 1MHz.
  - `1` Tiempo de establecimiento de 2.5us y corriente de salida de 350uA. Permite actualización de 400kHz.

## LPC_DAC->DACCTRL
`Control del DAC [R/W]`
- **0 INT_DMA_REQ [0]**: Habilita la solicitud de DMA.
  - `0` El bit se pone a 0 cuando se escribe en `DACR`.
  - `1` El bit se pone a 1 cuando se agota el timer de DMA.
- **1 DBLBUF_ENA [0]**: Habilita el dobble buffer.
  - `0` Se actualiza la salida del DAC apenas se escribe en `DACR`.
  - `1` Los datos pasan por un buffer antes de sacarlos, por sincronización. CNT_ENA debe estar habilitado.
- **2 CNT_ENA [0]**:
  - `0` El contador de time-out no se habilita.
  - `1` El contador de time-out se habilita.
- **3 DMA_ENA [0]**: Habilita DMA.
  - `0` El acceso a DMA está deshabilitado.
  - `1` Se habilita el DMA burst request input 7. 

## LPC_DAC->DACCNTVAL
`Valor del contador de time-out [R/W]`
- **15:0 VALUE [0]**

---

# Drivers del DAC
## Estructuras de configuración
- **DAC_CONVERTER_CFG_Type**
  - **uint8_t DBLBUF_ENA**:
    - `0` o `1`
  - **uint8_t CNT_ENA**:
    - `0` o `1`
  - **uint8_t DMA_ENA**:
    - `0` o `1`

## DAC_Init(LPC_DAC)
`Activa el Power al DAC, el CLK/4 y el bias de 700uA`

## DAC_UpdateValue (LPC_DAC, dac_value)
`Actualiza el valor de salida del DAC`
- **dac_value**: Valor de salida (0-1023).

## DAC_SetBias (LPC_DAC, bias)
`Setea el bias del DAC`
- `0` = 700uA, 1us, 1MHz
- `1` = 350uA, 2.5us, 400kHz

## DAC_ConfigDAConverterControl (LPC_DAC, DAC_ConverterConfigStruct)
`Configuración del DMA (DACCTRL)`
- **DAC_ConverterConfigStruct**: Estructura DAC_CONVERTER_CFG_Type.

## DAC_SetDMATimeOut(LPC_DAC, time_out)
`Setea el time-out del DMA`
- **time_out**: Valor del contador de time-out.