#include "bitset.h"

int main() {
    bitset_t *a = bitset_create(9);

    puts("Print a:");
    bitset_print(a);
    putchar('\n');

    bitset_set(a, 2);
    puts("Print a(set 2):");
    bitset_print(a);
    putchar('\n');

    bitset_set(a, 4);
    puts("Print a(set 4):");
    bitset_print(a);
    putchar('\n');

    bitset_toggle(a, 4);
    puts("Print a(toggle 4):");
    bitset_print(a);
    putchar('\n');

    bitset_toggle(a, 4);
    puts("Print a(toggle 4):");
    bitset_print(a);
    putchar('\n');

    bitset_unset(a, 2);
    puts("Print a(unset 2):");
    bitset_print(a);
    putchar('\n');

    bitset_toggle(a, 8);
    puts("Print a(toggle 8):");
    bitset_print(a);
    putchar('\n');

    bitset_destroy(a);

    return 0;
}
