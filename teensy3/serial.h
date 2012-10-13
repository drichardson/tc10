#ifndef _serial_h_
#define _serial_h_

#include "mk20dx128.h"

#define BAUD2DIV(baud) (((F_CPU * 2) + ((baud) >> 1)) / (baud))

#ifdef __cplusplus
extern "C" {
#endif
void serial_begin(uint32_t divisor);
void serial_write(uint8_t c);
void serial_print(const char *p);
void serial_print_uint(unsigned int n);
void serial_phex(uint32_t n);
void serial_phex16(uint32_t n);
void serial_phex32(uint32_t n);
#ifdef __cplusplus
}
#endif



#endif
