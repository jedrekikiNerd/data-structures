#ifndef manual_ui_ht
#define manual_ui_ht

#include <iostream>
#include "I_hash_table.hpp"


// Agent between UI and data structure insert
int insert_ht(IHashTable<int> *ht);

// Agent between UI and data structure remove
int remove_ht(IHashTable<int> *ht);

// Agent between UI and data structure get_size
int get_size_ht(IHashTable<int> *ht);

// Agent between UI and data structure find
int find_ht(IHashTable<int> *ht);

// Agent between UI and data structure value_at
int value_at_ht(IHashTable<int> *ht);

// Agent between UI and data structure get_load_factor
int get_load_factor_ht(IHashTable<int> *ht);

// Agent between UI and data structure has_key
int has_key_ht(IHashTable<int> *ht);

// Agent between UI and data structure clear
int clear_ht(IHashTable<int> *ht);

// Agent between UI and filling from file
int fill_from_file_ht(IHashTable<int> *ht);

#endif