# Registros de los GPIO

## LPC_GPIOx->FIODIR
`Dirección de los pines`
- **31:0 [0]**: `0 = Entrada`, `1 = Salida`, 1 bit por pin.

## LPC_GPIOx->FIOMASK
`Máscara de bits`
- **31:0 [0]**: Habilita la lectura y escritura de cada pin, 1 bit por pin.
  - `0` 
  - `1`

## LPC_GPIOx->FIOPIN
`Estado de los pines`
- **31:0 [0]**: Estado de cada pin, 1 bit por pin.
  - `0`
  - `1`

## LPC_GPIOx->FIOSET
`Pone en alto los pines a los que les asigne un 1 en este registro`
- **31:0 [0]** 1 bit por pin.

## LPC_GPIOx->FIOCLR
`Pone en bajo los pines a los que les asigne un 1 en este registro`
- **31:0 [0]** 1 bit por pin.

## LPC_GPIOINT->IOxIntEnR
`Habilita las interrupciones por flanco de subida en el puerto x`
- **31:0 [0]**

## LPC_GPIOINT->IOxIntEnF
`Habilita las interrupciones por flanco de bajada en el puerto x`
- **31:0 [0]**

## LPC_GPIOINT->IntStatus
`Estado de las interrupciones`
- **0 P0Int [0]**: Se pone en 1 cuando hay por lo menos una interrupción pendiente en el puerto 0.
- **2 P2Int [0]**: Se pone en 1 cuando hay por lo menos una interrupción pendiente en el puerto 2.

## LPC_GPIOINT->IOxIntStatR
`Estado de las interrupciones por flanco de subida en el puerto x`
- **31:0 [0]**: Se pone en 1 cuando hubo una interrupción por flanco de subida en el pin correspondiente.

## LPC_GPIOINT->IOxIntStatF
`Estado de las interrupciones por flanco de bajada en el puerto x`
- **31:0 [0]**: Se pone en 1 cuando hubo una interrupción por flanco de bajada en el pin correspondiente.

## LPC_GPIOINT->IOxIntClr
`Limpia las interrupciones de los pines correspondientes del puerto x`
- **31:0 [0]**

---

# Drivers de los GPIO

## GPIO_SetDir(portNum, bitValue, dir)
`Define la dirección de los pines`
- **portNum**: Puerto a configurar. `0` al `4`
- **bitValue**: `0` a `0xFFFFFFFF` para elegir los pines a configurar.
- **dir**: `0 = Entrada`, `1 = Salida`

## GPIO_SetValue(portNum, bitValue)
`Pone en alto pines específicos (salidas únicamente)`
- **portNum**: Puerto a configurar. `0` al `4`
- **bitValue**: `0` a `0xFFFFFFFF` para elegir los pines a configurar.

## GPIO_ClearValue(portNum, bitValue)
`Pone en bajo pines específicos (salidas únicamente)`
- **portNum**: Puerto a configurar. `0` al `4`
- **bitValue**: `0` a `0xFFFFFFFF` para elegir los pines a configurar.

## uint32_t GPIO_ReadValue(portNum)
`Retorna el estado de los pines de un puerto`
- **portNum**: Puerto a leer. `0` al `4`

## FIO_SetMask(portNum, bitValue, maskValue)
`Habilita o deshabilita la máscara de pines específicos (salidas únicamente)`
- **portNum**: Puerto a configurar. `0` al `4`
- **bitValue**: `0` a `0xFFFFFFFF` para elegir los pines a configurar.
- **maskValue**:
  - `0`: Deshabilita la máscara
  - `1`: Habilita la máscara

## GPIO_IntCmd(portNum, bitValue, edgeState)
`Habilita las interrupciones por flanco de subida o bajada (P0.0-P0.30, P2.0-P2.13)`
- **portNum**: Puerto a configurar. `0` o `2` únicamente.
- **bitValue**: `0` a `0xFFFFFFFF` para elegir los pines a configurar. No hace |= con el registro, lo sobreescribe.
- **edgeState**:
  - `0`: Flanco de subida
  - `1`: Flanco de bajada

## FunctionalState GPIO_GetIntStatus(portNum, pinNum, edgeState)
`Devuelve el estado de la interrupción (1 o 0) de un pin (P0.0-P0.30, P2.0-P2.13)`
- **portNum**: Puerto a leer. `0` o `2` únicamente.
- **pinNum**: Pin a leer. `0` al `30` para el puerto 0 y `0` al `13` para el puerto 2.
- **edgeState**: Estado que se quiere leer.
  - `0`: Flanco de subida
  - `1`: Flanco de bajada

## GPIO_ClearInt(portNum, bitValue)
`Limpia la interrupción de un pin (P0.0-P0.30, P2.0-P2.13)`
- **portNum**: Puerto a limpiar. `0` o `2` únicamente.
- **bitValue**: Elección de los pines a limpiar.