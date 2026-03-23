#include <iostream>
#include "resource_location.h"

int main() {
    ResourceLocation rl1 = ResourceLocation("game", "test");
    ResourceLocation rl2 = ResourceLocation::empty();
    rl2.parse("game2:test");

    std::cout << rl1.toString() << " " << rl2.toString() << std::endl;

    return 0;
}
