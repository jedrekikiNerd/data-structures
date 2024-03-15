#include "list.h"

template <typename Type>
void LinkedListH<Type>::add_front(Type value)
{
    Node<Type>* new_node = new Node<Type>(value);
    if (head == nullptr)
        head = new_node;
    else
    {
        head->next = new_node;
    }
    size++;
}

template <typename Type>
void add_back();

template <typename Type>
void add_at();

template <typename Type>
void remove_front();

template <typename Type>
void remove_back();

template <typename Type>
void remove_at();

template <typename Type>
void clear();

template <typename Type>
void first_element();

template <typename Type>
void last_element();

template <typename Type>
void first_value();

template <typename Type>
void last_value();

template <typename Type>
void size();

template <typename Type>
void find();