#include "WProgram.h"

int main(void)
{
	_init_Teensyduino_internal_();

#if !defined(ARDUINO)

	// To use Teensy 3.0 without Arduino, simply put your code here.
	// For example:

	pinMode(13, OUTPUT);
	while (1) {
		digitalWrite(13, HIGH);
		delay(500);
		digitalWrite(13, LOW);
		delay(500);
	}


#else
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
	}
#endif
}

#ifdef USB_SERIAL
usb_serial_class Serial;
#endif
