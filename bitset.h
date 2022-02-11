#ifndef __BITWISE_H__
#define __BITWISE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define cshl(x,c,m) (x)<<((c)&(m))|(x)>>(s)-((c)&(m))
#define cshr(x,c,m) (x)>>((c)&(m))|(x)<<(s)-((c)&(m))

#define cshl8(x,c)  cshl(x,c,0x07)
#define cshl16(x,c) cshl(x,c,0x0F)
#define cshl32(x,c) cshl(x,c,0x1F)
#define cshr8(x,c)  cshr(x,c,0x07)
#define cshr16(x,c) cshr(x,c,0x0F)
#define cshr32(x,c) cshr(x,c,0x1F)

typedef struct {
    uint32_t bitCount;
    char *data;
} bitset_t;

bitset_t *bitset_create(uint32_t);
void bitset_destroy(bitset_t*);
void bitset_print(bitset_t*);
void bitset_set(bitset_t*, uint32_t);
void bitset_unset(bitset_t*, uint32_t);
void bitset_toggle(bitset_t*, uint32_t);

#endif
