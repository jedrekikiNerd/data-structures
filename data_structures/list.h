#ifndef LISTH
#define LISTH

#include <iostream>
#include "I_data_structure.h"
#include <type_traits>


/**
 * Node class for single container used by basic list
 * It contains pointer to next container and stores value of type read from template
 * 
 */
template <typename Type>
class Node
{
public:
    Type value;
    Node<Type>* next_element;

    Node(Type value) : value(value), next_element(nullptr) {}
};


/**
 * LinkedListH class that represents a list data structure with methodes
 * 
 */
template <typename Type>
class LinkedListH : public IDataStructure<Type>
{
private:
    Node<Type>* head;
    int size;


public:
    LinkedListH() : head(nullptr), size(0) {}
    ~LinkedListH() {
        clear();
    }

    
    // Adds element where head ptr is pointing
    void add_front(Type value)
    {
        Node<Type>* new_node = new Node<Type>(value);
        if (head == nullptr)
            head = new_node;
        else
        {
            new_node->next_element = head;
            head = new_node;
        }
        size++;
    }

    // Adds element to the tail of the list
    void add_back(Type value)
    {
        Node<Type>* new_node = new Node<Type>(value);
        if (head == nullptr)
            head = new_node;
        else
        {
            Node<Type>* last_node = head;
            while(last_node->next_element != nullptr)
            {
                last_node = last_node->next_element;
            }
            last_node->next_element = new_node;
        }
        size++;
    }

    // Adds element on specified index starting counting from head
    void add_at(Type value, int position)
    {
        if (position >= size or position < 0)
            std::cerr << "Position exceeds size!";
        else
        {
            Node<Type>* new_node = new Node<Type>(value);
            
            if (position == 0)
            {
                new_node->next_element = head;
                head = new_node;
                size++;
                return;
            }

            Node<Type>* currrent_node = head;
            for(int i=1; i<position; i++)
            {
                currrent_node = currrent_node->next_element;
            }
            new_node->next_element = currrent_node->next_element;
            currrent_node->next_element = new_node;
            size++;
        }
    }

    // Removes first element - based on head pointer
    void remove_front()
    {
        if (head != nullptr) 
        {
            Node<Type>* temp = head;
            head = head->next_element;
            delete temp;
            size--;
        }
    }

    // Removes last element - needs to iterate from head to tail
    void remove_back()
    {
        if (head != nullptr)
        {
            if (head->next_element == nullptr)
            {
                delete head;
                head = nullptr;
            }
            else
            {
                Node<Type>* prev_last_node = head;
                // We have to reach last element - 1 in order to change pointers and then delete last one
                while(prev_last_node->next_element->next_element != nullptr)
                {
                    prev_last_node = prev_last_node->next_element;
                }
                // We delete last element and set nullptr for prev_last
                delete prev_last_node->next_element;
                prev_last_node->next_element = nullptr;
            }
            size--;
        }
    }

    // Removes element at specified position counting from head (0)
    void remove_at(int position)
    {
        if (position >= size or position < 0)
            std::cerr << "Position exceeds size!";
        else
        {
            if (position == 0)
            {
                Node<Type>* temp = head;
                head = head->next_element;
                delete temp;
                size--;
            }

            Node<Type>* currrent_node = head;
            for(int i=1; i<position; i++)
            {
                currrent_node = currrent_node->next_element;
            }
            Node<Type>* temp = currrent_node->next_element;
            currrent_node->next_element = currrent_node->next_element->next_element;
            delete temp;
            size--;
        }
    }

    // Clears all nodes stored by this list, useful for deconstructing to free all memory
    void clear()
    {
        while(head)
            this->remove_front();
    }

    // Returns first value (head value)
    Type first_value()
    {
        return head->value;
    }

    // Returns last value (tail value)
    Type last_value()
    {
        Node<Type>* last_node = head;
        while(last_node->next_element != nullptr)
        {
            last_node = last_node->next_element;
        }
        return last_node->value;
    }

    Type value_at(int position)
    {
        if (position >= size or position < 0)
        {
            std::cerr << "Position exceeds size!";
            return -1;
        }
        else
        {
            Node<Type>* current_node = head;
            for(int i=0; i<position; i++)
                current_node=current_node->next_element;
            return current_node->value;
        }
    }

    // Returns size of list
    int get_size()
    {
        return size;
    }

    // Returns position of element
    int find(Type value)
    {
        Node<Type>* current_node = head;
        int i = 0;
        while(current_node != nullptr)
        {
            if (current_node->value == value)
                return i;
            i++;
            current_node = current_node->next_element;
        }
        return -1;
    }

    // Returns string representation of data inside list
    std::string get_as_string()
    {
        std::string output = "List[";
        Node<Type>* current_node = head;
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by print method!";
        while(current_node != nullptr)
        {
            output += std::to_string(current_node->value);
            current_node = current_node->next_element;
            if (current_node != nullptr)
                output += ", ";
        }
        output += "]";
        return output;
    }
    
};
#endif
