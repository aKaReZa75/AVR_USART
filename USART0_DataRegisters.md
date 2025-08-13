This document provides a detailed description of UDR0 operation, including how data is buffered for transmission and reception, timing considerations, and tips for avoiding data loss.

## **UDR0 – USART Data Register**
| Bit  | Name     | Description                                                      |
|------|----------|------------------------------------------------------------------|
| 7-0  | UDR0     | Data: Holds the data byte being transmitted or received.         |

The `UDR0` register serves as the interface for both sending and receiving data via USART0. It is connected to two internal buffers:

- **Transmit Buffer**: Holds data to be sent.
- **Receive Buffer**: Holds the most recently received byte.

---

## **Transmission via UDR0**

To send data, write a byte to `UDR0` when the transmit buffer is empty. This is indicated by the `UDRE0` flag in `UCSR0A`.

```c
/* Wait until transmit buffer is empty */
bitWaitLow(UCSR0A, UDRE0);

/* Load data into UDR0 */
UDR0 = dataByte;
```

> [!NOTE]
> Writing to `UDR0` when `UDRE0` is not set may overwrite unsent data.

### **Best Practice:**

Use the Data Register Empty interrupt (`UDRIE0`) to automate transmission:

```c
ISR(USART_UDRE_vect) 
{
    UDR0 = nextByte;
}
```

---

## **Reception via UDR0**

When a byte is received, it is placed into the receive buffer and the `RXC0` flag in `UCSR0A` is set. Reading `UDR0` retrieves the byte and clears the flag.

```c
/* Wait until data is received */
bitWaitLow(UCSR0A, RXC0);

/* Read received byte */
uint8_t receivedByte = UDR0;
```

> [!CAUTION]
> If new data arrives before the previous byte is read, the old data will be lost.

---

## **Timing Considerations**

| Condition                  | Action Required                     |
|---------------------------|--------------------------------------|
| `UDRE0 = 1`               | Safe to write to `UDR0`              |
| `RXC0 = 1`                | Data available in `UDR0`             |
| `TXC0 = 1`                | Transmission complete (optional)     |

### **Avoiding Data Loss**

- Always check `RXC0` before reading `UDR0`.
- Use interrupts for reception (`RXCIE0`) to avoid missing data.
- Flush the receive buffer before starting new communication:

---

## **Example: Simple Echo Program**

```c
void usart_Echo(void) 
{
    if (bitCheckHigh(UCSR0A, RXC0)) 
    {
        uint8_t byte = UDR0;
        bitWaitLow(UCSR0A, UDRE0);
        UDR0 = byte;
    }
}
```

This function reads a received byte and immediately sends it back.

---

## **Interrupt-Based Reception**

```c
ISR(USART_RX_vect) 
{
    uint8_t byte = UDR0;
    // Store or process byte
}
```

Using interrupts ensures no data is missed, even at high baud rates.

---

## **Summary of Flags Related to UDR0**

| Flag    | Register | Meaning                          | Cleared When             |
|---------|----------|----------------------------------|--------------------------|
| `RXC0`  | UCSR0A   | Data received                    | After reading `UDR0`     |
| `UDRE0` | UCSR0A   | Transmit buffer empty            | After writing to `UDR0`  |
| `TXC0`  | UCSR0A   | Transmission complete            | After writing to `UDR0`  |

> [!TIP]
> Use `TXC0` only if you need to know when the last bit has been sent (e.g., before disabling transmitter).


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
