#ifndef HASH_TABLE_OPEN_ADDRESSING
#define HASH_TABLE_OPEN_ADDRESSING

#include "dynamic_array.hpp"
#include <functional>
#include <sstream>
#include <type_traits>

template <typename Key, typename Type>
class HashTableOpenAddressing {
private:
    struct Entry {
        Key key;
        Type value;
        bool occupied;
        bool deleted;

        Entry() : occupied(false), deleted(false) {}
    };

    DynamicArray<Entry> table;
    unsigned int num_elements;

    unsigned int hash(Key key) {
        return std::hash<Key>{}(key) % table.get_size();
    }

    void resize() {
        DynamicArray<Entry> old_table = table;
        table = DynamicArray<Entry>(old_table.get_size() * 2);

        for (unsigned int i = 0; i < old_table.get_size(); ++i) {
            if (old_table[i].occupied && !old_table[i].deleted) {
                insert(old_table[i].key, old_table[i].value);
            }
        }
    }

public:
    HashTableOpenAddressing() : num_elements(0) {
        table = DynamicArray<Entry>(8);
    }

    void insert(Key key, Type value) {
        if (num_elements >= table.get_size() / 2) {
            resize();
        }

        unsigned int index = hash(key);
        while (table[index].occupied && !table[index].deleted) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % table.get_size();
        }

        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        table[index].deleted = false;
        num_elements++;
    }

    bool find(Key key, Type &value) {
        unsigned int index = hash(key);
        unsigned int start_index = index;

        while (table[index].occupied) {
            if (table[index].key == key && !table[index].deleted) {
                value = table[index].value;
                return true;
            }
            index = (index + 1) % table.get_size();
            if (index == start_index) {
                break;
            }
        }
        return false;
    }

    void remove(Key key) {
        unsigned int index = hash(key);
        unsigned int start_index = index;

        while (table[index].occupied) {
            if (table[index].key == key && !table[index].deleted) {
                table[index].deleted = true;
                num_elements--;
                return;
            }
            index = (index + 1) % table.get_size();
            if (index == start_index) {
                break;
            }
        }
    }

    unsigned int get_size() const {
        return num_elements;
    }

    std::string get_as_string() const {
        std::ostringstream output;
        output << "HashTableOpenAddressing[";

        bool first = true;
        for (unsigned int i = 0; i < table.get_size(); ++i) {
            if (table[i].occupied && !table[i].deleted) {
                if (!first) {
                    output << ", ";
                }
                output << "<" << std::to_string(table[i].key) << ", " << choose_to_string(table[i].value) << ">";
                first = false;
            }
        }
        output << "]";
        return output.str();
    }

    unsigned int get_size() {
        return table.get_size;
    }

    void clear() override
    {
        table.clear();
    }

    unsigned int get_byte_size() override
    {
        return sizeof(HashTableOpenAddressing) + array.get_byte_size();
    }



    void add_front(Type value) override
    {
        // We don't support queue_array add_front
        throw std::logic_error("Adding at the front of queue_array is not supported.");
    }

    void add_back(Type value) override
    {
        // We don't support queue_array add_front
        throw std::logic_error("Adding at the front of queue_array is not supported.");
    }

    void remove_front() override
    {
        // We don't support remove_back
        throw std::logic_error("Removing from the front of queue is not supported.");
    }

    void remove_back() override
    {
        // We don't support remove_back
        throw std::logic_error("Removing from the back of queue_array is not supported.");
    }

    Type last_value() override
    {
        // We don't support getting last value
        throw std::logic_error("Getting last value of priority queue is not supported.");
    }

    void change_at(Type value, unsigned int position, int new_priority=0) override
    {
     throw std::logic_error("Getting last value of priority queue is not supported.");
    }

    Type first_value() override 
    {
    throw std::logic_error("Getting last value of priority queue is not supported.");
    }

    Type value_at(unsigned int position) override
    {
    throw std::logic_error("Getting last value of priority queue is not supported.");
    }


};
#endif