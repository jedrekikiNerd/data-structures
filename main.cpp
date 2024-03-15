#include <curses.h>
#include <iostream>
#include "ui.h"
#include "generator.h"
#include "ui_actions.h"


Menu* setup_structures_menu()
{
    Menu *structures_menu = new Menu();
    structures_menu->add_item("Struktura1", nullptr);
    structures_menu->add_item("Struktura2", nullptr);
    structures_menu->add_item("Struktura3", nullptr);
    structures_menu->add_item("Wróć do menu głównego", exit_action);

    return structures_menu;
}


Menu* set_up_ui()
{
    // Init PDCurses and wait for user before jumping to main menu
    initscr();
    setlocale(LC_ALL, "pl_PL.utf8");
    keypad(stdscr, TRUE);
    noecho();
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
