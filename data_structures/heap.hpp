#ifndef HEAP
#define HEAP

#include "dynamic_array.hpp"
#include "I_data_structure.hpp"
#include "to_string_functions.hpp"


// Heap class with some methods, but most of them is still not supported
template <typename Type>
class Heap : public IDataStructure<Type>
{
private:
    DynamicArray<Type> heap;

    //heapify a subtree that starts at index
    void heapify_down(int index)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.get_size() and heap[left] > heap[largest])
            largest = left;

        if (right < heap.get_size() and heap[right] > heap[largest])
            largest = right;

        if (largest != index)
        {
            Type tmp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = tmp;
            heapify_down(largest);
        }
    }

    //heapify up until everything is at its place
    void heapify_up(int index)
    {
        int parent_index = (index - 1) / 2;
        if (parent_index >= 0)
        {
            if (heap[index] > heap[parent_index])
            {
                Type tmp = heap[index];
                heap[index] = heap[parent_index];
                heap[parent_index] = tmp;
                heapify_up(parent_index); 
            }
        }
    }

public:
    void add_front(Type value) override
    {
        // We don't support heap add_front
        throw std::logic_error("Adding at the front of heap is not supported.");
    }

    void add_back(Type value, int additional = 0) override
    {
        heap.add_back(value);
        heapify_up(heap.get_size()-1);
    }

    void add_at(Type value, unsigned int position) override
    {
        // We don't support heap add_at
        throw std::logic_error("Adding at a specific position in heap is not supported.");
    }

    void remove_front() override
    {
        if (!heap.get_size())
        {
            return;
        }

        heap[0] = heap.last_value();
        heap.remove_back();
        heapify_down(0);
    }

    void remove_back() override
    {
        // We don't support remove_back
        throw std::logic_error("Removing from the back of heap is not supported.");
    }

    void remove_at(unsigned int position) override
    {
        // We don't support remove_at
        throw std::logic_error("Removing from a specific position in heap is not supported.");
    }

    void clear() override
    {
        heap.clear();
    }

    Type first_value() override
    {
        if (heap.get_size() == 0)
            throw std::out_of_range("Heap is empty.");
        return heap[0];
    }

    Type last_value() override
    {
        // We don't support getting last value
        throw std::logic_error("Getting last value of heap is not supported.");
    }

    Type value_at(unsigned int position) override
    {
        return heap[position];
    }

    unsigned int get_size() override
    {
        return heap.get_size();
    }

    unsigned int get_byte_size() override
    {
        return sizeof(Heap) + sizeof(heap);
    }

    unsigned int find(Type value) override
    {
        // We don't support value at
        throw std::logic_error("Find on heap is not supported.");
    }

    void change_at(Type value, unsigned int position, int additional = 0) override
    {
        if (position >= heap.get_size())
            throw std::out_of_range("Index out of range.");
        Type old_value = heap[position];
        heap[position] = value;
        if (value > old_value)
           heapify_up(position);
        else
            // Heapify down after change to maintain order
            heapify_down(position);
    }

    std::string get_as_string() override
    {
        std::string output = "Heap[";
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by this method!";
        for(int i=0; i<heap.get_size(); i++)
        {
            output += choose_to_string(heap.value_at(i));
            if (i != heap.get_size()-1)
                output += ", ";
        }
        output += "]";
        return output;
    }
};

#endif