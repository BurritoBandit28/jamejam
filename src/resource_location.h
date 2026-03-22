//
// Created by burrito on 22/03/2026.
//

#ifndef JAMEJAM_RESOURCE_LOCATION_H
#define JAMEJAM_RESOURCE_LOCATION_H
#include <string>
#include <utility>

#include "serializable_field.h"

class ResourceLocation : public SerializableField {

public:

    ResourceLocation(std::string nameSpace, std::string path) {
        this->nameSpace = std::move(nameSpace);
        this->path = std::move(path);
    }


    static ResourceLocation empty();

    void setNamespace(std::string nameSpace);

    void setPath(std::string path);

    std::string toString() override;

    void parse(std::string value) override;

private:
    std::string nameSpace;
    std::string path;
};

#endif //JAMEJAM_RESOURCE_LOCATION_H