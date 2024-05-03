#include <curses.h>
#include <iostream>
#include "data_structures/priority_item.hpp"
#include "ui.hpp"
#include "generator.hpp"
#include "ui_actions.hpp"
#include "data_structures/list.hpp"
#include "data_structures/list_ht.hpp"
#include "data_structures/list_double.hpp"
#include "data_structures/priority_queue2.hpp"
#include "data_structures/dynamic_array.hpp"
#include "data_structures/heap.hpp"
#include "data_structures/priority_queue.hpp"
#include "data_structures/priority_queue3.hpp"
#include "data_structures/int_structures_manual_ui.hpp"
#include "test.hpp"


// Create and return menu for list
MenuDt<int>* setup_queue_menu()
{
    MenuDt<int> *queue_menu = new MenuDt<int>(new PriorityQueue<int>);
    queue_menu->add_item_dt("|Włóż do kolejki", insert);
    queue_menu->add_item_dt("|Wyjmij z kolejki", extract);
    queue_menu->add_item_dt("|Wyczyść", clear_dt);
    queue_menu->add_item_dt("|Podejrzyj element o największym priorytecie", findmax_q);
    queue_menu->add_item_dt("|Zmień wartość i priorytet na danym polu", change_at_q);
    queue_menu->add_item_dt("|Wypisz rozmiar", get_size);
    queue_menu->add_item_dt("|Wczytaj z pliku", fill_from_file_q);
    queue_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    queue_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return queue_menu;
}

// Create and return menu for list
MenuDt<int>* setup_heapq_menu()
{
    MenuDt<int> *heapq_menu = new MenuDt<int>(new PriorityQueueHeap<int>);
    heapq_menu->add_item_dt("|Włóż do kolejki", insert);
    heapq_menu->add_item_dt("|Wyjmij z kolejki", extract);
    heapq_menu->add_item_dt("|Wyczyść", clear_dt);
    heapq_menu->add_item_dt("|Podejrzyj element o największym priorytecie", findmax_q);
    heapq_menu->add_item_dt("|Zmień wartość i priorytet na danym polu", change_at_q);
    heapq_menu->add_item_dt("|Wypisz rozmiar", get_size);
    heapq_menu->add_item_dt("|Wczytaj z pliku", fill_from_file_q);
    heapq_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    heapq_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return heapq_menu;
}

// Create and return menu for list
MenuDt<int>* setup_list_menu()
{
    MenuDt<int> *list_menu = new MenuDt<int>(new SingleListH<int>);
    list_menu->add_item_dt("|Dodaj z przodu", add_front);
    list_menu->add_item_dt("|Dodaj z tyłu", add_back);
    list_menu->add_item_dt("|Dodaj na wybranej pozycji", add_at);
    list_menu->add_item_dt("|Usuń z przodu", remove_front);
    list_menu->add_item_dt("|Usuń z tyłu", remove_back);
    list_menu->add_item_dt("|Usuń na pozycji", remove_at);
    list_menu->add_item_dt("|Wyczyść", clear_dt);
    list_menu->add_item_dt("|Znajdź element", find_index);
    list_menu->add_item_dt("|Zmień wartość na danym polu", change_at);
    list_menu->add_item_dt("|Wypisz rozmiar", get_size);
    list_menu->add_item_dt("|Wczytaj z pliku", fill_from_file);
    list_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    list_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return list_menu;
}

// Create and return menu for list_ht
MenuDt<int>* setup_list_ht_menu()
{
    MenuDt<int> *list_ht_menu = new MenuDt<int>(new SingleListHT<int>);
    list_ht_menu->add_item_dt("|Dodaj z przodu", add_front);
    list_ht_menu->add_item_dt("|Dodaj z tyłu", add_back);
    list_ht_menu->add_item_dt("|Dodaj na wybranej pozycji", add_at);
    list_ht_menu->add_item_dt("|Usuń z przodu", remove_front);
    list_ht_menu->add_item_dt("|Usuń z tyłu", remove_back);
    list_ht_menu->add_item_dt("|Usuń na pozycji", remove_at);
    list_ht_menu->add_item_dt("|Wyczyść", clear_dt);
    list_ht_menu->add_item_dt("|Znajdź element", find_index);
    list_ht_menu->add_item_dt("|Zmień wartość na danym polu", change_at);
    list_ht_menu->add_item_dt("|Wypisz rozmiar", get_size);
    list_ht_menu->add_item_dt("|Wczytaj z pliku", fill_from_file);
    list_ht_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    list_ht_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return list_ht_menu;
}

