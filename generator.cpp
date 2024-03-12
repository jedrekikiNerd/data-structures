#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Inicjalizacja generatora liczb pseudolosowych
    srand(time(0));

    int liczbaProbek, temp, temp2, temp3, liczbaZapis;
    int liczba = rand() % 10;
    // Wczytanie liczby próbek
    cout << "Podaj liczbe probek: ";
    cin >> liczbaProbek;

    temp = 2147483647 / liczbaProbek;
    temp3 = temp / 2;

    // Otwarcie pliku do zapisu
    fstream plik("wyniki.txt",ios::out);
    // Sprawdzenie, czy plik został otwarty poprawnie
    if (!plik.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku do zapisu." << endl;
        return 1; // Zwrócenie kodu błędu
    }

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

    return 0;
}
