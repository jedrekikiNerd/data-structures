#ifndef manual_ui_dt
#define manual_ui_dt

#include <iostream>
#include "I_data_structure.h"


int add_front(IDataStructure<int> *dt);

int add_back(IDataStructure<int> *dt);

int add_at(IDataStructure<int> *dt);

int remove_front(IDataStructure<int> *dt);

int remove_back(IDataStructure<int> *dt);

int remove_at(IDataStructure<int> *dt);

int clear(IDataStructure<int> *dt);

int first_value(IDataStructure<int> *dt);

int last_value(IDataStructure<int> *dt);

int value_at(IDataStructure<int> *dt);

int get_size(IDataStructure<int> *dt);

int find(IDataStructure<int> *dt);

int get_as_string(IDataStructure<int> *dt);

#endif
