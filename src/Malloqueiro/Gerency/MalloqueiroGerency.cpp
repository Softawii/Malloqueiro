#include "MalloqueiroGerency.hpp"
#include "../LowLevel/MalloqueiroLowLevel.hpp"
#include <iostream>

namespace MalloqueiroGerency {

    /**
     * @brief Exibe o estado da memória alocada atual
     * 
     * @return Retorna o total de memória alocada
     */
    unsigned long long memoryState(){
        MalloqueiroLowLevel::t_block block = (MalloqueiroLowLevel::t_block) MalloqueiroLowLevel::base;
        if (block == NULL) {
        #ifndef TEST
            std::cout << "Nenhum bloco foi alocado" << std::endl;
        #endif
            return -1;
        }
        
    #ifndef TEST
        std::cout << "Blocos alocados:" << std::endl;
    #endif
        unsigned long long totalAlocado = 0;
        for (size_t i = 0; block != NULL; i++, block = block->next) {
        #ifndef TEST
            std::cout << "Bloco " << i << ": " << block->size << " bytes" << std::endl;
        #endif
            totalAlocado += block->size;
        }
    #ifndef TEST
        std::cout << "Total de memória alocada: " << totalAlocado << " bytes" << std::endl;
    #endif
        return totalAlocado;
    };

}