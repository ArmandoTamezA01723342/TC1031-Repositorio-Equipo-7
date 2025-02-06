// Equipo 7

// Kanaru Ito A01723367
// Armando Tamez Larragoity A01723342
// Tomas Sommer A01781292

// Para compilar: g++ -std=c++17 -O3 -o main *.cpp
// Para ejecutar: ./main

#include "DoubleLinkedList.h"
#include "Utils.h"
#include <iostream>

int main() {
    DoubleLinkedList list;

    // Leer el archivo y agregar los datos a la lista
    string filename = "bitacoraData.txt"; // Especificar el nombre del archivo
    readFileAndPopulateList(filename, list); // Llama a la función para leer el archivo y llenar la lista

    // Aplicar el algoritmo de ordenamiento por mezcla (MergeSort) a la lista
    list.mergeSort();

    // Guardar los datos ordenados en un archivo
    list.saveToFile("bitacora_ordenada.txt");

    // Mostrar el contenido de la lista ordenada (comentado para no mostrar)
    // list.display();

    // Pedir al usuario un rango de fechas
    string start_date, end_date;
    cout << "fecha 1: ";  // Solicitar la primera fecha
    getline(cin, start_date);
    cout << "fecha 2: ";  // Solicitar la segunda fecha
    getline(cin, end_date);

    // Obtener los resultados de la búsqueda dentro del rango de fechas
    vector<LogData*> result = list.searchLogsByDateRange(start_date, end_date);

    // Si no hay resultados, mostrar un mensaje
    if (result.empty()) {
        cout << "No se pudo encontrar el registro" << endl;
    } else {

        // Agregar los resultados a una nueva lista doblemente enlazada
        DoubleLinkedList result_list;
        for (auto log : result) {
            result_list.append(log);  // Añadir los registros de resultados a result_list
        }

        // Mostrar el contenido de la lista de resultados
        result_list.display();

        // Guardar los resultados en un archivo con el nombre de rango de fechas
        result_list.saveToFileInRange(start_date, end_date, "resultado_busqueda.txt");
        cout << "El resultado se guardo en 'resultado_busqueda.txt'" << endl;
    }

    return 0;
}
