#include <stddef.h> /* size_t, NULL */
#include <stdio.h> /* printf */
#include <stdlib.h> /* realloc */

// https://stackoverflow.com/a/46351960

typedef struct intList {

    size_t size;
    size_t capacity;
    int value[];

} *intListP;


size_t getIntListSize (intListP *_list) {
    return *_list ? (_list[0] -> size) : 0;
}

size_t getIntListCapacity (intListP *_list) {
    return *_list ? (_list[0] -> capacity) : 0;
}

int setIntListCapacity (intListP *_list, size_t _capacity) {

    // reallocate to (size of empty list) + (size to fit n values)

    void *newPointer = realloc(*_list,
        sizeof(**_list) + _capacity * sizeof(_list[0] -> value[0]));
    
    // failed to realloc

    if (!newPointer) { return 1; }

    // assign pointers and values

    *_list = newPointer;
    _list[0] -> capacity = _capacity;
    return 0;

}

int setIntListCapacity_s (intListP *_list, size_t _capacity) {

    if (getIntListSize(_list) < _capacity) return 1;
    return setIntListCapacity(_list,_capacity);

}

int pushToIntList (intListP *_list, int _value) {
    
    // get the size and capacity of the list
    size_t size = getIntListSize(_list);
    size_t capacity = getIntListCapacity(_list);

    if (size >= capacity) {

        // realloc to an arbitarily scaled size
        if (setIntListCapacity(_list,capacity ? (capacity << 1) : 2)) return 1;

    }

    // assign values and new size
    _list[0] -> value[size] = _value;
    _list[0] -> size = size + 1;
    return 0;

}

int removeAtIntList (intListP *_list, size_t _index) {
    
    // safety check
    if (_index < 0) return 1;

    // get and check the size of the list
    size_t size = getIntListSize(_list);
    if (_index >= size) return 1;
    
    // shift all back
    ++_index;
    while (_index < size) {
        _list[0] -> value[_index] = _list[0] -> value[_index + 1];
        ++_index;
    }

    // assign new size
    --(_list[0] -> size);
    return 0;
}

int insertAtIntList (intListP *_list, int _value, size_t _index) {
    
    // safety check
    if (_index < 0) return 1;

    // get and check the size of the list
    size_t size = getIntListSize(_list);
    if (_index >= size) return pushToIntList(_list,_value);
    
    // shift all forward
    pushToIntList(_list,_list[0] -> value[size - 1]);
    --size;
    while (size > _index) {
        _list[0] -> value[size] = _list[0] -> value[size - 1];
        --size;
    }

    // insert new value
    _list[0] -> value[_index] = _value;

    // assign new size
    ++(_list[0] -> size);
    return 0;

}

int getAtIntList (intListP *_list, int _index) {

    return _list[0] -> value[_index];

}

int debugIntList (intListP *_list) {

    int size = (int)getIntListSize(_list);
    int capacity = (int)getIntListCapacity(_list);
    int i;

    printf("size: %d, capacity: %d\n",size,capacity);
    for (i = 0; i < size; i++) {
        printf("[%d] ",getAtIntList(_list,i));
    }
    printf("\n");

    return 0;

}

int main (void) {

    intListP intListA = NULL;
    int i;

    for (i = 0; i < 50; i++) {

        pushToIntList(&intListA,i);
        debugIntList(&intListA);

    }

    return 0;

}
