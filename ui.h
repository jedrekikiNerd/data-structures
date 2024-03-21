#ifndef UI_H
#define UI_H
#include <iostream>
#include <functional>
#include "data_structures/I_data_structure.h"


/**
 * Inteface of MenuItems
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

        MenuItemFunction();
        MenuItemFunction(std::string label, std::function<int()> func);
        int clicked();
};


/**
 * Class that represents menu button that should run given function and pass pointer to IDataStructure as argument. It stores label and function that should be called when element is selected and ENTER key is pressed.
 * 
 */
template <typename Type>
class MenuItemDTFunction : public MenuItemInterface
{
    private:
        // Function we call when element is clicked (ptr to it)
        std::function<int(IDataStructure<Type>*)> func;
        IDataStructure<Type> *dt;

    public:

        MenuItemDTFunction() : MenuItemInterface(), func(nullptr), dt(nullptr){}
        MenuItemDTFunction(std::string label, std::function<int(IDataStructure<Type>*)> func, IDataStructure<Type> *dt) : MenuItemInterface(label), func(func), dt(dt){}
        int clicked()
        {
            // Do not call func if it's null!
            if (func != nullptr) 
            {
                int result = func(dt);
                return result;
            }
            // 2 is exit status meaning func is nullptr
            return 2;
        }
};


/**
 * Class representing single menu. It stores items with labels and callable functions and datastructure - look at MenuItem, it also stores which element is selected.
 * 
 **/
class Menu
{
    protected:
        static const int MAX_ITEMS = 15;

    public:
        MenuItemInterface *items[MAX_ITEMS];
        int items_number;
        int selected_option;
        Menu();
        void add_item(std::string label, std::function<int()> func);
        void add_item(std::string label, Menu *menu);
        int handle_click();
        int display_menu();
};


/**
 * Class representing menu that interacts with datastructure. It stores data structure of given type and can have menu items that call functions that edit given datastructure
 * 
 **/
template <typename Type>
class MenuDt : public Menu
{
    private:
        IDataStructure<Type> *dt;

    public:
        MenuDt() : Menu(), dt(nullptr){}
        MenuDt(IDataStructure<Type> *ptr_to_dt) : Menu(), dt(ptr_to_dt) {}
        void add_item_dt(std::string label, std::function<int(IDataStructure<Type>*)> func)
        {
            if (items_number<MAX_ITEMS)
            {
                items[items_number] = new MenuItemDTFunction<Type>(label, func, dt);
                items_number++;
            }
            else
            {
                throw "MAX_ITEMS in menu exceeded!";
            } 
        }
};


/**
 * Class that represents menu button that should run other menu. It stores label and menu that should be activated when selected.
 * 
 */
class MenuItemSwitcher : public MenuItemInterface
{
    private:
        Menu *menu_to_switch;

    public:
        MenuItemSwitcher();
        MenuItemSwitcher(std::string label, Menu *menu);
        int clicked();
};

#endif