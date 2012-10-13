#include "mk20dx128.h"
#include "serial.h"

void serial_begin(uint32_t divisor)
{
	SIM_SCGC4 |= SIM_SCGC4_UART0;	// turn on clock
	// configure pins: transmit on PTA2 -- for use with EZ Port adaptor
	//PORTA_PCR2 = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(2);
	//GPIOA_PDDR |= (1 << 2);
	// configure pins: transmit on PTB17 -- for release PCB
	PORTB_PCR17 = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(3);
	GPIOB_PDDR |= (1 << 17);
	UART0_BDH = (divisor >> 13) & 0x1F;
	UART0_BDL = (divisor >> 5) & 0xFF;
	UART0_C4 = divisor & 0x1F;
	UART0_C1 = 0;
	UART0_C2 = UART_C2_TE;	// transmit only
	//UART0_C2 = UART_C2_TE | UART_C2_RE; // transmit and receive
	UART0_PFIFO = UART_PFIFO_TXFE | UART_PFIFO_RXFE;
}

void serial_write(uint8_t c)
{
	//GPIOB_PSOR = (1<<19); // PB19 high while waiting
	//while ((UART0_S1 & UART_S1_TDRE) == 0) /* wait */ ;
	while (UART0_TCFIFO >= 8) /* wait */ ;
	//GPIOB_PCOR = (1<<19);
	UART0_D = c;
}

void serial_print(const char *p)
{
	while (*p) {
		char c = *p++;
		if (c == '\n') serial_write('\r');
		serial_write(c);
	}
}

void serial_phex1(uint32_t n)
{
	n &= 15;
	if (n < 10) {
		serial_write('0' + n);
	} else {
		serial_write('A' - 10 + n);
	}
}

void serial_phex(uint32_t n)
{
	serial_phex1(n >> 4);
	serial_phex1(n);
}

void serial_phex16(uint32_t n)
{
	serial_phex(n >> 8);
	serial_phex(n);
}

void serial_phex32(uint32_t n)
{
	serial_phex(n >> 24);
	serial_phex(n >> 16);
	serial_phex(n >> 8);
	serial_phex(n);
}

void printNumber(uint32_t n, uint32_t base, uint8_t sign)
{
	char buf[33];
	uint32_t i, digit;

	if (base == 0) {
		serial_write(n);
		return;
	} else if (base == 1) {
		base = 10;
	}
	if (n == 0) {
		serial_write('0');
		return;
	}
	i = 32;
	while (1) {
		digit = n % base;
		buf[i] = ((digit < 10) ? '0' + digit : 'A' + digit - 10);
		n /= base;
		if (n == 0) break;
		i--;
	}
	if (sign) buf[i--] = '-';
	while (i <= 32) {
		serial_write(buf[i++]);
	}
}


