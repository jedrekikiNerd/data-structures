#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <filesystem>
#include <random>
#include "ui_actions.hpp"
#include "generator.hpp"
#include <set>

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

int generator(int number_samples, int number_of_data, int file_number) {
    // Initialization of the pseudorandom number generator
    srand(time(0));
    std::random_device rd;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(-2147483647,2147483647);

    string folder_name = "generated_data";

    removeFilesInFolder(folder_name);


    for (int j = 1; j <= file_number; j++) 
    {

        for(int x = 1; x <= number_of_data; x++) // number of data is a new variable that we add to the UI 
        {
            generator.seed(rd());


        string nazwaPliku = folder_name + "/wyniki_" + to_string(j) + "_" + to_string(x) + ".txt";
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
        plik.close();
        }
        
        // Increasing the number of samples for the next file
        number_samples = number_samples * 2; 
    }
    return 0;
}

int generator2(int number_samples, int number_of_data, int file_number) {
    // Initialization of the pseudorandom number generator
    srand(time(0));
    std::random_device rd;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(-2147483647,2147483647);

    string folder_name = "generated_data_queues";

    removeFilesInFolder(folder_name);


    for (int j = 1; j <= file_number; j++) 
    {
        uniform_int_distribution<int> distribution_priorities(0,2*number_samples);

        for(int x = 1; x <= number_of_data; x++) // number of data is a new variable that we add to the UI 
        {
            generator.seed(rd());


        string nazwaPliku = folder_name + "/wyniki_" + to_string(j) + "_" + to_string(x) + ".txt";
        fstream plik(nazwaPliku, ios::out);
        if (!plik.is_open()) 
        {
            return 1;
        }

        //Generate random numbers 
        for (int i = 0; i < number_samples; i++) 
        {
            int temp = distribution(generator);
            int priority = distribution_priorities(generator);
            plik << temp << " " << priority << endl;
        }
        plik.close();
        }
        
        // Increasing the number of samples for the next file
        number_samples = number_samples * 2; 
    }
    return 0;
}

int generator3(int number_samples, int number_of_data, int file_number) {
    // Initialization of the pseudorandom number generator
    srand(time(0));
    std::random_device rd;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(-2147483647,2147483647);

    string folder_name = "generated_data_hash";

    removeFilesInFolder(folder_name);


    for (int j = 1; j <= file_number; j++) 
    {
        uniform_int_distribution<int> distribution_priorities(-number_samples*2, number_samples*2);

        for(int x = 1; x <= number_of_data; x++) // number of data is a new variable that we add to the UI 
        {
            generator.seed(rd());


        string nazwaPliku = folder_name + "/wyniki_" + to_string(j) + "_" + to_string(x) + ".txt";
        fstream plik(nazwaPliku, ios::out);
        if (!plik.is_open()) 
        {
            return 1;
        }

        std::set<int> unique_keys;

        //Generate random numbers 
        for (int i = 0; i < number_samples; i++) 
        {
            int temp = distribution(generator);
            int key;
            do
            {
                key = distribution_priorities(generator);
            }
            while (!unique_keys.insert(key).second);
            plik << key << " " << temp << endl;
        }
        plik.close();
        }
        
        // Increasing the number of samples for the next file
        number_samples = number_samples * 2; 
    }
    return 0;
}

// Function prepared for connecting to UI - calls genertor with arguments from user input
int ui_run_generator()
{
    int number_files = user_input_action("Podaj ile próbek danych chcesz otrzymać: ");
    int first_sample_size = user_input_action("Podaj ilość danych do wylosowania: ");
    int number_of_data = user_input_action("Podaj ile próbek każdej wielkości wygenerować: ");
    //generator(first_sample_size, number_of_data, number_files);
    //generator2(first_sample_size, number_of_data, number_files);
    generator3(first_sample_size, number_of_data, number_files);
    display_action("Dane zostały wygenerowane!");
    return 0;
}
