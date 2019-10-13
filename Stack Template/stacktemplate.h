#ifndef STACKTEMPLATE_H
#define STACKTEMPLATE_H

#include <stdlib.h> /* malloc, free */

/* ----- */

#define DefineStackForType(T)                            \
    typedef struct Stack_##T Stack_##T;                  \
    struct Stack_##T {                                   \
        T value;                                         \
        Stack_##T *nextInStack;                          \
    };                                                   \
    Stack_##T *Stack_Create_##T (void);                  \
    void Stack_Push_##T (Stack_##T **_stack, T _in);     \
    int Stack_Pull_##T (Stack_##T **_stack, T *_out);    \
    void Stack_Clear_##T (Stack_##T **_stack);     

#define DeclareStackForType(T)                           \
    Stack_##T *Stack_Create_##T (void) {                 \
        Stack_##T *stack = malloc(sizeof(Stack_##T));    \
        stack->nextInStack = NULL;                       \
        return stack;                                    \
    }                                                    \
    void Stack_Push_##T (Stack_##T **_stack, T _in) {    \
        Stack_##T *push = malloc(sizeof(Stack_##T));     \
        if (!push) return;                               \
        push->value = _in;                               \
        push->nextInStack = *_stack;                     \
        *_stack = push;                                  \
    }                                                    \
    int Stack_Pull_##T (Stack_##T **_stack, T *_out) {   \
        Stack_##T *nextInStack = (*_stack)->nextInStack; \
        if (nextInStack == NULL) return 0;               \
        *_out = (*_stack)->value;                        \
        free(*_stack);                                   \
        *_stack = nextInStack;                           \
        return 1;                                        \
    }                                                    \
    void Stack_Clear_##T (Stack_##T **_stack) {          \
        Stack_##T *nextInStack = (*_stack)->nextInStack; \
        while (nextInStack != NULL) {                    \
            free(*_stack);                               \
            *_stack = nextInStack;                       \
            nextInStack = (*_stack)->nextInStack;        \
        }                                                \
    }

/* ----- */

#endif
