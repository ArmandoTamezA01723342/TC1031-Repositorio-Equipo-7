#ifndef BITACORA_PROCESSOR_H
#define BITACORA_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <map>
#include "MyVector.h"
#include "HeapSort.h"
#include "PriorityQueue.h"

using namespace std;

class BitacoraProcessor {
private:
    string filename;
    MyVector<string> logEntries;

    string extractIP(const string& logEntry) const;

public:
    BitacoraProcessor(const string& filename);
    void loadData();
    MyVector<string> extractSortedIPs();
    void saveToFile(const string& outputFilename, const MyVector<string>& data) const;
    void saveTopIPs(const string& outputFilename, int topN);
};

// Constructor
BitacoraProcessor::BitacoraProcessor(const string& filename) : filename(filename) {}

// Carga los datos desde el archivo
void BitacoraProcessor::loadData() {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Couldn't open the file: " + filename);
    }
    
    string line;
    while (getline(file, line)) {
        logEntries.pushing(line);
    }
    file.close();
}

// Extrae la IP de una entrada del log
string BitacoraProcessor::extractIP(const string& logEntry) const {
    istringstream iss(logEntry);
    string word;
    
    // Saltar al tercer espacio
    for (int i = 0; i < 3; i++) {
        if (!(iss >> word)) {
            throw runtime_error("Invalid log entry format");
        }
    }

    // Obtenga la cuarta palabra (IP:puerto)
    string ipPort;
    if (!(iss >> ipPort)) {
        throw runtime_error("Invalid log entry format");
    }

    // Encuentra la posición de `:` para obtener solo la IP
    size_t pos = ipPort.find(':');
    if (pos == std::string::npos) {
        throw runtime_error("Invalid IP format in log entry");
    }

    // para debug
    // cout << "Log Entry: " << ipPort.substr(0, pos) << endl;

    return ipPort.substr(0, pos);  // `Devuelve solo la parte antes de :` (solo dirección IP)
}


// Extrae y ordena todas las IPs
MyVector<string> BitacoraProcessor::extractSortedIPs() {
    MyVector<string> ips;
    size_t errorCount = 0;
    for (size_t i = 0; i < logEntries.gettingSize(); i++) {
        try {
            ips.pushing(extractIP(logEntries[i]));
        } catch (const exception& e) {
            errorCount++;
        }
    }
    
    if (errorCount > 0) {
        cerr << "Skipped " << errorCount << " invalid log entries." << endl;
    }

    HeapSort<string>::sort(ips);
    return ips;
}

// Guarda los datos en un archivo
void BitacoraProcessor::saveToFile(const string& outputFilename, const MyVector<string>& data) const {
    ofstream outFile(outputFilename);
    if (!outFile) {
        throw runtime_error("Couldn't open output file: " + outputFilename);
    }
    
    for (size_t i = 0; i < data.gettingSize(); i++) {
        outFile << data[i] << endl;
    }
    outFile.close();
}

// Guarda las IPs con mas accesos
void BitacoraProcessor::saveTopIPs(const string& outputFilename, int topN) {
    map<string, int> ipCount;
    for (size_t i = 0; i < logEntries.gettingSize(); i++) {
        try {
            ipCount[extractIP(logEntries[i])]++;
        } catch (...) {
            continue;
        }
    }

    PriorityQueue<string> pq;
    for (const auto& entry : ipCount) {
        pq.push(entry.first, entry.second);
    }

    ofstream outFile(outputFilename);
    if (!outFile) {
        throw runtime_error("Couldn't open output file: " + outputFilename);
    }

    for (int i = 0; i < topN && !pq.isEmpty(); i++) {
        string ip = pq.pop();
        outFile << ip << " " << ipCount[ip] << endl;
    }

    outFile.close();
}

#endif // BITACORA_PROCESSOR_H
