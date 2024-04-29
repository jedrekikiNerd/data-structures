#ifndef PRIOQUE

#include <iostream>
#include "heap.hpp"
#include "priority_item.hpp" 

template <typename Type>
class PriorityQueueHeap : public IDataStructure<Type>
{
private:
    Heap<PriorityItem<Type>> queue; // We use heap for storing values of type PriorityItem
public:

    // insert
    void add_back(Type value, int priority=0)
    {
        // Adding element
       PriorityItem<Type> element(value, priority);
       queue.add_back(element);
    }

    // extractFirst
    Type first_value() override
    {
       if (queue.get_size() == 0)
           throw std::out_of_range("Priority Queue is empty.");

       PriorityItem<Type> first = queue.first_value();
       queue.remove_front();
       return first.value;
    }

    // findMax
    Type find_max(Type value) override
    {
       if (queue.get_size() == 0)
           throw std::out_of_range("Priority Queue is empty.");

       return queue.first_value().value;
    }

    // modifyPriority
    void change_at(Type value, unsigned int position, int priority=0) override
    {
        PriorityItem<Type> element(value, priority);
        queue.change_at(element, position);
        return;
    }

    unsigned int get_size() override
    {
        return queue.get_size();
    }

    void add_front(Type value) override
    {
        // We don't support heap add_front
        throw std::logic_error("Adding at the front of priority queue is not supported.");
    }

    void add_at(Type value, unsigned int position) override
    {
        // We don't support heap add_at
        throw std::logic_error("Adding at a specific position in priority queue is not supported.");
    }

    void remove_back() override
    {
        // We don't support remove_back
        throw std::logic_error("Removing from the back of priority queue is not supported.");
    }

    void remove_front() override
    {
        // We don't support remove_back
        throw std::logic_error("Removing from the back of priority queue is not supported.");
    }

    void remove_at(unsigned int position) override
    {
        // We don't support remove_at
        throw std::logic_error("Removing from a specific position in priority queue is not supported.");
    }

    void clear() override
    {
        queue.clear();
    }

    // find index - we don't implement it in queue
    unsigned int find(Type value) override
    {
        // We don't support index of searched value
        throw std::logic_error("Getting last value of priority queue is not supported.");
    }

    Type last_value() override
    {
        // We don't support getting last value
        throw std::logic_error("Getting last value of priority queue is not supported.");
    }

    Type value_at(unsigned int position) override
    {
        // We don't support value at
        throw std::logic_error("Getting value at a specific position in priority queue is not supported.");
    }

    unsigned int get_byte_size() override
    {
        return sizeof(PriorityQueueHeap) + sizeof(queue);
    }

    std::string get_as_string() override
    {
        std::string output = "PriorQueueOnHeap[";
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by this method!";
        for(int i=0; i<queue.get_size(); i++)
        {
            output += "<";
            output += std::to_string(queue.value_at(i).priority);
            output += ", " + std::to_string(queue.value_at(i).value);
            output += ">";
            if (i != queue.get_size()-1)
                output += ", ";
        }
        output += "]";
        return output;
    }
};
#endif
