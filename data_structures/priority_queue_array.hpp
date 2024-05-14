#ifndef PRIOQUE3
#define PRIOQUE3

#include <iostream>
#include "dynamic_array.hpp"
#include "priority_item.hpp"

using namespace std;

template <typename Type>
class PriorityQueuearray : public IDataStructure<Type>
{
private:
   DynamicArray<PriorityItem<Type>> array; // for stroing priority items
public:

 PriorityQueuearray() {}
 
 ~PriorityQueuearray()
 {
 	array.clear();
 }
 
 void add_front(Type value) override
    {
        // We don't support queue_array add_front
        throw std::logic_error("Adding at the front of queue_array is not supported.");
    }
    
// Insert an element with its priority into the priority queue
void add_back(Type value, int priority)
{
    PriorityItem<Type> item(value, priority);  // New priority item object

    unsigned int low = 0; //First element as left border
    unsigned int high = array.get_size() - 1; // Last element as right border
    unsigned int insert_position = array.get_size() - 1;  // Defult insert is on high
    bool found = false;

    if (array.get_size() == 0)
    {
    	array.add_front(item);
    	return;
    }

    if (array[0].priority >= priority)
    {
        array.add_front(item);
        return;
    }

    if (array[array.get_size()-1].priority < priority)
    {
        array.add_back(item);
        return;  
    }

    // Bin search where to put new value
    while (low <= high)
    {
        unsigned int mid = (high + low) / 2;

        if (array[mid].priority == priority)
        {
            insert_position = mid;
            found = true;
            break;
        }
        else if (array[mid].priority > priority)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;  // We continue bin search on right side
        }
    }
    if (!found)
        insert_position = low;

    while(array[insert_position-1].priority == priority and insert_position != 1)
    {
        insert_position--;
    }

    // Else if position is valid add at specified index
    array.add_at(item, insert_position);
}

void add_at(Type value, unsigned int position) override
    {
        // We don't support queue_array add_at
        throw std::logic_error("Adding at a specific position in queue_array is not supported.");
    }

void remove_front() override
{
        // We don't support remove_back
        throw std::logic_error("Removing from the front of queue is not supported.");
}

void remove_back() override
{
        // We don't support remove_back
        throw std::logic_error("Removing from the back of queue_array is not supported.");
}

void remove_at(unsigned int position) override
{
        // We don't support remove_at
        throw std::logic_error("Removing from a specific position in queue_array is not supported.");
}
Type last_value() override
{
        // We don't support getting last value
        throw std::logic_error("Getting last value of priority queue is not supported.");
}

// Modify whole element
void change_at(Type value, unsigned int position, int new_priority=0) override
{
    if (position < array.get_size())
    {
        position = array.get_size() - position - 1;
        array.remove_at(position);
        this->add_back(value, new_priority);
    }
    else
    {
        return;
    }
}

// extract-max
Type first_value() override 
{
   if (get_size())
    {
        PriorityItem<Type> first = array.last_value();  // Pobieramy wartość pierwszego elementu (o najwyższym priorytecie)
        array.remove_back();  // Usuwamy pierwszy element
        return first.value;
    }
    throw std::out_of_range("Index out of range");
}

unsigned int find(Type value) override
  {
        for (int i = 0; i < array.get_size(); i++)
        {
            if (array.value_at(i).value == value)
            {
                return i;
            }
        }
        return -1;
    }

Type find_max()
{
    if (array.get_size())
    {
        return array.last_value().value;
    }
    throw std::out_of_range("Index out of range");
}

Type value_at(unsigned int position) override
{
    return array.value_at(position).value;
}

void clear() override
{
    array.clear();
}

unsigned int  get_size() override
{
    return array.get_size();
}

unsigned int get_byte_size() override
{
    return sizeof(PriorityQueuearray) + array.get_byte_size();
}

std::string get_as_string() override
{
    std::string output = "PriorQueueOnarray[";
    if (std::is_integral_v<Type> != true)
        return "ERROR: typename of this array is not supported by this method!";
    for(int i=array.get_size()-1; i>=0; i--)
    {
            output += "<";
            PriorityItem<Type> first = array.value_at(i);
            output += std::to_string(first.priority);
            output += ", " + std::to_string(first.value);
            output += ">";
            if (i != 0)
                output += ", ";
    }
    output += "]";
    return output;
}

};
#endif
