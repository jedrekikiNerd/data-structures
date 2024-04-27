#include "dynamic_array.hpp"
#include "I_data_structure.hpp"


// Heap class with some methods, but most of them is still not supported
template <typename Type>
class Heap : public IDataStructure<Type>
{
private:
    DynamicArray<Type> heap;

    void heapify(int index)
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
            heapify(largest);
        }
    }

public:
    void add_front(Type value) override
    {
        // We don't support heap add_front
        throw std::logic_error("Adding at the front of heap is not supported.");
    }

    void add_back(Type value) override
    {
        heap.add_back(value);
        int index = heap.get_size() - 1;

        while (index > 0 and heap[(index - 1) / 2] < heap[index])
        {
            Type tmp = heap[index];
            heap[index] = heap[(index - 1) / 2];
            heap[(index - 1) / 2] = tmp;
            index = (index - 1) / 2;
        }
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
        heapify(0);
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
        // We don't support value at
        throw std::logic_error("Getting value at a specific position in heap is not supported.");
    }

    unsigned int get_size() override
    {
        return heap.get_size();
    }

    unsigned int get_byte_size() override
    {
        // We don't support getting byte size
        throw std::logic_error("Getting byte size of heap is not supported.");
    }

    unsigned int find(Type value) override
    {
        // We don't support finding element
        throw std::logic_error("Finding value in heap is not supported.");
    }

    void change_at(Type value, unsigned int position) override
    {
        // We don't support change at
        throw std::logic_error("Changing value at a specific position in heap is not supported.");
    }

    std::string get_as_string() override
    {
        // We don't support getting as string
        return "";
    }
};
