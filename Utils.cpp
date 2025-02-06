#include "Utils.h"
#include <fstream>
#include <algorithm>
#include <sstream>

// Funcion para leer los registros desde un archivo y almacenarlos en un vector.
// Complejidad: O(n)
void leerArchivo(const std::string& nombreArchivo, std::vector<Registro>& registros) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string mes, ip, razon;
        int dia, hora, minuto, segundo;
        char separator;
        iss >> mes >> dia >> hora >> separator >> minuto >> separator >> segundo >> ip;
        std::getline(iss, razon);
        registros.emplace_back(mes, dia, hora, minuto, segundo, ip, razon);
    }
    archivo.close();
}

// Funcion para guardar los registros en un archivo.
// Complejidad: O(n)
void guardarArchivo(const std::string& nombreArchivo, const std::vector<Registro>& registros) {
    std::ofstream archivo(nombreArchivo);
    for (const auto& registro : registros) {
        archivo << registro.toString() << "\n";
    }
    archivo.close();
}

// Implementacion del algoritmo de ordenamiento por burbuja para ordenar los registros.
// Peor caso: O(n^2)
// Mejor caso: O(n) (si la lista ya esta ordenada)
void ordenarBurbuja(std::vector<Registro>& registros, int& comparaciones, int& intercambios) {
    comparaciones = 0;
    intercambios = 0;
    size_t n = registros.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            comparaciones++;
            if (registros[j + 1] < registros[j]) {
                std::swap(registros[j], registros[j + 1]);
                intercambios++;
            }
        }
    }
}

// Implementacion del algoritmo de ordenamiento QuickSort para ordenar los registros.
// Complejidad promedio: O(nlog(n)) 
void ordenarPorQuickSort(std::vector<Registro>& registros, int& comparaciones, int& intercambios) {
    comparaciones = 0;
    intercambios = 0;
    std::sort(registros.begin(), registros.end(), [&](const Registro& a, const Registro& b) {
        comparaciones++;
        if (a < b) return true;
        intercambios++;
        return false;
    });
}

// Funcion para buscar registros dentro de un rango de tiempo especifico.
// conplejidad Complejidad: O(logn+k) n: Tamaño del vector. k: Número de elementos en el rango encontrado.
std::vector<Registro> buscarRango(const std::vector<Registro>& registros, const Registro& inicio, const Registro& fin) {
    auto itInicio = std::lower_bound(registros.begin(), registros.end(), inicio);
    auto itFin = std::upper_bound(registros.begin(), registros.end(), fin);
    return std::vector<Registro>(itInicio, itFin);
}
