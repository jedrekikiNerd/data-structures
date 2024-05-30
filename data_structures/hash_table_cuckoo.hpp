#ifndef I_HASH_CUCKOO
#define I_HASH_CUCKOO

#include "I_hash_table.hpp"
#include "default_values.hpp"
#include <functional>
#include <stdexcept>

#define MAX_ITERATIONS 1000

template <typename Type>
class HashTableCuckoo : public IHashTable<Type>
{
private:
    unsigned int table_size = 16;
    Bucket<Type>* table1;
    Bucket<Type>* table2;
    std::function<unsigned int(int, unsigned int)> hash_func1;
    std::function<unsigned int(int, unsigned int)> hash_func2;

    unsigned int get_index1(int key)
    {
        return this->hash_func1(key, table_size);
    }

    unsigned int get_index2(int key)
    {
        return this->hash_func2(key, table_size);
    }

    unsigned int hash_func_quadratic(int key, unsigned int table_size, unsigned int i)
    {
        return (key + i * i) % table_size;
    }

    void resize_table()
    {
        unsigned int new_size = table_size * 2;
        Bucket<Type>* new_table1 = new Bucket<Type>[new_size]();
        Bucket<Type>* new_table2 = new Bucket<Type>[new_size]();

        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table1[i].taken)
                insert_into_new_table(new_table1, new_table2, new_size, table1[i].key, table1[i].value);
            if (table2[i].taken)
                insert_into_new_table(new_table1, new_table2, new_size, table2[i].key, table2[i].value);
        }

        delete[] table1;
        delete[] table2;
        table1 = new_table1;
        table2 = new_table2;
        table_size = new_size;
    }

    void insert_into_new_table(Bucket<Type>* new_table1, Bucket<Type>* new_table2, unsigned int new_size, int key, Type value)
    {
        unsigned int index1 = this->hash_func1(key, new_size);
        if (!new_table1[index1].taken)
        {
            new_table1[index1] = Bucket<Type>(key, value, true);
        }
        else
        {
            unsigned int index2 = this->hash_func2(key, new_size);
            if (!new_table2[index2].taken)
            {
                new_table2[index2] = Bucket<Type>(key, value, true);
            }
            else
            {
                throw std::runtime_error("Rehashing failed during table resizing.");
            }
        }
    }

public:
    HashTableCuckoo(std::function<unsigned int(int, unsigned int)> hash_func1, std::function<unsigned int(int, unsigned int)> hash_func2)
        : hash_func1(hash_func1), hash_func2(hash_func2)
    {
        table1 = new Bucket<Type>[table_size]();
        table2 = new Bucket<Type>[table_size]();
    }

    ~HashTableCuckoo()
    {
        delete[] table1;
        delete[] table2;
    }

    void insert(int key, Type value)
    {
        int original_key = key;
        Type original_value = value;

        for (unsigned int i = 0; i < MAX_ITERATIONS; ++i)
        {
            unsigned int index1 = hash_func_quadratic(key, table_size, i);
            if (!table1[index1].taken)
            {
                table1[index1] = Bucket<Type>(key, value, true);
                this->size++;
                return;
            }

            // Przemieszczenie elementu z tablicy 1 do zmiennych tymczasowych
            int temp_key = table1[index1].key;
            Type temp_value = table1[index1].value;
            table1[index1] = Bucket<Type>(key, value, true);

            key = temp_key;
            value = temp_value;

            unsigned int index2 = hash_func_quadratic(key, table_size, i);
            if (!table2[index2].taken)
            {
                table2[index2] = Bucket<Type>(key, value, true);
                this->size++;
                return;
            }

            // Przemieszczenie elementu z tablicy 2 do zmiennych tymczasowych
            temp_key = table2[index2].key;
            temp_value = table2[index2].value;
            table2[index2] = Bucket<Type>(key, value, true);

            key = temp_key;
            value = temp_value;
        }

        // Jeśli pętla się zakończy, oznacza to, że wykryto cykl
        resize_table();
        insert(original_key, original_value);
    }

    void remove(int key)
    {
        // Iterowanie przez całą tablicę 1
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table1[i].taken && table1[i].key == key)
            {
                table1[i].taken = false;
                this->size--;
                return;
            }
        }

        // Iterowanie przez całą tablicę 2
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table2[i].taken && table2[i].key == key)
            {
                table2[i].taken = false;
                this->size--;
                return;
            }
        }
    }

    void clear() override
    {
        delete[] table1;
        delete[] table2;
        table1 = new Bucket<Type>[table_size]();
        table2 = new Bucket<Type>[table_size]();
        this->size = 0;
    }

    Type value_at(int key)
    {
        unsigned int index1 = get_index1(key);
        if (table1[index1].key == key && table1[index1].taken)
            return table1[index1].value;

        unsigned int index2 = get_index2(key);
        if (table2[index2].key == key && table2[index2].taken)
            return table2[index2].value;

        throw std::runtime_error("Key not found");
    }

    unsigned int get_byte_size()
    {
        return sizeof(*this) + sizeof(Bucket<Type>) * 2 * table_size;
    }

    int find(Type value)
    {
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table1[i].taken && table1[i].value == value)
                return table1[i].key;
            if (table2[i].taken && table2[i].value == value)
                return table2[i].key;
        }
        return UINT_MAX;
    }

    std::string get_as_string() override
    {
        std::string output;
        for (unsigned int i = 0; i < table_size; ++i)
        {
            if (table1[i].taken)
                output += "Table 1 - Index " + std::to_string(i) + ": " + choose_to_string(table1[i]) + "\n";
            if (table2[i].taken)
                output += "Table 2 - Index " + std::to_string(i) + ": " + choose_to_string(table2[i]) + "\n";
        }
        return output;
    }

    bool has_key(int key) override
    {
        unsigned int index1 = get_index1(key);
        if (table1[index1].key == key && table1[index1].taken)
            return true;

        unsigned int index2 = get_index2(key);
        if (table2[index2].key == key && table2[index2].taken)
            return true;

        return false;
    }

    float get_load_factor()
    {
        return static_cast<float>(this->size) / (2 * table_size);
    }
};

#endif
