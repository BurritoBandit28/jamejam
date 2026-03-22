//
// Created by burrito on 22/03/2026.
//

#include "resource_location.h"

#include "util.h"

ResourceLocation ResourceLocation::empty() {
    return {"none","none"};
}

void ResourceLocation::setNamespace(std::string nameSpace) {
    this->nameSpace = std::move(nameSpace);
}

void ResourceLocation::setPath(std::string path) {
    this->path = std::move(path);
}

std::string ResourceLocation::toString() {
    return this->nameSpace + ":" + this->path;
}

void ResourceLocation::parse(std::string value) {
    std::vector<std::string> values = split(value, ":");
    this->setNamespace(values[0]);
    this->setPath(values[1]);
}
