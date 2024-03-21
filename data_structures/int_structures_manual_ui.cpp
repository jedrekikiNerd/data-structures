#include <iostream>
#include "../ui_actions.h"
#include "int_structures_manual_ui.hpp"
#include "I_data_structure.h"


int add_front(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    dt->add_front(value);
    return 0;
}

int add_back(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    dt->add_back(value);
    return 0;
}

int add_at(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    int pos = user_input_action("Podaj pozycję na której chcesz dodać liczbę: ");
    dt->add_at(value, pos);
    return 0;
}

int remove_front(IDataStructure<int> *dt)
{
    dt->remove_front();
    return 0;
}

int remove_back(IDataStructure<int> *dt)
{
    dt->remove_back();
    return 0;
}

int remove_at(IDataStructure<int> *dt)
{
    int pos = user_input_action("Podaj pozycję na której chcesz usunąć liczbę: ");
    dt->remove_at(pos);
    return 0;
}

int clear(IDataStructure<int> *dt)
{
    dt->clear();
    return 0;
}

int first_value(IDataStructure<int> *dt)
{
    display_action(std::to_string(dt->first_value()));
    return 0;
}

int last_value(IDataStructure<int> *dt)
{
    display_action(std::to_string(dt->last_value()));
    return 0;
}

int value_at(IDataStructure<int> *dt)
{
    int pos = user_input_action("Podaj pozycję z której chcesz wyświetlić liczbę: ");
    display_action(std::to_string(dt->value_at(pos)));
    return 0;
}

int get_size(IDataStructure<int> *dt)
{
    display_action(std::to_string(dt->get_size()));
    return 0;
}

int find(IDataStructure<int> *dt)
{
    int value_to_find = user_input_action("Podaj liczbę, której pozycję chcesz znaleźć (wynik -1 oznacza nie znalezienie): ");
    display_action(std::to_string(dt->find(value_to_find)));
    return 0;
}

int get_as_string(IDataStructure<int> *dt)
{
    display_action(dt->get_as_string());
    return 0;
}
