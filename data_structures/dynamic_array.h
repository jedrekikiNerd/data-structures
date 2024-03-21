#include "I_data_structure.h"
#include <iostream>
#include <type_traits>

template <typename Type>
class DynamicArray : public IDataStructure<Type>
{private:
    Type *arr;
    int capacity;
    int size;

public:
    DynamicArray() {
        capacity = 1;
        size = 0;
        arr = new Type[capacity];
    }

     ~DynamicArray() {
        delete[] arr;
    }

    void add_back(Type value) {
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


    void add_front(Type value) {
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


    void add_at(Type value,int index) {
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
                arr[i] = arr[i-1];
            }
            arr[index] = value;
         }
        size++;
    }
    }




    void remove_front() {
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
                arr[i] = arr[i+1];
            }  
        }
        size--;
    }
    }


    void remove_back() { if (size > 0){
        if(size - 1 <= capacity / 2 && capacity > 1){
            int newCapacity = capacity / 2;
            Type *tempArr = new int[newCapacity];
            for ( int i =0; i < size - 1; i++){
                tempArr[i] = arr[i];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        }
        size--;
    }
    }

    void remove_at(int index) {
        if (size > 0 && index >= 0 && index <= size){
        if (size - 1 <= capacity / 2 && capacity > 1){
            int newCapacity = capacity / 2;
            Type *tempArr = new int[newCapacity];

            for (int i = 0; i < index; i++){
                tempArr[i] = arr[i];
            }

            for (int i = index; i < size - 1; i++){
                tempArr[i] = arr[i+1];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        } else{
            for (int i = index; i < size - 1;i++){
               arr[i] = arr[i+1];
            } 
        }
        size--;
    }
    }



    void clear() {
        delete[] arr;
        capacity = 1;
        size = 0;
        arr = new Type[capacity];
    }
    
    int& operator[](int index) {
        return arr[index];
    };

    int get_size() {
        return size;
    }

    int  first_value(){
        return arr[0];
    }

    int  last_value(){
        return arr[size];
    }

    int find(Type value){
        for(int i = 0; i < size;i++){
            if (arr[i] == value)
                return i;
        }
        return -1;
    }

    int value_at(int index) {
         if (index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
    }


std::string get_as_string()
    {
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by print method!";
        std::string output = "DynamicArray[";
        for (int i = 0; i < size; i++){
            output += std::to_string(arr[i]);
            if ( i < size-1 )
                output += ", ";
        }
        output += "]";
        return output;
    }
};
