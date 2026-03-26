//
// Created by tris4 on 23/03/2026.
//

#include "level_editor.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

std::string LevelEditor::getFilename() {
    return this->filename;
}

void LevelEditor::constructLines() {
    std::ifstream file(this->filename);
    //std::ifstream file(R"(C:\Users\tris4\OneDrive\Documents\2. springgamejam\clones\jamejam-master\src\level.json)");
    //std::ifstream file("level.json");
    //file.open("level.json");

    if (!file.is_open()) {
        std::cout << "file is not open" << std::endl;
    }

    std::string line;
    std::string lines;

    while (getline(file, line)) {
        //std::cout << line << std::endl;
        lines.append(line);
        lines.append("\n");
    }
    this->lines = lines;
    file.close();
}

void LevelEditor::setFilename(std::string filename) {
    this->filename = filename;
    this->constructLines();
}

std::string LevelEditor::getLines() {
    return this->lines;
}

void LevelEditor::refresh() {
    this->constructLines();
}
