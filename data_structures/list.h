#include <iostream>
#include "I_data_structure.h"

/**
 * Node class for single container used by basic list
 * It contains pointer to next container and stores value of type read from template
 * 
 */
template <typename Type>
class Node
{
    Type element_data;
    Node<Type>* next_element;

    Node(Type value) : element_data(value), next(nullptr) {}
};


/**
 * LinkedListH class that represents a list data structure with methodes
 * 
 */
template <typename Type>
class LinkedListH : IDataStructure
{
private:
    Node<Type>* head;
    int size;


public:
    LinkedListH() : head(nullptr), size(0) {}
    ~LinkedListH() {
        clear();
    }

    void add_front(Type value);
    void add_back(Type value);
    void add_at(Type value, int position);

    void remove_front();
    void remove_back();
    void remove_at(int position);
    void clear();

    Type first_value();
    Type last_value();
    Type value_at(int position);

    void size();
    int find(Type value);
    std::string get_as_string();

};
