#ifndef HASHFUNC
#define HASHFUNC

#include <iostream>


unsigned int hash_modulo_str(std::string key, unsigned int table_size);

unsigned int hash_modulo(int key, unsigned int table_size);

#endif