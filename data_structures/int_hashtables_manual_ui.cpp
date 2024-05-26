#include "int_hashtables_manual_ui.hpp"
#include "../ui_actions.hpp"
#include "../Timer.hpp"
#include <fstream>
#include <limits>
#include <iomanip>

// Agent between UI and data structure insert
int insert_ht(IHashTable<int> *ht)
{
    std::string key = user_input_action_string("Podaj klucz: ");
    int value = user_input_action("Podaj liczbę jaką chcesz dodać: ");
    Timer timer;
    timer.start();
    ht->insert(key, value);
    timer.stop();
    if (print_time)
        display_action("Dodawanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure remove
int remove_ht(IHashTable<int> *ht)
{
    std::string key = user_input_action_string("Podaj klucz: ");
    Timer timer;
    timer.start();
    ht->remove(key);
    timer.stop();
    if (print_time)
        display_action("Usuwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

// Agent between UI and data structure get_size
int get_size_ht(IHashTable<int> *ht)
{
    Timer timer;
    timer.start();
    int val = ht->get_size();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Pobranie rozmiaru zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure find
int find_ht(IHashTable<int> *ht)
{
    int value_to_find = user_input_action("Podaj liczbę, której klucz chcesz znaleźć: ");
    Timer timer;
    timer.start();
    std::string val = ht->find(value_to_find);
    timer.stop();
    if (val == "-1")
    {
        if (print_time)
            display_action2("Nie znaleziono!", "Wyszkuiwanie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
        else
            display_action("Nie znaleziono!");
        return 0;
    }
    if (print_time)
        display_action2(val, "Znalezienie klucza zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(val);
    return 0;
}

// Agent between UI and data structure value_at
int value_at_ht(IHashTable<int> *ht)
{
    std::string key = user_input_action_string("Podaj klucz: ");
    Timer timer;
    timer.start();
    if (!ht->has_key(key))
        return 0;
    
    int val = ht->value_at(key);
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Wyświetlenie wartości zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure get_load_factor
int get_load_factor_ht(IHashTable<int> *ht)
{
    Timer timer;
    timer.start();
    float val = ht->get_load_factor();
    timer.stop();
    if (print_time)
        display_action2(std::to_string(val), "Wyświetlenie współczynnika zajętości " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(std::to_string(val));
    return 0;
}

// Agent between UI and data structure has_key
int has_key_ht(IHashTable<int> *ht)
{
    Timer timer;
    std::string key = user_input_action_string("Podaj klucz: ");
    std::string val = "True";
    timer.start();
    if (!ht->has_key(key))
        val = "False";
    timer.stop();
    if (print_time)
        display_action2(val, "Sprawdzenie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    else
        display_action(val);
    return 0;
}

// Agent between UI and data structure clear
int clear_ht(IHashTable<int> *ht)
{
    Timer timer;
    timer.start();
    ht->clear();
    timer.stop();
    if (print_time)
        display_action("Czyszczenie zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}

int fill_from_file_ht(IHashTable<int> *ht)
{
    std::string file_name = user_input_action_string("Podaj nazwę pliku, który chcesz wczytać (ścieżka względem programu): ");

    Timer timer;
    timer.start();
    std::ifstream file(file_name);
    if (file.is_open()) 
    {
        std::string key;
        int value;
        while (file) 
        {
            file >> key;
            file >> value;
            ht->insert(key, value);
        }
        file.close();
    }
    timer.stop();
    if (print_time)
        display_action("Wypełnienie danymi z pliku zajęło " + std::to_string(timer.elapsedSeconds()) + "ns");
    return 0;
}
