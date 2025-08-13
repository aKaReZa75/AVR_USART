This section provides a detailed description of the functions in the `usart.h` file for handling USART communication on the ATmega328 microcontroller. Each function is designed to manage data transmission and reception through USART, as well as configure the necessary registers.

> [!NOTE]  
> The library and all of its APIs provided below have been developed by myself.  
This library utilizes various macros defined in the `aKaReZa.h` header file, which are designed to simplify bitwise operations and register manipulations.    
Detailed descriptions of these macros can be found at the following link:  
> [https://github.com/aKaReZa75/AVR/blob/main/Macros.md](https://github.com/aKaReZa75/AVR/blob/main/Macros.md)

### Default Settings
| Setting           | Value                 |
|-------------------|-----------------------|
| CPU Frequency     | 16 MHz                |
| Baud Rate         | 115200                |
| Data Bits         | 8 bits                |
| Parity            | None (No Parity)      |
| Stop Bits         | 1 stop bit            |
| Receive Method    | Interrupt-based (Default) |

### **Initialization**
```c
void usart_Init(bool _initStatus);
```
 * Initializes the USART module.
 * This function must be called before any other USART function.
 * It configures the baud rate, frame format, and enables both the transmitter and receiver.
 * @param `_initStatus`:  
   - If `_initStatus` is set to `Initialize`, the USART module will be configured and enabled.
   - If `_initStatus` is set to `deInitialize`, the USART module will be disabled and deinitialized. 
  
> [!NOTE]
To modify the default settings (such as baud rate, data bits, stop bits, parity, etc.), 
the corresponding registers within the UCSR0A, UCSR0B, and UCSR0C registers can be adjusted 
according to the desired configuration. This will allow you to customize the USART settings
for specific use cases.

**Example:**
```c
#include "aKaReZa.h"
#include "usart.h"

int main(void) 
{
    usart_Init(Initialize); /**< Initialize USART with default settings */
    while(1)
    {
        /* ... your code ... */
    }
}
```

### **Transmit Data**
```c
void usart_Write(uint8_t _Data);
```
 * Writes a byte of data to the USART data register.
 * This function waits for the USART data register to be empty before transmitting.
 * @param `_Data`: The byte of data to transmit.
 
**Example:**
```c
#include "aKaReZa.h"
#include "usart.h"

int main(void) 
{
    usart_Init(Initialize); /**< Initialize USART */
    usart_Write('A'); /**< Transmit the character 'A' */
    
    while(1)
    {
        /* ... your code ... */
    }
}
```

### **Send String**
```c
void usart_Puts(char* _Data);
```
 * Sends a null-terminated string over USART.
 * The string is transmitted byte by byte until the null terminator is reached.
 * @param `_Data`: The null-terminated string to be transmitted.
 
**Example:**
```c
#include "aKaReZa.h"
#include "usart.h"

int main(void) 
{
    usart_Init(Initialize); /**< Initialize USART */
    usart_Puts("Hello, USART!"); /**< Send a string */
    
    while(1)
    {
        /* ... your code ... */
    }
}
```

### **Send String with Null-terminated**
```c
void usart_Putsln(char* _Data);
```

 * Sends a null-terminated string over USART followed by a carriage return (CR) and newline (NL) character.
 * This is useful for protocols that require both carriage return and line break after each message.
 * @param `_Data`: The null-terminated string to be transmitted, followed by a carriage return and newline.

**Example:**
```c
#include "aKaReZa.h"
#include "usart.h"

int main(void) 
{
    usart_Init(Initialize); /**< Initialize USART */
    usart_Putsln("Hello, world!"); /**< Send string with carriage return and newline */
    while(1)
    {
        /* Your main loop code here */
    }
}
```

### **Receive Data**
```c
uint8_t usart_getChar(void);
```

 * Waits for incoming data and returns one byte of data.
 * This function blocks until the data is received.
 * @return The received byte of data.

**Example:**
```c
#include "aKaReZa.h"
#include "usart.h"
#include "alcd.h"

uint8_t receivedData = 0x00;

int main(void) 
{
    alcd_init(); /**< Initialize the LCD */    
    usart_Init(Initialize); /**< Initialize USART */

    while(1)
    {
        uint8_t receivedData = usart_getChar(); /**< Receive one byte of data */
        alcd_putc(receivedData); /**< Print Receive data from usart to the LCD */    
    }
}
```

### **Flush Buffers**
```c
void usart_Flush(void);
```

 * Clears the USART receive and transmit buffers.
 * This function ensures that any leftover or unprocessed data is cleared.
 * It can be used to maintain data integrity by flushing the buffers before starting new transmission.

**Example:**
```c
#include "aKaReZa.h"
#include "usart.h"

int main(void) 
{
    usart_Init(Initialize); /**< Initialize USART */
    usart_Flush(); /**< Flush USART buffers */
    
    while(1)
    {
        /* ... your code ... */
    }
}
```

## USART Receive Interrupt and Ring Buffer

By default, USART communication in this library is configured to receive data using interrupts. When data is received, the USART Receive Interrupt Service Routine (ISR) is triggered, and the received data is stored in a **ring buffer**. This buffer is pre-configured with a default size of **32 bytes** for data, plus **1 byte** for the null terminator, making the total buffer size **33 bytes**. This size is defined in the `usart.h` file.

### Buffer Configuration

The buffer for storing received data is declared as:

```c
char usart_RxBuffer[__usart_RxBufferSize];
```
Where the default buffer size is set by `__usart_RxBufferSize` (32 bytes + 1 by default).

> [!CAUTION]
The buffer size should be chosen carefully to ensure that enough space is available to store the received data without losing any. However, it is equally important to avoid allocating excessive memory, as SRAM is limited on microcontrollers. A well-balanced buffer size ensures that you can handle incoming data efficiently while optimizing memory usage.

### Flag and Buffer Usage

To use the receive buffer in your code, you need to declare the following variables as `extern` in the file where you want to access the received data:

```c
extern bool usart_RxFlag;  
extern char usart_RxBuffer[__usart_RxBufferSize];  
```

The `usart_RxFlag` flag is set to `true` when a complete line of data has been received. This happens when the USART ISR detects the end of the received data, which is marked by either a **newline (`\n`)** or **carriage return (`\r`)**, or both.

### How to Read Data

The USART receive interrupt works by checking if any errors occur (such as buffer overflow, framing errors, or data overrun). If there are no errors, the received byte is stored in the `usart_RxBuffer` until a newline (`\n`) or carriage return (`\r`) is encountered, at which point the data is considered complete.

If the buffer is full, the `usart_RxBUfferOVF` flag will be set to `true` to indicate that the buffer overflowed and some data might have been lost.

Once the `usart_RxFlag` is set to `true`, the data can be read from the `usart_RxBuffer`:

```c
if(usart_RxFlag) 
{
    /* Process the received data
       Example: Print the received data to the LCD */
    alcd_puts(usart_RxBuffer);
    
    usart_Flush();  /* Clears the flag and the buffer, preparing for new data */
}
```

> [!CAUTION]
Always ensure that global interrupts are enabled using the `sei()` function. Without enabling global interrupts, the microcontroller will not respond to any interrupt triggers.  
The `sei()` function sets the Global Interrupt Flag (I-bit) in the Status Register (SREG), which allows interrupt requests to be processed by the microcontroller.

You can use the following macros to enable and disable global interrupts:

- **`globalInt_Enable`**: This macro is equivalent to calling `sei()`. It enables global interrupts, allowing the microcontroller to respond to interrupt requests.

- **`globalInt_Disable`**: This macro is equivalent to calling `cli()`. It disables global interrupts, preventing the microcontroller from processing any interrupts.


The data is stored in `usart_RxBuffer` and can be processed as needed. Each new line of data will overwrite the previous content in the buffer. The buffer will continue to receive new data as long as the USART interrupt routine is running. After processing the data, calling `usart_Flush()` will clear the buffer and reset the flag, preparing the system to receive the next set of data without any issues.

### Summary
| Function         | Description                                                    |
|------------------|----------------------------------------------------------------|
| `usart_Init`     | Initializes the USART peripheral|
| `usart_Write`    | Transmits a single byte of data via USART. |
| `usart_Puts`     | Sends a null-terminated string over USART.  |
| `usart_Putsln`   | Sends a null-terminated string followed by carriage return and newline characters |
| `usart_getChar`  | Receives a byte of data from USART. Blocks until data is received. |
| `usart_Flush`    | Clears the receive buffer, resets buffer index, and clears error flags. |

## Complete Example
```c
#include "aKaReZa.h"
#include "usart.h"

extern bool usart_RxFlag;  
extern char usart_RxBuffer[__usart_RxBufferSize];  

int main(void) 
{
    usart_Init(true); /**< Initialize USART */
    
    usart_Putsln("Hello, world with carriage return and newline!"); /**< Send string with CR and NL */
    
    while(1)
    {
        if(usart_RxFlag) 
        {
            /* Process the received data
               Example: Print the received data to the LCD */
            alcd_puts(usart_RxBuffer);
            
            usart_Flush();  /* Clears the flag and the buffer, preparing for new data */
        }
    }
}
```

## Important Notes
- Always ensure that the baud rate is correctly configured.
- For string transmission, ensure the string is properly null-terminated (`'\0'`) to prevent incorrect transmission behavior.
- **usart_frameError**: Checks if a framing error has occurred in the USART communication.
- **usart_daraOverRun**: Checks if a data overrun error has occurred.
These macros help you detect communication errors related to framing and data overrun.
- **Receive with Interrupts**: Data is received via interrupts, which ensures that the USART can asynchronously collect data.
- **Ring Buffer**: The received data is stored in a ring buffer (`usart_RxBuffer`) with a default size of 32 bytes. You can modify the buffer size in `usart.h` if needed.
- **Flag Usage**: The `usart_RxFlag` is used to indicate when a complete line of data is received. You should check this flag before reading data from the buffer.
- **Termination Characters**: The received data is considered complete when a newline (`\n`) or carriage return (`\r`) character is encountered. You can adjust this based on your communication protocol's requirements.


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
