#include "dynamic_array.h"
#include <iostream>


template <typename Type>
void DynamicArray<Type>::push_back(Type value) {
    if (size >= capacity) {
        // If the array is full, double its size
        int newCapacity = capacity * 2;
        Type *tempArr = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            tempArr[i] = arr[i];
        }
        delete[] arr;
        arr = tempArr;
        capacity = newCapacity;

    }
    arr[size] = value;
    size++;
}

template <typename Type>
void DynamicArray<Type>::push_front(Type value) {
    if (size >= capacity) {
        // If the array is full, double its size
        int newCapacity = capacity * 2;
        Type *tempArr = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            tempArr[i+1] = arr[i];
        }
        delete[] arr;
        arr = tempArr;
        capacity = newCapacity;

    }else { // Shift all elements by one
        for(int i = size; i > 0; i--){
            arr[i] = arr[i-1];
        }
    }
    arr[0] = value;
    size++;
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