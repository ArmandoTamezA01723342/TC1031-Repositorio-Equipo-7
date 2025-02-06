/*
Equipo 7

Kanaru Ito A01723367
Armando Tamez Larragoity A01723342
Tomas Sommer A01781292

Para compilar: g++ -std=c++17 -o main *.cpp
Para ejecutar: ./main
El archivo BitacoraGrafos.txt debe estar en el mismo directorio.
*/


#include <iostream>
#include <string>
#include <vector>
#include "BitacoraParser.h"
#include "Graph.h"
#include "HashTable.h"

int main() {
    Graph graph;
    try {
        // Lee el archivo "bitacoraGrafos.txt" y construye el grafo
        graph = BitacoraParser::parseFile("bitacoraGrafos.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Error al procesar la bitacora: " << e.what() << std::endl;
        return 1;
    }
    
    // El tamano de la tabla hash se puede ajustar.
    int tableSize = 13381;//13381
    HashTable hashTable(tableSize);
    
    // Para cada IP en el grafo, se calcula el resumen y se inserta en la tabla hash
    std::vector<std::string> ipList = graph.getAllIPs();
    for (const std::string& ip : ipList) {
        int totalOut = graph.getOutCount(ip);
        int totalIn  = graph.getInCount(ip);
        Entry entry(ip, totalOut, totalIn);
        try {
            hashTable.insert(entry);
        }
        catch (const std::exception& e) {
            std::cerr << "Error al insertar en la tabla hash: " << e.what() << std::endl;
        }
    }
    
    std::cout << "Total de colisiones en la tabla hash: " << hashTable.getTotalCollisions() << std::endl;
    
    // Solicita al usuario la IP para mostrar el resumen
    std::cout << "Ingrese la IP que desea consultar: ";
    std::string ipSolicitada;
    std::cin >> ipSolicitada;
    
    if (!graph.exists(ipSolicitada)) {
        std::cout << "La IP ingresada no existe en la bitacora." << std::endl;
    }
    else {
        hashTable.getIPSummary(ipSolicitada, graph);
    }
    
    return 0;
}
