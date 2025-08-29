/**
 * @file     usart.c
 * @brief    USART (Universal Synchronous and Asynchronous serial Receiver and Transmitter) Library
 * @note     This file provides functions to manage USART communication for AVR microcontrollers, 
 *           specifically for the ATmega328 microcontroller.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations of this library, along with additional notes and examples of usage, 
 *           please visit the following repository:
 *           https://github.com/aKaReZa75/AVR_USART
 */
#include "usart.h"


/* USART Flags */
bool usart_RxFlag      = false; /**< True: Data has been received completely */     
bool usart_RxBUfferOVF = false; /**< True: Receive buffer overflow occurred */
bool usart_errFlag     = false; /**< True: An error occurred during communication */

/* Index to keep track of the next available space in the receive buffer */
uint8_t bufferIndex    = 0; 
/* Buffer to store received data, with defined size */
char usart_RxBuffer[__usart_RxBufferSize]; 


/**
 * @brief Initializes the USART module.
 * 
 * This function configures the USART for asynchronous communication with the following settings:
 * - Baud Rate: 115200
 * - 8 data bits
 * - No parity
 * - 1 stop bit
 * - Double speed mode
 * - Enables the receiver and transmitter, along with interrupts for receiving data.
 * 
 * @param _initStatus If true, the USART module is initialized; if false, it is disabled.
 */
void usart_Init(bool _initStatus)
{
    if(_initStatus)
    {       
        /* Configure USART for Asynchronous mode */
        bitClear(UCSR0C, UMSEL01);
        bitClear(UCSR0C, UMSEL00);
        /* Disable Parity */
        bitClear(UCSR0C, UPM01);
        bitClear(UCSR0C, UPM00);
        bitClear(UCSR0C, USBS0);  /**< Stop bit = 1 */
        /* Set Data Bits to 8 */
        bitClear(UCSR0B, UCSZ02);
        bitSet  (UCSR0C, UCSZ01);
        bitSet  (UCSR0C, UCSZ00);
        bitSet  (UCSR0B, TXEN0);  /**< Enable Transmit Mode */
        bitSet  (UCSR0B, RXEN0);  /**< Enable Receive Mode */
        bitSet  (UCSR0B, RXCIE0); /**< Enable Receive Intrrupts */
        bitSet  (UCSR0A, U2X0);   /**< Double Speed Mode */
        /* Set Baud Rate to 115200 */
        UBRR0H = 0;
        UBRR0L = 16; 
        usart_Flush();
    }
    else
    {    
        /* Disable USART and reset configuration */   
        bitClear(UCSR0C, UMSEL01);
        bitClear(UCSR0C, UMSEL00);
        bitClear(UCSR0C, UPM01);
        bitClear(UCSR0C, UPM00);
        bitClear(UCSR0C, USBS0);  
        bitClear(UCSR0B, UCSZ02);
        bitClear(UCSR0C, UCSZ01);
        bitClear(UCSR0C, UCSZ00);
        bitClear(UCSR0B, TXEN0);  
        bitClear(UCSR0B, RXEN0); 
        bitClear(UCSR0B, RXCIE0); 
        bitClear(UCSR0A, U2X0);  
        UBRR0H = 0;
        UBRR0L = 0; 
    };
};


/**
 * @brief USART Receive Interrupt Service Routine.
 * 
 * This interrupt service routine handles data reception, checks for errors (buffer overflow or framing errors), 
 * and stores the received data in the USART receive buffer.
 *
 * @note **Important**: For the interrupt to work, `globalInt_Enable` must be called to enable global interrupts. 
 *       Alternatively, you can set the I-bit (Interrupt Enable) in the `SREG` (Status Register) manually by writing `1` to the I-bit.
 */
ISR(USART_RX_vect)
{
    uint8_t _RxData;
    usart_errFlag = false;

    /* Check for reception errors (Buffer Overflow, Framing Errors, Data Overrun) */
    usart_errFlag = usart_RxBUfferOVF | usart_frameError | usart_daraOverRun;

    _RxData = UDR0; /**< Read received data from the USART data register */

    if(!usart_errFlag)
    {
        if(_RxData == '\n')
        {
            /* End of string: Add null-terminator and set flag */
            usart_RxBuffer[bufferIndex++] = '\0';
            usart_RxFlag = true;
        }
        else
        {
            if(_RxData != '\r')
            {
                /* Store the received byte in buffer */
                usart_RxBuffer[bufferIndex++] = _RxData;
                if(bufferIndex > __usart_RxBufferSize) usart_RxBUfferOVF = true;
            };
        };
    };
};


/**
 * @brief Transmits a byte of data via USART.
 * 
 * This function waits for the USART data register to be ready and then sends a byte of data.
 * 
 * @param _Data The byte of data to transmit.
 */
void usart_Write(uint8_t _Data)
{
    /* Wait until the data register is ready for new data */
    bitWaitHigh(UCSR0A, UDRE0);
    UDR0 = _Data;
    /* Wait until transmission is complete */
    bitWaitHigh(UCSR0A, TXC0);
};


/**
 * @brief Sends a null-terminated string via USART.
 * 
 * This function transmits each byte of the string sequentially until the null terminator ('\0') is encountered.
 * 
 * @param _Data A pointer to the null-terminated string to be transmitted.
 */
void usart_Puts(char* _Data)
{
    while(*_Data != '\0')  usart_Write(*_Data++);
};


/**
 * @brief Sends a null-terminated string followed by a newline via USART.
 * 
 * This function transmits the string, followed by carriage return (`\r`) and newline (`\n`) characters.
 * 
 * @param _Data A pointer to the null-terminated string to be transmitted, followed by newline.
 */
void usart_Putsln(char* _Data)
{
    usart_Puts(_Data);
    usart_Write('\r');  /**< Carraige Return (CR) */
    usart_Write('\n');  /**< NewLine (NL) */
};


/**
 * @brief Receives a byte of data from USART.
 * 
 * This function blocks until data is received. It waits for the data to be available in the USART receive buffer.
 * 
 * @return The byte of received data.
 */
uint8_t usart_getChar(void)
{
    /* Wait for data to be received */
    bitWaitHigh(UCSR0A, RXC0);    
    return UDR0;
};


/**
 * @brief Clears the USART receive and transmit buffers.
 * 
 * This function flushes the receive buffer, clears the buffer index, and resets error flags.
 */
void usart_Flush(void)
{
    uint8_t _Index = 0;
    
    /* Clear the receive buffer */
    for(_Index = 0; _Index < __usart_RxBufferSize; _Index++)
    {
        usart_RxBuffer[_Index] = '\0';
    };

    /* Reset flags and buffer index */
    bufferIndex = 0;
    usart_RxBUfferOVF = false;
    usart_RxFlag      = false;
    usart_errFlag     = false;
};
