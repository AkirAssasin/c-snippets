#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "stacktemplate.h"

DeclareStackForType(int)
DefineStackForType(int)

int main (void) {

    Stack_int *stack = Stack_Create_int();

    for (int i = 0; i < 69; ++i) Stack_Push_int(&stack,69);
    Stack_Clear_int(&stack);

    for (int i = 0; i < 69; ++i) Stack_Push_int(&stack,i);

    int output;
    while (Stack_Pull_int(&stack,&output)) {
        printf("%d ",output);
    }

    free(stack);
    return 0;

}
