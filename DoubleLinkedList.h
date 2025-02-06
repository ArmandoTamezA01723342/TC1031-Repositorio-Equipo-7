#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "LogData.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// Estructura de un nodo en la lista doblemente enlazada
struct Node {
    LogData* data;  // Puntero a un objeto LogData
    Node* prev;  // Puntero al nodo anterior
    Node* next;  // Puntero al siguiente nodo

    // Constructor del nodo
    Node(LogData* d) : data(d), prev(nullptr), next(nullptr) {}
};

class DoubleLinkedList {
public:
    Node* head;  // Puntero al primer nodo de la lista
    Node* tail;  // Puntero al último nodo de la lista

    // Constructor de la lista
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    // Función para añadir un dato al final de la lista
    // Complejidad: O(1)
    void append(LogData* log) {
        Node* new_node = new Node(log);
        if (!head) {
            head = tail = new_node;  // Si la lista está vacía, el nuevo nodo será el primero y el último
        } else {
            tail->next = new_node;  // Se añade al final
            new_node->prev = tail;  // Se establece la relación con el nodo anterior
            tail = new_node;  // Actualizamos el puntero al último nodo
        }
    }

    // Función para mostrar el contenido de la lista
    // Complejidad: O(n)
    void display() {
        Node* temp = head;
        while (temp) {
            // Mostrar la fecha en formato "Mes Día Hora:Minuto:Segundo"
            string month_str = temp->data->monthToString();
            cout << month_str << " "
                 << setfill('0') << setw(2) << temp->data->day << " "
                 << setfill('0') << setw(2) << temp->data->hour << ":"
                 << setfill('0') << setw(2) << temp->data->minute << ":"
                 << setfill('0') << setw(2) << temp->data->second << " "
                 << temp->data->ip_address << " "
                 << temp->data->reason << endl;
            temp = temp->next;  // Avanzamos al siguiente nodo
        }
    }

    // Función para aplicar el algoritmo de merge sort a la lista
    // Complejidad: O(n log n)
    void mergeSort() {
        if (!head) return;
        vector<LogData*> data_vector;

        // Convertir la lista a un vector para aplicar el merge sort
        Node* current = head;
        while (current) {
            data_vector.push_back(current->data);
            current = current->next;
        }

        // Realizar el merge sort
        mergeSortHelper(data_vector);

        // Volver a poner los datos ordenados en la lista
        current = head;
        for (auto data : data_vector) {
            current->data = data;
            current = current->next;
        }
    }

