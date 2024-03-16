#include "list.h"
#include <iostream>

template <typename Type>
void LinkedListH<Type>::add_front(Type value)
{
    Node<Type>* new_node = new Node<Type>(value);
    if (head == nullptr)
        head = new_node;
    else
    {
        new_node->next_element = head->next_element;
        head = new_node;
    }
    size++;
}

template <typename Type>
void LinkedListH<Type>::add_back(Type value)
{
    Node<Type>* new_node = new Node<Type>(value);
    if (head == nullptr)
        head = new_node;
    else
    {
        Node<Type>* last_node = &head;
        while(last_node->next_element != nullptr)
        {
            last_node = last_node->next_element;
        }
        last_node->next_element = new_node;
    }
    size++;
}

template <typename Type>
void LinkedListH<Type>::add_at(Type value, int position)
{
    Node<Type>* new_node = new Node<Type>(value);
    if (position >= size or position < 0)
        std::cerr << "Position exceeds size!";
    else
    {
        Node<Type>* currrent_node = head;
        for(int i=0; i<position; i++)
        {
            // TODO: finish
        }
    }
    size++;
}

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

template <typename Type>
void get_at();

template <typename Type>
void print();