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
class HashTableOpenAddressingSTR : public IHashTable<Type>
{
private:
    // Table that contains buckets - we set initial value as 16
    unsigned int table_size = 16;
    BucketString<Type>* table;

    // Get the index for a given key
    unsigned int get_index(std::string& key)
    {
        return this->hash_function_str(key, table_size);
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
    // Resize the table to a new size
void resize_table(unsigned int new_size)
{
    BucketString<Type>* new_table = new BucketString<Type>[new_size]();
    for (unsigned int i = 0; i < table_size; ++i)
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
    table_size = new_size;
}


public:
    HashTableOpenAddressingSTR(std::function<unsigned int(const std::string&, unsigned int)> hash_func) : IHashTable<Type>(hash_func)
    {
        table = new BucketString<Type>[16];
    }

    ~HashTableOpenAddressing()
    {
        delete[] table;
    }

    // Insert value with given key
    void insert(std::string key, Type value)
{
    resize_table(); // Before inserting new element, check if we need to resize the table

    unsigned int index = get_index(key);
    unsigned int original_index = index;
    while (table[index].taken)
    {
        if (table[index].key == key) {
            table[index].value = value; // Update value if key already exists
            return;
        }
        index = (index + 1) % table_size;
        if (index == original_index) // If we have traversed the whole table and found no empty slot, resize the table
        {
            resize_table(table_size * 2);
            original_index = get_index(key);
            index = original_index;
        }
    }
    table[index] = BucketString<Type>(key, value, true);
    this->size++;
}

// Remove value with given key
void remove(std::string key)
{
    unsigned int index = get_index(key);
    unsigned int original_index = index;
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
        if (index == original_index) // If we have traversed the whole table and found no entry with the given key, exit
            return;
    }
}

    // Clears/removes all values from hash table bringing it to initial state
    void clear()
    {
        delete[] table;
        table_size = 16;
        table = new BucketString<Type>[table_size];
        this->size = 0;
    }

    // Returns value with given key
    Type value_at(std::string key)
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
    unsigned int get_byte_size()
    {
        return sizeof(*this) + sizeof(BucketString<Type>) * table_size;
    }

    // Returns key at which first occurrence of given value is found - if it doesnt exist it returns "-1"
    std::string find(Type value)
    {
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table[i].taken && table[i].value == value)
                return table[i].key;
        }
        return "-1";
    }

    // Returns data structure representation as string (useful for displaying)
    std::string get_as_string()
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
    bool has_key(std::string key)
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
    float get_load_factor()
    {
        return static_cast<float>(this->size) / table_size;
    }
};

#endif
