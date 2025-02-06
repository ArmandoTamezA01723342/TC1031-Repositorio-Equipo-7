#include "HashTable.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

// Complejidad: O(n) (donde n es el tamaño de la tabla, ya que se redimensiona la tabla)
HashTable::HashTable(int size) : tableSize(size), totalCollisions(0) {
    table.resize(tableSize, nullptr);
}

// Complejidad: O(n) (donde n es el tamaño de la tabla, ya que se recorren todas las entradas para eliminarlas)
HashTable::~HashTable() {
    for (auto entry : table) {
        delete entry;
    }
}

// Complejidad: O(k) (donde k es la longitud de la cadena de la IP, ya que se recorre cada caracter de la IP)
int HashTable::hashFunction(const std::string& ip) const {
    unsigned long hash = 0;
    // Proceso de hash: para cada caracter, se multiplica el hash acumulado por 31 y se suma el valor ASCII del caracter.
    for (char ch : ip) {
        hash = hash * 31 + ch;
    }
    return hash % tableSize;
}

 // Complejidad: O(k + n) (O(k) para calcular el hash y O(n) para la inserción, donde n es el tamaño de la tabla)
void HashTable::insert(const Entry& entry) {
    int index = hashFunction(entry.ip);
    int i = 0;
    int pos;
    while (true) {
        pos = (index + i * i) % tableSize;
        if (table[pos] == nullptr) {
            table[pos] = new Entry(entry);
            break;
        }
        else {
            // Si ya existe la misma IP, se actualiza la informacion
            if (table[pos]->ip == entry.ip) {
                table[pos]->totalOut = entry.totalOut;
                table[pos]->totalIn  = entry.totalIn;
                break;
            }
            totalCollisions++;
            i++;
            if (i == tableSize) {
                throw std::runtime_error("Tabla hash llena, no se pudo insertar: " + entry.ip);
            }
        }
    }
}

// Complejidad: O(k + n) (O(k) para calcular el hash y O(n) para la búsqueda, donde n es el tamaño de la tabla)
Entry* HashTable::search(const std::string& ip) const {
    int index = hashFunction(ip);
    int i = 0;
    int pos;
    while (true) {
        pos = (index + i * i) % tableSize;
        if (table[pos] == nullptr) {
            return nullptr; // No se encontro la entrada
        }
        if (table[pos]->ip == ip) {
            return table[pos];
        }
        i++;
        if (i == tableSize) {
            return nullptr;
        }
    }
}

// Complejidad: O(k + n + m log m) (O(k) para calcular el hash, O(n) para la búsqueda y O(m log m) para ordenar las IPs adyacentes)
void HashTable::getIPSummary(const std::string& ip, const Graph& graph) const {
    Entry* entry = search(ip);
    if (entry == nullptr) {
        std::cout << "No se encontro informacion para la IP: " << ip << std::endl;
        return;
    }
    std::cout << "Resumen para la IP: " << entry->ip << std::endl;
    std::cout << "Total de direcciones accesadas (out): " << entry->totalOut << std::endl;
    std::cout << "Total de accesos recibidos (in): " << entry->totalIn << std::endl;
    
    // Obtiene la lista de IPs accesadas desde la IP y la ordena en forma descendente
    std::vector<std::string> adjacent = graph.getAdjacentIPs(ip);
    std::sort(adjacent.begin(), adjacent.end(), std::greater<std::string>());
    
    std::cout << "Direcciones accesadas desde " << ip << " (ordenadas descendentemente):" << std::endl;
    for (const auto& adjIP : adjacent) {
        std::cout << adjIP << std::endl;
    }
}

// Complejidad: O(1)
int HashTable::getTotalCollisions() const {
    return totalCollisions;
}
