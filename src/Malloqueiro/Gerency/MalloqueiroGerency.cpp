#include "MalloqueiroGerency.hpp"
#include "../LowLevel/MalloqueiroLowLevel.hpp"
#include <iostream>

namespace MalloqueiroGerency {

    unsigned long long memoryState(){
        MalloqueiroLowLevel::t_block block = (MalloqueiroLowLevel::t_block) MalloqueiroLowLevel::base;
        if (block == NULL) {
            std::cout << "Nenhum bloco foi alocado" << std::endl;
            return -1;
        }
        
        std::cout << "Blocos alocados:" << std::endl;
        unsigned long long totalAlocado = 0;
        for (size_t i = 0; block != NULL; i++, block = block->next) {
            std::cout << "Bloco " << i << ": " << block->size << " bytes" << std::endl;
            totalAlocado += block->size;
        }
        std::cout << "Total de memória alocada: " << totalAlocado << " bytes" << std::endl;
        return totalAlocado;
    };

}