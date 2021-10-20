#include <iostream>
#include "Malloqueiro/Malloqueiro.h"
#include "Malloqueiro/Gerency/MalloqueiroGerency.h"

int main(int argc, char const *argv[]) {
    
    std::cout << "hello world" << std::endl;
    Malloqueiro::init(10);
    Malloqueiro::malloc(20);
    Malloqueiro::free(NULL);
    MalloqueiroGerency::memoryState();

    return 0;
}
