#include "hash_functions.hpp"

unsigned int hash_modulo_str(std::string key, unsigned int table_size)
{
    unsigned int sum = 0;
    
    for(char c : key)
    {
        sum += c;
    }

    return sum % table_size;
}

unsigned int hash_modulo(int key, unsigned int table_size)
{
    return std::abs(key) % table_size;
}

unsigned int hash_modulo2(int key, unsigned int table_size)
{
    return (std::abs(key) / table_size) % table_size;
}

unsigned int jenkins_one_at_a_time_hash(int key, unsigned int table_size)
{
    unsigned int hash = 0;
    unsigned char* data = (unsigned char*)&key;

    for (size_t i = 0; i < sizeof(key); i++)
    {
        hash += data[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash % table_size;
}
