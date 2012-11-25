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
	// NOTE: The output of pin 3 is being inverted by the PNP transistor attached to the open
	// collector output on the SN7417N Hex Buffer/Driver. This is why decreasing the duty cycle
	// on pin3 actually makes the speed controller go faster, since the speed controllers duty cycle
	// is increasing.
	FTM1_C0V = 35050; // barely turning
	FTM1_C0V = 35040; // turning slowly
	FTM1_C0V = 35020; // turning medium
	FTM1_C0V = 35000; // turning medium fast
	FTM1_C0V = 34900; // turning at what sounds like max speed
	CORE_PIN3_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE; // from pins_teensy.c

#else
#error need configuration for F_CPU
#endif
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
static void setFutabaS3003Servo(void)
{
	// From: http://mcu-programming.blogspot.com/2006/09/servo-motor-control.html
	// - Want 20ms period
	// From: Introduction to Servomotor Programming
	// - 1.0ms is one side (for a futaba S3004, not the S3003 I have) and 2.0ms is the other. 1.5ms is center.
	pinMode(5, OUTPUT);

#if F_CPU == 48000000
	// config divisors: 48 MHz core, 48 MHz bus, 24 MHz flash

	// PERIOD = (MOD − CNTIN + 0x0001), in clock ticks
	// A 20ms period means (1/0.02) = 50 Hz
	// 48000000/50 = 960000. I.e., there are 960000 clock cycles for each cycle of the speed controller clock.
	// Since 960000 is more than the 16-bit FTM counter can handle, set the pre-scaler to 4 so that it
	// takes 16 clock ticks to increment the FTM counter. That means we have
	// (48000000/16)/50 = 60000
	// To get a 1.5ms pulse, we need 1.5/20*60000 = 4500
	// To get a 1.0ms pulse (left), we need 1/20*60000 = 3000
	// To get a 2.0ms pulse (right), we need 2/20*60000 = 6000
	FTM0_SC = FTM_SC_CLKS(1) | FTM_SC_PS(4);
	FTM0_MOD = 60000;
	FTM0_CNTIN = 1;

	// Duty cycle is determined by (CnV − CNTIN)
	// NOTE: The duty cycle must be inverted because of the PNP transistor on the open collector of the
	// Hex Buffer driver I'm using.
	FTM0_C7V = 60000 - 4500; // center
	//FTM0_C7V = 60000 - 6000; // left (because it's inverted)
	//FTM0_C7V = 60000 - 3000; // right (because it's inverted)
	//FTM0_C7V = 60000 - (4500 - 500);

	CORE_PIN5_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE; // from pins_teensy.c

#else
#error need configuration for F_CPU
#endif
}

extern "C" int main(void)
{
	// To use Teensy 3.0 without Arduino, simply put your code here.
	// For example:

	setFutabaMC230CRSpeed();
	setFutabaS3003Servo();

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

