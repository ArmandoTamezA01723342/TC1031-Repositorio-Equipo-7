#ifndef UTILS_H
#define UTILS_H

#include "DoubleLinkedList.h"
#include <string>
#include <sstream>

#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Excepción personalizada para errores de lectura de archivo
class FileReadException : public runtime_error {
public:
    explicit FileReadException(const string& message) : runtime_error(message) {}
};

// Función para leer el archivo y llenar la lista
// Complejidad: O(n)
void readFileAndPopulateList(const string& filename, DoubleLinkedList& list) {
    ifstream file;
    try {
        // Intentar abrir el archivo
        file.open(filename);
        if (!file.is_open()) {
            throw FileReadException("No se puede abrir el archivo: " + filename); // Lanzar excepción si el archivo no se puede abrir
        }

        string line;
        while (getline(file, line)) { // Leer el archivo línea por línea
            // Dividir la línea y obtener la información necesaria
            stringstream ss(line);
            string month_str, ip, reason;
            int day, hour, minute, second;

            // Separar la parte de la fecha (mes, día, hora, minuto, segundo)
            ss >> month_str >> day; // Mes y día
            ss >> hour; ss.ignore(1, ':'); // Hora
            ss >> minute; ss.ignore(1, ':'); // Minuto
            ss >> second; // Segundo
            ss >> ip; // Dirección IP

            // El resto se considera como el motivo (reason)
            getline(ss, reason);

            // Eliminar los espacios al principio y al final del motivo
            reason.erase(reason.begin(), find_if(reason.begin(), reason.end(), [](unsigned char c) { return !isspace(c); }));
            reason.erase(find_if(reason.rbegin(), reason.rend(), [](unsigned char c) { return !isspace(c); }).base(), reason.end());

            // Convertir el nombre del mes a un número entero
            int month = LogData::monthNameToInt(month_str);

            // Crear un objeto LogData y agregarlo a la lista
            LogData* log = new LogData(month, day, hour, minute, second, ip, reason); // Se ajustan los parámetros (7 en lugar de 8)
            list.append(log); // Agregar el objeto a la lista
        }

        file.close(); // Cerrar el archivo después de leer
    }
    catch (const FileReadException& e) {
        cerr << "Error: " << e.what() << endl; // Mostrar el mensaje de error si no se puede abrir el archivo
    }
    catch (const exception& e) {
        cerr << "Ocurrió un error inesperado: " << e.what() << endl; // Manejar otros errores
    }
}

#endif // UTILS_H
