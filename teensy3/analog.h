#ifndef _analog_h_
#define _analog_h_

#include "mk20dx128.h"

#ifdef __cplusplus
extern "C" {
#endif
int analogRead(uint8_t pin);
void analogReference(uint8_t type);
void analogReadRes(unsigned int bits);
void analog_init(void);
#ifdef __cplusplus
}
#endif


#define DEFAULT		0
#define INTERNAL	2
#define INTERNAL1V2	2
#define INTERNAL1V1	2
#define EXTERNAL	0


#endif
