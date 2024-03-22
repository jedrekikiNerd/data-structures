#include <iostream>
#include "../ui_actions.h"
#include "int_structures_manual_ui.hpp"
#include "I_data_structure.h"
#include <fstream>


// Agent between UI and data structure add_front
int add_front(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    dt->add_front(value);
    return 0;
}

// Agent between UI and data structure add_back
int add_back(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    dt->add_back(value);
    return 0;
}

// Agent between UI and data structure add_at
int add_at(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    int pos = user_input_action("Podaj pozycję na której chcesz dodać liczbę: ");
    dt->add_at(value, pos);
    return 0;
}

// Agent between UI and data structure remove_front
int remove_front(IDataStructure<int> *dt)
{
    dt->remove_front();
    return 0;
}

// Agent between UI and data structure remove_back
int remove_back(IDataStructure<int> *dt)
{
    dt->remove_back();
    return 0;
}

// Agent between UI and data structure remove_at
int remove_at(IDataStructure<int> *dt)
{
    int pos = user_input_action("Podaj pozycję na której chcesz usunąć liczbę: ");
    dt->remove_at(pos);
    return 0;
}

// Agent between UI and data structure clear
int clear_dt(IDataStructure<int> *dt)
{
    dt->clear();
    return 0;
}

// Agent between UI and data structure first_value
int first_value(IDataStructure<int> *dt)
{
    display_action(std::to_string(dt->first_value()));
    return 0;
}

// Agent between UI and data structure last_value
int last_value(IDataStructure<int> *dt)
{
    display_action(std::to_string(dt->last_value()));
    return 0;
}

// Agent between UI and data structure value_at
int value_at(IDataStructure<int> *dt)
{
    int pos = user_input_action("Podaj pozycję z której chcesz wyświetlić liczbę: ");
    display_action(std::to_string(dt->value_at(pos)));
    return 0;
}

// Agent between UI and data structure get_size
int get_size(IDataStructure<int> *dt)
{
    display_action(std::to_string(dt->get_size()));
    return 0;
}

// Agent between UI and data structure find
int find(IDataStructure<int> *dt)
{
    int value_to_find = user_input_action("Podaj liczbę, której pozycję chcesz znaleźć (wynik -1 oznacza nie znalezienie): ");
    display_action(std::to_string(dt->find(value_to_find)));
    return 0;
}

// Agent between UI and data structure get_as_string
int get_as_string(IDataStructure<int> *dt)
{
    display_action(dt->get_as_string());
    return 0;
}

int fill_from_file(IDataStructure<int> *dt)
{
    std::string file_name = user_input_action_string("Podaj nazwę pliku, który chcesz wczytać (ścieżka względem programu): ");
    bool direction = user_input_action("Czy dane od góry pliku wczytywać na koniec struktury danych? (1 - TAK, 0 - NIE): ");

    std::ifstream file(file_name);
    if (file.is_open()) 
    {
        int value;
        //std::string line;
        while (file) 
        {
            file >> value;
            if (direction)
                dt->add_back(value);
            else
                dt->add_front(value);
        }
        file.close();
    }
    return 0;
}
