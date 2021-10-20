#include "Malloqueiro.h"
#include <iostream>

namespace Apenas {

    int Malloqueiro::init(int size) {
        std::cout << "Initialized " << size << " bytes" << std::endl;
    }

    void* Malloqueiro::malloc(int size) {
        std::cout << "Allocated " << size << " bytes" << std::endl;
    }

    int Malloqueiro::free(void *ptr) {
        std::cout << "Memory released " << std::endl;
    }

}