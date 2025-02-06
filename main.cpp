// Equipo 7

// Kanaru Ito A01723367
// Armando Tamez Larragoity A01723342
// Tomas Sommer A01781292

// Para compilar: g++ -o main main.cpp Registro.cpp utils.cpp
// Para ejecutar: ./main


#include <iostream>
#include <sstream> // Para std::istringstream
#include <vector>
#include <algorithm>
#include "Utils.h"
#include "Registro.h"

// Complejidad: O(1)
Registro leerFechaUsuario(const std::string& mensaje) {
    std::cout << mensaje << ": ";
    std::string entrada;
    std::getline(std::cin, entrada);

    std::istringstream iss(entrada);
    std::string mes;
    int dia, hora, minuto, segundo;
    char separador;

    iss >> mes >> dia >> hora >> separador >> minuto >> separador >> segundo;
    return Registro(mes, dia, hora, minuto, segundo, "", ""); // IP y razon vacios para comparacion
}

//// Complejidad: dependiendo de la opcion
void mostrarMenu() {
    std::cout << "\n--- MENU ---\n";
    std::cout << "1. Realizar los dos metodos de ordenamiento\n";
    std::cout << "2. Buscar registros en un rango de fechas\n";
    std::cout << "3. Salir\n";
    std::cout << "Ingrese una opcion: ";
}

int main() {
    std::vector<Registro> registros;
    leerArchivo("bitacoraData.txt", registros);

    bool salir = false;
    while (!salir) {
        mostrarMenu();
        int opcion;
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                std::vector<Registro> copiaRegistros = registros;

                // Burbuja {Complejidad: O(n^2)}
                std::cout << "Ordenando con Burbuja...\n";
                int comparacionesBurbuja = 0, intercambiosBurbuja = 0;
                ordenarBurbuja(copiaRegistros, comparacionesBurbuja, intercambiosBurbuja);
                guardarArchivo("bitacora_ordenada_burbuja.txt", copiaRegistros);

                // QuickSort {Complejidad temporal promedio: O(n log n), peor caso: O(n^2)}
                std::cout << "Ordenando con QuickSort...\n";
                int comparacionesQuickSort = 0, intercambiosQuickSort = 0;
                ordenarPorQuickSort(registros, comparacionesQuickSort, intercambiosQuickSort);
                guardarArchivo("bitacora_ordenada_quicksort.txt", registros);

                // Mostrar estadisticas de ordenamiento
                std::cout << "\nEstadisticas de ordenamiento:\n";
                std::cout << "Burbuja - Comparaciones: " << comparacionesBurbuja << ", Intercambios: " << intercambiosBurbuja << "\n";
                std::cout << "QuickSort - Comparaciones: " << comparacionesQuickSort << ", Intercambios: " << intercambiosQuickSort << "\n";
                break;
            }
            case 2: {
                // Solicitar fechas al usuario
                Registro fechaInicio = leerFechaUsuario("fecha 1");
                Registro fechaFin = leerFechaUsuario("fecha 2");

                // Validar fechas usando busqueda binaria
                auto itInicio = std::lower_bound(registros.begin(), registros.end(), fechaInicio);
                auto itFin = std::upper_bound(registros.begin(), registros.end(), fechaFin);

                if (itInicio == registros.end() || *itInicio < fechaInicio) {
                    std::cout << "La fecha de inicio no se encuentra en la bitacora.\n";
                    break;
                }

                if (itFin == registros.begin() || *(itFin - 1) > fechaFin) {
                    std::cout << "La fecha de fin no se encuentra en la bitacora.\n";
                    break;
                }

                // Calcular y mostrar el numero total de registros en el rango
                int numRegistros = std::distance(itInicio, itFin);
                std::cout << "\nResultado: " << numRegistros << " Registros\n";

                // Imprimir los registros en el rango
                std::cout << "\nRegistros en el rango [" << fechaInicio.toString()
                          << "] a [" << fechaFin.toString() << "]:\n";
                for (auto it = itInicio; it != itFin; ++it) {
                    std::cout << it->toString() << "\n";
                }
                break;
            }
            case 3:
                std::cout << "Saliendo del programa...\n";
                salir = true;
                break;
            default:
                std::cout << "Opcion no valida. Por favor, intente nuevamente.\n";
        }
    }

    return 0;
}