# DMA

# Registros del DMA

## LPC_GPDMA->DMACIntStat
`Estado de las interrupciones por canal [RO]`
- **7:0 [0]**: 1 bit por canal. Para limpiarla, debería preguntar si la interrupción es de TC o de error y limpiar la correspondiente.

## LPC_GPDMA->DMACIntTCStat
`Estado de las interrupciones por transferencia completa [RO]`
- **15:0 [0]**: 1 bit por canal. Se pone en 1 cuando se completa una transferencia (todo el TransferSize).

## LPC_GPDMA->DMACIntTCClear
`Limpia las interrupciones por transferencia completa [WO]`
- **15:0 [0]**: 1 bit por canal. Escribir un 1 limpia la interrupción del canal correspondiente.

## LPC_GPDMA->DMACIntErrStat
`Estado de las interrupciones por error [RO]`
- **15:0 [0]**: 1 bit por canal. Se pone en 1 cuando hay un error en la transferencia.

## LPC_GPDMA->DMACIntErrClr
`Limpia las interrupciones por error [WO]`
- **15:0 [0]**: 1 bit por canal. Escribir un 1 limpia la interrupción del canal correspondiente.

## LPC_GPDMA->DMACRawIntTCStat
`Estado de las interrupciones por transferencia completa sin enmascarar [RO]`
- **15:0 [0]**: 1 bit por canal.

## LPC_GPDMA->DMACRawIntErrStat
`Estado de las interrupciones por error sin enmascarar [RO]`
- **15:0 [0]**: 1 bit por canal.

## LPC_GPDMA->DMACEnbldChns
`Estado de los canales [RO]`
- **7:0 [0]**: 1 bit por canal. NO habilita los canales, solo muestra su estado.
  - `0` = Canal deshabilitado.
  - `1` = Canal habilitado.

## LPC_GPDMA->DMACSoftBReq
`Solicitud de transferencia burst [R/W]`
<br>Si se escribe un 1 en un bit, se solicita una transferencia burst en el canal correspondiente.
Se pone en 0 cuando se completa la transferencia burst.
- **0 [0]**: `SSP0 Tx`
- **1 [0]**: `SSP0 Rx`
- **2 [0]**: `SSP1 Tx`
- **3 [0]**: `SSP1 Rx`
- **4 [0]**: `ADC`
- **5 [0]**: `I2S Ch0`
- **6 [0]**: `I2S Ch1`
- **7 [0]**: `DAC`
- **8 [0]**: `UART0 Tx/MAT0.0`
- **9 [0]**: `UART0 Rx/MAT0.1`
- **10 [0]**: `UART1 Tx/MAT1.0`
- **11 [0]**: `UART1 Rx/MAT1.1`
- **12 [0]**: `UART2 Tx/MAT2.0`
- **13 [0]**: `UART2 Rx/MAT2.1`
- **14 [0]**: `UART3 Tx/MAT3.0`
- **15 [0]**: `UART3 Rx/MAT3.1`

## LPC_GPDMA->DMACSoftSReq
`Solicitud de transferencia simple [R/W]`
<br>Si se escribe un 1 en un bit, se solicita una transferencia simple en el canal correspondiente.
Se pone en 0 cuando se completa la transferencia simple.
- **15:0 [0]**: Mismas fuentes que `DMACSoftBReq`.

## LPC_GPDMA->DMACSoftLBReq
`Solicitud de última transferencia de ráfaga [R/W]`
- **15:0 [0]**: Mismas fuentes que `DMACSoftBReq`.

## LPC_GPDMA->DMACSoftLSReq
`Solicitud de última transferencia simple [R/W]`
- **15:0 [0]**: Mismas fuentes que `DMACSoftBReq`.

## LPC_GPDMA->DMACConfig
`Configuración del DMA [R/W]`
- **0 E [0]**: Habilita el DMA.
- **1 M [0]**:
  - `0` = Little endian.
  - `1` = Big endian.

## LPC_GPDMA->DMACSync
`Sincronización de las solicitudes de DMA [R/W]`
- **0 [0]**: `0` = Sincroniza, `1` = no sincroniza.

## LPC_SC->DMAREQSEL
`Selección de fuente de solicitud de DMA para las fuentes compartidas (8-15) [R/W]`
- **0 DMASEL08 [0]**:
    - `0` = UART
    - `1` = Timer
- **1 DMASEL09 [0]**
- **2 DMASEL10 [0]**
- **3 DMASEL11 [0]**
- **4 DMASEL12 [0]**
- **5 DMASEL13 [0]**
- **6 DMASEL14 [0]**
- **7 DMASEL15 [0]**

## LPC_GPDMACHx->DMACCSrcAddr
`Dirección de la fuente de la transferencia [R/W]`
- **31:0 [0]**: Dirección de la fuente.

## LPC_GPDMACHx->DMACCDestAddr
`Dirección del destino de la transferencia [R/W]`
- **31:0 [0]**: Dirección del destino.

## LPC_GPDMACHx->DMACCLLI
`Dirección del siguiente LLI [R/W]`
- **1:0 [0]**: Siempre 0, ya que las direcciones son múltiplos de 4 (word-aligned).
- **31:2 [0]**: Dirección del siguiente LLI.

## LPC_GPDMACHx->DMACCControl
`Control de la transferencia [R/W]`
- **11:0 TransferSize [0]**: Tamaño total de la transferencia.
- **14:12 SBSize [0]**: Tamaño de la transferencia de burst.
  - `000` = 1
  - `001` = 4
  - `010` = 8
  - `011` = 16
  - `100` = 32
  - `101` = 64
  - `110` = 128
  - `111` = 256
