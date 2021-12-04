#pragma once
#include <unistd.h>

namespace MalloqueiroLowLevel {
    
    struct s_block {
        size_t size;
        struct s_block *next;
        struct s_block *prev;
        void *ptr;
        bool free;
        char data[1]; // Determina final do header e inicio do ponteiro
    } __attribute__((packed)); // Remove alinhamento de memória feito pelo compilador
    
    #define BLOCK_SIZE (sizeof(s_block) - 1) // sizeof(s_block) - 1 do char data[1]

    typedef struct s_block *t_block;
    
    extern void *base;
    
    void splitBlock(t_block, size_t);
    t_block extendHeap(t_block, size_t);
    t_block findFittingBlock(t_block, size_t);
    void *malloc(size_t);
    t_block fusion(t_block);
    t_block getBlock(void*);
    bool isValidAddress(void*);
    bool free(void*);
}