#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "Registro.h"

// Funcion para leer los registros desde un archivo y almacenarlos en un vector.
void leerArchivo(const std::string& nombreArchivo, std::vector<Registro>& registros);

// Funcion para guardar los registros en un archivo.
void guardarArchivo(const std::string& nombreArchivo, const std::vector<Registro>& registros);

// Implementacion del algoritmo de ordenamiento por burbuja para ordenar los registros.
void ordenarBurbuja(std::vector<Registro>& registros, int& comparaciones, int& intercambios);

// Implementacion del algoritmo de ordenamiento QuickSort para ordenar los registros.
void ordenarPorQuickSort(std::vector<Registro>& registros, int& comparaciones, int& intercambios);

// Funcion para buscar registros dentro de un rango de tiempo especifico.
std::vector<Registro> buscarRango(const std::vector<Registro>& registros, const Registro& inicio, const Registro& fin);

#endif // UTILS_H
