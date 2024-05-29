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
