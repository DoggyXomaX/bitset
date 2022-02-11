#include "bitset.h"

bitset_t *bitset_create(uint32_t size) {
    bitset_t *bitset = malloc(sizeof(bitset_t));
    bitset->bitCount = size;
    if (size & 0x07)
        bitset->data = calloc((size >> 3) + 1, sizeof(uint8_t));
    else
        bitset->data = calloc(size >> 3, sizeof(uint8_t));
    return bitset;
}

void bitset_destroy(bitset_t *bitset) {
    if (bitset) {
        if (bitset->data) free(bitset->data);
        free(bitset);
    }
}

void bitset_print(bitset_t *bitset) {
    uint32_t count = bitset->bitCount;
    while (count--) putchar('0' + (bitset->data[count >> 3] >> (count & 7) & 1));
}

void bitset_set(bitset_t *bitset, uint32_t index) {
    if (index >= bitset->bitCount) return;
    bitset->data[index>>3] |= 1 << (index & 0x07);
}

void bitset_unset(bitset_t *bitset, uint32_t index) {
    if (index >= bitset->bitCount) return;
    bitset->data[index>>3] &= ~(1 << (index & 0x07));
}

void bitset_toggle(bitset_t *bitset, uint32_t index) {
    if (index >= bitset->bitCount) return;
    bitset->data[index>>3] ^= 1 << (index & 0x07);
}

void bitset_shl(bitset_t *bitset, uint32_t offset) {
    uint32_t length = bitset->bitCount >> 3;
    if (offset >= bitset->bitCount) {
        for (uint32_t i = 0; i < length; i++) bitset->data[i] = 0;
        return;
    }

    uint32_t counter = length;
    while (counter--) {
        if (counter + 1 << 3 < offset) {
            bitset->data[counter] = 0;
            continue;
        }

        bitset->data[counter] = bitset->data[] << (offset & 0x07) | bitset->data[] << (8 - (offset & 0x07))
    }
}


// 01100000 00000---
// >> 9
// -------- -0110000
