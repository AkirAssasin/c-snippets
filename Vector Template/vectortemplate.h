#ifndef VECTORTEMPLATE_H
#define VECTORTEMPLATE_H

#include <stdlib.h>

#define VECTOR_INIT_SIZE 4

#define DeclareVectorForType(T)                                       \
    typedef struct Vector_##T {                                       \
        T* itemArray;                                                 \
        int allocatedSize;                                            \
        int currentSize;                                              \
    } Vector_##T;                                                     \
    void Vector_Init_##T (Vector_##T *_vector);                       \
    int Vector_GetCount_##T (Vector_##T *_vector);                    \
    void Vector_Resize_##T (Vector_##T *_vector, int _newSize);       \
    void Vector_Add_##T (Vector_##T *_vector, T _item);               \
    void Vector_SetAt_##T (Vector_##T *_vector, int _index, T _item); \
    T Vector_GetAt_##T (Vector_##T *_vector, int _index);             \
    void Vector_DeleteAt_##T (Vector_##T *_vector, int _index);       \
    void Vector_Delete_##T (Vector_##T *_vector, T _item);            \
    void Vector_Reverse_##T (Vector_##T *_vector);                    \
    int Vector_Contain_##T (Vector_##T *_vector, T _item);            \
    void Vector_CleanUp_##T (Vector_##T *_vector);

#define DefineVectorForType(T)                                                \
    void Vector_Init_##T (Vector_##T *_vector) {                              \
	    _vector->allocatedSize = VECTOR_INIT_SIZE;                            \
	    _vector->currentSize = 0;                                             \
	    _vector->itemArray = malloc(sizeof(T) * (unsigned long)_vector->allocatedSize);      \
    }                                                                         \
    int Vector_GetCount_##T (Vector_##T *_vector) {                           \
	    return _vector->currentSize;                                          \
    }                                                                         \
    void Vector_Resize_##T (Vector_##T *_vector, int _newSize) {              \
	    T* newArray = realloc(_vector->itemArray, sizeof(T) * (unsigned long)_newSize);      \
	    if (newArray) {                                                       \
            _vector->itemArray = newArray;                                    \
            _vector->allocatedSize = _newSize;                                \
        }                                                                     \
    }                                                                         \
    void Vector_Add_##T (Vector_##T *_vector, T _item) {                      \
	    if (_vector->allocatedSize == _vector->currentSize) {                 \
		    Vector_Resize_##T (_vector, _vector->allocatedSize + 1);          \
        }                                                                     \
        _vector->itemArray[_vector->currentSize++] = _item;                   \
    }                                                                         \
    void Vector_SetAt_##T (Vector_##T *_vector, int _index, T _item) {        \
        _vector->itemArray[_index] = _item;                                   \
	}                                                                         \
    T Vector_GetAt_##T (Vector_##T *_vector, int _index) {                    \
        return _vector->itemArray[_index];                                    \
	}                                                                         \
    void Vector_DeleteAt_##T (Vector_##T *_vector, int _index) {              \
        for (int i = _index; i < _vector->currentSize - 1; ++i) {             \
		    _vector->itemArray[i] = _vector->itemArray[i + 1];                \
	    }                                                                     \
        --(_vector->currentSize);                                             \
	    Vector_Resize_##T (_vector, _vector->currentSize);                    \
    }                                                                         \
    void Vector_Delete_##T (Vector_##T *_vector, T _item) {                   \
        for (int i = 0; i < _vector->currentSize; ++i) {                      \
		    if (_vector->itemArray[i] == _item) {                             \
			    Vector_DeleteAt_##T(_vector,i);                               \
			    return;                                                       \
		    }                                                                 \
	    }                                                                     \
    }                                                                         \
    void Vector_Reverse_##T (Vector_##T *_vector) {                           \
	    Vector_##T temp;                                                      \
	    Vector_Init_##T(&temp);                                               \
        for (int i = _vector->currentSize - 1; i > 0; --i) {                  \
		    Vector_Add_##T(&temp, _vector->itemArray[i]);                     \
	    }                                                                     \
        free(_vector->itemArray);                                             \
        _vector->itemArray = temp.itemArray;                                  \
    }                                                                         \
    int Vector_Contain_##T (Vector_##T *_vector, T _item) {                   \
        for (int i = 0; i < _vector->currentSize; ++i) {                      \
		    if (_vector->itemArray[i] == _item) return 1;                     \
		}                                                                     \
	    return 0;                                                             \
    }                                                                         \
    void Vector_CleanUp_##T (Vector_##T *_vector) {                           \
        _vector->allocatedSize = 0;                                           \
        _vector->currentSize = 0;                                             \
        free(_vector->itemArray);                                             \
        _vector->itemArray = NULL;                                            \
    }

#endif
