#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "vectortemplate.h"

DeclareVectorForType(int)
DefineVectorForType(int)

int main (void) {

    Vector_int vector;
    Vector_Init_int(&vector);

    for (int i = 0; i < 69; ++i) Vector_Add_int(&vector,69);
    Vector_CleanUp_int(&vector);

    for (int i = 0; i < 69; ++i) Vector_Add_int(&vector,i);

    for (int i = 0; i < Vector_GetCount_int(&vector); ++i) {
        printf("%d ",Vector_GetAt_int(&vector,i));
    }

    Vector_CleanUp_int(&vector);
    return 0;

}
