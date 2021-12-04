#include "Malloqueiro/Malloqueiro.hpp"
#include "Malloqueiro/Gerency/MalloqueiroGerency.hpp"
#include "Malloqueiro/LowLevel/MalloqueiroLowLevel.hpp"
#include "libs/Clock.hpp"
#include "libs/Color.hpp"
#include <cassert>
#include <unistd.h>
#include <iostream>

/**
 * @brief Teste que verifica se os valores não foram alterados no processo
 * 
 */
void test_1() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Teste 1: iniciando" << RED << std::endl;
    const size_t n = 1000;
    int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; i++) {
        inteiros[i] = 10;
    }

    float *floats = (float *) Malloqueiro::malloc(sizeof(float) * n);
    for (size_t i = 0; i < n; i++) {
        floats[i] = 5.5;
    }

    for (size_t i = 0; i < n; i++) {
        assert(inteiros[i] == 10);
        assert(floats[i] == 5.5);
    }

    constexpr size_t size = sizeof(int) * n + sizeof(float) * n;
    assert(MalloqueiroGerency::memoryState() == size);
    assert(Malloqueiro::free(inteiros) == true);
    assert(Malloqueiro::free(floats) == true);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << COLOR_RESET;
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Teste 1: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Teste que aloca uma matriz n X m e verifica se os valores não foram alterados no processo
 * 
 */
void test_2() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Teste 2: iniciando" << RED << std::endl;
    const size_t n = 100;
    const size_t m = 50;
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
    
    constexpr size_t size = (sizeof(int*) * n) + (sizeof(int) * n * m);
    assert(MalloqueiroGerency::memoryState() == size);
    for (size_t i = 0; i < n; i++) {
        assert(Malloqueiro::free(inteiros[i]) == true);
    }
    std::cout << RED;
    assert(Malloqueiro::free(inteiros) == true);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << COLOR_RESET;
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Teste 2: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Teste que aloca uma matriz n X m X p e verifica se os valores não foram alterados no processo
 * 
 */
void test_3() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Teste 3: iniciando" << RED << std::endl;
    const size_t n = 100;
    const size_t m = 5;
    const size_t p = 99;
    int ***inteiros = (int ***) Malloqueiro::malloc(sizeof(int**) * n);
    for (size_t i = 0; i < n; i++) {
        inteiros[i] = (int **) Malloqueiro::malloc(sizeof(int*) * m);
        for (size_t j = 0; j < m; j++) {
            inteiros[i][j] = (int *) Malloqueiro::malloc(sizeof(int) * p);
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            for (size_t k = 0; k < p; k++) {
                inteiros[i][j][k] = 13;
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            for (size_t k = 0; k < p; k++) {
                assert(inteiros[i][j][k] == 13);
            }
        }
    }
    
    constexpr size_t size = (sizeof(int**) * n) + (sizeof(int*) * n * m) + (sizeof(int) * n * m * p);
    assert(MalloqueiroGerency::memoryState() == size);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            assert(Malloqueiro::free(inteiros[i][j]) == true);
        }
        assert(Malloqueiro::free(inteiros[i]) == true);
    }
    
    assert(Malloqueiro::free(inteiros) == true);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << COLOR_RESET;
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Teste 3: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Teste que aloca uma matriz n X m X p vetorizada e verifica se os valores não foram alterados no processo
 * 
 */
void test_4() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Teste 4: iniciando" << RED <<std::endl;
    const size_t n = 5;
    const size_t m = 5;
    const size_t p = 5;
    int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * n * m * p);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            for (size_t k = 0; k < p; k++) {
                size_t indice = k*n*2*2 + j*n + i;
                inteiros[indice] = 71;
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            for (size_t k = 0; k < p; k++) {
                size_t indice = k*n*2*2 + j*n + i;
                assert(inteiros[indice] == 71);
            }
        }
    }
    
    constexpr size_t size = (sizeof(int) * n * m * p);
    assert(MalloqueiroGerency::memoryState() == size);
    assert(Malloqueiro::free(inteiros) == true);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << COLOR_RESET;
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Teste 4: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Teste que verifica se o ponteiro da heap é o mesmo apos desalocar tudo
 * 
 */
void test_5() {
    void *init_ptr = sbrk(0);
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Teste 5: iniciando" << RED << std::endl;
    const size_t n = 1000;
    int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * n);
    for (size_t i = 0; i < n; i++) {
        inteiros[i] = 10;
    }

    float *floats = (float *) Malloqueiro::malloc(sizeof(float) * n);
    for (size_t i = 0; i < n; i++) {
        floats[i] = 5.5;
    }

    for (size_t i = 0; i < n; i++) {
        assert(inteiros[i] == 10);
        assert(floats[i] == 5.5);
    }

    constexpr size_t size = sizeof(int) * n + sizeof(float) * n;
    assert(MalloqueiroGerency::memoryState() == size);
    void *mid_ptr = sbrk(0);
    assert(init_ptr != mid_ptr && init_ptr < mid_ptr);
    assert(Malloqueiro::free(inteiros) == true);
    assert(Malloqueiro::free(floats) == true);
    void *end_ptr = sbrk(0);
    assert(init_ptr == end_ptr);
    assert(MalloqueiroGerency::memoryState() == -1llu);
    std::cout << COLOR_RESET;
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Teste 5: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

int main(int argc, char const *argv[]) {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << YELLOW << "Tempo total dos testes: " << time_spent << "ms" << COLOR_RESET << std::endl;
    return 0;
}
