# PINSEL

# Registros de configuración de los pines

## LPC_PINCON->PINSELx
`Selección de función de los pines. x de 0 a 9, 2 registros por puerto [R/W]`
- **31:0 [0]**: 2 bits por pin. 
  - `00 = Generalmente GPIO`
  - `01 = Función 1`
  - `10 = Función 2`
  - `11 = Función 3`

## LPC_PINCON->PINMODEx
`Configura las resistencias de entrada en los pines. x de 0 a 9, 2 registros por puerto [R/W]`
- **31:0 [0]**: 2 bits por pin.
  - `00 = Pull-up`
  - `01 = Repeater` Se habilita PU o PD según el nivel del pin. Para evitar estado flotante y no consumir energía.
  - `10 = None`
  - `11 = Pull-down`

## LPC_PINCON->PINMODE_ODx
`Configura los pines como de drenador abierto. x de 0 a 4 [R/W]`
- **31:0 [0]**: 1 bit por pin.
  - `0 = Normal`
  - `1 = Open-drain`

---

# Drivers de configuración de los pines
## Estructuras de configuración
- **PINSEL_CFG_Type**
    - **uint8_t Portnum**:
      - `PINSEL_PORT_x` x de 0 a 4.
    - **uint8_t Pinnum**:
      - `PINSEL_PIN_x` x de 0 a 31.
    - **uint8_t Funcnum**:
      - `PINSEL_FUNC_x` x de 0 a 3.
    - **uint8_t Pinmode**:
      - `PINSEL_PINMODE_PULLUP`
      - `PINSEL_PINMODE_TRISTATE`
      - `PINSEL_PINMODE_PULLDOWN`
    - **uint8_t OpenDrain**:
      - `PINSEL_PINMODE_NORMAL`
      - `PINSEL_PINMODE_OPENDRAIN`

## PINSEL_ConfigPin(PinCfg)
`Configura un pin`
- **PinCfg**: Estructura de configuración.
