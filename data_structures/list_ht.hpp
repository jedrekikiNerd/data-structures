#ifndef LISTHT
#define LISTHT

#include <iostream>
#include <stdexcept>
#include "I_data_structure.hpp"
#include <type_traits>
#include "nodes.hpp"


/**
 * SingleListHT class that represents a list data structure with methods
 * 
 */
template <typename Type>
class SingleListHT : public IDataStructure<Type>
{
private:
    Node<Type>* head;
    Node<Type>* tail;
    unsigned int size;


public:
    SingleListHT() : head(nullptr), tail(nullptr), size(0) {}
    ~SingleListHT()
    {
        clear();
    }

    // Adds element where head ptr is pointing
    void add_front(Type value) override
    {
        Node<Type>* new_node = new Node<Type>(value);
        if (head == nullptr)
        {
            // If null set head and tail to new node
            head = new_node;
            tail = new_node;
        }
        else
        {
            // Add new head but previously add pointer to previous head
            new_node->next_element = head;
            head = new_node;
        }
        size++;
    }

    // Adds element to the tail of the list
    void add_back(Type value, int additional=0) override
    {
        Node<Type>* new_node = new Node<Type>(value);
        if (head == nullptr)
        {
            // If head null then add new node to both head and tail pointer
            head = new_node;
            tail = new_node;
        }
        else
        {
            // Add new tail but previously set previous tail next element to new node
            tail->next_element = new_node;
            tail = new_node;
            
        }
        size++;
    }

    // Adds element on specified index starting counting from head
    void add_at(Type value, unsigned int position) override
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
    void remove_front() override
    {
        if (head != nullptr) 
        {
            // Deleting first element but before that we need to make second element the head element
            Node<Type>* temp = head;
            head = head->next_element;
            delete temp;
            // If there was only one element then set also tail to nullptr
            if(head == nullptr)
                tail = nullptr;
            size--;
        }
    }

    // Removes last element - needs to iterate from head to tail
    void remove_back() override
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
                Node<Type>* prev_last_node = head;
                // We have to reach last element-1 in order to change pointers and then delete last one
                while(prev_last_node->next_element != tail)
                {
                    prev_last_node = prev_last_node->next_element;
                }
                // We delete last element and set nullptr for prev_last
                delete tail;
                tail = prev_last_node;
                tail->next_element = nullptr;
            }
            size--;
        }
    }

    // Removes element at specified position counting from head (0)
    void remove_at(unsigned int position) override
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

            Node<Type>* currrent_node = head;
            // Move to desired position
            for(unsigned int i=1; i<position; i++)
            {
                currrent_node = currrent_node->next_element;
            }
            // Reasign pointers of neighbours and after that delete reached node
            Node<Type>* temp = currrent_node->next_element;
            currrent_node->next_element = temp->next_element;
            delete temp;
            if (currrent_node->next_element == nullptr)
                tail = currrent_node;
            size--;

        }
    }

    // Clears all nodes stored by this list, useful for deconstructing to free all memory
    void clear() override
    {
        // Until head is not nullptr perform delete front
        while(head)
            this->remove_front();
    }

    // Returns first value (head value)
    Type first_value() override
    {
        if (head==nullptr)
            throw std::out_of_range("Index is out of range");
        return head->value;
    }

    // Returns last value (tail value)
    Type last_value() override
    {
        if (tail==nullptr)
            throw std::out_of_range("Index is out of range");
        return tail->value;
    }

    Type value_at(unsigned int position) override
    {
        // Check if position is valid
        if (position >= size or position < 0)
            throw std::out_of_range("Index is out of range");
        else
        {
            // Return tail if position is size-1
            if(position == size-1)
                return tail->value;
            // Move until desired position
            Node<Type>* current_node = head;
            for(unsigned int i=0; i<position; i++)
                current_node=current_node->next_element;
            return current_node->value;
        }
    }

    // Returns size of list
    unsigned int get_size() override
    {
        return size;
    }

    // Returns position of element
    unsigned int find(Type value) override
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
    std::string get_as_string() override
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
    unsigned int get_byte_size() override
    {
        return sizeof(SingleListHT) + sizeof(Node<Type>)*size;
    }

    // Change value at given position
    void change_at(Type value, unsigned int position, int additional=0) override
    {
        if (position < 0 || position >= size)
            return;
            //throw std::out_of_range("Position out of range");
    
        if(position == size-1)
        {
            tail->value = value;
            return;
        }

        // Reach desired position
        Node<Type>* current_node = head;

        for(unsigned int i=0; i<position; i++)
            current_node=current_node->next_element;
        
        // Perform value change
        current_node->value = value;
    }
};
#endif
