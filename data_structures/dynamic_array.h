#include "I_data_structure.h"
#include <iostream>

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
         if (position >= size or position < 0)
            std::cerr << "Position exceeds size!";
        else
        {
            Node<Type>* new_node = new Node<Type>(value);
            
            if (position == 0)
            {
                new_node->next_element = head;
                head = new_node;
                size++;
                return;
            }

            Node<Type>* currrent_node = head;
            for(int i=1; i<position; i++)
            {
                currrent_node = currrent_node->next_element;
            }
            new_node->next_element = currrent_node->next_element;
            currrent_node->next_element = new_node;
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
                arr[i] = arr[i+1;]
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
                tempArr[i] = arr[i]
            }

            for (int i = index; i < size - 1; i++){
                tempArr[i] = arr[i+1]
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        } else{
            for (int i = index; i < size - 1;i++){
               arr[i] = arr[i+1]
            } 
        }
        size--;
    }else{
        return 1;
    }
    }



    void clear() {
         for(int i=0; i <= size ;i++){
        delete[i] arr;
    }
    }
    
    int& operator[](int index) {
        return arr[index];
    };

    int size() const {
        return size;
    }

    int getElement(int index) const {
         if (index < 0 || index >= size) {
        return -1;
    }
    return arr[index];
    }
};
