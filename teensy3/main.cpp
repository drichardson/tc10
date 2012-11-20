#include "WProgram.h"
#include <stdarg.h>
#include <stdio.h>

static void myprint(const char* msg, ...)
{
	va_list va;
	va_start(va, msg);
	char buf[512];
	vsprintf(buf, msg, va);
	usb_serial_write(buf, strlen(buf));
	va_end(va);
}

// Edge Aligned PWM. Section 35.4.6 in K20 Sub-Family Reference Manual, Rev. 2, Feb 2012
// FROM THE DOCUMENT
// The EPWM period is determined by (MOD − CNTIN + 0x0001) and the pulse
// width (duty cycle) is determined by (CnV − CNTIN).
// The CHnF bit is set and the channel (n) interrupt is generated if CHnIE = 1 at
// the channel (n) match (FTM counter = CnV), that is, at the end of the pulse width.
// This type of PWM signal is called edge-aligned because the leading edges of all
// PWM signals are aligned with the beginning of the period, which is the same for all
// channels within an FTM.
// END FROM THE DOCUMENT
static void setFutabaMC230CRSpeed(void)
{
	// The Speed controller wants a frequency of 1500Hz.

	// MC230CR Speed Controller
	// High Frequency:    Yes, 1,500Hz (a period of .000666667 seconds)
	pinMode(3, OUTPUT);

#if F_CPU == 48000000
	// config divisors: 48 MHz core, 48 MHz bus, 24 MHz flash

	// PERIOD = (MOD − CNTIN + 0x0001), in clock ticks
	// 48000000/1500 = 32000. I.e., there are 32000 clock cycles for each cycle of the speed controller clock.
	//FTM1_MOD = 32000;
	//FTM1_MOD = 32000;
	FTM1_MOD = 64000;
	FTM1_CNTIN = 1;

	// Duty cycle is determined by (CnV − CNTIN)
	FTM1_C0V = 35050; // barely turning
	FTM1_C0V = 35040; // turning slowly
	FTM1_C0V = 35020; // turning medium
	FTM1_C0V = 35000; // turning medium fast
	FTM1_C0V = 34900; // turning at what sounds like max speed
	CORE_PIN3_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;

#else
#error need configuration for F_CPU
#endif
}

extern "C" int main(void)
{
	// To use Teensy 3.0 without Arduino, simply put your code here.
	// For example:

	setFutabaMC230CRSpeed();

	pinMode(13, OUTPUT);
	int i = 0;
	while (1) {
		myprint("ok: %d\n", i++);
		digitalWriteFast(13, HIGH);
		delay(500);
		digitalWriteFast(13, LOW);
		delay(500);
	}
}

