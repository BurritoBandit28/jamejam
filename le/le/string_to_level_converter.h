//
// Created by tris4 on 26/03/2026.
//

#ifndef JAMEJAM_STRING_TO_LEVEL_CONVERTER_H
#define JAMEJAM_STRING_TO_LEVEL_CONVERTER_H
#include <string>
#include <list>
#include "tile_layer.h"

class StringToLevelConverter {
    public:
    StringToLevelConverter(std::string jsonString) {
        this->jsonString = jsonString;
        convert();
    };

    private:
    std::string jsonString;
    void convert();
    TileLayer readTileLayer(std::string name, int index);
};


#endif //JAMEJAM_STRING_TO_LEVEL_CONVERTER_H