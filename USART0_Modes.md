This document provides a detailed explanation of all operating modes for USART0, including Asynchronous, Synchronous modes, along with the register configurations required and timing implications for each.

## **UCSR0C (USART Control and Status Register C)**
| Bit  | Name     | Description                                                      |
|------|----------|------------------------------------------------------------------|
| 7    | UMSEL01  | USART Mode Select 1: Defines the USART mode (Asynchronous/Synchronous). |
| 6    | UMSEL00  | USART Mode Select 0: Defines the USART mode (Asynchronous/Synchronous). |
| 5    | UPM01    | Parity Mode 1: Defines parity bit mode (Even/Odd/None).          |
| 4    | UPM00    | Parity Mode 0: Defines parity bit mode (Even/Odd/None).          |
| 3    | USBS0    | Stop Bit Select: Defines the number of stop bits.                |
| 2    | UCSZ01   | Character Size 1: Defines the data frame size.                   |
| 1    | UCSZ00   | Character Size 0: Defines the data frame size.                   |
| 0    | UCPOL0   | Clock Polarity: Defines the clock polarity in synchronous mode. |

### **UMSEL01/UMSEL00 (USART Mode Select)**
These bits define the operating mode of USART0:

| **Mode** | **UMSEL01** | **UMSEL00** | **Operation Mode**     | **Clock Source** | **UCPOL0 Usage** | **Timing Characteristics** |
|----------|-------------|-------------|-------------------------|------------------|------------------|-----------------------------|
| 0        | 0           | 0           | Asynchronous USART      | Internal         | Ignored          | Baud rate via UBRR         |
| 1        | 0           | 1           | Synchronous USART       | External         | Used             | Baud rate via UBRR         |
| 3        | 1           | 1           | Master SPI Mode         | Internal         | Used             | SPI-style synchronous       |

> [!CAUTION]
Mode 2 (UMSEL01 = 1, UMSEL00 = 0) is reserved and should not be used.

---

### **Mode 0: Asynchronous USART**

This is the default mode. Data is transmitted and received without a clock signal. Baud rate is controlled by the UBRR0 register.

```c
/* Configure USART0 for Asynchronous Mode */
bitClear(UCSR0C, UMSEL00);
bitClear(UCSR0C, UMSEL01);
```

- Ideal for standard serial communication (e.g., UART).
- UCPOL0 is ignored.
- Baud rate = F_CPU / (16 * (UBRR0 + 1))

---

### **Mode 1: Synchronous USART**

In this mode, USART0 uses an external clock signal for data transmission. UCPOL0 controls the clock polarity.

```c
/* Configure USART0 for Synchronous Mode */
bitSet(UCSR0C, UMSEL00);
bitClear(UCSR0C, UMSEL01);
```

- Suitable for short-distance high-speed communication.
- UCPOL0 = 0 → Rising edge transmit, falling edge receive  
- UCPOL0 = 1 → Falling edge transmit, rising edge receive

```c
/* Set clock polarity */
bitChange(UCSR0C, UCPOL0, desiredPolarity);
```

## **Additional Configuration Tips**
- **Character Size**: Use UCSZ01 and UCSZ00 to set data frame size (5 to 9 bits).
- **Stop Bits**: USBS0 = 0 → 1 stop bit, USBS0 = 1 → 2 stop bits.
- **Parity**: UPM01/UPM00 control parity (None, Even, Odd).

```c
/* Example: 8-bit data, no parity, 1 stop bit */
bitSet(UCSR0C, UCSZ01);
bitSet(UCSR0C, UCSZ00);
bitClear(UCSR0C, UPM01);
bitClear(UCSR0C, UPM00);
bitClear(UCSR0C, USBS0);
```

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
