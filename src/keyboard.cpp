#include <fstream>
#include <string>

#include "io.h"

word keyboard::read() {
    std::ifstream fin("keyboard.io");
    if (!fin) {
        return 0;
    }

    std::string input;
    fin >> input;
    if (input.empty()) {
        return 0;
    }

    try {
        return static_cast<word>(std::stoul(input));
    } catch (...) {
        return 0;
    }
}

