#include <curses.h>
#include <iostream>
#include "data_structures/priority_item.hpp"
#include "ui.hpp"
#include "generator.hpp"
#include "ui_actions.hpp"
#include "data_structures/list.hpp"
#include "data_structures/list_ht.hpp"
#include "data_structures/list_double.hpp"
#include "data_structures/priority_queue_heap.hpp"
#include "data_structures/priority_queue_list.hpp"
#include "data_structures/priority_queue_array.hpp"
#include "data_structures/dynamic_array.hpp"
#include "data_structures/heap.hpp"
#include "data_structures/hash_table_chain.hpp"
#include "data_structures/hash_table_cuckoo.hpp"
#include "data_structures/hash_table_open.hpp"
#include "data_structures/I_hash_table.hpp"
#include "data_structures/hash_functions.hpp"
#include "data_structures/int_structures_manual_ui.hpp"
#include "data_structures/int_hashtables_manual_ui.hpp"
#include "test.hpp"


// Create and return menu for hash table chain
MenuHt<int>* setup_hashchain_menu()
{
    MenuHt<int> *hashchain_menu = new MenuHt<int>(new HashTableSeperateChaining<int>(hash_modulo));
    hashchain_menu->add_item_dt("|Włóż element", insert_ht);
    hashchain_menu->add_item_dt("|Usuń element", remove_ht);
    hashchain_menu->add_item_dt("|Wyczyść", clear_ht);
    hashchain_menu->add_item_dt("|Wyszukaj klucz", find_ht);
    hashchain_menu->add_item_dt("|Zobacz wartość o danym kluczu", value_at_ht);
    hashchain_menu->add_item_dt("|Wyświetl współczynnik zajętości", get_load_factor_ht);
    hashchain_menu->add_item_dt("|Sprawdź czy klucz istnieje", has_key_ht);
    hashchain_menu->add_item_dt("|Wypisz rozmiar", get_size_ht);
    hashchain_menu->add_item_dt("|Wczytaj z pliku", fill_from_file_ht);
    hashchain_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    hashchain_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return hashchain_menu;
}

// Create and return menu for hash table open
MenuHt<int>* setup_hashopen_menu()
{
    MenuHt<int> *hashopen_menu = new MenuHt<int>(new HashTableOpenAddressing<int>(hash_modulo));
    hashopen_menu->add_item_dt("|Włóż element", insert_ht);
    hashopen_menu->add_item_dt("|Usuń element", remove_ht);
    hashopen_menu->add_item_dt("|Wyczyść", clear_ht);
    hashopen_menu->add_item_dt("|Wyszukaj klucz", find_ht);
    hashopen_menu->add_item_dt("|Zobacz wartość o danym kluczu", value_at_ht);
    hashopen_menu->add_item_dt("|Wyświetl współczynnik zajętości", get_load_factor_ht);
    hashopen_menu->add_item_dt("|Sprawdź czy klucz istnieje", has_key_ht);
    hashopen_menu->add_item_dt("|Wypisz rozmiar", get_size_ht);
    hashopen_menu->add_item_dt("|Wczytaj z pliku", fill_from_file_ht);
    hashopen_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    hashopen_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return hashopen_menu;
}

// Create and return menu for hash table open
MenuHt<int>* setup_hashcuckoo_menu()
{
    MenuHt<int> *hashcuckoo_menu = new MenuHt<int>(new HashTableCuckoo<int>(hash_modulo, hash_modulo));
    hashcuckoo_menu->add_item_dt("|Włóż element", insert_ht);
    hashcuckoo_menu->add_item_dt("|Usuń element", remove_ht);
    hashcuckoo_menu->add_item_dt("|Wyczyść", clear_ht);
    hashcuckoo_menu->add_item_dt("|Wyszukaj klucz", find_ht);
    hashcuckoo_menu->add_item_dt("|Zobacz wartość o danym kluczu", value_at_ht);
    hashcuckoo_menu->add_item_dt("|Wyświetl współczynnik zajętości", get_load_factor_ht);
    hashcuckoo_menu->add_item_dt("|Sprawdź czy klucz istnieje", has_key_ht);
    hashcuckoo_menu->add_item_dt("|Wypisz rozmiar", get_size_ht);
    hashcuckoo_menu->add_item_dt("|Wczytaj z pliku", fill_from_file_ht);
    hashcuckoo_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    hashcuckoo_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return hashcuckoo_menu;
}


// Create and return menu for queue
MenuDt<int>* setup_queue_menu()
{
    MenuDt<int> *queue_menu = new MenuDt<int>(new PriorityQueuearray<int>);
    queue_menu->add_item_dt("|Włóż do kolejki", insert);
    queue_menu->add_item_dt("|Wyjmij z kolejki", extract);
    queue_menu->add_item_dt("|Wyczyść", clear_dt);
    queue_menu->add_item_dt("|Wyszukaj pozycję", find_index);
    queue_menu->add_item_dt("|Podejrzyj element o największym priorytecie", findmax_q);
    queue_menu->add_item_dt("|Zmień wartość i priorytet na danym polu", change_at_q);
    queue_menu->add_item_dt("|Wypisz rozmiar", get_size);
    queue_menu->add_item_dt("|Wczytaj z pliku", fill_from_file_q);
    queue_menu->add_item("|Wyświetlanie czasu", change_print_flag);
    queue_menu->add_item("|Wróć do wyboru struktur", exit_action);

    return queue_menu;
}

// Create and return menu for queue on heap
MenuDt<int>* setup_heapq_menu()
{
    MenuDt<int> *heapq_menu = new MenuDt<int>(new PriorityQueueHeap<int>);
    heapq_menu->add_item_dt("|Włóż do kolejki", insert);
    heapq_menu->add_item_dt("|Wyjmij z kolejki", extract);
    heapq_menu->add_item_dt("|Wyczyść", clear_dt);
    heapq_menu->add_item_dt("|Wyszukaj pozycję", find_index);
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
    structures_menu->add_item("|Tablica mieszająca łańcuchowa", setup_hashchain_menu());
    structures_menu->add_item("|Tablica mieszająca otwarta", setup_hashopen_menu());
    structures_menu->add_item("|Tablica mieszająca kukułcza", setup_hashcuckoo_menu());
    structures_menu->add_item("|Kolejka priorytetowa na kopcu", setup_heapq_menu());
    structures_menu->add_item("|Kolejka priorytetowa na tablicy dynamicznej", setup_queue_menu());
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
