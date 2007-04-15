/*
 * Karl-Martin Skontorp LA9PMA <kms@skontorp.net>
 * $Id: fRound.h 93 2006-05-22 09:30:07Z kms $
 */

#define F_CPU 8E6

#include <math.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void delay_200(void);

void delay_200() {
    uint8_t i;

    for (i = 0; i < 200; i++) {
	_delay_ms(5);
    }
}

int main(void) {
    wdt_reset();
    wdt_disable();

    PORTB = 0xff;
    PORTC = 0xff;
    PORTD = 0xff;

    //    DDRD = _BV(DDD6);
    //    DDRD |= _BV(DDD0);
    //    DDRC = 0xff;

    TWBR = 20;

    uint16_t f;
    for (;;)  {
	for (f = 2076; f < 2388;) {
	    f += 1;

	    TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTA);
	    while (!(TWCR & _BV(TWINT))) {
	    }

	    TWDR = 0xc6;
	    TWCR = _BV(TWINT) | _BV(TWEN);
	    while (!(TWCR & _BV(TWINT))) {
	    }

	    TWDR = (f & 0x7f00) >> 8;
	    //TWDR = 0x10;
	    TWCR = _BV(TWINT) | _BV(TWEN);
	    while (!(TWCR & _BV(TWINT))) {
	    }

	    TWDR = f & 0xff;
	    //TWDR = 0x87;
	    TWCR = _BV(TWINT) | _BV(TWEN);
	    while (!(TWCR & _BV(TWINT))) {
	    }

	    TWDR = 0x8e;
	    TWCR = _BV(TWINT) | _BV(TWEN);
	    while (!(TWCR & _BV(TWINT))) {
	    }

	    TWDR = 0xa0;
	    TWCR = _BV(TWINT) | _BV(TWEN);
	    while (!(TWCR & _BV(TWINT))) {
	    }

	    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);

	    delay_200();
	}
    }
}
