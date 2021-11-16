#include "Malloqueiro/Malloqueiro.hpp"
#include "Malloqueiro/Gerency/MalloqueiroGerency.hpp"
#include "Malloqueiro/LowLevel/MalloqueiroLowLevel.hpp"
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

/*
Teste que aloca uma matriz n X m e verifica se os valores não foram alterados no processo
*/
void test_2() {
    std::cout << "Teste 2: iniciando" << std::endl;
    size_t n = 5;
    size_t m = 5;
    int **inteiros = (int **) Malloqueiro::malloc(sizeof(int*) * n);
    for (size_t i = 0; i < n; i++) {
        inteiros[i] = (int *) Malloqueiro::malloc(sizeof(int) * m);
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            inteiros[i][j] = 99;
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            assert(inteiros[i][j] == 99);
        }
    }
    
    assert(MalloqueiroGerency::memoryState() == (sizeof(int*) * n) + (sizeof(int) * n * m));
    for (size_t i = 0; i < n; i++) {
        assert(Malloqueiro::free(inteiros[i]) == true);
    }
    assert(Malloqueiro::free(inteiros) == true);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << "Teste 2: encerrado sem falhas" << std::endl;
}

int main(int argc, char const *argv[]) {
    test_1();
    test_2();
    return 0;
}
