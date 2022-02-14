#include "bitset.h"

int main() {
    bitset_t *a = bitset_create(17);

    puts("Print a:");
    bitset_print(a);

    puts("Print a(1234):");
    bitset_set16(a, 1234);
    bitset_print(a);

    bitset_shl(a, 10);
    puts("Print a(shl 10):");
    bitset_print(a);

    bitset_shr(a, 10);
    puts("Print a(shr 10):");
    bitset_print(a);

    bitset_destroy(a);

    return 0;
}
