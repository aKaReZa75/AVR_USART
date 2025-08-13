This file explains USART0 error flags in UCSR0A (Frame Error, Data Overrun, and Parity Error), how to detect them, and strategies for robust recovery in high-reliability systems.

---

## **UCSR0A – USART Control and Status Register A (Error Flags)**
| Bit | Name   | Description                                      |
|-----|--------|--------------------------------------------------|
| 4   | FE0    | Frame Error: Set if a framing error is detected.                 |
| 3   | DOR0   | Data OverRun: Set if a data overrun error occurs.                |
| 2   | UPE0   | USART Parity Error: Set if a parity error is detected.           |

These flags are set when a corresponding error occurs during reception. They are cleared automatically when `UDR0` is read.

---
## **1. Frame Error (FE0)**

Occurs when the expected stop bit is not detected at the end of a received frame. This may be caused by:

- Incorrect baud rate
- Noise on the RX line
- Mismatched frame format

### **Detection:**

```c
if (bitCheck(UCSR0A, FE0)) 
{
    // Handle frame error
}
```

### **Recovery Strategy:**

- Flush the receive buffer
- Reinitialize USART if persistent
- Log error for diagnostics

```c
void handle_FrameError(void) 
{
    usart_Flush();
    // Optionally: usart_Init(baud, doubleSpeed);
}
```

---

## **2. Data Overrun (DOR0)**

Occurs when a new byte arrives before the previous one is read from `UDR0`. The old data is lost.

### **Detection:**

```c
if (bitCheck(UCSR0A, DOR0)) 
{
    // Handle overrun
}
```

### **Recovery Strategy:**

- Increase interrupt priority
- Use circular buffer for reception
- Ensure `UDR0` is read promptly in ISR

```c
ISR(USART_RX_vect) 
{
    if (bitCheck(UCSR0A, DOR0)) 
    {
        // Log or count overrun
    }
    uint8_t byte = UDR0;
    // Store byte safely
}
```

---

## **3. Parity Error (UPE0)**

Occurs when the received data does not match the expected parity. Only relevant if parity is enabled.

### **Detection:**

```c
if (bitCheck(UCSR0A, UPE0)) 
{
    // Handle parity error
}
```

### **Recovery Strategy:**

- Reconfigure parity settings
- Use checksum or CRC for critical data
- Ignore or request retransmission

---

## **Best Practices for Error Handling**

| Strategy                  | Benefit                                      |
|---------------------------|----------------------------------------------|
| Use ISR for reception     | Prevent overrun and ensure timely handling   |
| Validate flags before read| Detect and isolate corrupted data            |
| Flush buffer on error     | Clear stale or invalid data                  |
| Log error events          | Useful for debugging and reliability metrics |

---

## **Example: Robust USART Receive Handler**

```c
ISR(USART_RX_vect) 
{
    uint8_t status = UCSR0A;
    if (bitCheck(status, FE0) || bitCheck(status, DOR0) || bitCheck(status, UPE0)) 
    {
        usart_Flush(); // Clear buffer and flags
        return;        // Skip corrupted data
    }

    uint8_t byte = UDR0;
    // Process valid byte
}
```

> [!TIP]
> Always read `UCSR0A` before `UDR0` to ensure error flags are captured correctly.

---

## **Summary of Error Flags**

| Flag   | Meaning            | Cleared When `UDR0` is Read | Suggested Action         |
|--------|--------------------|-----------------------------|--------------------------|
| FE0    | Frame Error        | ✅                          | Flush, log, reinit       |
| DOR0   | Data Overrun       | ✅                          | ISR optimization         |
| UPE0   | Parity Error       | ✅                          | Parity check or ignore   |


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
