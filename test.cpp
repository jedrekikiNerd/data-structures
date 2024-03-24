#include "Timer.h"
#include "data_structures/I_data_structure.h"
#include "data_structures/list.h"
#include "data_structures/list_ht.h"
#include "data_structures/list_double.h"
#include "data_structures/dynamic_array.h"
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
Timer timer;


int countTxtFiles(const std::string& folderPath) {
    int count = 0;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            count++;
        }
    }
    return count;
}

// Function that loads one file into given data structure
double fill_from_file(IDataStructure<int> *dt, std::ifstream file, bool direction)
{
    // TODO: Finish
    return;
}

// Adds one line to given file
int add_line_to_file(std::string line, std::ofstream file)
{
    // TODO: Finish
    return;
}


// Function that runs all tests for all data structures and saves time series to files
int run_all_tests()
{
    // We create each data structure
    SingleListH<int> list;
    SingleListHT<int> list_ht;
    DoubleListHT<int> double_list;
    DynamicArray<int> dyn_array;

    // TODO: Finish
    for(file in files)
        //Tutaj każdy test dla każdej struktury i każdy pomiar czasu zapisywany odpowiednio za pomocą add_line_to_file
    
    return;
}

// TODO - DELETE THIS AND MOVE TO FUNCTION DECLRED FEW LINES UP
double fill_from_file(IDataStructure<int> *dt,bool direction)
{
    std::string folderPath = "generated_data";
    int fileCount = countTxtFiles(folderPath);
    for (int i = 0; i < fileCount ; i++)
    {
        const std::string filePre =  "plik";
        const std::string fileExt = ".txt";
        std::string file_name = filePre + std::to_string(i) + fileExt;

        std::ifstream file(file_name);
        if (file.is_open()) 
        {
         int value;
            //std::string line;
            while (file) 
         {
            file >> value;
            if (direction)
                dt->add_back(value);
            else
                dt->add_front(value);
            }
            file.close();
         }
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
    timer.elapsedSeconds();
}

void addLineToFile(const std::string& filePath, const std::string& line) {
    std::ofstream file(filePath, std::ios_base::app); 
    if (file.is_open()) {
        file << line << std::endl; 
        file.close(); 
    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
}

