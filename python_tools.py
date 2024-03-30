import os
import pandas as pd
import matplotlib.pyplot as plt

# Ścieżka do folderu, w którym znajdują się pliki z pomiarami
folder_path = 'test_results'
current_directory = os.path.dirname(__file__)
folder_path = os.path.join(current_directory, folder_path)

# Funkcja do wczytywania danych z plików tekstowych i obliczania średniej
def process_files_in_folder(folder_path):
    data = {}

    # Iteruj przez pliki w folderze
    for filename in os.listdir(folder_path):
        if filename.endswith(".txt"):
            # Wczytaj dane z pliku
            file_path = os.path.join(folder_path, filename)
            df = pd.read_csv(file_path, delimiter=';', header=None, names=['size', 'time'])

            # Pobierz nazwę struktury danych i operacji z nazwy pliku
            data_structure, operation_name = filename.split('_')[0], filename.split('_')[1]

            # Jeśli nie istnieje jeszcze klucz w słowniku, stwórz go
            if (data_structure, operation_name) not in data:
                data[(data_structure, operation_name)] = {'sizes': [], 'times': []}
                # Dodaj dane do słownika
                data[(data_structure, operation_name)]['sizes'].extend(df['size'])
                data[(data_structure, operation_name)]['times'].extend(df['time'])
            else:
                data[(data_structure, operation_name)]['times'] += df['time']
                

    return data

print(process_files_in_folder(folder_path))
