#ifndef I_HASH_CHAIN
#define I_HASH_CHAIN

#include "I_hash_table.hpp"
#include "list_double.hpp"
#include "default_values.hpp"
#include "nodes.hpp"


/**
 * Hash Table Separate Chaining
 * 
 */
template <typename Type>
class HashTableSeperateChaining : public IHashTable<Type>
{
private:
    // Table that contains buckets - we set initial value as 16
    unsigned int table_size = 16;
    DoubleListHT<Bucket<Type>>* table;
    std::function<unsigned int(int, unsigned int)> hash_function;

    // Get the index for a given key
    unsigned int get_index(int key)
    {
        return this->hash_function(key, table_size);
    }

    // Resize the table (increase or decrease) based on the load factor
    void resize_table()
    {
        float load_factor = static_cast<float>(this->size) / table_size;

        if (load_factor > 0.5)
        {
            resize_table(table_size * 2);
        }
        else if (load_factor < 0.125 and table_size > 16)
        {
            resize_table(table_size / 2);
        }
    }

    // Resize the table to a new size
    void resize_table(unsigned int new_size)
    {
        DoubleListHT<Bucket<Type>>* new_table = new DoubleListHT<Bucket<Type>>[new_size];
        unsigned int old_size = table_size;
        table_size = new_size;

        // Rehash all elements into the new table
        for (unsigned int i = 0; i < old_size; i++)
        {
            DoubleNode<Bucket<Type>>* current_node = table[i].get_head_ptr();
        
            while(current_node != nullptr)
            {
                unsigned int index = get_index(current_node->value.key);
                new_table[index].add_back(current_node->value);
                current_node = current_node->next_element;
            }
        }

        delete[] table;
        table = new_table;
    }

public:
    HashTableSeperateChaining(std::function<unsigned int(int, unsigned int)> hash_func) : hash_function(hash_func) {table = new DoubleListHT<Bucket<Type>>[16];}

    ~HashTableSeperateChaining()
    {
        delete[] table;
    }

    // Insert value with given key
    void insert(int key, Type value) override
    {
        resize_table(); // Before inserting new_element check if we need to resize the table

        unsigned int index = get_index(key);
        Bucket<Type> new_bucket(key, value, true);
        
        if (!table[index].find_and_replace(new_bucket, new_bucket))
        {
            table[index].add_back(new_bucket);
            this->size++;
        }
    }

    // Remove value with given key
    void remove(int key) override
    {
        unsigned int index = get_index(key);
        Bucket<Type> remove_bucket(key, default_value<Type>(), true);
        
        if (table[index].find_and_remove(remove_bucket))
            this->size--;
        
        resize_table(); // After removing check if we need to resize the table
    }

    // Clears/removes all values from hash table bringing it to initial state
    void clear() override
    {
        delete[] table;
        table_size = 16;
        table = new DoubleListHT<Bucket<Type>>[table_size];
        this->size = 0;
    }

    // Returns value with given key
    Type value_at(int key) override
    {
        unsigned int index = get_index(key);
        DoubleNode<Bucket<Type>> * current_node = table[index].get_head_ptr();
        
        while(current_node != nullptr)
        {
            if (current_node->value.key == key)
                return current_node->value.value;
            current_node = current_node->next_element;
        }
        throw std::runtime_error("Key not present");
    }

    // Returns size of hash table in bytes
    unsigned int get_byte_size() override
    {
        unsigned int byte_size = sizeof(*this);
        for (unsigned int i = 0; i < table_size; i++)
        {
            byte_size += table[i].get_byte_size();
        }
        return byte_size;
    }

    // Returns key at which first occurrence of given value is found - if it doesnt existr it returns -1 as string
    int find(Type value) override
    {
        int i=0;
        int i2 = 0;
        while(i<this->size)
        {
            DoubleNode<Bucket<Type>>* current_node = table[i2].get_head_ptr();
            
            while(current_node != nullptr)
            {
                if (current_node->value.value == value)
                    return current_node->value.key;
                current_node = current_node->next_element;
                i++;
            }
            i2++;
        }
        return UINT_MAX;
    }

    // Returns data structure representation as string (useful for displaying)
    std::string get_as_string() override
    {
        std::string output;
        unsigned int i2 = 0;
        unsigned int i = 0;
        while (i2 < this->size and i < table_size)
        {
            if (table[i].get_size())
            {
                output += "Bucket " + std::to_string(i) + ": ";
                output += table[i].get_as_string();
                i2 += table[i].get_size();
                output += "\n";
            }
            i++;
        }
        return output;
    }

    // Checks if a key exists in the hash table
    bool has_key(int key) override
    {
        unsigned int index = get_index(key);
        if (table[index].get_size())
        {
            DoubleNode<Bucket<Type>>* current_node = table[index].get_head_ptr();
            while(current_node != nullptr)
            {
                if (current_node->value.key == key)
                    return true;
                current_node = current_node->next_element;
            }
            return false;
        }
        return false;
    }

    // Returns load factor
    float get_load_factor() override
    {
        return static_cast<float>(this->size) / table_size;
    }

    // Returns number of collisions
    unsigned int get_collisons()
    {
        unsigned int collisions = 0;
        for(unsigned int i=0; i<table_size; i++)
        {
            collisions += table[i].get_size()-1;
        }
        return collisions;
    }

};
#endif
