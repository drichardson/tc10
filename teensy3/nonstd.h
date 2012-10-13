#ifndef _nonstd_h_
#define _nonstd_h_

#ifdef __cplusplus
extern "C" {
#endif
char * ultoa(unsigned long val, char *buf, int radix);
char * ltoa(long val, char *buf, int radix);
static inline char * utoa(unsigned int val, char *buf, int radix) __attribute__((always_inline, unused));
static inline char * utoa(unsigned int val, char *buf, int radix) { return ultoa(val, buf, radix); }
static inline char * itoa(int val, char *buf, int radix) __attribute__((always_inline, unused));
static inline char * itoa(int val, char *buf, int radix) { return ltoa(val, buf, radix); }
#ifdef __cplusplus
}
#endif

#endif