// Create and return menu for double list
MenuDt<int>* setup_dlist_menu()
{
    MenuDt<int> *dlist_menu = new MenuDt<int>(new DoubleListHT<int>);
    dlist_menu->add_item_dt("|Dodaj z przodu", add_front);
    dlist_menu->add_item_dt("|Dodaj z tyłu", add_back);
    dlist_menu->add_item_dt("|Dodaj na wybranej pozycji", add_at);
    dlist_menu->add_item_dt("|Usuń z przodu", remove_front);
    dlist_menu->add_item_dt("|Usuń z tyłu", remove_back);
    dlist_menu->add_item_dt("|Usuń na pozycji", remove_at);
    dlist_menu->add_item_dt("|Wyczyść", clear_dt);
    dlist_menu->add_item_dt("|Znajdź element", find_index);
    dlist_menu->add_item_dt("|Zmień wartość na danym polu", change_at);
    dlist_menu->add_item_dt("|Wypisz rozmiar", get_size);
    dlist_menu->add_item_dt("|Wczytaj z pliku", fill_from_file);
    dlist_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    dlist_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return dlist_menu;
}

// Create and return menu for dynarray
MenuDt<int>* setup_dynarray_menu()
{
    MenuDt<int> *dynarray_menu = new MenuDt<int>(new DynamicArray<int>);
    dynarray_menu->add_item_dt("|Dodaj z przodu", add_front);
    dynarray_menu->add_item_dt("|Dodaj z tyłu", add_back);
    dynarray_menu->add_item_dt("|Dodaj na wybranej pozycji", add_at);
    dynarray_menu->add_item_dt("|Usuń z przodu", remove_front);
    dynarray_menu->add_item_dt("|Usuń z tyłu", remove_back);
    dynarray_menu->add_item_dt("|Usuń na pozycji", remove_at);
    dynarray_menu->add_item_dt("|Wyczyść", clear_dt);
    dynarray_menu->add_item_dt("|Znajdź element", find_index);
    dynarray_menu->add_item_dt("|Zmień wartość na danym polu", change_at);
    dynarray_menu->add_item_dt("|Wypisz rozmiar", get_size);
    dynarray_menu->add_item_dt("|Wczytaj z pliku", fill_from_file);
    dynarray_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    dynarray_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return dynarray_menu;
}

// Create and return menu for structure selection
Menu* setup_structures_menu()
{
    Menu *structures_menu = new Menu();
    structures_menu->add_item("|Kolejka priorytetowa na kopcu", setup_heapq_menu());
    structures_menu->add_item("|Kolejka priorytetowa na liście", setup_queue_menu());
    structures_menu->add_item("|Tablica dynamiczna", setup_dynarray_menu());
    structures_menu->add_item("|Lista jednokierunkowa (head)", setup_list_menu());
    structures_menu->add_item("|Lista jednokierunkowa (head, tail)", setup_list_ht_menu());
    structures_menu->add_item("|Lista dwukierunkowa (head, tail)", setup_dlist_menu());
    structures_menu->add_item("|Wróć do menu głównego", exit_action);

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
    main_menu->add_item("|Wykonaj automatyczne testy", run_tests);
    main_menu->add_item("|Wybór struktury", setup_structures_menu());
    main_menu->add_item("|Generuj dane", ui_run_generator);
    main_menu->add_item("|Pomoc", display_help);
    main_menu->add_item("|Exit", exit_action);
    
    return main_menu;
}


int main()
{
    Menu *main_menu = set_up_ui();
    main_menu->display_menu();
    endwin();

    delete main_menu;

    return 0;
}
