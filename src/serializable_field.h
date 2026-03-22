//
// Created by burrito on 22/03/2026.
//

#ifndef JAMEJAM_SERIALIZABLEFIELD_H
#define JAMEJAM_SERIALIZABLEFIELD_H
#include <string>


class SerializableField {
public:

    virtual ~SerializableField();

    virtual std::string toString();

    virtual void parse(std::string);
};


#endif //JAMEJAM_SERIALIZABLEFIELD_H