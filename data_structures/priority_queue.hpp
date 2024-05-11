// #ifndef PRIOQUE

// #include <iostream>
// #include "list_double.hpp"
// #include "priority_item.hpp"

// using namespace std;


// template <typename Type>
// class PriorityQueue : public IDataStructure<Type>
// {
// private:
//    DoubleListHT<PriorityItem<Type>> list;
// public:
 
//  void add_front(Type value) override
// {
//     // We don't support heap add_front
//     throw std::logic_error("Adding at the front of heap is not supported.");
// }
    
// // Insert an element with its priority into the priority queue
// void add_back(Type element, int priority) override
// {
//     PriorityItem<Type> item(element, priority);

//     if (list.empty()) {
//         // Lista jest pusta, dodaj element jako pierwszy
//         list.add_back(item);
//     } else {
//         // Znajdź odpowiednie miejsce dla nowego elementu według priorytetu
//         DoubleNode<PriorityItem<Type>>* current = list.get_head() ;
//         while (current != nullptr) {
//             current = current->next_element;
//         }

//         if (current == nullptr) {
//             // Wstawianie na koniec listy (najniższy priorytet)
//             list.add_back(item);
//         } else {
//             if(item->priority > current->priority)
//             // Wstawianie przed bieżącym węzłem
//             list.add_at(item, list.find(current->value));
//         }
//     }

//     list.size++;
// }

// void add_at(Type value, unsigned int position) override
//     {
//         // We don't support heap add_at
//         throw std::logic_error("Adding at a specific position in heap is not supported.");
//     }


// void remove_front() override
// {
//    if (!list.get_size());
//    {
//     return;
//    }
// }

// void remove_back() override
//     {
//         // We don't support remove_back
//         throw std::logic_error("Removing from the back of heap is not supported.");
//     }

// void remove_at(unsigned int position) override
// {
//     // We don't support remove_at
//     throw std::logic_error("Removing from a specific position in heap is not supported.");
// }


// void change_at(Type value,unsigned int position, int newPriority=0) override
// {
//     if (position >= list.getsize()) {
//         throw std::out_of_range("Position out of range");
//     }
//         Node<Type>* current = list.get_head();
//     for (unsigned int i = 0; i < position; ++i) 
//     {
//         current = current->next;
//     }
//         // Zmiana priorytetu węzła na nowy priorytet
//     current->priority = newPriority;
//     current->value = value;
//     // Przywróć porządek listy po zmianie priorytetu
//     while (current->prev && current->prev->priority < newPriority) {
//         // Węzeł ma wyższy priorytet niż poprzedni, przesuń w górę
//         Node<Type>* prev = current->prev;
//         Node<Type>* next = current->next;

//         // Usunięcie aktualnego węzła z aktualnej pozycji
//         if (next) {
//             next->prev = prev;
//         } else {
//             list.get_tail() = prev;
//         }
//         prev->next = next;

//         // Umieszczenie aktualnego węzła na początku listy (głowa)
//         current->prev = nullptr;
//         current->next = list.get_head();
//         list.get_head()->prev = current;
//         list.get_head() = current;
//     }

//     while (current->next && current->next->priority > newPriority) {
//         // Węzeł ma niższy priorytet niż następny, przesuń w dół
//         Node<Type>* next = current->next;
//         Node<Type>* prev = current->prev;

//         // Usunięcie aktualnego węzła z aktualnej pozycji
//         prev->next = next;
//         next->prev = prev;

//         // Umieszczenie aktualnego węzła na końcu listy (ogon)
//         current->prev = list.get_tail();
//         current->next = nullptr;

//         if ( list.get_tail()) {
//             list.get_tai()->next = current;
//         }
//         list.get_tail() = current;
//     }
// }

// // extreact-max
// Type first_value() override 
// {
//     Type maxValue = list.gethead()->value;
//     list.remove_front();
//     return maxValue;
// }

// unsigned int find(Type value) override
// {
//     // We don't support index of searched value
//     throw std::logic_error("Getting last value of priority queue is not supported.");
// }

// Type find_max(Type value) override
// {
//     if (get_size() > 1);
//     {
//         return list.first_value();
//     }
// }

// unsigned int  get_size() override
// {
//     return list.get_size();
// }

//   unsigned int get_byte_size() override
// {
//     // We don't support getting byte size
//     throw std::logic_error("Getting byte size of heap is not supported.");
// }

// void clear() override
// {
//     list.clear();
// }

// std::string get_as_string() override
// {
//     std::string output = "PriorQueueOnList[";
//     if (std::is_integral_v<Type> != true)
//         return "ERROR: typename of this list is not supported by this method!";
//     for(int i=0; i<list.get_size(); i++)
//     {
//         output += std::to_string(list.value_at(i));
//         if (i != list.get_size()-1)
//             output += ", ";
//     }
//     output += "]";
//     return output;
// }



// Type value_at(unsigned int position) override
// {
//     // We don't support value at
//     throw std::logic_error("Getting value at a specific position in heap is not supported.");
// }

// unsigned int find(Type value) override
// {
//     // We don't support value at
//     throw std::logic_error("Finding value is not supported.");
// }

// Type last_value() override
// {
//     // We don't support getting last value
//     throw std::logic_error("Getting last value of heap is not supported.");
// }
// };
// #endif
