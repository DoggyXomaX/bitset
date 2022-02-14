#include "bitset.h"

bitset_t *bitset_create(uint32_t size) {
    bitset_t *bitset = malloc(sizeof(bitset_t));
    bitset->bitCount = size;
    bitset->dataLength = size >> 3;
    if (size & 0x07) bitset->dataLength++;
    bitset->data = calloc(bitset->dataLength, sizeof(uint8_t));
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
    uint32_t i = 0;
    char str[bitset->bitCount + 1];
    str[bitset->bitCount] = '\0';
    while (count--) {
        str[i] = '0' + ((bitset->data[count >> 3] >> (count & 0x07) & 0x01));
        i++;
    }
    printf("%s\n", str);
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

void bitset_set8(bitset_t *bitset, uint8_t value) {
    if (bitset->dataLength >= 1) {
        bitset->data[0] = value;
        for (uint32_t i = 1; i < bitset->dataLength; i++) bitset->data[i] = 0;
        bitset_normalize(bitset);
    }
}

void bitset_set16(bitset_t *bitset, uint16_t value) {
    if (bitset->dataLength >= 2) bitset->data[1] = value >> 8 & 0xFF;
    if (bitset->dataLength >= 1) {
        bitset->data[0] = value & 0xFF;
        for (uint32_t i = 2; i < bitset->dataLength; i++) bitset->data[i] = 0;
        bitset_normalize(bitset);
    }
}

void bitset_set32(bitset_t *bitset, uint32_t value) {
    if (bitset->dataLength >= 4) bitset->data[3] = value >> 24 & 0xFF;
    if (bitset->dataLength >= 3) bitset->data[2] = value >> 16 & 0xFF;
    if (bitset->dataLength >= 2) bitset->data[1] = value >> 8 & 0xFF;
    if (bitset->dataLength >= 1) {
        bitset->data[0] = value & 0xFF;
        for (uint32_t i = 4; i < bitset->dataLength; i++) bitset->data[i] = 0;
        bitset_normalize(bitset);
    }
}

void bitset_normalize(bitset_t *bitset) {
    switch (bitset->bitCount & 0x07) {
        case 0: break;
        case 1: bitset->data[bitset->dataLength - 1] &= 0x01;
        case 2: bitset->data[bitset->dataLength - 1] &= 0x03;
        case 3: bitset->data[bitset->dataLength - 1] &= 0x07;
        case 4: bitset->data[bitset->dataLength - 1] &= 0x0F;
        case 5: bitset->data[bitset->dataLength - 1] &= 0x1F;
        case 6: bitset->data[bitset->dataLength - 1] &= 0x3F;
        case 7: bitset->data[bitset->dataLength - 1] &= 0x7F;
    }
}

void bitset_shl(bitset_t *bitset, uint32_t offset) {
    if (offset >= bitset->bitCount) {
        for (int32_t i = 0; i < bitset->dataLength; i++) bitset->data[i] = 0;
        return;
    }

    uint32_t pre_offset = offset >> 3;
    for (int32_t i = bitset->dataLength - 1; i >= 0; i--) {
        int left_index = i - pre_offset;
        int right_index = i - pre_offset - 1;
        uint8_t left = (left_index >= 0) ? bitset->data[left_index] : 0;
        uint8_t right = (right_index >= 0) ? bitset->data[right_index] : 0;
        bitset->data[i] = left << (offset & 0x07) | right >> (8 - (offset & 0x07));
    }

    bitset_normalize(bitset);
}

void bitset_shr(bitset_t *bitset, uint32_t offset) {
    if (offset >= bitset->bitCount) {
        for (int32_t i = 0; i < bitset->dataLength; i++) bitset->data[i] = 0;
        return;
    }

    uint32_t pre_offset = offset >> 3;
    for (int32_t i = 0; i < bitset->dataLength; i++) {
        int left_index = i + pre_offset + 1;
        int right_index = i + pre_offset;
        uint8_t left = (left_index < bitset->dataLength) ? bitset->data[left_index] : 0;
        uint8_t right = (right_index < bitset->dataLength) ? bitset->data[right_index] : 0;
        bitset->data[i] = (left << (8 - (offset & 0x07))) | (right >> (offset & 0x07));
    }
}