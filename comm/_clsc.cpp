#include <iostream>
#include "../utils.hpp"

int _clsc() {
    std::cout << "\033[0;40m\033[H\033[J" << std::flush;
    return 0;
}
