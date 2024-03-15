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


template <typename Type>
class LinkedListH
{
private:
    Node<Type>* head;
    int size;


public:
    LinkedListH() : head(nullptr), size(0) {}
    ~LinkedListH() {
        clear();
    }

    void add_front();
    void add_back();
    void add_at();

    void remove_front();
    void remove_back();
    void remove_at();
    void clear();

    void first_element();
    void last_element();
    void first_value();
    void last_value();
    void size();
    void find();

};

template <typename Type>
class LinkedListHT
{
private:
    Node<Type>* head;
    Node<Type>* tail;
    int size;


public:
    LinkedListHT() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedListHT() {
        clear();
    }

    void add_front();
    void add_back();
    void add_at();

    void remove_front();
    void remove_back();
    void remove_at();
    void clear();

    void first_element();
    void last_element();
    void first_value();
    void last_value();
    void size();
    void find();

};
