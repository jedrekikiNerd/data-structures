#include "dynamic_array.hpp"
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
void DynamicArray<Type>::push_at(Type value,int index) {
    if (index >= 0 && index <= size){
        if (size >= capacity) {
            // If the array is full, double its size
            int newCapacity = capacity * 2;
            Type *tempArr = new int[newCapacity];
            for (int i = 0; i < index ; ++i) {
                tempArr[i] = arr[i];
            }
            tempArr[index] = value;
            for ( int i = index; i < size; i++){
                tempArr[i+1] = arr[i];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;

        } else {
            for (int i = size; i >index; i--){
                arr[i] = arr[i-1]
            }
            arr[index] = value
         }

        size++;
    } else {
        cout << "Incorrect index";
    }

}


template <typename Type>
void DynamicArray<Type>::pop_front(){
    if (size > 0){
        if(size-1 <= capacity/2 && capacity > 1 ){
            int newCapacity = capacity /2;
            Type *tempArr = new int[newCapacity];
            for ( int i=0; i < size - 1;i++){
                tempArr[i] = arr[i+1];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        } else {
            for(int i =0; i <size - 1; i++){
                arr[i] = arr[i+1;]
            }  
        }
        size--;
    }
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