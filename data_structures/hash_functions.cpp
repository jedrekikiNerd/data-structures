#include "hash_functions.hpp"
#include <cmath>

unsigned get_number_of_digits(unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

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

unsigned int hash_modulo_knuth_version(int key, unsigned int table_size)
{
    return std::abs(key*(key+3)) % table_size;
}

unsigned int hash_multiplication(int key, unsigned int table_size)
{
    double A = (std::sqrt(3) - 1) / 2; // some const value between 0 and 1
    double fractional_part = (key * A) - std::floor(key * A); // Fractional part of key times A
    return static_cast<unsigned int>(std::floor(table_size * fractional_part));
}

unsigned int hash_midsquare(int key, unsigned int table_size)
{
    int square = key*key;
    unsigned int dig_num = get_number_of_digits(square);

    for(int i=0; i<(dig_num/2)-1; i++)
        key /= 10;

    int temp = pow(10, get_number_of_digits(table_size));

    return key % temp;
}
