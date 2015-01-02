#ifndef UART_H
#define UART_H

/* A function pointer to user defined procedure that will be called by the RX ISR*/
typedef void (*rx_procedure_t) (void);

void uart_init( rx_procedure_t rx_function );
void uart_sendChar( uint8_t c );
void uart_readChar( uint8_t *c );
void uart_write( uint8_t* pBuf, uint8_t length );

#endif
