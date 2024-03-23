#ifndef I_DATA
#define I_DATA
#include<iostream>
/**
 * DataStructure Interface
 * 
 */
template <typename Type>
class IDataStructure
{
public:
    ~IDataStructure() {}

    virtual void add_front(Type value) = 0;
    virtual void add_back(Type value) = 0;
    virtual void add_at(Type value, unsigned int position) = 0;

    virtual void remove_front() = 0;
    virtual void remove_back() = 0;
    virtual void remove_at(unsigned int position) = 0;
    virtual void clear() = 0;

    virtual Type first_value() = 0;
    virtual Type last_value() = 0;
    virtual Type value_at(unsigned int position) = 0;

    virtual unsigned int get_size() = 0;
    virtual unsigned int get_byte_size() = 0;
    virtual unsigned int find(Type value) = 0;
    virtual void change_at(Type value, unsigned int position) = 0;
    virtual std::string get_as_string() = 0;

};
#endif
