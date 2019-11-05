#pragma once
#include <stdlib.h> /* rand */

void shuffle (int* _array, int _arraySize) {

    int t, i, j;

    for (i = _arraySize - 1; i > 0; i--) {

        j = rand() % i;
        t = _array[j];
        _array[j] = _array[i];
        _array[i] = t;

    }

}
