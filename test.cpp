#include "Timer.h"
#include "data_structures/I_data_structure.h"
#include "data_structures/list.h"
#include "data_structures/list_ht.h"
#include "data_structures/list_double.h"
#include "data_structures/dynamic_array.h"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <sstream>
#include "ui_actions.h"
#include <iomanip>

namespace fs = std::filesystem;
Timer timer;

//clearing the folder before adding files
void removeFilesInFolder2(const std::string folderName) {
    if (!fs::exists(folderName)) {
        fs::create_directories(folderName);
    }

    for (const auto& entry : fs::directory_iterator(folderName)) {
        if (entry.is_regular_file()) {
            fs::remove(entry.path());
        }
    }
}

// Function that loads one file into given data structure
int fill_from_file(IDataStructure<int> *dt, bool direction,int file_index, int file_index2)
{
    std::string folderPath = "generated_data";
    const std::string filePre = "wyniki_";
    const std::string fileExt = ".txt";
    std::string file_name = folderPath + "/" + filePre + std::to_string(file_index) + "_" + std::to_string(file_index2) + fileExt;

    std::ifstream file(file_name);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            if (direction)
                dt->add_back(value);
            else
                dt->add_front(value);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return -1;
    }
    return 0;
}

// Adds one line to given file
int add_line_to_file(std::string line, std::string filePath)
{
    std::ofstream file("test_results/"+filePath, std::ios_base::app); 
    if (file.is_open()) {
        file << line << std::endl; 
        file.close(); 
    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
    return 0;
}

double add_first_test(IDataStructure<int> *dt,int Value){
    timer.start();
    dt->add_front(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double add_back_test(IDataStructure<int> *dt,int Value){
    timer.start();
    dt->add_back(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double add_at_test(IDataStructure<int> *dt,int Value,int index){
    timer.start();
    dt -> add_at(Value, index);
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_front_test(IDataStructure<int> *dt){
    timer.start();
    dt -> remove_front();
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_back_test(IDataStructure<int> *dt){
    timer.start();
    dt -> remove_back();
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_at_test(IDataStructure<int> *dt,int index){
    timer.start();
    dt -> remove_at(index);
    timer.stop();
    return timer.elapsedSeconds();
}

double find_number_test(IDataStructure<int> *dt,int Value){
    timer.start();
    dt -> find(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double clear_test(IDataStructure<int> *dt){
    timer.start();
    dt -> clear();
    timer.stop();
    return timer.elapsedSeconds();
}

int generate_random_number(bool symbol){
    int number;
    std::default_random_engine generate_random_number;
    if(symbol == 1)
    {
        std::uniform_int_distribution<int> distribution(0,2147483647);
        number = distribution(generate_random_number);
    }else{
        std::uniform_int_distribution<int> distribution(-2147483647,2147483647);
        number = distribution(generate_random_number);
    }
    return number;
}

// Function that runs all tests for all data structures and saves time series to files
int run_all_tests_for_dt(IDataStructure<int>* dt, int to_find, int to_add, int random_position, int data_size, std::string dt_name, int data_sample_number, int series_number)
{
    std::ostringstream stream;
    std::string measure_line;
    std::string data_sample = std::to_string(data_sample_number);
    std::string repetition = std::to_string(series_number);
    double temp_double_buffor;
    
    // Insert on first index
    temp_double_buffor = add_first_test(dt, to_add);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_add_first" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Remove first element
    temp_double_buffor = remove_front_test(dt);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_remove_first" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Add last element
    temp_double_buffor = add_back_test(dt, to_add);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_add_last" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Remove last element
    temp_double_buffor = remove_back_test(dt);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_remove_last" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Add element at random position
    temp_double_buffor = add_at_test(dt, to_add, random_position);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_add_random" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Remove element at random position (same posotion we added random, its generated for each loaded data set)
    temp_double_buffor = remove_at_test(dt, random_position);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_remove_random" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Add element at center
    temp_double_buffor = add_at_test(dt, to_add, data_size/2);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_add_center" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Remove element at center
    temp_double_buffor = remove_at_test(dt, data_size/2);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_remove_center" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Find element
    temp_double_buffor = find_number_test(dt, to_find);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_find_random" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Clear and measure
    temp_double_buffor = clear_test(dt);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_clear" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    return 0;
}

// Function that loads data from file to each data structure and runs all tests for it
int run_tests()
{
    // We create each data structure
    SingleListH<int> list;
    SingleListHT<int> list_ht;
    DoubleListHT<int> double_list;
    DynamicArray<int> dyn_array;

    removeFilesInFolder2("test_results");

    int file_number = user_input_action("Podaj ilość różnych wielkości danych, które zostały wygenerowane w katalogu generated_data: ");
    int data_number = user_input_action("Podaj ilość wygenerowanych instancji dla jednej wielkości: ");
    int repetition = user_input_action("Podaj numer serii pomiarowej (przydatne jeżeli nie chcesz utracić wyników poprzedniego pomiaru, ale dokonać kolejnego): ");

    for(int r=1; r<=repetition; r++)
    {
        for(int i=1; i<=file_number; i++)
        {
            for(int j=1; j<=data_number; j++)
            {
                int to_add = generate_random_number(0);
                int to_find = generate_random_number(0);
                int random_position = generate_random_number(1);
                int bytes;

                // Run tests for list
                fill_from_file(&list, 0, i, j);
                bytes = list.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1 and r==1)
                    add_line_to_file(std::to_string(list.get_size()) + ";" + std::to_string(bytes), ("SingleList_size_growth.txt"));
                run_all_tests_for_dt(&list, to_find, to_add, random_position, list.get_size(), "SingleList", j, r);

                // Run tests for list with head and tail
                fill_from_file(&list_ht, 0, i, j);
                bytes = list_ht.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1 and r==1)
                    add_line_to_file(std::to_string(list_ht.get_size()) + ";" + std::to_string(bytes), ("SingleListHeadTail_size_growth.txt"));
                run_all_tests_for_dt(&list_ht, to_find, to_add, random_position, list_ht.get_size(), "SingleListHeadTail", j, r);

                // Run tests for double list
                fill_from_file(&double_list, 0, i, j);
                bytes = double_list.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1 and r==1)
                    add_line_to_file(std::to_string(double_list.get_size()) + ";" + std::to_string(bytes), ("DoubleList_size_growth.txt"));
                run_all_tests_for_dt(&double_list, to_find, to_add, random_position, double_list.get_size(), "DoubleList", j, r);

                // Run tests for dynamic array
                fill_from_file(&dyn_array, 0, i, j);
                bytes = dyn_array.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1 and r==1)
                    add_line_to_file(std::to_string(dyn_array.get_size()) + ";" + std::to_string(bytes), ("DynamicArray_size_growth.txt"));
                run_all_tests_for_dt(&dyn_array, to_find, to_add, random_position, dyn_array.get_size(), "DynamicArray", j, r);
            }
        }
    }
    
    return 0;
}
