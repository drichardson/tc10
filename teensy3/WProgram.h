#ifndef WProgram_h
#define WProgram_h

#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include <avr/interrupt.h>
#include "wiring.h"

#ifdef __cplusplus

#include "avr_emulation.h"
#include "usb_serial.h"

//#include "usb_api.h"
//#include "WCharacter.h"
#include "WString.h"
//#include "HardwareSerial.h"
#include "elapsedMillis.h"

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t pin, uint16_t frequency, uint32_t duration = 0);
void noTone(uint8_t pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned int);
long map(long, long, long, long, long);

#include "pins_arduino.h"

#endif // __cplusplus

#endif // WProgram_h
