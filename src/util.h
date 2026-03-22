//
// Created by burrito on 22/03/2026.
//

#ifndef JAMEJAM_UTIL_H
#define JAMEJAM_UTIL_H
#include <string>
#include <vector>

std::vector<std::string> split(std::string value, std::string delimiter) {
    return {value.substr(0,value.find(delimiter)),value.substr(value.find(delimiter)+1,value.length()-1)};
}

#endif //JAMEJAM_UTIL_H