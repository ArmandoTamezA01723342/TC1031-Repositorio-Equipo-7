#include "BitacoraParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

// Complejidad: O(1) (la inicialización de un objeto Graph es O(1))
Graph BitacoraParser::parseFile(const std::string& filename) {
    Graph graph;
    std::ifstream file;
    // Habilita excepciones para failbit y badbit
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        file.open(filename);
    }
    catch (const std::ifstream::failure& e) {
        throw std::runtime_error("Error al abrir el archivo: " + filename);
    }
    
    try {
        int n, m;
        file >> n >> m;
        file.ignore(); // Descartar el caracter de nueva linea
        
        // Lee n direcciones IP y las agrega al grafo
        for (int i = 0; i < n; i++) {
            std::string ip;
            std::getline(file, ip);
            if (ip.empty()) {
                i--; // Si la linea esta vacia, vuelve a leer
                continue;
            }
            graph.addNode(ip);
        }
        
        // Lee m incidencias y agrega cada una como una arista en el grafo
        for (int i = 0; i < m; i++) {
            std::string line;
            std::getline(file, line);
            if (line.empty()) {
                i--;
                continue;
            }
            std::istringstream iss(line);
            std::string month, day, time;
            std::string ipOriginPort, ipDestPort;
            std::string weight;
            // Lee los primeros 6 tokens
            if (!(iss >> month >> day >> time >> ipOriginPort >> ipDestPort >> weight)) {
                continue; // Si la linea tiene formato incorrecto, se salta
            }
            // Extrae la IP (sin puerto) de ipOriginPort e ipDestPort
            std::string ipOrigin = ipOriginPort.substr(0, ipOriginPort.find(':'));
            std::string ipDest   = ipDestPort.substr(0, ipDestPort.find(':'));
            
            graph.addEdge(ipOrigin, ipDest);
        }
    }
    catch (const std::ifstream::failure& e) {
        throw std::runtime_error("Error al leer el archivo: " + filename);
    }
    
    file.close();
    return graph;
}
