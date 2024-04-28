#ifndef PRIOQUE

#include <iostream>
#include "heap.hpp"
#include "priority_item.hpp" 

using namespace std;

template <typename Type>
class PriorityQueueHeap : public IDataStructure<Type>
{
private:
    Heap<PriorityItem<Type>> queue; // We use heap for storing values of type PriorityItem
public:

    // insert
    void add_back(Type element, int priority)
    {
        // Dodawanie elementu do kolejki przy użyciu listy dwukierunkowej
        queue.add_back(PriorityItem(element, priority));
    }

    // extractFirst
    pair<Type, int> first_value() override
    {
        // Usuwanie i zwracanie maksymalnego elementu z kolejki
        // Wykorzystujemy odpowiednią operację z implementacji listy dwukierunkowej
        pair<Type, int> maxElement = queue.last_value();
        queue.remove_back();
        return maxElement;
    }

    // findMax
    pair<Type, int> find() override
    {
        // Znajdowanie i zwracanie maksymalnego elementu z kolejki
        // Wykorzystujemy odpowiednią operację z implementacji listy dwukierunkowej
        return queue.last_value();
    }

    // modifyPriority
    void change_at(Type element, int newPriority) override
    {
        // Modyfikowanie priorytetu elementu w kolejce
        // Wykorzystujemy odpowiednią operację z implementacji listy dwukierunkowej
        unsigned int index = 0;
        while (index < queue.get_size())
        {
            if (queue.value_at(index).first == element)
            {
                queue.change_at(make_pair(element, newPriority), index);
                return;
            }
            index++;
        }
    }

    int size()
    {
        return queue.get_size();
    }

    void add_front(Type value) override
    {
        // We don't support heap add_front
        throw std::logic_error("Adding at the front of heap is not supported.");
    }

    void add_at(Type value, unsigned int position) override
    {
        // We don't support heap add_at
        throw std::logic_error("Adding at a specific position in heap is not supported.");
    }

    void remove_back() override
    {
        // We don't support remove_back
        throw std::logic_error("Removing from the back of heap is not supported.");
    }

    void remove_front() override
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
        queue.clear();
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

    unsigned int get_byte_size() override
    {
        // We don't support getting byte size
        throw std::logic_error("Getting byte size of heap is not supported.");
    }

    void change_at(Type value, unsigned int position) override
    {
        // We don't support change at
        throw std::logic_error("Changing value at a specific position in heap is not supported.");
    }

    std::string get_as_string() override
    {
        std::string output = "PriorQueueOnList[";
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by this method!";
        for(int i=0; i<queue.get_size(); i++)
        {
            output += std::to_string(queue.value_at(i));
            if (i != queue.get_size()-1)
                output += ", ";
        }
        output += "]";
        return output;
    }
};
#endif
