#include "Malloqueiro/Malloqueiro.h"
#include "Malloqueiro/Gerency/MalloqueiroGerency.h"
#include "Malloqueiro/LowLevel/MalloqueiroLowLevel.h"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <cassert>


int main(int argc, char const *argv[]) {
    
    std::cout << "hello world" << std::endl;
    // Malloqueiro::init(10);
    int * aa = (int *) Malloqueiro::malloc(4);
    (*aa) = 10;
    MalloqueiroGerency::memoryState();
    std::cout << *(aa) << std::endl;
    std::cout << Malloqueiro::free(aa) << std::endl;
    std::cout << *(aa) << std::endl;
    MalloqueiroGerency::memoryState();

    return 0;
}
