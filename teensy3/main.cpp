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

inline static float clamp(float val)
{
	if ( val > 1 )
	{
		val = 1;
	}
	else if ( val < -1 )
	{
		val = -1;
	}

	return val;
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
static void setFutabaMC230CRSpeed(float speedClamped)
{
	speedClamped = clamp(speedClamped);

	// The Speed controller wants a frequency of 1500Hz.

	// MC230CR Speed Controller
	// High Frequency:    Yes, 1,500Hz (a period of .000666667 seconds)

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

	// Sounds like the the fastest the wheels are spinning.
	// Lower values don't seem to increase the speed (only using hearing to measure)
	const int MAX_SPEED = 36350;

	// Moving but slow
	const int MIN_SPEED = 36550;

	const int STOPPED = 63000;

	int speed = STOPPED;

	if ( speedClamped == 0 )
	{
		// TODO: Implement breaking, not just turning the motor off. Not sure how to do this but accorinding to
		// it's minimal data sheet, the speed controller can support breaking.
		speed = STOPPED;
	}
	else if ( speedClamped > 0 )
	{
		const int SPEED_RANGE = MIN_SPEED - MAX_SPEED;
		speed = MIN_SPEED - SPEED_RANGE * speedClamped;
	}
	else if ( speedClamped < 0 )
	{
		// TODO: Reverse not yet implemented. According to data sheet, it does implement reverse if in the
		// correct mode.
		speed = STOPPED;
	}

	myprint("Changing speed to %d (from clamped %f)\n", speed, speedClamped);
	FTM1_C0V = speed;

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
static void setFutabaS3003Servo(float fromCenterClamped)
{
	fromCenterClamped = clamp(fromCenterClamped);

	// From: http://mcu-programming.blogspot.com/2006/09/servo-motor-control.html
	// - Want 20ms period
	// From: Introduction to Servomotor Programming
	// - 1.0ms is one side (for a futaba S3004, not the S3003 I have) and 2.0ms is the other. 1.5ms is center.

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
	FTM0_C7V = 60000 - (4500 + (1500.0 * fromCenterClamped)); // center
	//FTM0_C7V = 60000 - 6000; // left (because it's inverted)
	//FTM0_C7V = 60000 - 3000; // right (because it's inverted)
	//FTM0_C7V = 60000 - (4500 - 500);

#else
#error need configuration for F_CPU
#endif
}

// TODO: Generalize loop_XHz. Perhap use a real time run loop that has timing information
// loop function, and initialization function, and context.

// About a 1Hz loop, depending on what everyone else is doing.
static void loop_1Hz(void)
{
	// TODO: Don't keep track of seconds... what about rollover? Perhaps that's not possible
	// with seconds and a battery, but what about higher frequency loops  using this technique.

	static int seconds = 0;
	seconds++;

	myprint("1Hz Loop: seconds: %d\n", seconds);

	switch(seconds)
	{
	case 2:
		setFutabaMC230CRSpeed(1);
		break;
	case 4:
		setFutabaMC230CRSpeed(0.5);
		break;
	case 5:
		setFutabaS3003Servo(-1.0);
		break;
	case 6:
		setFutabaS3003Servo(1.0);
		setFutabaMC230CRSpeed(0.0);
		break;
	case 7:
		setFutabaS3003Servo(0);
		break;
	case 8:
		setFutabaS3003Servo(0.2);
		break;
	case 9:
		setFutabaS3003Servo(0.4);
		break;
	}
}

static void loop_2Hz(void)
{
	// TODO: Don't keep track of half_seconds... what about rollover? Perhaps that's not possible
	// with half_seconds and a battery, but what about higher frequency loops  using this technique.

	static int half_seconds = 0;
	half_seconds++;

	myprint("2Hz Loop: seconds: %f\n", half_seconds / 2.0);

	digitalWriteFast(13, half_seconds % 2 == 0 ? HIGH : LOW);
}

static void loop_initialization(void)
{
	pinMode(3, OUTPUT); // PWM to speed controller
	pinMode(5, OUTPUT); // PWM to steering servo
	pinMode(13, OUTPUT); // Teensy LED

	// Configure pin 3. I don't know what this does, I just stole it from pins_teensy.c
	CORE_PIN3_CONFIG = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE; // from pins_teensy.c

	// Configure pin 5. I don't know what this does, I just stole it from pins_teensy.c
	CORE_PIN5_CONFIG = PORT_PCR_MUX(4) | PORT_PCR_DSE | PORT_PCR_SRE; // from pins_teensy.c

	setFutabaMC230CRSpeed(0);
	setFutabaS3003Servo(0);
}

extern "C" int main(void)
{
	loop_initialization();

	while (1) {

		// TODO: Make loop_nHz loops be more accurate by adjusting the delay to account for
		// processing time. It still won't be a gaurentee and it relies on all loop functions
		// to be good non-blocking citizens, but it may create more predictable behavior.
		
		delay(500);
		loop_2Hz();

		delay(500);
		loop_2Hz();
		loop_1Hz();

	}
}
