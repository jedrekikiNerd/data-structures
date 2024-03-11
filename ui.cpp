/**
 * @file ui.cpp
 * @author Jędrzej Boruczkowski
 * @brief Code in this file is responsible for user interface (we use curses.h)
 * @version 0.1
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <curses.h>
#include <iostream>
#include <string>
#include <functional>
#include "ui_actions.h"

#define MY_KEY_EXIT 27
#define MY_KEY_ENTER 10



/**
 * Inteface of MenuItems
 * Has clicked() function that should be overwritten to functionality our MenuItem object will provide.
 * 
 */
class MenuItemInterface {
public:
    std::string label;
    MenuItemInterface() : label("") {} // Constructor when no label
    MenuItemInterface(std::string label) : label(label) {} // Constructor when label specified
    virtual int clicked() = 0; //clicked function that gives our button a functionality
    virtual ~MenuItemInterface() {} // Virtual destructor to make sure all subclasses have their destructors run
};


/**
 * Class that represents menu button that should run given function. It stores label and function that should be called when element is selected and ENTER key is pressed.
 * 
 */
class MenuItemFunction : public MenuItemInterface
{
    private:
        // Function we call when element is clicked (ptr to it)
        std::function<int()> func;

    public:
        // Name of item
        
        // Conctructor for empty object
        MenuItemFunction() : MenuItemInterface(), func(nullptr){}
        // Constructor when label and ptr to function are specified
        MenuItemFunction(std::string label, std::function<int()> func) : MenuItemInterface(label), func(func){}

        // Clicked function - we should run it when someone presses enter while having this item selected
        int clicked() 
        {
            // Do not call func if it's null!
            if (func != nullptr) 
            {
                int result = func();
                return result;
            }
            // 2 is exit status meaning func is nullptr
            return 2;
        }
};


/**
 * Class representing single menu. It stores items with labels and callable function - look at MenuItem, it also stores which element is selected.
 * 
 **/
class Menu
{
    private:
        static const int MAX_ITEMS = 10; // Max menu elements

    public:
        MenuItemInterface *items[MAX_ITEMS];
        int items_number;
        int selected_option;
        Menu() : items_number(0), selected_option(0) {}

        // Add element (that runs standalone function) to menu
        void add_item(std::string label, std::function<int()> func) 
        {
            if (items_number<MAX_ITEMS)
            {
                items[items_number] = new MenuItemFunction(label, func);
                items_number++;
            }
            else
            {
                throw "MAX_ITEMS in menu exceeded!";
            }
        }

        // Add element (that switches menu) to menu - forward declaration to prevent conflicts
        void add_item(std::string label, Menu menu);

        // Call clicked function in selected element
        int handle_click()
        {
            int result = items[selected_option]->clicked();
            return result;
        }

        // displays menu and handles input
        int display_menu()
        {
            int pressed_key;
            while (true)
            {
                // We clear terminal screen before printing new elements
                clear();
                // We iterate through every element and display it
                for (int item_index=0; item_index<items_number; item_index++)
                {
                    // Add background to selected option
                    if (item_index == selected_option)
                        attron(A_REVERSE);
                    mvprintw(item_index+1, 1, items[item_index]->label.c_str());
                    attroff(A_REVERSE);
                }
                // refresh displays new elements
                refresh();

                // Wait for input and handle it
                pressed_key = getch();
                switch(pressed_key)
                {
                    case KEY_DOWN:
                    {
                        selected_option = (selected_option + 1) % items_number;
                        break;
                    }
                    case KEY_UP:
                    {
                        selected_option = (selected_option - 1);
                        if (selected_option < 0)
                            selected_option = items_number - 1;
                        break;
                    }
                    case MY_KEY_ENTER:
                    {
                        int result = handle_click();
                        if (result == 1)
                            return 1;
                        break;
                    }
                    case MY_KEY_EXIT:
                        return 1;
                }
            }
            return 0;
        }
};


/**
 * Class that represents menu button that should run other menu. It stores label and menu that should be activated when selected.
 * 
 */
class MenuItemSwitcher : public MenuItemInterface
{
    private:
        // Function we call when element is clicked (ptr to it)
        Menu *menu_to_switch;

    public:
        // Name of item
        //std::string label;
        
        // Conctructor for empty object
        MenuItemSwitcher() : MenuItemInterface(), menu_to_switch(nullptr){}
        // Constructor when label and menu object are specified
        MenuItemSwitcher(std::string label, Menu *menu) : MenuItemInterface(label), menu_to_switch(menu){}

        // Clicked function - we should run it when someone presses enter while having this item selected
        int clicked() 
        {
            // Do not call func if it's null!
            if (menu_to_switch != nullptr) 
            {
                menu_to_switch->display_menu();
                return 3;
            }
            // 2 is exit status meaning menu_to_switch is nullptr
            return 2;
        }
};


// Body of add_item Menu method
void Menu::add_item(std::string label, Menu menu)
{
    if (items_number < MAX_ITEMS)
    {
        items[items_number] = new MenuItemSwitcher(label, &menu);
        items_number++;
    }
    else
    {
        throw "MAX_ITEMS in menu exceeded!";
    }
}


int main() 
{
    // Init PDCurses and wait for user before jumping to main menu
    initscr();
    printw( "Wcisnij dowolny przycisk, aby rozpoczac prace..\n" );
    keypad(stdscr, TRUE);
    noecho();
    getch();

    Menu main_menu;
    Menu test1;
    test1.add_item("Opcja 2-1", nullptr);
    test1.add_item("Exit", exit_action);
    main_menu.add_item("Opcja 1-1", test1);
    main_menu.add_item("Exit", exit_action);
    main_menu.display_menu();
    
    return 0;
}
