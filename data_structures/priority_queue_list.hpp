#ifndef PRIOQUE2
#define PRIOQUE2

#include <iostream>
#include "list_double.hpp"
#include "priority_item.hpp"
#include "nodes.hpp"

using namespace std;

template <typename Type>
class PriorityQueueList : public IDataStructure<Type>
{
private:
   DoubleListHT<PriorityItem<Type>> list; // for stroing priority items
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
    DoubleNode<PriorityItem<Type>>* hp = list.get_head_ptr();
    if (hp == nullptr)
    {
        list.add_front(item);

        return;
    }
    while(hp->value.priority >= priority)
    {
        if (hp->next_element == nullptr)
        {
            list.add_back(item);
            return;
        }
        hp = hp->next_element;
    }

    if (hp->previous_element == nullptr)
    {
        list.add_front(item);
        return;
    }

    // Dodajemy element na znalezionej pozycji
    list.add_at_ptr(item, hp);
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
    if (position < list.get_size())
    {
        // Usuwamy element na określonej pozycji i dodajemy go ponownie z nowym priorytetem
        PriorityItem<Type> element(value, newPriority);
        list.change_at(element,position);
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
        PriorityItem<Type> first = list.first_value();  // Pobieramy wartość pierwszego elementu (o najwyższym priorytecie)
        list.remove_front();  // Usuwamy pierwszy element
        return first.value;
    }
    throw std::out_of_range("Index out of range");
}

unsigned int find(Type value) override
{
    DoubleNode<PriorityItem<Type>>* hp = list.get_head_ptr();
    unsigned int position = 0;
    while(hp->value.value != value and hp != nullptr)
    {
        hp = hp->next_element;
        position++;
    }
    if (hp != nullptr)
    {
        return position;
    }
    return -1;
}

Type find_max()
{
    if (list.get_size())
    {
        return list.first_value().value;
    }
    throw std::out_of_range("Index out of range");
}

Type value_at(unsigned int position) override
{
    return list.value_at(position).value;
}

void clear() override
{
    list.clear();
}

unsigned int  get_size() override
{
    return list.get_size();
}

unsigned int get_byte_size() override
{
    return sizeof(PriorityQueueList) + list.get_byte_size();
}

std::string get_as_string() override
{
    std::string output = "PriorQueueOnList[";
    if (std::is_integral_v<Type> != true)
        return "ERROR: typename of this list is not supported by this method!";
    for(int i=0; i<list.get_size(); i++)
    {
            output += "<";
            PriorityItem<Type> first = list.value_at(i);
            output += std::to_string(first.priority);
            output += ", " + std::to_string(first.value);
            output += ">";
            if (i != list.get_size()-1)
                output += ", ";
    }
    output += "]";
    return output;
}

};
#endif
