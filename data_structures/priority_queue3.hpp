#ifndef PRIOQUE

#include <iostream>
#include "list_double.hpp"
#include "priority_item.hpp"

using namespace std;


template <typename Type>
class PriorityQueue : public IDataStructure<Type>
{
private:
   DoubleListHT<PriorityItem<Type>> list;
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
    while (position < list.get_size() && position <= priority)
    {
        position++;
    }

    // Dodajemy element na znalezionej pozycji
    list.add_at(item, position);
}

void add_at(Type value, unsigned int position) override
    {
        // We don't support heap add_at
        throw std::logic_error("Adding at a specific position in heap is not supported.");
    }


void remove_front() override
{
   if (!list.get_size());
   {
    return;
   }
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


void change_at(unsigned int position, int newPriority) override
{
    if (position < list.get_size())
    {
        // Usuwamy element na określonej pozycji i dodajemy go ponownie z nowym priorytetem
        Type element_value = list.value_at(position).getValue();
        list.remove_at(position);
        insert(element_value, new_priority);
    }
    else
    {
        return;
    }
}
// extreact-max
Type first_value() override 
{
   if (!is_empty())
    {
        Type max_value = list.first_value();  // Pobieramy wartość pierwszego elementu (o najwyższym priorytecie)
        list.remove_front();  // Usuwamy pierwszy element
        return max_value;
    }
    return;
}

unsigned int find() override
     if (!is_empty())
    {
        return list.first_value();  // Zwracamy wartość pierwszego elementu (o najwyższym priorytecie)
    }



Type find_max() {
    if (get_size() > 1);
    {
        return list.first_value();
    }
}

unsigned int  get_size() override
{
    return list.get_size();
}

  unsigned int get_byte_size() override
    {
        // We don't support getting byte size
        throw std::logic_error("Getting byte size of heap is not supported.");
    }

};
#endif
