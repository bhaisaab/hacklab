#include <avr/io.h>
#include <avr/interrupt.h>
#include "cocoos.h"

//16Mhz Clock
#define CPU_CLOCK 16000000
#define N_PRESCALER_VALUES 5

const uint8_t prescaler[] = { 0, 3, 6, 8, 10};
static uint8_t counterValue;

void clock_init(uint32_t tick_ms) {
	uint32_t nPulses;
	TCCR0=0x00;
	uint8_t i = 0;
	do {
        nPulses = ( CPU_CLOCK * tick_ms / 1000 ) / (1 << prescaler[ i ]);
		if (( 0 < nPulses ) && ( nPulses < 256 )) {
			counterValue = 256 - nPulses;
			break;
		}
	} while ( ++i < N_PRESCALER_VALUES  );

	if ( i < N_PRESCALER_VALUES ) {
		TCNT0 = counterValue;
		TCCR0 = ( (i+1) << CS00 );
	}
	else {
		TCNT0 = 0;
		TCCR0 = (5 << CS00 );
	}

	TIMSK=(1<<TOIE0);	/* Timer Overflow Interrupt Enabled */
}



ISR(SIG_OVERFLOW0) {
	TCNT0 = counterValue;
    os_tick();
}
