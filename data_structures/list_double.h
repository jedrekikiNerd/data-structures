#ifndef DLISTHT
#define DLISTHT

#include <iostream>
#include <stdexcept>
#include "I_data_structure.h"
#include <type_traits>
#include "nodes.h"


/**
 * LinkedListHT class that represents a list data structure with methods
 * 
 */
template <typename Type>
class DoubleListHT : public IDataStructure<Type>
{
private:
    DoubleNode<Type>* head;
    DoubleNode<Type>* tail;
    unsigned int size;


public:
    DoubleListHT() : head(nullptr), tail(nullptr), size(0) {}
    ~DoubleListHT() {
        clear();
    }

    // Adds element where head ptr is pointing
    void add_front(Type value)
    {
        DoubleNode<Type>* new_node = new DoubleNode<Type>(value);
        // Check if not null
        if (head == nullptr)
        {
            // If null set head and tail to new node
            head = new_node;
            tail = new_node;
        }
        else
        {
            // Add new head but previously add pointer to previous head
            // Also set prev pointer of second element
            new_node->next_element = head;
            head->previous_element = new_node;
            head = new_node;
        }
        size++;
    }

    // Adds element to the tail of the list
    void add_back(Type value)
    {
        DoubleNode<Type>* new_node = new DoubleNode<Type>(value);
        if (head == nullptr)
        {
            // If head null then add new node to both head and tail pointer
            head = new_node;
            tail = new_node;
        }
        else
        {
            // Add new tail but previously set previous tail next element to new node and new node previous to tail
            tail->next_element = new_node;
            new_node->previous_element = tail;
            tail = new_node;  
        }
        size++;
    }

    // Adds element on specified index starting counting from head or from tail
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

            // If size just perform add back
            if (position == size)
            {
                add_back(value);
                return;
            }

            DoubleNode<Type>* new_node = new DoubleNode<Type>(value);
            // Move until desired position but now we can check if start from last or first element
            if(position <= size/2)
            {
                DoubleNode<Type>* currrent_node = head;
                for(unsigned int i=1; i<position; i++)
                {
                    currrent_node = currrent_node->next_element;
                }
                // Reasign pointers in order to add new element
                new_node->next_element = currrent_node->next_element;
                new_node->next_element->previous_element = new_node;
                new_node->previous_element = currrent_node;
                currrent_node->next_element = new_node;
            }
            else
            {
                DoubleNode<Type>* currrent_node = tail;
                for(unsigned int i=size-1; i>position; i--)
                {
                    currrent_node = currrent_node->previous_element;
                }
                // Reasign pointers in order to add new element
                new_node->next_element = currrent_node;
                new_node->previous_element = currrent_node->previous_element;
                currrent_node->previous_element = new_node;
                new_node->previous_element->next_element = new_node;
            }
            size++;
        }
    }

    // Removes first element - based on head pointer
    void remove_front()
    {
        if (head != nullptr) 
        {
            // Deleting first element but before that we need to make second element the head element
            DoubleNode<Type>* temp = head;
            head = head->next_element;
            delete temp;
            size--;
            // If there was only one element then set also tail to nullptr
            if(head == nullptr)
            {
                tail = nullptr;
                return;
            }
            head->previous_element = nullptr;
        }
    }

    // Removes last element - needs to iterate from head to tail
    void remove_back()
    {
        if (head != nullptr)
        {
            // if size 1 just delete head
            if (head == tail)
            {
                delete head;
                tail = nullptr;
                head = nullptr;
            }
            else
            {
                // We delete last element and set nullptr to previous one
                // We can do it in O(1)
                DoubleNode<Type>* temp = tail;
                tail = tail->previous_element;
                tail->next_element = nullptr;
                delete temp;
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
            // If position is size-1 perform remove last
            if (position == size-1)
            {
                remove_back();
                return;
            }

            DoubleNode<Type>* current_node = nullptr;
            // Move to desired position but first decide if we start from first or last element
            if(position <= size/2)
            {
                current_node = head;
                for(unsigned int i = 0; i < position; i++)
                {
                current_node = current_node->next_element;
                }
            }
            else
            {
                current_node = tail;
                for(unsigned int i = size-1; i > position; i--)
                {
                current_node = current_node->previous_element;
                }
            }
            // Reasign pointers of neighbours and after that delete reached node
            DoubleNode<Type>* prev_node = current_node->previous_element;
            DoubleNode<Type>* next_node = current_node->next_element;

            if (prev_node != nullptr)
                prev_node->next_element = next_node;
            if (next_node != nullptr)
                next_node->previous_element = prev_node;

            delete current_node;
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
        if (tail==nullptr)
            throw std::out_of_range("Index is out of range");
        return tail->value;
    }

    Type value_at(unsigned int position)
    {
        // Check if position is valid
        if (position >= size or position < 0)
            throw std::out_of_range("Index is out of range");
        else
        {
            DoubleNode<Type>* current_node = nullptr;
            // Move until desired position starting from first or last element depending on position we want to reach
            if(position <= size/2)
            {
                current_node = head;
                for(unsigned int i=0; i<position; i++)
                    current_node=current_node->next_element;
            }
            else
            {
                current_node = tail;
                for(unsigned int i=size-1; i>position; i--)
                    current_node=current_node->previous_element;
            }
                
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
        DoubleNode<Type>* current_node = head;
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
    std::string get_as_string()
    {
        std::string output = "List[";
        DoubleNode<Type>* current_node = head;
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
        return sizeof(DoubleListHT) + sizeof(DoubleNode<Type>)*size;
    }

    // Change value at given position
    void change_at(Type value, unsigned int position)
    {
        if (position < 0 || position >= size)
            return;
            //throw std::out_of_range("Position out of range");
        
        DoubleNode<Type>* current_node = nullptr;
        // Move until desired position starting from first or last element depending on position we want to reach
        if(position <= size/2)
        {
            current_node = head;
            for(unsigned int i=0; i<position; i++)
                current_node=current_node->next_element;
        }
        else
        {
            current_node = tail;
            for(unsigned int i=size-1; i>position; i--)
                current_node=current_node->previous_element;
        }
        
        current_node->value = value;
    }
};
#endif
