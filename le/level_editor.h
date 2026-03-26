//
// Created by tris4 on 23/03/2026.
//

#ifndef JAMEJAM_LEVELEDITOR_H
#define JAMEJAM_LEVELEDITOR_H
#include <fstream>
#include <iostream>
#include <string>

class LevelEditor {
    private:
        std::string filename;
        std::string lines;

        void constructLines();

    public:
        LevelEditor(std::string filename) {
            this->filename = filename;
            this->constructLines();
    }

    std::string getFilename();

    void setFilename(std::string filename);

    std::string getLines();

    void setLines(std::string lines);

    void refresh();
};


#endif //JAMEJAM_LEVELEDITOR_H