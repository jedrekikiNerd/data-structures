#ifndef TO_STRINGS
#define TO_STRINGS

#include <iostream>
#include "priority_item.hpp"

template <typename Type>
std::string my_to_string(const PriorityItem<Type>& item)
{
    return "<" + std::to_string(item.priority) + ", " + std::to_string(item.value) + ">";
}

// Funkcja wybierająca odpowiednią konwersję w zależności od typu
template <typename Type>
std::string choose_to_string(const Type& value)
{
    if constexpr (std::is_same_v<Type, int>)
    {
        return std::to_string(value);
    }
    else
    {
        return my_to_string(value);
    }
}

#endif
