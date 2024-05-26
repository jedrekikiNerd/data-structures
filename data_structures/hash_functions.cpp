#include "hash_functions.hpp"

unsigned int hash_modulo(std::string key, unsigned int table_size)
{
    unsigned int sum = 0;
    
    for(char c : key)
    {
        sum += c;
    }

    return sum % table_size;
}