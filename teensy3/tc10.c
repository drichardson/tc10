#include "serial.h"
#include "core_pins.h"

static void myprint(const char* msg)
{
	usb_serial_write(msg, strlen(msg));
}

int main(void)
{
	_init_Teensyduino_internal_();

	//serial_begin(BAUD2DIV(9600));
	//serial_print("starting...\n");
	myprint("Hi\n");

	// Set prescaler on FTM1 to divide by 128 (and some other crap)
	FTM1_SC = FTM_SC_CLKS(1) | FTM_SC_PS(0);

	pinMode(3, OUTPUT);
	pinMode(13, OUTPUT);

#if 0
	char buf[200];
	sprintf(buf, "%u\n", FTM1_MOD);
	myprint(buf);
#endif

	//FTM1_MOD defaults to 32767
	//FTM0_MOD = 20767;
	//FTM1_MOD = 20767;
	
	analogWrite(3, 128);

	//pinMode(13, OUTPUT);
	while (1)
	{
		digitalWrite(13, HIGH);
		//myprint("on\n");
		delay(500);
		//delayMicroseconds(1000);
		digitalWrite(13, LOW);
		//myprint("off\n");
		//myprint(buf);
		delay(500);
		//delayMicroseconds(1000);
	}

	return 0;
}