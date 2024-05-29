#ifndef I_HASH_CHAIN
#define I_HASH_CHAIN

#include "I_hash_table.hpp"
#include "list_double.hpp"
//#include "default_values.hpp"
#include "nodes.hpp"


/**
 * Hash Table Separate Chaining
 * 
 */
template <typename Type>
class HashTableSeperateChainingSTR : public IHashTable<Type>
{
private:
    // Table that contains BucketStrings - we set initial value as 16
    unsigned int table_size = 16;
    DoubleListHT<BucketString<Type>>* table;

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
    void resize_table(unsigned int new_size)
    {
        DoubleListHT<BucketString<Type>>* new_table = new DoubleListHT<BucketString<Type>>[new_size];

        // Rehash all elements into the new table
        for (unsigned int i = 0; i < table_size; i++)
        {
            DoubleNode<BucketString<Type>>* current_node = table[i].get_head_ptr();
        
            while(current_node != nullptr)
            {
                unsigned int index = get_index(current_node->value.key);
                new_table[index].add_back(current_node->value);
                current_node = current_node->next_element;
            }
        }

        delete[] table;
        table = new_table;
        table_size = new_size;
    }

public:
    HashTableSeperateChainingSTR(std::function<unsigned int(const std::string&, unsigned int)> hash_func) : IHashTable<Type>(hash_func) {table = new DoubleListHT<BucketString<Type>>[16];}

    ~HashTableSeperateChaining()
    {
        delete[] table;
    }

    // Insert value with given key
    void insert(std::string key, Type value)
    {
        resize_table(); // Before inserting new_element check if we need to resize the table

        unsigned int index = get_index(key);
        BucketString<Type> new_BucketString(key, value, true);
        
        if (!table[index].find_and_replace(new_BucketString, new_BucketString))
        {
            table[index].add_back(new_BucketString);
            this->size++;
        }
    }

    // Remove value with given key
    void remove(std::string key)
    {
        unsigned int index = get_index(key);
        BucketString<Type> remove_BucketString(key, default_value<Type>(), true);
        
        if (table[index].find_and_remove(remove_BucketString))
            this->size--;
        
        resize_table(); // After removing check if we need to resize the table
    }

    // Clears/removes all values from hash table bringing it to initial state
    void clear()
    {
        delete[] table;
        table_size = 16;
        table = new DoubleListHT<BucketString<Type>>[table_size];
        this->size = 0;
    }

    // Returns value with given key
    Type value_at(std::string key)
    {
        unsigned int index = get_index(key);
        DoubleNode<BucketString<Type>> * current_node = table[index].get_head_ptr();
        
        while(current_node != nullptr)
        {
            if (current_node->value.key == key)
                return current_node->value.value;
            current_node = current_node->next_element;
        }
        return "";
        throw std::runtime_error("Key not present");
    }

    // Returns size of hash table in bytes
    unsigned int get_byte_size()
    {
        unsigned int byte_size = sizeof(*this);
        for (unsigned int i = 0; i < table_size; i++)
        {
            byte_size += table[i].get_byte_size();
        }
        return byte_size;
    }

    // Returns key at which first occurrence of given value is found - if it doesnt existr it returns -1 as string
    std::string find2(Type value)
    {
        int i=0;
        int i2 = 0;
        while(i<this->size)
        {
            DoubleNode<BucketString<Type>>* current_node = table[i2].get_head_ptr();
            
            while(current_node != nullptr)
            {
                if (current_node->value.value == value)
                    return current_node->value.key;
                current_node = current_node->next_element;
                i++;
            }
            i2++;
        }
        return "-1";
        throw std::runtime_error("Key not found");
    }

    // Returns data structure representation as string (useful for displaying)
    std::string get_as_string()
    {
        std::string output;
        unsigned int i2 = 0;
        unsigned int i = 0;
        while (i2 < this->size and i < table_size)
        {
            if (table[i].get_size())
            {
                output += "BucketString " + std::to_string(i) + ": ";
                output += table[i].get_as_string();
                i2 += table[i].get_size();
                output += "\n";
            }
            i++;
        }
        return output;
    }

    // Checks if a key exists in the hash table
    bool has_key(std::string key)
    {
        unsigned int index = get_index(key);
        if (table[index].get_size())
            return true;
        return false;
    }

    // Returns load factor
    float get_load_factor()
    {
        return static_cast<float>(this->size) / table_size;
    }

};
#endif
