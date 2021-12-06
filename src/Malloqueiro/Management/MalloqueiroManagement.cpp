#include "MalloqueiroManagement.hpp"
#include "../LowLevel/MalloqueiroLowLevel.hpp"
#include <iostream>

namespace MalloqueiroManagement {

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

    /**
     * @brief Exibe o estado dos blocos (se está livre e o seu tamanho)
     * 
     * @return Retorna o total de blocos livres
     */
    unsigned long long freeBlocks(){
        MalloqueiroLowLevel::t_block block = (MalloqueiroLowLevel::t_block) MalloqueiroLowLevel::base;
        if (block == NULL) {
        #ifndef TEST
            std::cout << "Nenhum bloco foi alocado" << std::endl;
        #endif
            return -1;
        }
        
    #ifndef TEST
        std::cout << "Blocos livres:" << std::endl;
    #endif
        unsigned long long totalBlocosLivres = 0;
        for (size_t i = 0; block != NULL; i++, block = block->next) {
        #ifndef TEST
            std::cout << "Bloco " << i << ": está livre?" << (block->free ? "Sim":"Não") << ". Tamanho: " << block->size << " bytes" << std::endl;
        #endif
            totalBlocosLivres += block->size;
        }
    #ifndef TEST
        std::cout << "Total de blocos livres: " << totalBlocosLivres << " bytes" << std::endl;
    #endif
        return totalBlocosLivres;
    };

}