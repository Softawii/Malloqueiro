#include "Malloqueiro/Malloqueiro.h"
#include "Malloqueiro/Gerency/MalloqueiroGerency.h"
#include "Malloqueiro/LowLevel/MalloqueiroLowLevel.h"
#include <cassert>
#include <unistd.h>
#include <iostream>

/*
Teste que verifica se os valores não foram alterados no processo
*/
void test_1() {
    std::cout << "Teste 1: iniciando" << std::endl;
    size_t size = 1000;
    int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        inteiros[i] = 10;
    }

    float *floats = (float *) Malloqueiro::malloc(sizeof(float) * size);
    for (size_t i = 0; i < size; i++) {
        floats[i] = 5.5;
    }

    for (size_t i = 0; i < size; i++) {
        assert(inteiros[i] == 10);
        assert(floats[i] == 5.5);
    }

    assert(MalloqueiroGerency::memoryState() == sizeof(int) * size + sizeof(float) * size);
    assert(Malloqueiro::free(inteiros) == true);
    assert(Malloqueiro::free(floats) == true);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << "Teste 1: encerrado sem falhas" << std::endl;
}

int main(int argc, char const *argv[]) {
    test_1();
    return 0;
}
