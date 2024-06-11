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
    int num_bits = (int)log2(table_size);

    // Calculate how many bits key has
    unsigned int key_bits = 0;
    int temp_key = key;
    while (temp_key > 0)
    {
        temp_key >>= 1;
        key_bits++;
    }

    int shift = (key_bits - num_bits) / 2;

    // Bit mask - out table scales as power of 2 we can mask bits!
    unsigned int mask = (1 << num_bits) - 1;

    unsigned int middle_bits = (key >> shift) & mask;


    std::cerr << key << "\n";

    return key % table_size;
}

unsigned int hash_midsquare_ten(int key, unsigned int table_size)
{
    int square = key*key;
    unsigned int dig_num = get_number_of_digits(square);
    std::cerr << key << "\n";

    for(int i=0; i<(dig_num/2)-1; i++)
        key /= 10;

    // This works well for table scaling as power of 10
    //int temp = pow(10, get_number_of_digits(table_size));

    return key % table_size;
}
