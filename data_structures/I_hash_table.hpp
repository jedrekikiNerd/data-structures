#ifndef I_HASH
#define I_HASH

#include<iostream>
#include <functional>


template <typename Type>
class BucketString
{
public:
    std::string key;
    Type value;
    bool taken;

    BucketString() : key(""), value(Type()), taken(false) {} // Domyślny konstruktor

    BucketString(std::string k, Type v, bool t) : key(k), value(v), taken(t) {}
    ~BucketString() {}

    bool operator==(const BucketString& other) const
    {
        return key == other.key;
    }
};

template <typename Type>
class Bucket
{
public:
    int key;
    Type value;
    bool taken;

    Bucket() : key(0), value(Type()), taken(false) {} // Domyślny konstruktor

    Bucket(int k, Type v, bool t) : key(k), value(v), taken(t) {}
    ~Bucket() {}

    bool operator==(const Bucket& other) const
    {
        return key == other.key;
    }
};

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

public:
    IHashTable() : size(0) {}
    ~IHashTable() {}

    // Insert value with given key
    virtual void insert(std::string key, Type value) {}
    virtual void insert(int key, Type value) {}


    // Remove value with given key
    virtual void remove(std::string key) {}
    virtual void remove(int key) {}

    // Clears/removes all values from hash table bringing it to initial state
    virtual void clear() {}

    // Returns value with given key
    virtual Type value_at(std::string key) {}
    virtual Type value_at(int key) {}

    // Returns size of hash table - only full buckets
    unsigned int get_size()
    {
        return size;
    }

    // Returns size of hash table in bytes
    virtual unsigned int get_byte_size() {}

    // Returns index/key at which first occurrence of given value is found
    virtual std::string find2(Type value) {}
    virtual int find(Type value) {}

    // Returns data structure representation as string (useful for displaying)
    virtual std::string get_as_string() {}

    // Checks if a key exists in the hash table
    virtual bool has_key(std::string key) {}
    virtual bool has_key(int key) {}

    // Returns load factor
    virtual float get_load_factor() {}

};
#endif
