#include "Malloqueiro/Malloqueiro.hpp"
#include "Malloqueiro/Management/MalloqueiroManagement.hpp"
#include "Malloqueiro/LowLevel/MalloqueiroLowLevel.hpp"
#include "libs/Clock.hpp"
#include "libs/Color.hpp"
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <string>

/**
 * @brief Compara malloc e malloqueiro e informa o tempo de ambos
 * 
 */
void benchmark_1(size_t step, std::string filepath) {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Benchmark 1: iniciando passo " << step << std::endl;
    std::ofstream result;
    result.open(filepath, std::ios_base::app);

    {
        // Malloqueiro
        result << step << ";";
        Stopwatch tempoMalloqueiro;
        FREQUENCY(tempoMalloqueiro);
        START_STOPWATCH(tempoMalloqueiro);
        int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * step);
        for (size_t i = 0; i < step; i++) {
            inteiros[i] = 7;
        }
        for (size_t i = 0; i < step; i++) {
            assert(inteiros[i] == 7);
        }
        Malloqueiro::free(inteiros);
        STOP_STOPWATCH(tempoMalloqueiro);
        double time_spent = tempoMalloqueiro.mElapsedTime;
        result << std::fixed << std::setprecision(10) << time_spent << ";";
        // GLIBC
        Stopwatch tempoMalloc;
        FREQUENCY(tempoMalloc);
        START_STOPWATCH(tempoMalloc);
        inteiros = (int *) malloc(sizeof(int) * step);
        for (size_t i = 0; i < step; i++) {
            inteiros[i] = 22;
        }
        for (size_t i = 0; i < step; i++) {
            assert(inteiros[i] == 22);
        }
        free(inteiros);
        STOP_STOPWATCH(tempoMalloc);
        time_spent = tempoMalloc.mElapsedTime;
        result << std::fixed << std::setprecision(10) << time_spent << std::endl;
    }

    result.close();
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Benchmark 1: passo " << step << " encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Avalia se ao alocar sem desalocar muitos blocos ocorrerá algum erro
 * 
 */
void benchmark_2() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Benchmark 2: iniciando" << RED << std::endl;
    for (size_t j = 1024; j <= 1024000; j+= 1024) {
        int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * j);
        for (size_t i = 0; i < j; i++) {
            inteiros[i] = 7;
        }
        for (size_t i = 0; i < j; i++) {
            assert(inteiros[i] == 7);
        }
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Benchmark 2: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Tempo de alocação do malloqueiro de 1024 até 1024000 bytes a cada 1024 bytes de forma sequencial
 * 
 */
void benchmark_3() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::ofstream result;
    result.open("./resultados/benchmark_3/resultado.csv", std::ios_base::app);
    std::cout << "Benchmark 3: iniciando" << RED << std::endl;
    for (size_t j = 1024; j <= 1024000; j+= 1024) {
        int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * j);
        for (size_t i = 0; i < j; i++) {
            inteiros[i] = 21;
        }
        for (size_t i = 0; i < j; i++) {
            assert(inteiros[i] == 21);
        }
        Malloqueiro::free(inteiros);
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    result << std::fixed << std::setprecision(10) << time_spent << std::endl;
    result.close();
    std::cout << GREEN << "Benchmark 3: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Tempo de alocação do malloqueiro de 1024 até 1024000 bytes a cada 1024 bytes de forma paralela
 * 
 */
void benchmark_4() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::ofstream result;
    result.open("./resultados/benchmark_4/resultado.csv", std::ios_base::app);
    std::cout << "Benchmark 4: iniciando" << RED << std::endl;
    #pragma omp parallel for 
    for (size_t j = 1024; j <= 1024000; j+= 1024) {
        int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * j);
        for (size_t i = 0; i < j; i++) {
            inteiros[i] = 21;
        }
        for (size_t i = 0; i < j; i++) {
            assert(inteiros[i] == 21);
        }
        Malloqueiro::free(inteiros);
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    result << std::fixed << std::setprecision(10) << time_spent << std::endl;
    result.close();
    std::cout << GREEN << "Benchmark 4: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Tempo de alocação do malloc do glibc de 1024 até 1024000 bytes a cada 1024 bytes de forma paralela
 * 
 */
void benchmark_5() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::ofstream result;
    result.open("./resultados/benchmark_5/resultado.csv", std::ios_base::app);
    std::cout << "Benchmark 5: iniciando" << RED << std::endl;
    #pragma omp parallel for 
    for (size_t j = 1024; j <= 1024000; j+= 1024) {
        int *inteiros = (int *) malloc(sizeof(int) * j);
        for (size_t i = 0; i < j; i++) {
            inteiros[i] = 77;
        }
        for (size_t i = 0; i < j; i++) {
            assert(inteiros[i] == 77);
        }
        free(inteiros);
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    result << std::fixed << std::setprecision(10) << time_spent << std::endl;
    result.close();
    std::cout << GREEN << "Benchmark 5: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

/**
 * @brief Tempo de alocação do malloc do glibc de 1024 até 1024000 bytes a cada 1024 bytes de forma sequencial
 * 
 */
void benchmark_6() {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::ofstream result;
    result.open("./resultados/benchmark_6/resultado.csv", std::ios_base::app);
    std::cout << "Benchmark 6: iniciando" << RED << std::endl;
    for (size_t j = 1024; j <= 1024000; j+= 1024) {
        int *inteiros = (int *) malloc(sizeof(int) * j);
        for (size_t i = 0; i < j; i++) {
            inteiros[i] = 77;
        }
        for (size_t i = 0; i < j; i++) {
            assert(inteiros[i] == 77);
        }
        free(inteiros);
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    result << std::fixed << std::setprecision(10) << time_spent << std::endl;
    result.close();
    std::cout << GREEN << "Benchmark 6: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

int main(int argc, char const *argv[]) {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    if (std::atoi(argv[1]) == 1) {
        std::string filepath = "./resultados/benchmark_1/result_" + std::string(argv[3]) + ".csv";
        benchmark_1(std::atoi(argv[2]), filepath);
    } else if (std::atoi(argv[1]) == 2) {
        benchmark_2();
    } else if (std::atoi(argv[1]) == 3) {
        benchmark_3();
        benchmark_4();
        benchmark_5();
        benchmark_6();
    } else {
        exit(-2);
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << YELLOW << "Tempo total dos benchmarks: " << time_spent << "ms" << COLOR_RESET << std::endl;
    return 0;
}
