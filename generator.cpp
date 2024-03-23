#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <filesystem>
#include <random>
#include "ui_actions.h"
#include "generator.h"

using namespace std;
namespace fs = std::filesystem;

//clearing the folder before adding files
void removeFilesInFolder(const std::string& folderName) {
    if (!fs::exists(folderName)) {
        fs::create_directories(folderName);
    }

    for (const auto& entry : fs::directory_iterator(folderName)) {
        if (entry.is_regular_file()) {
            fs::remove(entry.path());
        }
    }
}

int generator(int number_samples, int sample_skip, int file_number) {
    // Initialization of the pseudorandom number generator
    srand(time(0));
    default_random_engine generator;
    uniform_int_distribution<int> distribution(-2147483647,2147483647);

    string folder_name = "generated_data";

    removeFilesInFolder(folder_name);


    for (int j = 0; j < file_number; j++) 
    {
        string nazwaPliku = folder_name + "/wyniki_" + to_string(j + 1) + ".txt";
        fstream plik(nazwaPliku, ios::out);
        if (!plik.is_open()) 
        {
            return 1;
        }

        //Generate random numbers 
        for (int i = 0; i < number_samples; i++) 
        {
            int temp = distribution(generator);
            plik << temp << endl;
        }
        
        // Increasing the number of samples for the next file
        number_samples += sample_skip;
        
        plik.close();
    }
    return 0;
}


// Function prepared for connecting to UI - calls genertor with arguments from user input
int ui_run_generator()
{
    int number_files = user_input_action("Podaj ile próbek danych chcesz otrzymać: ");
    int first_sample_size = user_input_action("Podaj ilość danych do wylosowania: ");
    int sample_increment = user_input_action("Podaj o ile zwiększać dane: ");
    generator(first_sample_size, sample_increment, number_files);
    display_action("Dane zostały wygenerowane!");
    return 0;
}
