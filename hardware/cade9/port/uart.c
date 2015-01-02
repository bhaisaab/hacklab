#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "main.h"

#define BUF_SIZE	32
#define BUF_MASK	31

typedef struct buffer Buffer;

struct buffer {
	uint8_t data[ BUF_SIZE ];
	uint8_t head;
	uint8_t tail;
	uint8_t nFreePositions;
};



static Buffer rx;
static Buffer tx;
static Bool tx_active;

static rx_procedure_t rx_procedure;

/* Sets up the AVR to 38400 baud, 8 bit, no parity, one stopbit */
void uart_init(rx_procedure_t function_address)
{
	UBRRH=0;
	UBRRL=22;

	/* Enable transmitter, enable receiver, receive complete interrupt */
	UCSRB = (1<<TXEN)|(1<<RXEN)|(1<<RXCIE);

	/* 8 bit mode */
	UCSRC=(1<<URSEL)|(3<<UCSZ0);

	/* Initialize buffers */
	rx.head = 0;
	rx.tail = 0;
	rx.nFreePositions = BUF_SIZE - 1;

	tx.head = 0;
	tx.tail = 0;
	tx.nFreePositions = BUF_SIZE - 1;

	tx_active = FALSE;

    rx_procedure = function_address;
}


void uart_write(uint8_t* pBuf, uint8_t length)
{
	uint8_t nBytes = length;
	if ( length <= tx.nFreePositions )
	{
		/* Copy data to tx buffer */
		do {
		tx.data[ tx.head ] = *pBuf++;
		tx.head = ( (tx.head + 1) & BUF_MASK );
		} while ( --nBytes > 0 );
		tx.nFreePositions -= length;

		if ( ! tx_active )
		{
			/* Wait for the data register to be ready for new data */
			while (!(UCSRA & (1<<UDRE))) ;

			/* Update tail */
			uint8_t oldTail = tx.tail;
			tx.tail = ( ( oldTail + 1 ) & BUF_MASK );
			tx_active = TRUE;
			++tx.nFreePositions;

			/* Transmit first byte */
			UDR = tx.data[ oldTail ];

			UCSRB |= ( 1 << UDRIE );
		}

	}
}


ISR (USART_UDRE_vect)
{
	if ( tx.tail == tx.head )
	{
		UCSRB &= ~( 1 << UDRIE );
		tx_active = FALSE;
	}
	else
	{
		/* Update tail */
		uint8_t oldTail = tx.tail;
		tx.tail = ( ( oldTail + 1 ) & BUF_MASK );
		++tx.nFreePositions;

		/* Transmit next byte */
		UDR = tx.data[ oldTail ];
	}
}


void uart_sendChar(uint8_t c)
{
	/* Wait for the data register to be ready for new data */
	while (!(UCSRA & (1<<UDRE)))
	     ;

    /* Send the character to the serial port */
	UDR=c;
}


void uart_readChar(uint8_t *c)
{
	*c = rx.data[ rx.tail ];
	rx.tail = ( rx.tail + 1  ) & BUF_MASK;
}


ISR (SIG_UART_RECV)
{
	rx.data[ rx.head ] = UDR;
	rx.head = ( (rx.head + 1) & BUF_MASK );

    rx_procedure();

}
