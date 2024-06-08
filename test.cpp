#include "Timer.hpp"
#include "data_structures/I_data_structure.hpp"
#include "data_structures/list.hpp"
#include "data_structures/list_ht.hpp"
#include "data_structures/list_double.hpp"
#include "data_structures/dynamic_array.hpp"
#include "data_structures/priority_queue_heap.hpp"
#include "data_structures/priority_queue_array.hpp"
#include "data_structures/priority_queue_array.hpp"
#include "data_structures/I_hash_table.hpp"
#include "data_structures/hash_table_chain.hpp"
#include "data_structures/hash_table_open.hpp"
#include "data_structures/hash_table_cuckoo.hpp"
#include "data_structures/hash_functions.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>
#include <sstream>
#include "ui_actions.hpp"
#include <iomanip>

namespace fs = std::filesystem;
Timer timer;

//clearing the folder before adding files
void removeFilesInFolder2(const std::string folderName)
{
    if (!fs::exists(folderName))
    {
        fs::create_directories(folderName);
    }

    for (const auto& entry : fs::directory_iterator(folderName))
    {
        if (entry.is_regular_file())
        {
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
    if (file.is_open())
    {
        int value;
        while (file >> value) {
            if (direction)
                dt->add_back(value);
            else
                dt->add_front(value);
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return -1;
    }
    return 0;
}

// Function that loads one file into given data structure of queue type with priority
int fill_from_file2(IDataStructure<int> *dt, int file_index, int file_index2)
{
    std::string folderPath = "generated_data_queues";
    const std::string filePre = "wyniki_";
    const std::string fileExt = ".txt";
    std::string file_name = folderPath + "/" + filePre + std::to_string(file_index) + "_" + std::to_string(file_index2) + fileExt;

    std::ifstream file(file_name);
    if (file.is_open()) {
        int value;
        int priority;
        while (file >> value)
        {
            file >> priority;
            dt->add_back(value, priority);
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return -1;
    }
    return 0;
}

int fill_from_file_ht(IHashTable<int> *ht, int file_index, int file_index2)
{
    std::string folderPath = "generated_data_hash";
    const std::string filePre = "wyniki_";
    const std::string fileExt = ".txt";
    std::string file_name = folderPath + "/" + filePre + std::to_string(file_index) + "_" + std::to_string(file_index2) + fileExt;

    std::ifstream file(file_name);
    if (file.is_open()) 
    {
        int key;
        int value;
        while (file) 
        {
            file >> key;
            file >> value;
            ht->insert(key, value);
        }
        file.close();
    }
    else
    {
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

double add_first_test(IDataStructure<int> *dt,int Value)
{
    timer.start();
    dt->add_front(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double add_back_test(IDataStructure<int> *dt,int Value)
{
    timer.start();
    dt->add_back(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double add_at_test(IDataStructure<int> *dt,int Value,unsigned int index)
{
    timer.start();
    dt -> add_at(Value, index);
    timer.stop();
    return timer.elapsedSeconds();
}

double insert_test(IDataStructure<int> *dt, int Value, int priority)
{
    timer.start();
    dt->add_back(Value, priority);
    timer.stop();
    return timer.elapsedSeconds();
}

double get_size_test(IDataStructure<int> *dt)
{
    timer.start();
    dt->get_size();
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_front_test(IDataStructure<int> *dt)
{
    timer.start();
    dt -> remove_front();
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_back_test(IDataStructure<int> *dt)
{
    timer.start();
    dt -> remove_back();
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_at_test(IDataStructure<int> *dt,unsigned int index)
{
    timer.start();
    dt -> remove_at(index);
    timer.stop();
    return timer.elapsedSeconds();
}

double extract_test(IDataStructure<int> *dt)
{
    timer.start();
    dt->first_value();
    timer.stop();
    return timer.elapsedSeconds();
}

double modify_test(IDataStructure<int> *dt, int value, int priority, int position_to_change)
{
    timer.start();
    dt->change_at(value, position_to_change, priority);
    timer.stop();
    return timer.elapsedSeconds();
}

double find_max_test(IDataStructure<int> *dt)
{
    timer.start();
    dt->find_max();
    timer.stop();
    return timer.elapsedSeconds();
}

double find_number_test(IDataStructure<int> *dt,unsigned int Value)
{
    timer.start();
    dt -> find(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double find_existing_number_test(IDataStructure<int> *dt, unsigned int index)
{
    int find_value = dt->value_at(index);
    timer.start();
    dt -> find(find_value);
    timer.stop();
    return timer.elapsedSeconds();
}

double clear_test(IDataStructure<int> *dt)
{
    timer.start();
    dt -> clear();
    timer.stop();
    return timer.elapsedSeconds();
}

// Here are functions for hash table testing:

double insert_test_hash(IHashTable<int> *dt, int Value, int key)
{
    timer.start();
    dt->insert(key, Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double remove_test_hash(IHashTable<int> *dt, int key)
{
    timer.start();
    dt->remove(key);
    timer.stop();
    return timer.elapsedSeconds();
}

double find_test_hash(IHashTable<int> *dt, int Value)
{
    timer.start();
    dt->find(Value);
    timer.stop();
    return timer.elapsedSeconds();
}

double haskey_test_hash(IHashTable<int> *dt, int key)
{
    timer.start();
    dt->has_key(key);
    timer.stop();
    return timer.elapsedSeconds();
}

double clear_test_hash(IHashTable<int> *dt)
{
    timer.start();
    dt->clear();
    timer.stop();
    return timer.elapsedSeconds();
}

int generate_random_number(std::default_random_engine& random_generator)
{
    int number;
    std::uniform_int_distribution<int> distribution(-2147483647,2147483647);
    number = distribution(random_generator);
    return number;
}

int generate_random_number_range(std::default_random_engine& random_generator, int from, int to)
{
    int number;
    std::uniform_int_distribution<int> distribution(from, to);
    number = distribution(random_generator);
    return number;
}

unsigned int generate_random_number_unsigned(unsigned int size_dt, std::default_random_engine& random_generator)
{
    unsigned int number;
    std::uniform_int_distribution<unsigned int> distribution(0,size_dt);
    number = distribution(random_generator);
    return number;
}

// Function that runs all tests for all data structures and saves time series to files
// We use buffer (stream) because thats the solution we found to output more than 4 digits after decimal point to string
int run_all_tests_for_dt(IDataStructure<int>* dt, int to_find, int to_add, unsigned int random_position, int data_size, std::string dt_name, int data_sample_number, int series_number)
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

    // Find existing element
    temp_double_buffor = find_existing_number_test(dt, random_position);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_find_random_existing" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    // Clear and measure
    temp_double_buffor = clear_test(dt);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_clear" + data_sample + "_" + repetition + ".txt"));
    stream.str("");

    return 0;
}

int run_all_tests_for_queue(IDataStructure<int>* dt, int to_find, int to_add, int to_add_p, unsigned int random_position, int data_size, std::string dt_name, int data_sample_number, int repetition)
{
    std::ostringstream stream;
    std::string measure_line;
    std::string data_sample = std::to_string(data_sample_number);
    double temp_double_buffor;
    double temp_double_buffor2;

    
    // Insert to queue
    temp_double_buffor = 0.0;
    temp_double_buffor2 = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += insert_test(dt, to_add, to_add_p);
        temp_double_buffor2 += extract_test(dt);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_insert" + data_sample + ".txt"));
    stream.str("");

    // Extract from queue
    temp_double_buffor2 /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_extract" + data_sample + ".txt"));
    stream.str("");

    // See max
    temp_double_buffor = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += find_max_test(dt);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_seemax" + data_sample + ".txt"));
    stream.str("");

    // Find value that exists 
    temp_double_buffor = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += find_existing_number_test(dt, random_position);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_find" + data_sample + ".txt"));
    stream.str("");

    // get size
    temp_double_buffor = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += get_size_test(dt);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_getsize" + data_sample + ".txt"));
    stream.str("");

    // change at given position
    temp_double_buffor = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += modify_test(dt, to_add, to_add_p, random_position);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_modifytest" + data_sample + ".txt"));
    stream.str("");

    // Clear operation
     temp_double_buffor = 0.0;
    temp_double_buffor += clear_test(dt);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_clear" + data_sample + ".txt"));
    stream.str("");

    return 0;
}

int run_all_tests_for_hashtable(IHashTable<int>* dt, int to_find, int to_add, int to_add_key, int random_key, int data_size, std::string dt_name, int data_sample_number, int repetition)
{
    std::ostringstream stream;
    std::string measure_line;
    std::string data_sample = std::to_string(data_sample_number);
    double temp_double_buffor;
    double temp_double_buffor2;

    
    // Insert to hash table
    temp_double_buffor = 0.0;
    temp_double_buffor2 = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += insert_test_hash(dt, to_add, to_add_key);
        temp_double_buffor2 += remove_test_hash(dt, to_add_key);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_insert" + data_sample + ".txt"));
    stream.str("");

    // Remove from hash table
    temp_double_buffor2 /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_remove" + data_sample + ".txt"));
    stream.str("");

    // Find key for value
    temp_double_buffor = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += find_test_hash(dt, to_find);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_find" + data_sample + ".txt"));
    stream.str("");

    // Check if key is present
    temp_double_buffor = 0.0;
    for(int i=1; i<=repetition; i++)
        temp_double_buffor += haskey_test_hash(dt, to_find);
    temp_double_buffor /= repetition;
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_haskey" + data_sample + ".txt"));
    stream.str("");

    // Clear operation
     temp_double_buffor = 0.0;
    temp_double_buffor += clear_test_hash(dt);
    stream << std::fixed << std::setprecision(10) << temp_double_buffor;
    measure_line = std::to_string(data_size) + ";" + stream.str();
    add_line_to_file(measure_line, (dt_name + "_clear" + data_sample + ".txt"));
    stream.str("");

    return 0;
}

// Function that loads data from file to each data structure and runs all tests for it
int run_tests()
{
    // We create random engine
    std::random_device rd;
    std::default_random_engine random_generator(rd());

    // We create each data structure
    SingleListH<int> list;
    SingleListHT<int> list_ht;
    DoubleListHT<int> double_list;
    DynamicArray<int> dyn_array;
    PriorityQueueHeap<int> queue_heap;
    PriorityQueuearray<int> queue_array;
    HashTableSeperateChaining<int> hash_chain(hash_modulo);
    HashTableOpenAddressing<int> hash_open(hash_modulo);
    HashTableCuckoo<int> hash_cuckoo(hash_modulo, hash_modulo);

    removeFilesInFolder2("test_results");

    int file_number = user_input_action("Podaj ilość różnych wielkości danych, które zostały wygenerowane w katalogu generated_data: ");
    int data_number = user_input_action("Podaj ilość wygenerowanych instancji dla jednej wielkości: ");
    int repetition = user_input_action("Podaj ilość powtórzeń dla każdej próbki: ");
    int what_to_test = user_input_action("Podaj co testować (1: pierwszy projekt, 2: drugi projekt, 3: trzeci projekt): ");

    if (what_to_test == 1)
        for(int i=1; i<=file_number; i++)
        {
            for(int j=1; j<=data_number; j++)
            {
                int to_add = generate_random_number(random_generator);
                int to_find = generate_random_number(random_generator);
                int bytes;

                // Run tests for list
                fill_from_file(&list, 0, i, j);
                // We need size for generating random position
                unsigned int random_position = generate_random_number_unsigned(list.get_size()-1, random_generator);
                bytes = list.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(list.get_size()) + ";" + std::to_string(bytes), ("SingleList_size_growth.txt"));
                run_all_tests_for_dt(&list, to_find, to_add, random_position, list.get_size(), "SingleList", j, repetition);

                // Run tests for list with head and tail
                fill_from_file(&list_ht, 0, i, j);
                bytes = list_ht.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(list_ht.get_size()) + ";" + std::to_string(bytes), ("SingleListHeadTail_size_growth.txt"));
                run_all_tests_for_dt(&list_ht, to_find, to_add, random_position, list_ht.get_size(), "SingleListHeadTail", j, repetition);

                // Run tests for double list
                fill_from_file(&double_list, 0, i, j);
                bytes = double_list.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(double_list.get_size()) + ";" + std::to_string(bytes), ("DoubleList_size_growth.txt"));
                run_all_tests_for_dt(&double_list, to_find, to_add, random_position, double_list.get_size(), "DoubleList", j, repetition);

                // Run tests for dynamic array
                fill_from_file(&dyn_array, 0, i, j);
                bytes = dyn_array.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(dyn_array.get_size()) + ";" + std::to_string(bytes), ("DynamicArray_size_growth.txt"));
                run_all_tests_for_dt(&dyn_array, to_find, to_add, random_position, dyn_array.get_size(), "DynamicArray", j, repetition);
            }
        }
    else if (what_to_test == 2)
        for(int i=1; i<=file_number; i++)
        {
            for(int j=1; j<=data_number; j++)
            {
                int to_add = generate_random_number(random_generator);
                int to_find = generate_random_number(random_generator);
                int bytes;

                // Run tests for list
                fill_from_file2(&queue_heap, i, j);
                int to_add_p = generate_random_number_range(random_generator, 0, queue_heap.get_size()*2);
                // We need size for generating random position
                unsigned int random_position = generate_random_number_unsigned(queue_heap.get_size()-1, random_generator);
                bytes = queue_heap.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(queue_heap.get_size()) + ";" + std::to_string(bytes), ("QueueHeap_size_growth.txt"));
                run_all_tests_for_queue(&queue_heap, to_find, to_add, to_add_p, random_position, queue_heap.get_size(), "QueueHeap", j, repetition);

                fill_from_file2(&queue_array, i, j);
                bytes = queue_array.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(queue_array.get_size()) + ";" + std::to_string(bytes), ("QueueList_size_growth.txt"));
                run_all_tests_for_queue(&queue_array, to_find, to_add, to_add_p, random_position, queue_array.get_size(), "QueueArray", j, repetition);
            }
        }
    else if (what_to_test == 3)
        for(int i=1; i<=file_number; i++)
        {
            std::cerr << "\n" << i << "\n";
            for(int j=1; j<=data_number; j++)
            {
                std::cerr << j << " ";
                int to_add = generate_random_number(random_generator);
                int to_find = generate_random_number(random_generator);
                int bytes;

                // Run tests for list
                fill_from_file_ht(&hash_chain, i, j);
                int to_add_key = generate_random_number_range(random_generator, -hash_chain.get_size()*2, hash_chain.get_size()*2);
                // We need size for generating random position
                unsigned int random_key = generate_random_number_unsigned(hash_chain.get_size()-1, random_generator);
                bytes = hash_chain.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(hash_chain.get_size()) + ";" + std::to_string(bytes), ("HashChain_size_growth.txt"));
                run_all_tests_for_hashtable(&hash_chain, to_find, to_add, to_add_key, random_key, hash_chain.get_size(), "HashChain", j, repetition);

                fill_from_file_ht(&hash_open, i, j);
                bytes = hash_open.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(hash_open.get_size()) + ";" + std::to_string(bytes), ("HashOpen_size_growth.txt"));
                run_all_tests_for_hashtable(&hash_open, to_find, to_add, to_add_key, random_key, hash_open.get_size(), "HashOpen", j, repetition);

                fill_from_file_ht(&hash_cuckoo, i, j);
                bytes = hash_cuckoo.get_byte_size();
                // We check (and save) size for only one iteration over data sizes
                if(j==1)
                    add_line_to_file(std::to_string(hash_cuckoo.get_size()) + ";" + std::to_string(bytes), ("HashCuckoo_size_growth.txt"));
                run_all_tests_for_hashtable(&hash_cuckoo, to_find, to_add, to_add_key, random_key, hash_cuckoo.get_size(), "HashCuckoo", j, repetition);
            }
        }
    return 0;
}
