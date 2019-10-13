#include <stdio.h> /* printf, scanf */
#include "VLArray.h" /* VLArray */

int main (void) {

    printf("Create array with size: ");
    unsigned int n;

    if (scanf("%u",&n) != 1) return 1;

    VLArray(int) *vlarray = VLArray_New(int,n);
    printf("vlarray has %lu elements\n",vlarray->size);

    for (unsigned int i = 0; i < vlarray->size; ++i) {
        VLArray_Get(vlarray,i) = (int)i;
    }

    for (unsigned int i = 0; i < vlarray->size; ++i) {
        printf("Element %u: %d\n",i,VLArray_Get(vlarray,i));
    }

    free(vlarray);

    return 0;

}
