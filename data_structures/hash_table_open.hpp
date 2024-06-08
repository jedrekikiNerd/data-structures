#ifndef I_HASH_OPEN_ADDRESSING
#define I_HASH_OPEN_ADDRESSING

#include "I_hash_table.hpp"
#include "default_values.hpp"
#include <functional>
#include <stdexcept>

/**
 * Hash Table with Open Addressing
 * 
 */
template <typename Type>
class HashTableOpenAddressing : public IHashTable<Type>
{
private:
    // Table that contains buckets - we set initial value as 16
    unsigned int table_size = 16;
    Bucket<Type>* table;
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
        Bucket<Type>* new_table = new Bucket<Type>[new_size]();
        unsigned int old_size = table_size;
        table_size = new_size;

        for (unsigned int i = 0; i < old_size; ++i)
        {
            if (table[i].taken)
            {
                unsigned int index = get_index(table[i].key);
                while (new_table[index].taken)
                {
                    index = (index + 1) % new_size;
                }
                new_table[index] = table[i];
            }
        }

        delete[] table;
        table = new_table;
    }

public:
    HashTableOpenAddressing(std::function<unsigned int(int, unsigned int)> hash_func) : hash_function(hash_func)
    {
        table = new Bucket<Type>[16];
    }

    ~HashTableOpenAddressing()
    {
        delete[] table;
    }

    // Insert value with given key
    void insert(int key, Type value)
    {
        resize_table(); // Before inserting new element, check if we need to resize the table

        unsigned int index = get_index(key);
        unsigned int original_index = index;

        // Check for empty place
        while (table[index].taken)
        {
            if (table[index].key == key)
            {
                // Key already exists - just update :)
                table[index].value = value;
                return;
            }
            index = (index + 1) % table_size;
            if (index == original_index)
            {
                throw std::runtime_error("Hashtable is full, even after resizing.");
            }
        }

        // Insert the new element into empty slot
        table[index] = Bucket<Type>(key, value, true);
        this->size++;
    }


    void remove(int key) 
    {
        unsigned int index = get_index(key);

        // Find key - linear search from index returned by hash function
        while (table[index].taken)
        {
            if (table[index].key == key)
            {
                table[index].taken = false;
                this->size--;

                resize_table(); // After removing check if we need to resize the table
                return;
            }
            index = (index + 1) % table_size;
        }
    }


    // Clears/removes all values from hash table bringing it to initial state
    void clear() override
    {
        delete[] table;
        table_size = 16;
        table = new Bucket<Type>[table_size];
        this->size = 0;
    }

    // Returns value with given key
    Type value_at(int key) override
    {
        unsigned int index = get_index(key);
        while (table[index].taken)
        {
            if (table[index].key == key)
                return table[index].value;
            index = (index + 1) % table_size;
        }
        throw std::runtime_error("Key not found");
    }

    // Returns size of hash table in bytes
    unsigned int get_byte_size() override
    {
        return sizeof(*this) + sizeof(Bucket<Type>) * table_size;
    }

    // Returns key at which first occurrence of given value is found - if it doesnt exist it returns "-1"
    int find(Type value) override
    {
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table[i].taken && table[i].value == value)
                return table[i].key;
        }
        return UINT_MAX;
    }

    // Returns data structure representation as string (useful for displaying)
    std::string get_as_string() override
    {
        std::string output;
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table[i].taken)
            {
                output += "Index " + std::to_string(i) + ": ";
                output += choose_to_string(table[i]);
                output += "\n";
            }
        }
        return output;
    }

    // Checks if a key exists in the hash table
    bool has_key(int key) override
    {
        unsigned int index = get_index(key);
        while (table[index].taken)
        {
            if (table[index].key == key)
                return true;
            index = (index + 1) % table_size;
        }
        return false;
    }

    // Returns load factor
    float get_load_factor() override
    {
        return static_cast<float>(this->size) / table_size;
    }
};

#endif
