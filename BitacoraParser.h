#ifndef BITACORAPARSER_H
#define BITACORAPARSER_H

#include <string>
#include "Graph.h"

class BitacoraParser {
public:
    // Recibe el nombre del archivo y retorna un grafo construido a partir de la bitacora.
    // Lanza una excepcion en caso de error.
    static Graph parseFile(const std::string& filename);
};

#endif // BITACORAPARSER_H
