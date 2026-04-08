//
// Created by tris4 on 26/03/2026.
//

#include "string_to_level_converter.h"

Level StringToLevelConverter::convert() {
    int depth = 0;
    bool atValue = false;
    bool atString = false;
    bool inTileLayers = false;
    bool inTileLayer = false;
    std::string currString = "";
    std::string levelName = "";
    std::string description = "";
    std::string beingChecked = "";
    std::pmr::list <TileLayer> tileLayers;
    for (int i = 0; i < this->jsonString.length(); i++) {
        char c = this->jsonString[i];
        if (c == '"') {
            if (atString) {
                if (!inTileLayers) {
                    if (atValue) {
                        if (beingChecked == "levelname") {
                            levelName = currString;
                        } else if (beingChecked == "description") {
                            description = currString;
                        } else if (beingChecked == "tile_layer") {
                            inTileLayers = true;
                        }
                    } else {
                        beingChecked = currString;
                        atValue = true;
                    }
                }
            }
            atString = !atString;
        } else if (atString) {
            currString.push_back(c);
        }
        if (c == '{' || inTileLayers || !inTileLayer) {
            tileLayers.push_back(readTileLayer(currString, i));
        }
    }
    return Level(levelName, description, tileLayers);
}

TileLayer StringToLevelConverter::readTileLayer(std::string tileLayerName, int index) {
    int depth = 0;
    int pointInTile = 0;
    int i = index + 1;
    bool atValue = false;
    bool atString = false;
    bool inTiles = false;
    bool inTile = false;
    bool oneCloseFound = false;
    std::string currString = "";
    std::string resolution = "";
    std::string gridx = "";
    std::string gridy = "";
    std::string parallaxModifier = "";
    std::string beingChecked = "";
    std::pmr::list <std::pmr::list<std::string>> tiles;
    std::pmr::list <std::string> tile;
    char c = '_';
    for (int i = index + 1; i < this->jsonString.length() && c != '}'; i++) {
        c = this->jsonString[i];
        if (c == '"') {
            if (atString) {
                if (inTiles) {
                    tile.push_back(std::string(currString));
                    pointInTile++;
                    if (pointInTile >= 3) {
                        tiles.push_back(tile);
                        tile.clear();
                        pointInTile = 0;
                    }
                } else {
                    if (atValue) {
                        if (beingChecked == "resolution") {
                            resolution = currString;
                        } else if (beingChecked == "gridx") {
                            gridx = currString;
                        } else if (beingChecked == "gridy") {
                            gridy = currString;
                        } else if (beingChecked == "parallax_modifier") {
                            parallaxModifier = currString;
                        } else if (beingChecked == "tiles") {
                            inTiles = true;
                        }
                    } else {
                        beingChecked = currString;
                        atValue = true;
                    }
                }
            }
            atString = !atString;
        }
    }
    return TileLayer(tileLayerName, resolution, gridx, gridy, parallaxModifier, tiles);
}
