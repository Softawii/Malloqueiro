#include "Malloqueiro/Malloqueiro.hpp"
#include "Malloqueiro/Gerency/MalloqueiroGerency.hpp"
#include "Malloqueiro/LowLevel/MalloqueiroLowLevel.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <cassert>


int main(int argc, char const *argv[]) {
    
    std::cout << "hello world" << std::endl;
    std::cout << UINT64_MAX << std::endl;

    // int * aa = (int *) Malloqueiro::malloc(-1);
    // MalloqueiroGerency::memoryState();
    // std::cout << *(aa) << std::endl;
    // std::cout << (Malloqueiro::free(aa) ? "sucesso no free": "falha no free") << std::endl;

    // MalloqueiroGerency::memoryState();

    return 0;
}