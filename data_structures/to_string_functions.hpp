#ifndef TO_STRINGS
#define TO_STRINGS

#include <iostream>
#include "I_hash_table.hpp"

template <typename Type>
std::string my_to_string2(const Bucket<Type>& bucket)
{
    return "<" + bucket.key + " -> " + std::to_string(bucket.value) + ">";
}

// Funkcja wybierająca odpowiednią konwersję w zależności od typu
template <typename Type>
std::string choose_to_string(const Type& value)
{
    if constexpr (std::is_same_v<Type, int>)
    {
        return std::to_string(value);
    }
    else if constexpr (std::is_same_v<Type, Bucket<int>>)
    {
        return my_to_string2(value);
    }
}

#endif