- **17:15 DBSize [0]**: Tamaño de la transferencia de burst.
- **20:18 SWidth [0]**: Ancho de la transferencia de fuente.
  - `000` = 8 bits
  - `001` = 16 bits
  - `010` = 32 bits
- **23:21 DWidth [0]**: Ancho de la transferencia de destino.
- **26 SI [0]**: Indica si la dirección se debe incrementar después de cada transferencia. `0` = dirección constante.
- **27 DI [0]**: Indica si la dirección se debe incrementar después de cada transferencia. `0` = dirección constante.
- **31 I [0]**: Interrumpe al final de la transferencia total (TransferSize).

## LPC_GPDMACHx->DMACCConfig
`Configuración de la transferencia [R/W, 17=RO]`
- **0 E [0]**: Habilita el canal.
  - `0` = Canal deshabilitado.
  - `1` = Canal habilitado.
- **5:1 SrcPeripheral [0]**: Periférico fuente.
- **10:6 DestPeripheral [0]**: Periférico destino.
- **13:11 TransferType [0]**: Tipo de transferencia.
  - `000` = M2M
  - `001` = M2P
  - `010` = P2M
  - `011` = P2P
- **14 IE [0]**: Máscara de interrupción de error.
- **15 ITC [0]**: Máscara de interrupción de transferencia completa.
- **17 A [0]**: Estado del canal.
- **18 H [0]**: Ignora los pedidos de transferencia.

# Drivers del DMA

## Estructuras de configuración
- **GPDMA_Channel_CFG_Type**
  - **uint32_t ChannelNum**:
    - `0 a 7`. Número de canal. El canal 0 tiene la mayor prioridad.
  - **uint32_t TransferSize**:
    - `Tamaño total de la transferencia.`
  - **uint32_t TransferWidth**:
    - `Ancho de la transferencia.`
  - **uint32_t SrcMemAddr**:
    - `Dirección de la fuente.`
  - **uint32_t DstMemAddr**:
    - `Dirección del destino.`
  - **uint32_t TransferType**:
    - `GPDMA_TRANSFERTYPE_M2M`
    - `GPDMA_TRANSFERTYPE_M2P`
    - `GPDMA_TRANSFERTYPE_P2M`
    - `GPDMA_TRANSFERTYPE_P2P`
  - **uint32_t SrcConn**: Periférico fuente.
    - `GPDMA_CONN_SSP0_Tx`
    - `GPDMA_CONN_SSP0_Rx`
    - `GPDMA_CONN_SSP1_Tx`
    - `GPDMA_CONN_SSP1_Rx`
    - `GPDMA_CONN_ADC`
    - `GPDMA_CONN_I2S_Channel_0`
    - `GPDMA_CONN_I2S_Channel_1`
    - `GPDMA_CONN_DAC`
    - `GPDMA_CONN_UART0_Tx`
    - `GPDMA_CONN_UART0_Rx`
    - `GPDMA_CONN_UART1_Tx`
    - `GPDMA_CONN_UART1_Rx`
    - `GPDMA_CONN_UART2_Tx`
    - `GPDMA_CONN_UART2_Rx`
    - `GPDMA_CONN_UART3_Tx`
    - `GPDMA_CONN_UART3_Rx`
    - `GPDMA_CONN_MAT0_0`
    - `GPDMA_CONN_MAT0_1`
    - `GPDMA_CONN_MAT1_0`
    - `GPDMA_CONN_MAT1_1`
    - `GPDMA_CONN_MAT2_0`
    - `GPDMA_CONN_MAT2_1`
    - `GPDMA_CONN_MAT3_0`
    - `GPDMA_CONN_MAT3_1`
  - **uint32_t DstConn**: `Periférico destino.`
    - `Idem`
  - **uint32_t DMALLI**:
    - `Si no hay siguiente LLI, poner 0.`
- **GPDMA_LLI_Type**
  - **uint32_t SrcAddr**:
    - `Dirección de la fuente.`
  - **uint32_t DstAddr**:
    - `Dirección del destino.`
  - **uint32_t NextLLI**:
    - `Dirección del siguiente LLI.`
  - **uint32_t Control**:
    - `Control de la transferencia.`

## GPDMA_Init()
`Habilita el power, limpia los registros de configuración de los canales y limpia las interrupciones`

## Status GPDMA_Setup(GPDMAChannelConfig)
`Configura un canal, no lo habilita, devuelve 1 si la configuración fue exitosa`
- **GPDMAChannelConfig**: `Puntero a estructura de configuración de tipo GPDMA_Channel_CFG_Type`

## IntStatus GPDMA_IntGetStatus(type, channel)
`Devuelve el estado de las interrupciones, 1 si existe una interrupción activa`
- **type**:
  - `GPDMA_STAT_INT`
  - `GPDMA_STAT_INTTC`
  - `GPDMA_STAT_INTERR`
  - `GPDMA_STAT_RAWINTTC`
  - `GPDMA_STAT_RAWINTERR`
  - `GPDMA_STAT_ENABLED_CH`
- **channel**: Canal a consultar.

## GPDMA_ClearIntPending(type, channel)
`Limpia las interrupciones`
- **type**:
  - `GPDMA_STATCLR_INTTC`
  - `GPDMA_STATCLR_INTERR`
- **channel**: Canal a limpiar.

## GPDMA_ChannelCmd(channelNum, NewState)
`Habilita o deshabilita un canal`
- **channelNum**: Canal a habilitar/deshabilitar.
- **NewState**: `ENABLE` o `DISABLE`
