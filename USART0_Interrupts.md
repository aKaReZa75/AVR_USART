This document covers all USART0 interrupt sources: Receive Complete, Transmit Complete, and Data Register Empty. It explains how to enable them using UCSR0B, read the related flags in UCSR0A, and properly write interrupt service routines (ISR) for each case.

## **UCSR0B – USART Control and Status Register B**
| Bit  | Name     | Description                                                      |
|------|----------|------------------------------------------------------------------|
| 7    | RXCIE0   | USART Receive Interrupt Enable: Enables the USART receive interrupt. |
| 6    | TXCIE0   | USART Transmit Interrupt Enable: Enables the USART transmit interrupt. |
| 5    | UDRIE0   | USART Data Register Empty Interrupt Enable: Enables the interrupt when the data register is empty. |
| 4    | RXEN0    | Receiver Enable: Enables the USART receiver.                     |
| 3    | TXEN0    | Transmitter Enable: Enables the USART transmitter.               |
| 2    | UCSZ02   | Character Size: Defines the number of data bits for the communication. |
| 1    | RXB8     | Receive Data Bit 8: Used for 9-bit communication.                |
| 0    | TXB8     | Transmit Data Bit 8: Used for 9-bit communication.               |

## **UCSR0A – USART Control and Status Register A**

| Bit | Description |
|-----|-------------|
| 7    | RXC0     | USART Receive Complete: Set when the data is completely received. |
| 6    | TXC0     | USART Transmit Complete: Set when the data is completely transmitted. |
| 5    | UDRE0    | USART Data Register Empty: Set when the USART Data Register is empty and ready for new data. |
| 4–0 | Other status bits (not related to interrupts) |

---

## **Interrupt Sources and Usage**

### **1. Receive Complete Interrupt (RXCIE0)**

Triggered when a full character has been received and is ready to be read from `UDR0`.

```c
/* Enable Receive Complete Interrupt */
bitSet(UCSR0B, RXCIE0);

/* ISR for Receive Complete */
ISR(USART_RX_vect) 
{
    uint8_t receivedByte = UDR0;
    // Process receivedByte
}
```

- Flag: `RXC0` in `UCSR0A`
- Automatically cleared when `UDR0` is read

---

### **2. Transmit Complete Interrupt (TXCIE0)**

Triggered when the entire frame (including stop bit) has been transmitted.

```c
/* Enable Transmit Complete Interrupt */
bitSet(UCSR0B, TXCIE0);

/* ISR for Transmit Complete */
ISR(USART_TX_vect) 
{
    // Transmission is fully complete
    // You may disable transmitter or send next byte
}
```

- Flag: `TXC0` in `UCSR0A`
- Cleared by writing to `UDR0` or by reading `UCSR0A` followed by writing to `UDR0`

---

### **3. Data Register Empty Interrupt (UDRIE0)**

Triggered when `UDR0` is ready to accept new data (i.e., it's empty).

```c
/* Enable Data Register Empty Interrupt */
bitSet(UCSR0B, UDRIE0);

/* ISR for Data Register Empty */
ISR(USART_UDRE_vect)
{
    UDR0 = nextByteToSend;
}
```

- Flag: `UDRE0` in `UCSR0A`
- Cleared automatically when new data is written to `UDR0`

---

## **Interrupt Enable Summary**

| Interrupt Type       | Enable Bit | ISR Vector         | Trigger Condition         |
|----------------------|------------|---------------------|---------------------------|
| Receive Complete     | RXCIE0     | `USART_RX_vect`     | Data received in `UDR0`   |
| Transmit Complete    | TXCIE0     | `USART_TX_vect`     | Frame fully transmitted   |
| Data Register Empty  | UDRIE0     | `USART_UDRE_vect`   | `UDR0` ready for new data |

---

## **Example: Enable All USART0 Interrupts**

```c
bitSet(UCSR0B, RXCIE0);   // Enable RX interrupt
bitSet(UCSR0B, TXCIE0);   // Enable TX interrupt
bitSet(UCSR0B, UDRIE0);   // Enable Data Register Empty interrupt
globalInt_Enable;         // Enable global interrupts
```

---

## **Interrupt Flag Handling Tips**

- Flags in `UCSR0A` are mostly cleared automatically.
- Avoid polling flags when using interrupts.
- Use `globalInt_Enable` and `globalInt_Disable` macros to manage global interrupt state.

> [!CAUTION]
> Always ensure that `RXEN0` and `TXEN0` are set before enabling interrupts. Otherwise, USART hardware won’t function correctly.


# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
