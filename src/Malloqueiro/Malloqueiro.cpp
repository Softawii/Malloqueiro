#include "Malloqueiro.h"
#include <iostream>

namespace Malloqueiro {

    int init(int size) {
        std::cout << "Initialized " << size << " bytes" << std::endl;

        return -1;
    }

    void* malloc(int size) {
        std::cout << "Allocated " << size << " bytes" << std::endl;

        return NULL;
    }

    int free(void *ptr) {
        std::cout << "Memory released " << std::endl;

        return -1;
    }

}