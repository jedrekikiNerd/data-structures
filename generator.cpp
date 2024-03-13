#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

<<<<<<< HEAD
//clearing the folder before adding files
void removeFilesInFolder(const string& folderName) {
    for (const auto& entry : fs::directory_iterator(folderName)) {
        if (entry.is_regular_file()) {
            fs::remove(entry.path());
        }
    }
}

int generator(int number_samples, int sample_skip, int file_number) {
    // Initialization of the pseudorandom number generator
=======

int generator() {
    // Inicjalizacja generatora liczb pseudolosowych
>>>>>>> f281ce333acef48171811ff955a387a5b966a7c2
    srand(time(0));

    int temp, temp2, temp3, temp4;
    int liczba = rand() % 4;
     string folder_name = "generated_data";

    removeFilesInFolder(folder_name);

    for (int j = 0; j < file_number; j++) {
        string nazwaPliku = folder_name + "/wyniki_" + to_string(j + 1) + ".txt";
        fstream plik(nazwaPliku, ios::out);
        if (!plik.is_open()) {
            return 1;
        }

        temp = 2147483647 / number_samples;
        temp3 = temp / 4;

        // Generating data for each file
        if ((temp + (rand() % 10)) % 2 == 0) {
            temp2 = rand() % temp;
          temp = -((temp) + (temp2 * liczba));
        }

        for (int i = 0; i < number_samples; i++) {
            temp4 = temp + i * temp3;
            plik << temp4 << endl;
        }
        
        // increasing the number of samples for the next file
        number_samples += sample_skip;
        
        plik.close();
    }
<<<<<<< HEAD
=======

    if ((temp + (rand() % 10)) % 2 == 0) {
        temp2 = rand() % temp;
        temp = -2147483647 + (temp2 * liczba);
    }

    for (int i = 0; i < liczbaProbek; i++) {
        temp = temp + temp3;
        // Zapis do pliku po przecinku
        plik << temp << endl;

    }

    // Zamknięcie pliku
    plik.close();

    cout << "Dane zapisane do pliku 'wyniki.txt'." << endl;

>>>>>>> f281ce333acef48171811ff955a387a5b966a7c2
    return 0;
}
