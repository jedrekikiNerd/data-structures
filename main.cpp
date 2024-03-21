#include <curses.h>
#include <iostream>
#include "ui.h"
#include "generator.h"
#include "ui_actions.h"
#include "data_structures/list.h"
#include "data_structures/dynamic_array.h"
#include "data_structures/int_structures_manual_ui.hpp"


// Create and return menu for list
MenuDt<int>* setup_list_menu()
{
    MenuDt<int> *list_menu = new MenuDt<int>(new LinkedListH<int>);
    list_menu->add_item_dt("Dodaj z przodu", add_front);
    list_menu->add_item_dt("Dodaj z tyłu", add_back);
    list_menu->add_item_dt("Dodaj na wybranej pozycji", add_at);
    list_menu->add_item_dt("Usuń z przodu", remove_front);
    list_menu->add_item_dt("Usuń z tyłu", remove_back);
    list_menu->add_item_dt("Usuń na pozycji", remove_at);
    list_menu->add_item_dt("Wyczyść", clear_dt);
    list_menu->add_item_dt("Znajdź element", find);
    list_menu->add_item("Wróć do menu głównego", exit_action);

    return list_menu;
}

// Create and return menu for dynarray
MenuDt<int>* setup_dynarray_menu()
{
    MenuDt<int> *dynarray_menu = new MenuDt<int>(new DynamicArray<int>);
    dynarray_menu->add_item_dt("Dodaj z przodu", add_front);
    dynarray_menu->add_item_dt("Dodaj z tyłu", add_back);
    dynarray_menu->add_item_dt("Dodaj na wybranej pozycji", add_at);
    dynarray_menu->add_item_dt("Usuń z przodu", remove_front);
    dynarray_menu->add_item_dt("Usuń z tyłu", remove_back);
    dynarray_menu->add_item_dt("Usuń na pozycji", remove_at);
    dynarray_menu->add_item_dt("Wyczyść", clear_dt);
    dynarray_menu->add_item_dt("Znajdź element", find);
    dynarray_menu->add_item("Wróć do menu głównego", exit_action);

    return dynarray_menu;
}

// Create and return menu for structure selection
Menu* setup_structures_menu()
{
    Menu *structures_menu = new Menu();
    structures_menu->add_item("Tablica dynamiczna", setup_dynarray_menu());
    structures_menu->add_item("ListaH", setup_list_menu());
    structures_menu->add_item("Struktura2", nullptr);
    structures_menu->add_item("Struktura3", nullptr);
    structures_menu->add_item("Wróć do menu głównego", exit_action);

    return structures_menu;
}

// Create and return main menu, also setup values of curses library
Menu* set_up_ui()
{
    // Init PDCurses and wait for user before jumping to main menu
    initscr();
    setlocale(LC_ALL, "pl_PL.utf8");
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    curs_set(0);
    printw( "Wcisnij dowolny przycisk, aby rozpoczac prace..\n" );
    curs_set(0);
    getch();

    // Create main_menu and add menu items to it
    Menu *main_menu = new Menu();
    main_menu->add_item("Wybór struktury", setup_structures_menu());
    main_menu->add_item("Generuj dane", ui_run_generator);
    main_menu->add_item("Exit", exit_action);
    
    return main_menu;
}


int main()
{
    Menu *main_menu = set_up_ui();
    main_menu->display_menu();

    return 0;
}
