#ifndef PRIOQUE

#include <iostream>
#include "list_double.hpp" 

using namespace std;



// struct Node {
//     Type data;
//     int priority;
//     Node* prev;
//     Node* next;

//     Node(Type value, int prio, Node* p = nullptr, Node* n = nullptr)
//         : data(value), priority(prio), prev(p), next(n) {}
// };
template <typename Type>
class PriorityQueue : public IDataStructure<Type>
{
private:
    Node<Type>* head;
    Node<Type>* tail;
public:
 PriorityQueue() : head(nullptr), tail(nullptr) {}
    
void insert(Type element, int priority) 
{
    Node<Type>* newNode = new Node<Type>(element, priority);

    if (!head) 
    {
        // Lista jest pusta
        head = tail = newNode;
    } 
     else 
        {
            // Wstawianie elementu w odpowiednie miejsce według priorytetu (malejąco)
        Node<Type>* current = head;
        while (current && current->priority >= priority) 
        {
            current = current->next;
        }

            if (!current) 
            {
                // Wstawianie na końcu listy (najniższy priorytet)
                newNode->prev = tail;
                tail->next = newNode;
                tail = newNode;
            } else 
            {
                // Wstawianie przed bieżącym węzłem
                newNode->prev = current->prev;
                newNode->next = current;
                if (current == head) 
                {
                    head = newNode;
                } else 
                {
                    current->prev->next = newNode;
                }
                current->prev = newNode;
            }
        }
}


Type extractMax() 
{
    if (!head)
    {
        return 0;
    }

    Type element = head->data;
    Node<Type>* temp = head;

    if (head == tail) 
    {
        // Jedyny element w kolejce
        head = tail = nullptr;
    } else
    {
        // Usuwanie pierwszego elementu
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    return element;
}

void modify_key(Type element, int newPriority) 
{
        Node<Type>* current = head;
        while (current) 
        {
            if (current->data == element) 
            {
                current->priority = newPriority;
                // Przywróć porządek listy po zmianie priorytetu
                if (current != head) 
                {
                    // Przesuń węzeł w górę lub w dół, aby zachować porządek
                    if (current->prev->priority < newPriority) 
                    {
                        // Węzeł ma wyższy priorytet niż poprzedni, przesuń w górę
                        Node<Type>* prev = current->prev;
                        Node<Type>* next = current->next;
                        prev->next = next;
                        if (next) 
                        {
                            next->prev = prev;
                        } else 
                        {
                            tail = prev;
                        }
                        current->prev = nullptr;
                        current->next = head;
                        head->prev = current;
                        head = current;
                    } else if (current->next && current->next->priority > newPriority) 
                    {
                        // Węzeł ma niższy priorytet niż następny, przesuń w dół
                        Node<Type>* next = current->next;
                        current->prev->next = next;
                        next->prev = current->prev;
                        current->prev = tail;
                        current->next = nullptr;
                        tail->next = current;
                        tail = current;
                    }
                }
                break;
            }
            current = current->next;
        }
}



bool empty() const 
{
    return head == nullptr;
}


Type find_max() const {
    if (!head) 
    {
     return 0;
    }
    return head->data;
}

    int return_size() const {
        int size = 0;
        Node<Type>* current = head;
    while (current) 
    {
        size++;
        current = current->next;
    }
        return size;
    }

    void clear() override
    {
        queue.clear();
    }

};
#endif
