#ifndef PRIOQUE

#include <iostream>
#include "list_double.hpp" 

using namespace std;

class PriorityQueue {
private:
    DoubleListHT<pair<int, int>> queue; // Używamy DoubleListHT do przechowywania par (element, priorytet)
public:
    void insert(int element, int priority) {
        // Dodawanie elementu do kolejki przy użyciu listy dwukierunkowej
        queue.add_back(make_pair(element, priority));
    }

    pair<int, int> extractMax() {
        // Usuwanie i zwracanie maksymalnego elementu z kolejki
        // Wykorzystujemy odpowiednią operację z implementacji listy dwukierunkowej
        pair<int, int> maxElement = queue.last_value();
        queue.remove_back();
        return maxElement;
    }

    pair<int, int> findMax() {
        // Znajdowanie i zwracanie maksymalnego elementu z kolejki
        // Wykorzystujemy odpowiednią operację z implementacji listy dwukierunkowej
        return queue.last_value();
    }

    void modifyKey(int element, int newPriority) {
        // Modyfikowanie priorytetu elementu w kolejce
        // Wykorzystujemy odpowiednią operację z implementacji listy dwukierunkowej
        unsigned int index = 0;
        while (index < queue.get_size()) {
            if (queue.value_at(index).first == element) {
                queue.change_at(make_pair(element, newPriority), index);
                return;
            }
            index++;
        }
    }

    int size() {
        return queue.get_size();
    }
};
#endif
