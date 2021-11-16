#pragma once
#include <unistd.h>

namespace MalloqueiroLowLevel {
    
    struct s_block {
        size_t size; // 8 bytes?
        struct s_block *next; // 8 bytes?
        struct s_block *prev; // 8 bytes?
        void *ptr; // 8 bytes?
        bool free; // 1
        /* A pointer to the allocated block */
        char data[1]; // 1 byte, mas ignorado. Determina final do header e inicio do ponteiro
    } __attribute__((packed));
    
    
    #define BLOCK_SIZE 33 // 34 - 1 do char data[1]

    typedef struct s_block *t_block;
    
    extern void *base;
    
    void splitBlock(t_block, size_t);
    t_block extendHeap(t_block, size_t);
    t_block findFittingBlock(t_block, size_t);
    void *malloc(size_t);
    t_block fusion(t_block);
    t_block getBlock(void);
    int isValidAddress(void);
    bool free(void*);
}