#include <iostream>
#include "Malloqueiro/Malloqueiro.h"
#include "Malloqueiro/Gerency/MalloqueiroGerency.h"

int main(int argc, char const *argv[]) {
    
    std::cout << "hello world" << std::endl;
    Apenas::Malloqueiro::init(10);
    Apenas::Malloqueiro::malloc(20);
    Apenas::Malloqueiro::free(NULL);
    Apenas::MalloqueiroGerency::memoryState();

    return 0;
}
