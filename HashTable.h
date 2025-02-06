#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "Graph.h"

// Clase que representa una entrada de la tabla hash
class Entry {
public:
    std::string ip;
    int totalOut;
    int totalIn;

    Entry() : ip(""), totalOut(0), totalIn(0) {}
    Entry(const std::string& ip, int out, int in)
        : ip(ip), totalOut(out), totalIn(in) {}
};

class HashTable {
private:
    std::vector<Entry*> table; // Para direccionamiento abierto
    int tableSize;
    int totalCollisions;
public:
    HashTable(int size);
    ~HashTable();
    
    // Proceso: Se inicia con un hash en 0. Para cada caracter de la IP, se multiplica el hash
    // acumulado por 31 y se le suma el valor ASCII del caracter. Finalmente, se aplica el modulo
    // de tableSize para obtener el indice.
    int hashFunction(const std::string& ip) const;
    
    // Inserta una entrada en la tabla
    void insert(const Entry& entry);
    
    // Busca y retorna la entrada correspondiente a la IP
    Entry* search(const std::string& ip) const;
    
    // Muestra el resumen de la IP y la lista de direcciones accesadas (orden descendente)
    void getIPSummary(const std::string& ip, const Graph& graph) const;
    
    // Retorna el total de colisiones ocurridas durante las inserciones.
    int getTotalCollisions() const;
};

#endif // HASHTABLE_H
