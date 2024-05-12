#ifndef PRIOQUE2
#define PRIOQUE2

#include <iostream>
#include "dynamic_array.hpp"
#include "priority_item.hpp"
#include "nodes.hpp"

using namespace std;

template <typename Type>
class PriorityQueuearray : public IDataStructure<Type>
{
private:
   DynamicArray<PriorityItem<Type>> array; // for stroing priority items
public:
 
 void add_front(Type value) override
    {
        // We don't support heap add_front
        throw std::logic_error("Adding at the front of heap is not supported.");
    }
    
// Insert an element with its priority into the priority queue
void add_back(Type value, int priority)
{
    PriorityItem<Type> item(value, priority);  // Tworzymy obiekt PriorityItem

    // Dodajemy do listy w odpowiednim miejscu względem priorytetu
    unsigned int position = 0;
    // Przeszukujemy listę, aby znaleźć odpowiednie miejsce na element zgodnie z priorytetem
    while (position < array.get_size() && item.priority < priority)
    {
        position++;
    }

    // Dodajemy element na znalezionej pozycji
    array.add_at(item, position);
}


void add_at(Type value, unsigned int position) override
    {
        // We don't support heap add_at
        throw std::logic_error("Adding at a specific position in heap is not supported.");
    }

void remove_front() override
{
        // We don't support remove_back
        throw std::logic_error("Removing from the front of queue is not supported.");
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
Type last_value() override
{
        // We don't support getting last value
        throw std::logic_error("Getting last value of priority queue is not supported.");
}

void change_at(Type value,unsigned int position, int newPriority) override
{
    if (position < array.get_size())
    {
        // Usuwamy element na określonej pozycji i dodajemy go ponownie z nowym priorytetem
        PriorityItem<Type> element(value, newPriority);
        array.change_at(element,position);
    }
    else
    {
        return;
    }
}

// extreact-max
Type first_value() override 
{
   if (get_size())
    {
        PriorityItem<Type> first = array.first_value();  // Pobieramy wartość pierwszego elementu (o najwyższym priorytecie)
        array.remove_front();  // Usuwamy pierwszy element
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
        return array.first_value().value;
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
    for(int i=0; i<array.get_size(); i++)
    {
            output += "<";
            PriorityItem<Type> first = array.value_at(i);
            output += std::to_string(first.priority);
            output += ", " + std::to_string(first.value);
            output += ">";
            if (i != array.get_size()-1)
                output += ", ";
    }
    output += "]";
    return output;
}

};
#endif