#ifndef DEFAULTV
#define DEFAULTV

#include <iostream>


// Function to get default value for a type
template <typename T>
inline T default_value()
{
    return T();
}

// Specialization for int
template <>
inline int default_value<int>()
{
    return 0;
}

// Specialization for std::string
template <>
inline std::string default_value<std::string>()
{
    return "";
}

#endif