    // Función para guardar los datos ordenados en un archivo
    // Complejidad: O(n)
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "No se puede abrir el archivo: " << filename << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            // Guardar los datos en formato de fecha "Mes Día Hora:Minuto:Segundo"
            string month_str = temp->data->monthToString();
            file << month_str << " "
                 << setfill('0') << setw(2) << temp->data->day << " "
                 << setfill('0') << setw(2) << temp->data->hour << ":"
                 << setfill('0') << setw(2) << temp->data->minute << ":"
                 << setfill('0') << setw(2) << temp->data->second << " "
                 << temp->data->ip_address << " "
                 << temp->data->reason << endl;
            temp = temp->next;  // Avanzamos al siguiente nodo
        }

        file.close();  // Cerramos el archivo después de escribir
    }

    // Función para guardar los datos dentro de un rango de fechas en un archivo
    // Complejidad: O(n)
    void saveToFileInRange(const string& start_date, const string& end_date, const string& filename) {
        // Convertir las fechas de inicio y fin a objetos LogData
        LogData start_log = parseDate(start_date);
        LogData end_log = parseDate(end_date);

        // Obtener los registros dentro del rango de fechas
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "No se puede abrir el archivo: " << filename << endl;
            return;
        }

        // Guardar las fechas de inicio y fin en el archivo
        file << "Fecha 1: " << start_date << endl;
        file << "Fecha 2: " << end_date << endl;

        vector<LogData*> result;
        Node* temp = head;
        while (temp) {
            if (*temp->data >= start_log && *temp->data <= end_log) {
                result.push_back(temp->data);  // Si está dentro del rango, añadir al resultado
            }
            temp = temp->next;
        }

        // Guardar el número de registros encontrados
        file << "\nResultado: " << result.size() << " Registros" << endl;

        // Guardar los registros encontrados en el archivo
        for (auto log_data : result) {
            string month_str = log_data->monthToString();
            file << month_str << " "
                 << setfill('0') << setw(2) << log_data->day << " "
                 << setfill('0') << setw(2) << log_data->hour << ":"
                 << setfill('0') << setw(2) << log_data->minute << ":"
                 << setfill('0') << setw(2) << log_data->second << " "
                 << log_data->ip_address << " "
                 << log_data->reason << endl;
        }

        file.close();  // Cerramos el archivo después de escribir
    }

    // Función para buscar logs dentro de un rango de fechas utilizando búsqueda binaria 
    // Complejidad: O(n) debido a la búsqueda binaria y la conversión de la lista vinculada en un vector
    vector<LogData*> searchLogsByDateRange(const string& start_date, const string& end_date) {
        vector<LogData*> result;

        // Convertir las fechas de inicio y fin a objetos LogData
        LogData start_log = parseDate(start_date);
        LogData* end_log = new LogData(parseDate(end_date));

        // Convertir la lista vinculada en un vector para facilitar la búsqueda
        vector<LogData*> log_data_vector;
        Node* temp = head;
        while (temp) {
            log_data_vector.push_back(temp->data);
            temp = temp->next;
        }

        // Usar búsqueda binaria para encontrar el rango
        auto lower = lower_bound(log_data_vector.begin(), log_data_vector.end(), start_log, [](LogData* a, const LogData& b) {
            return *a < b;  // Desreferenciar el puntero para comparar los objetos LogData
        });

        auto upper = upper_bound(log_data_vector.begin(), log_data_vector.end(), end_log, [](LogData* a, LogData* b) {
            return *a < *b;
        });

        // Recoger los resultados dentro del rango especificado
        result.insert(result.end(), lower, upper);

        // Imprimir el tamaño del resultado para fines de depuración
        cout << "Resultado: " << result.size() << " Registros" << endl;
        
        delete end_log;

        return result;
    }

    // Función para convertir una cadena de fecha en un objeto LogData
    // Complejidad: O(1)
    LogData parseDate(const string& date_str) {
        stringstream ss(date_str);
        string month_str;
        int day, hour, minute, second;
        char colon;  // Variable para los dos puntos

        ss >> month_str >> day >> hour >> colon >> minute >> colon >> second;

        int month = LogData::monthNameToInt(month_str);  // Convertir el nombre del mes a número
        return LogData(month, day, hour, minute, second, "", "");
    }

    // Destructor para liberar la memoria de los nodos
    ~DoubleLinkedList() {
        Node* temp = head;
        while (temp) {
            Node* to_delete = temp;
            temp = temp->next;
            delete to_delete->data;  // Eliminar los datos
            delete to_delete;  // Eliminar el nodo
        }
    }

private:
    // Función auxiliar para realizar el merge sort
    void mergeSortHelper(vector<LogData*>& data_vector) {
        if (data_vector.size() <= 1) return;

        size_t mid = data_vector.size() / 2;
        vector<LogData*> left(data_vector.begin(), data_vector.begin() + mid);
        vector<LogData*> right(data_vector.begin() + mid, data_vector.end());

        mergeSortHelper(left);
        mergeSortHelper(right);

        merge(data_vector, left, right);  // Mezclar las mitades ordenadas
    }

    // Función para combinar dos vectores ordenados
    void merge(vector<LogData*>& data_vector, vector<LogData*>& left, vector<LogData*>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (*left[i] < *right[j]) {  // Comparar por mes
                data_vector[k++] = left[i++];
            } else {
                data_vector[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            data_vector[k++] = left[i++];
        }
        while (j < right.size()) {
            data_vector[k++] = right[j++];
        }
    }
};

#endif // DOUBLELINKEDLIST_H
