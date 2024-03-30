import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Ścieżka do folderu, w którym znajdują się pliki z pomiarami
folder_path = 'test_results'
current_directory = os.path.dirname(__file__)
folder_path = os.path.join(current_directory, folder_path)

# Nazwy plików do iteracji i wczytywania
endings = ["1_1.txt", "2_1.txt", "3_1.txt"]
prefixes = ["DoubleList", "DynamicArray", "SingleListHeadTail", "SingleList"]
operation_names = ["add_center", "add_first", "add_last", "add_random", "clear", "find_random", "find_random_existing", "remove_center", "remove_first", "remove_last", "remove_random"]

# Funkcja do wczytywania danych z plików tekstowych i obliczania średniej
def process_files_in_folder(folder_path):
    data = {}

    # Iteruj przez pliki w folderze
    for prefix in prefixes:
        for operation in operation_names:
            data_structure, operation_name = prefix, operation
            # Jeśli nie istnieje jeszcze klucz w słowniku, stwórz go
            if data_structure not in data:
                data[data_structure] = {}
            if operation_name not in data[data_structure]:
                data[data_structure][operation_name] = {'sizes': [], 'times': []}
            for ending in endings:
                # Wczytaj dane z pliku
                file_path = os.path.join(folder_path, prefix+"_"+operation+ending)
                df = pd.read_csv(file_path, delimiter=';', header=None, names=['size', 'time'])

                # lista 'times' musi mieć odpowiednią ilość elementów
                while len(data[data_structure][operation_name]['times']) < len(df['time']):
                    data[data_structure][operation_name]['times'].append(0)

                for i, time_value in enumerate(df['time']):
                    data[data_structure][operation_name]['times'][i] += time_value
                data[data_structure][operation_name]['sizes'] = df['size'].to_list()

            for i, time_value in enumerate(data[data_structure][operation_name]['times']):
                data[data_structure][operation_name]['times'][i] /= 3

    return data

data = process_files_in_folder(folder_path)
for data_structure in data:
    for operation in data[data_structure]:
        pass
        print(f"{data_structure} - {operation}: {data[data_structure][operation]}")



# Funkcja do wyświetlania wykresu i krzywej trendu dla danych operacji i struktury danych
def plot_operation_trend(data, data_structure, operation):
    sizes = data[data_structure][operation]['sizes']
    times = data[data_structure][operation]['times']
    
    # Rysowanie wykresu
    plt.plot(sizes, times, label='Actual Data', linestyle='-', marker='o')  # Linia ciągła z punktami
    
    # Obliczanie krzywej trendu
    z = np.polyfit(sizes, times, 1)
    p = np.poly1d(z)
    plt.plot(sizes, p(sizes), "r--", label='Linia trendu')
    
    plt.xlabel('Wielkość danych')
    plt.ylabel('Czas wykonania')
    plt.title(f'Czas wykonania operacji {operation} na strukturze {data_structure}')
    plt.legend()

    # Ustawienia osi
    plt.xscale('linear')  # Zmiana skali osi X
    plt.yscale('linear')  # Zmiana skali osi Y
    plt.xlim(left=0, right=max(sizes)+max(sizes)/100)  # Ustawienie zakresu osi X
    plt.ylim(bottom=0, top=max(times)+max(max(times)/10, 200))
    # Zmiana formatowania osi na liczby całkowite (bez notacji naukowej)
    plt.ticklabel_format(style='plain', axis='both')

    plt.show()

# Iteracja przez dane i rysowanie wykresów dla każdej operacji i struktury danych
for data_structure in data:
    for operation in data[data_structure]:
        plot_operation_trend(data, data_structure, operation)