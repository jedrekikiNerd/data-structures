#ifndef LISTH
#define LISTH

#include <iostream>
#include <stdexcept>
#include "I_data_structure.h"
#include <type_traits>
#include "nodes.h"


/**
 * SingleListH class that represents a list data structure with methodes
 * 
 */
template <typename Type>
class SingleListH : public IDataStructure<Type>
{
private:
    Node<Type>* head;
    unsigned int size;


public:
    SingleListH() : head(nullptr), size(0) {}
    ~SingleListH() {
        clear();
    }

    // Adds element where head ptr is pointing
    void add_front(Type value)
    {
        Node<Type>* new_node = new Node<Type>(value);
        // Check if not null
        if (head == nullptr)
            head = new_node;
        else
        {
            // Add new head but previously add pointer to previous head
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
            // Go through list until nullptr (last element is found)
            Node<Type>* last_node = head;
            while(last_node->next_element != nullptr)
            {
                last_node = last_node->next_element;
            }
            // add new last node
            last_node->next_element = new_node;
        }
        size++;
    }

    // Adds element on specified index starting counting from head
    void add_at(Type value, unsigned int position)
    {
        // Check if position is valid
        if (position > size or position < 0)
        {
            std::cerr << "Position exceeds size!";
            return;
        }
        else
        {
            // If 0 just perform add head
            if (position == 0)
            {
                add_front(value);
                return;
            }

            Node<Type>* new_node = new Node<Type>(value);
            // Move until desired position
            Node<Type>* currrent_node = head;
            for(unsigned int i=1; i<position; i++)
            {
                currrent_node = currrent_node->next_element;
            }
            // Reasign pointers in order to add new element
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
            // Deleting first element but before that we need to make second element the head element
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
            // if size 1 just delete head
            if (head->next_element == nullptr)
            {
                delete head;
                head = nullptr;
            }
            else
            {
                Node<Type>* prev_last_node = head;
                // We have to reach last element-1 in order to change pointers and then delete last one
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
    void remove_at(unsigned int position)
    {
        // Check if position is valid
        if (position >= size or position < 0)
        {
            std::cerr << "Position exceeds size!";
            return;
        }
        else
        {
            // If position is zero perform remove first
            if (position == 0)
            {
                remove_front();
                return;
            }

            // Move until desired position
            Node<Type>* currrent_node = head;
            for(unsigned int i=1; i<position; i++)
            {
                currrent_node = currrent_node->next_element;
            }
            // Reasign pointers of neighbours and after that delete reached node
            Node<Type>* temp = currrent_node->next_element;
            currrent_node->next_element = currrent_node->next_element->next_element;
            delete temp;
            size--;
        }
    }

    // Clears all nodes stored by this list, useful for deconstructing to free all memory
    void clear()
    {
        // Until head is not nullptr perform delete front
        while(head)
            this->remove_front();
    }

    // Returns first value (head value)
    Type first_value()
    {
        if (head==nullptr)
            throw std::out_of_range("Index is out of range");
        return head->value;
    }

    // Returns last value (tail value)
    Type last_value()
    {
        if (head==nullptr)
            throw std::out_of_range("Index is out of range");
        Node<Type>* last_node = head;
        // Move until last position
        while(last_node->next_element != nullptr)
        {
            last_node = last_node->next_element;
        }
        return last_node->value;
    }

    Type value_at(unsigned int position)
    {
        // Check if position is valid
        if (position >= size or position < 0)
            throw std::out_of_range("Index is out of range");
        else
        {
            // Move until desired position
            Node<Type>* current_node = head;
            for(unsigned int i=0; i<position; i++)
                current_node=current_node->next_element;
            return current_node->value;
        }
    }

    // Returns size of list
    unsigned int get_size()
    {
        return size;
    }

    // Returns position of element
    unsigned int find(Type value)
    {
        // Go through every element until value is equal to given value - then return counted position
        Node<Type>* current_node = head;
        unsigned int i = 0;
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
    // Useful for printing inside our UI
    std::string get_as_string()
    {
        std::string output = "List[";
        Node<Type>* current_node = head;
        if (std::is_integral_v<Type> != true)
            return "ERROR: typename of this list is not supported by this method!";
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

    // Return size of data structure in bytes
    unsigned int get_byte_size()
    {
        return sizeof(SingleListH) + sizeof(Node<Type>)*size;
    }

    // Change value at given position
    void change_at(Type value, unsigned int position)
    {
        if (position < 0 || position >= size)
            return;
            //throw std::out_of_range("Position out of range");
        // Reach desired position
        Node<Type>* current_node = head;
        for(unsigned int i=0; i<position; i++)
            current_node=current_node->next_element;
        current_node->value = value;
        
    }
};
#endif
