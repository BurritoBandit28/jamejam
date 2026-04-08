//
// Created by tris4 on 26/03/2026.
//

#ifndef JAMEJAM_TILE_LAYER_H
#define JAMEJAM_TILE_LAYER_H
#include <list>
#include <string>


class TileLayer {
    public:
        TileLayer(std::string tileLayerName, std::string resolution, std::string gridx, std::string gridy, std::string parallax_modifier, std::pmr::list <std::pmr::list <std::string>> tiles) {
            this->tileLayerName = tileLayerName;
            this->resolution = resolution;
            this->gridx = gridx;
            this->gridy = gridy;
            this->parallax_modifier = parallax_modifier;
            this->tiles = tiles;
        }

    private:
        std::string tileLayerName;
        std::string resolution;
        std::string gridx;
        std::string gridy;
        std::string parallax_modifier;
        std::pmr::list <std::pmr::list <std::string>> tiles;
};


#endif //JAMEJAM_TILE_LAYER_H