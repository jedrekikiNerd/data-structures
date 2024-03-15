/**
 * @file ui_actions.cpp
 * @author Jędrzej Boruczkowski
 * @brief 
 * @version 0.1
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 * This file stores all functions/actions that can be assigned to menu items from ui.cpp file.
 * All return codes meaning:
 * 0 - success, no custom action
 * 1 - exit menu
 * 2 - nullptr, no action assigned to menu item
 * 3 - start new menu
 * 4 - input error
 */

#include "ui_actions.h"
#include <curses.h>
#include <iostream>


/**
 * Returns 1 - this will be handled by menu and interpreted as call for menu exit
 * 
 * @return int 
 */
int exit_action()
{
    return 1;
}


/**
 * Returns 3 - this will be handled and interpreted as launching new menu, not used anymore
 * 
 * @return int 
 */
int launch_menu_action()
{
    return 3;
}


/**
 * Returns user input as int number
 * 
 * @return int 
 */
int user_input_action(std::string input_field_label)
{
    echo();
    clear();
    int user_input;
    mvprintw(1, 1, input_field_label.c_str());
    refresh();
    // Get int number provided by user from terminal window with scanw
    scanw("%d", &user_input);
    noecho();
    return user_input;
}
