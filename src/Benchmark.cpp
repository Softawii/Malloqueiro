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
void benchmark_1(int step) {
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    std::cout << "Benchmark 1: iniciando passo " << step << std::endl;
    std::ofstream result;
    std::string path = "./resultados/result_" + std::to_string(step) + ".csv";
    result.open(path);

    result << "tamanho;tempo_malloqueiro;tempo_malloc" << std::endl;

    for (size_t j = 1024; j <= 1024000; j+= 1024) {
        // Malloqueiro
        result << j << ";";
        Stopwatch tempoMalloqueiro;
        FREQUENCY(tempoMalloqueiro);
        START_STOPWATCH(tempoMalloqueiro);
        int *inteiros = (int *) Malloqueiro::malloc(sizeof(int) * j);
        for (size_t i = 1; i < j; i++) {
            inteiros[i] = 7;
        }
        for (size_t i = 1; i < j; i++) {
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
        inteiros = (int *) malloc(sizeof(int) * j);
        for (size_t i = 1; i < j; i++) {
            inteiros[i] = 22;
        }
        for (size_t i = 1; i < j; i++) {
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
        for (size_t i = 1; i < j; i++) {
            inteiros[i] = 7;
        }
        for (size_t i = 1; i < j; i++) {
            assert(inteiros[i] == 7);
        }
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << GREEN << "Benchmark 2: encerrado sem falhas. Tempo gasto: " << time_spent << "ms" << COLOR_RESET << std::endl;
}

int main(int argc, char const *argv[]) {
    Stopwatch stopwatch;
    if (argc < 2) {
        exit(-1);
    }
    FREQUENCY(stopwatch);
    START_STOPWATCH(stopwatch);
    if (std::atoi(argv[1]) == 1) {
        benchmark_1(std::atoi(argv[2]));
    } else if (std::atoi(argv[1]) == 2) {
        benchmark_2();
    } else {
        exit(-2);
    }
    STOP_STOPWATCH(stopwatch);
    double time_spent = stopwatch.mElapsedTime;
    std::cout << YELLOW << "Tempo total dos benchmarks: " << time_spent << "ms" << COLOR_RESET << std::endl;
    return 0;
}
