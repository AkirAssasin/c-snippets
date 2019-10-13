#ifndef VLARRAY_H
#define VLARRAY_H

#include <stddef.h> /* size_t, NULL */
#include <stdlib.h> /* realloc */

/* -- https://tiehu.is/blog/c1 -- */

#define VLArray(T)                \
    struct VLArray_##T {          \
        size_t size;              \
        T array[];                \
    }

#define VLArray_New(T, s)                                                           \
({                                                                                  \
    const size_t initialSize = s;                                                   \
    struct VLArray_##T *v = malloc(sizeof(VLArray(T)) + sizeof(T) * initialSize);   \
    v->size = initialSize;                                                          \
    v;                                                                              \
})

/*
#define VLArray_Resize(T, vp, s)                                                  \
({                                                                                \
    const size_t targetSize = s;                                                  \
    void *newPointer = realloc(*vp,sizeof(VLArray(T)) + sizeof(T) * targetSize);  \
    (!newPointer) ? (1) : ({                                                      \
        *vp = newPointer;                                                         \
        vp[0]->size = targetSize;                                                 \
        0;                                                                        \
    });                                                                           \
})
*/

#define VLArray_Get(v, i) (*(&v->array[i]))

/* ----- */

#endif
