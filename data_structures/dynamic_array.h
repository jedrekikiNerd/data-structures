#include "I_data_structure.h"
#include <iostream>
#include <type_traits>

template <typename Type>
class DynamicArray : public IDataStructure<Type>
{
private:
    Type *arr;
    unsigned int capacity;
    unsigned int size;

public:
    DynamicArray() 
    {
        capacity = 1;
        size = 0;
        arr = new Type[capacity];
    }

    ~DynamicArray() 
    {
        delete[] arr;
    }

    void add_back(Type value) 
    {
        if (size >= capacity)
        {
            // If the array is full, double its size
            unsigned int newCapacity = capacity * 2;
            Type *tempArr = new Type[newCapacity];
            for (unsigned int i = 0; i < size; ++i)
            {
                tempArr[i] = arr[i];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        }
        arr[size] = value;
        size++;
    }



    void add_front(Type value)
    {
        if (size >= capacity)
        {
            // If the array is full, double its size
            unsigned int newCapacity = capacity * 2;
            Type *tempArr = new Type[newCapacity];
            for (unsigned int i = 0; i < size; ++i)
            {
                tempArr[i+1] = arr[i];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        }
        else
        { 
            // Shift all elements by one
            for(unsigned int i = size; i > 0; i--)
            {
                arr[i] = arr[i-1];
            }
        }
        arr[0] = value;
        size++;
    }

    void add_at(Type value, unsigned int position)
    {
        if (position >= 0 && position <= size)
        {
            if (size >= capacity) 
            {
                // If the array is full, double its size
                unsigned int newCapacity = capacity * 2;
                Type *tempArr = new Type[newCapacity];
                for (unsigned int i = 0; i < position ; ++i)
                {
                    tempArr[i] = arr[i];
                }
                tempArr[position] = value;
                for (unsigned int i = position; i < size; i++)
                {
                    tempArr[i+1] = arr[i];
                }
                delete[] arr;
                arr = tempArr;
                capacity = newCapacity;
            }
            else
            {
                for (unsigned int i = size; i >position; i--)
                {
                    arr[i] = arr[i-1];
                }
                arr[position] = value;
            }
        size++;
        }
    }


    // Removes first element 
    void remove_front()
    {
        if (size > 0)
        {
        if(size-1 <= capacity/2 && capacity > 1 ){
            //after removal the number of elements is less than half the capacity of the array, 
            //reduces the capacity of the array to half.
            unsigned int newCapacity = capacity /2;
            Type *tempArr = new int[newCapacity];
            for (unsigned int i=0; i < size-1;i++){
                tempArr[i] = arr[i+1];
            }
            delete[] arr;
            arr = tempArr;
            capacity = newCapacity;
        } else {
            //shif all elements by one after removing first
            for(unsigned int i=0; i < size-1; i++){
                arr[i] = arr[i+1];
            }  
        }
        size--;
        }
    }

    // Removes last element
    void remove_back() 
    { 
        if (size > 0)
        {
            if (size - 1 <= capacity / 2 && capacity > 1)
            //after removal the number of elements is less than half the capacity of the array, 
            //reduces the capacity of the array to half.
            {
                unsigned int newCapacity = capacity / 2;
                Type *tempArr = new Type[newCapacity];
                for (unsigned int i = 0 ; i < size - 1 ; i++)
                {
                    tempArr[i] = arr[i];
                }
                delete[] arr;
                arr = tempArr;
                capacity = newCapacity;
            }
        size--;
        }
    }


    // Removes element at specified position counting from front or back depends in which half is element
    void remove_at(unsigned int position) 
    {
        if (size > 0 && position >= 0 && position <= size)
        {
            if (size - 1 <= capacity / 2 && capacity > 1)
            {
                unsigned int newCapacity = capacity / 2;
                Type *tempArr = new Type[newCapacity];
                //assign all elements on the left side
                for (unsigned int i = 0; i < position; i++)
                {
                    tempArr[i] = arr[i];
                }
                //then assign all elements shifted by one on the right
                for (unsigned int i = position; i < size - 1; i++)
                {
                    tempArr[i] = arr[i+1];
                }
                delete[] arr;
                arr = tempArr;
                capacity = newCapacity;
            }
            else
            {
                //we don't need to create temp arr just shift all elements by one 
                for (unsigned int i = position; i < size - 1;i++)
                {
                    arr[i] = arr[i+1];
                }
            }
            size--;
        }
    }
    // clears all cells by removing array
    void clear()
    {
        delete[] arr;
        capacity = 1;
        size = 0;
        arr = new Type[capacity];
    }
    //returns reference to the value of the specified cell
    Type& operator[](unsigned int position)
    {
        return arr[position];
    };

    // Returns size of list
    unsigned int get_size()
    {
        return size;
    }
    // Returns first value
    Type first_value()
    {
        return arr[0];
    }
    // Returns last value
    Type last_value()
    {
        return arr[size-1];
    }


    // Returns position of element
    unsigned int find(Type value)
    {
        for(unsigned int i = 0; i < size;i++)
        {
            if (arr[i] == value)
                return i;
        }
        return -1;
    }


    //returns the value of the specified cell
    Type value_at(unsigned int position)
    {
        if (position < 0 || position >= size)
            throw std::out_of_range("Position out of range");
        return arr[position];
    }

    // Returns string representation of data inside list
    std::string get_as_string()
    {
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by print method!";
        std::string output = "DynamicArray[";
        for (unsigned int i = 0; i < size; i++)
        {
            output += std::to_string(arr[i]);
            if ( i < size-1 )
                output += ", ";
        }
        output += "]";
        return output;
    }

    // Return size of data structure in bytes
    unsigned int get_byte_size()
    {
        return sizeof(DynamicArray) + sizeof(Type)*capacity;
    }

    // Change value at given position
    void change_at(Type value, unsigned int position)
    {
        if (position < 0 || position >= size)
            return;
            //throw std::out_of_range("Position out of range");
        arr[position] = value;
    }
};
