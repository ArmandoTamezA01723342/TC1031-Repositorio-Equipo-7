#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

class Graph {
private:
    // La clave es la IP y el valor es la lista de IPs a las que se puede acceder desde esa IP
    std::unordered_map<std::string, std::vector<std::string>> adjList;
public:
    Graph() {}
    
    // Agrega un nodo (IP) si no existe en el grafo
    void addNode(const std::string& ip);
    
    // Agrega una arista dirigida desde ipOrigin hacia ipDest
    void addEdge(const std::string& ipOrigin, const std::string& ipDest);
    
    // Retorna la lista de IPs adyacentes a la IP indicada
    std::vector<std::string> getAdjacentIPs(const std::string& ip) const;
    
    // Retorna el numero de aristas salientes desde la IP
    int getOutCount(const std::string& ip) const;
    
    // Retorna el numero de aristas entrantes a la IP
    int getInCount(const std::string& ip) const;
    
    // Verifica si la IP existe en el grafo
    bool exists(const std::string& ip) const;
    
    // Retorna una lista con todas las IPs del grafo
    std::vector<std::string> getAllIPs() const;
};

#endif // GRAPH_H
