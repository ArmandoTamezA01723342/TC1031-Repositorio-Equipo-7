#include "Graph.h"
#include <stdexcept>

//Complejidad：O(1)
void Graph::addNode(const std::string& ip) {
    if (adjList.find(ip) == adjList.end()) {
        adjList[ip] = std::vector<std::string>();
    }
}

// Complejidad: O(1) (en el peor caso O(log n))
void Graph::addEdge(const std::string& ipOrigin, const std::string& ipDest) {
    // Antes de agregar la arista, se asegura que ambas IPs existan en el grafo
    addNode(ipOrigin);
    addNode(ipDest);
    adjList[ipOrigin].push_back(ipDest);
}

// Complejidad: O(n) (en el peor caso O(n))
std::vector<std::string> Graph::getAdjacentIPs(const std::string& ip) const {
    auto it = adjList.find(ip);
    if (it != adjList.end()) {
        return it->second;
    } else {
        return std::vector<std::string>();
    }
}

// Complejidad: O(1)
int Graph::getOutCount(const std::string& ip) const {
    auto it = adjList.find(ip);
    if (it != adjList.end()) {
        return static_cast<int>(it->second.size());
    }
    return 0;
}

// Complejidad: O(n * m)
int Graph::getInCount(const std::string& ip) const {
    int count = 0;
    for (const auto& pair : adjList) {
        for (const std::string& dest : pair.second) {
            if (dest == ip) {
                count++;
            }
        }
    }
    return count;
}

// Complejidad: O(1)
bool Graph::exists(const std::string& ip) const {
    return (adjList.find(ip) != adjList.end());
}

// Complejidad: O(n)
std::vector<std::string> Graph::getAllIPs() const {
    std::vector<std::string> ips;
    for (const auto& pair : adjList) {
        ips.push_back(pair.first);
    }
    return ips;
}
