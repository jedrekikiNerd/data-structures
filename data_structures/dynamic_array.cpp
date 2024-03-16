#include "dynamic_array.h"
#include <iostream>


template <typename Type>
void DynamicArray<Type>::push_back(Type value) {
    if (size == capacity) {
        // If the array is full, double its size
        capacity *= 2;
        Type *tempArr = new int[capacity];
        for (int i = 0; i < size; ++i) {
            tempArr[i] = arr[i];
        }
        delete[] arr;
        arr = tempArr;
    }
    arr[size++] = value;
}


template <typename Type>
int& DynamicArray<Type>::operator[](int index) {
    return arr[index];
}


template <typename Type>
int DynamicArray<Type>::getSize() const {
    return size;
}


template <typename Type>
int DynamicArray<Type>::getCapacity() const {
    return capacity;
}