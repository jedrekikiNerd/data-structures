#ifndef I_HASH
#define I_HASH

#include<iostream>
#include <functional>


template <typename Type>
class Bucket
{
public:
    std::string key;
    Type value;
    bool taken;

    Bucket() : key(""), value(Type()), taken(false) {} // Domyślny konstruktor

    Bucket(std::string k, Type v, bool t) : key(k), value(v), taken(t) {}
    ~Bucket() {}

    bool operator==(const Bucket& other) const
    {
        return key == other.key;
    }
};
// class Bucket
// {
// public:
//     std::string key;
//     Type value;
//     bool taken;

//     Bucket(std::string k, Type v, bool t) : key(k), value(v), taken(t) {}
//     ~Bucket() {}

//     bool operator==(const Bucket& other) const
//     {
//         return key == other.key;
//     }
// };


/**
 * HASH TABLE Interface
 * 
 */
template <typename Type>
class IHashTable
{
protected:
    // Number of elements in the hash table
    unsigned int size;

    // Pointer to the hashing function
    std::function<unsigned int(const std::string&, unsigned int)> hash_function;

public:
    IHashTable(std::function<unsigned int(const std::string&, unsigned int)> hash_func) : hash_function(hash_func) {}
    ~IHashTable() {}

    // Insert value with given key
    virtual void insert(std::string key, Type value) = 0;

    // Remove value with given key
    virtual void remove(std::string key) = 0;

    // Clears/removes all values from hash table bringing it to initial state
    virtual void clear() = 0;

    // Returns value with given key
    virtual Type value_at(std::string key) = 0;

    // Returns size of hash table - only full buckets
    unsigned int get_size()
    {
        return size;
    }

    // Returns size of hash table in bytes
    virtual unsigned int get_byte_size() = 0;

    // Returns index at which first occurrence of given value is found
    virtual std::string find(Type value) = 0;

    // Returns data structure representation as string (useful for displaying)
    virtual std::string get_as_string() = 0;

    // Checks if a key exists in the hash table
    virtual bool has_key(std::string key) = 0;

    // Returns load factor
    virtual float get_load_factor() = 0;

};
#endif
