#ifndef UI_ACTIONS_H
#define UI_ACTIONS_H

#include <iostream>

/**
 * Returns 1 - this will be handled by menu and interpreted as call for menu exit
 * 
 * @return int 
 */
int exit_action();

/**
 * Returns 3 - this will be handled and interpreted as launching new menu, not used anymore
 * 
 * @return int 
 */
int launch_menu_action();

/**
 * Returns user input as int number
 * 
 * @return int 
 */
int user_input_action(std::string input_field_label);

/**
 * Displays given string
 * 
 * @return int 
 */
int display_action(std::string display_label);


#endif