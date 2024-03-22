#ifndef manual_ui_dt
#define manual_ui_dt

#include <iostream>
#include "I_data_structure.h"


// Agent between UI and data structure add_front
int add_front(IDataStructure<int> *dt);

// Agent between UI and data structure add_back
int add_back(IDataStructure<int> *dt);

// Agent between UI and data structure add_at
int add_at(IDataStructure<int> *dt);

// Agent between UI and data structure remove_front
int remove_front(IDataStructure<int> *dt);

// Agent between UI and data structure remove_back
int remove_back(IDataStructure<int> *dt);

// Agent between UI and data structure remove_at
int remove_at(IDataStructure<int> *dt);

// Agent between UI and data structure clear_dt
int clear_dt(IDataStructure<int> *dt);

// Agent between UI and data structure first_value
int first_value(IDataStructure<int> *dt);

// Agent between UI and data structure last_value
int last_value(IDataStructure<int> *dt);

// Agent between UI and data structure value_at
int value_at(IDataStructure<int> *dt);

// Agent between UI and data structure get_size
int get_size(IDataStructure<int> *dt);

// Agent between UI and data structure find
int find(IDataStructure<int> *dt);

// Agent between UI and data structure get_as_string
int get_as_string(IDataStructure<int> *dt);

// Function that fills data structure with data from file
int fill_from_file(IDataStructure<int> *dt);

#endif
