#include <iostream>
#include "../ui_actions.hpp"
#include "int_structures_manual_ui.hpp"
#include "I_data_structure.hpp"
#include "../Timer.hpp"
#include <fstream>
#include <limits>
#include <iomanip>

// Agent between UI and data structure add_front
int add_front(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    Timer timer;
    timer.start();
    dt->add_front(value);
    timer.stop();
    if (print_time)
        display_action("Dodawanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure add_back
int add_back(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    Timer timer;
    timer.start();
    dt->add_back(value);
    timer.stop();
    if (print_time)
        display_action("Dodawanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure add_at
int add_at(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    unsigned int pos = user_input_action_unsigned("Podaj pozycję na której chcesz dodać liczbę: ");
    Timer timer;
    timer.start();
    dt->add_at(value, pos);
    timer.stop();
    if (print_time)
        display_action("Dodawanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure remove_front
int remove_front(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    dt->remove_front();
    timer.stop();
    if (print_time)
        display_action("Usuwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure remove_back
int remove_back(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    dt->remove_back();
    timer.stop();
    if (print_time)
        display_action("Usuwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure remove_at
int remove_at(IDataStructure<int> *dt)
{
    unsigned int pos = user_input_action_unsigned("Podaj pozycję na której chcesz usunąć liczbę: ");
    Timer timer;
    timer.start();
    dt->remove_at(pos);
    timer.stop();
    if (print_time)
        display_action("Usuwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure clear
int clear_dt(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    dt->clear();
    timer.stop();
    if (print_time)
        display_action("Czyszczenie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure first_value
int first_value(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    int val = dt->first_value();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure last_value
int last_value(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    int val = dt->last_value();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure value_at
int value_at(IDataStructure<int> *dt)
{
    unsigned int pos = user_input_action_unsigned("Podaj pozycję z której chcesz wyświetlić liczbę: ");
    Timer timer;
    timer.start();
    int val = dt->value_at(pos);
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure get_size
int get_size(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    int val = dt->get_size();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie rozmiaru zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure find
int find(IDataStructure<int> *dt)
{
    int value_to_find = user_input_action("Podaj liczbę, której pozycję chcesz znaleźć: ");
    Timer timer;
    timer.start();
    unsigned int val = dt->find(value_to_find);
    timer.stop();
    if (val == UINT_MAX)
    {
        if (print_time)
            display_action2("Nie znaleziono!", "Znalezienie indeksu zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
        else
            display_action("Nie znaleziono!");
        return 0;
    }
    if (print_time)
        display_action2(std::to_string(val), "Znalezienie indeksu zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure get_as_string
int get_as_string(IDataStructure<int> *dt)
{
    display_action(dt->get_as_string());
    return 0;
}

// Agent bewteen UI and data structure change_at
int change_at(IDataStructure<int> *dt)
{
    unsigned int position_to_change = user_input_action_unsigned("Podaj indeks na którym chcesz coś zmienić: ");
    int new_value = user_input_action("Podaj liczbę jaką chcesz nadpisać podane pole: ");

    Timer timer;
    timer.start();
    dt->change_at(new_value, position_to_change);
    timer.stop();

    if (print_time)
        display_action("Wypełnienie danymi z pliku zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    
    return 0;
}

int fill_from_file(IDataStructure<int> *dt)
{
    std::string file_name = user_input_action_string("Podaj nazwę pliku, który chcesz wczytać (ścieżka względem programu): ");
    bool direction = user_input_action("Czy dane od góry pliku wczytywać na koniec struktury danych? (1 - TAK, 0 - NIE): ");

    Timer timer;
    timer.start();
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
    timer.stop();
    if (print_time)
        display_action("Wypełnienie danymi z pliku zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure add_back
int add_back_q(IDataStructure<int> *dt)
{
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    Timer timer;
    timer.start();
    dt->add_back(value);
    timer.stop();
    if (print_time)
        display_action("Dodawanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure remove_front
int remove_front_q(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    dt->remove_front();
    timer.stop();
    if (print_time)
        display_action("Usuwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure remove_back
int remove_back_q(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    dt->remove_back();
    timer.stop();
    if (print_time)
        display_action("Usuwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure clear
int clear_dt_q(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    dt->clear();
    timer.stop();
    if (print_time)
        display_action("Czyszczenie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure first_value
int first_value_q(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    int val = dt->first_value();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure last_value
int last_value_q(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    int val = dt->last_value();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure value_at
int value_at_q(IDataStructure<int> *dt)
{
    unsigned int pos = user_input_action_unsigned("Podaj pozycję z której chcesz wyświetlić liczbę: ");
    Timer timer;
    timer.start();
    int val = dt->value_at(pos);
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure get_size
int get_size_q(IDataStructure<int> *dt)
{
    Timer timer;
    timer.start();
    int val = dt->get_size();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie rozmiaru zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure find
int find_q(IDataStructure<int> *dt)
{
    int value_to_find = user_input_action("Podaj liczbę, której pozycję chcesz znaleźć: ");
    Timer timer;
    timer.start();
    unsigned int val = dt->find(value_to_find);
    timer.stop();
    if (val == UINT_MAX)
    {
        if (print_time)
            display_action2("Nie znaleziono!", "Znalezienie indeksu zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
        else
            display_action("Nie znaleziono!");
        return 0;
    }
    if (print_time)
        display_action2(std::to_string(val), "Znalezienie indeksu zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure get_as_string
int get_as_string_q(IDataStructure<int> *dt)
{
    display_action(dt->get_as_string());
    return 0;
}

// Agent bewteen UI and data structure change_at
int change_at_q(IDataStructure<int> *dt)
{
    unsigned int position_to_change = user_input_action_unsigned("Podaj indeks na którym chcesz coś zmienić: ");
    int new_value = user_input_action("Podaj liczbę jaką chcesz nadpisać podane pole: ");
    int new_priority = user_input_action("Podaj nowy priorytet: ");

    Timer timer;
    timer.start();
    dt->change_at(new_value, position_to_change);
    timer.stop();

    if (print_time)
        display_action("Wypełnienie danymi z pliku zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    
    return 0;
}

int fill_from_file_q(IDataStructure<int> *dt)
{
    std::string file_name = user_input_action_string("Podaj nazwę pliku, który chcesz wczytać (ścieżka względem programu): ");
    bool direction = user_input_action("Czy dane od góry pliku wczytywać na koniec struktury danych? (1 - TAK, 0 - NIE): ");

    Timer timer;
    timer.start();
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
    timer.stop();
    if (print_time)
        display_action("Wypełnienie danymi z pliku zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}