//
// Created by tris4 on 26/03/2026.
//

#ifndef JAMEJAM_LEVEL_H
#define JAMEJAM_LEVEL_H
#include <list>
#include <string>

#include "tile_layer.h"


class Level {
    public:
        Level(std::string name, std::string description, std::pmr::list <TileLayer> tileLayers) {
            this->name = name;
            this->description = description;
            this->tileLayers = tileLayers;
        };

    private:
        std::string name;
        std::string description;
        std::pmr::list <TileLayer> tileLayers;

};


#endif //JAMEJAM_LEVEL_H