#include "MalloqueiroLowLevel.hpp"
#include <iostream>

namespace MalloqueiroLowLevel {
    void *base = NULL;
    
    /*
    Divide o bloco 'b' baseado em size.
    Cria um bloco 'newBlock' com (tamanho_de_b - size - BLOCK_SIZE),
    O bloco 'b' fica com tamanho size.
    */
    void splitBlock(t_block b, size_t size) {
        t_block newBlock;
        newBlock = (t_block) (b->data + size);
        newBlock->size = b->size - size - BLOCK_SIZE;
        newBlock->next = b->next;
        newBlock->prev = b;
        newBlock->free = true;
        newBlock->ptr = newBlock->data;
        b->size = size;
        b->next = newBlock;
        if (newBlock->next) {
            newBlock->next->prev = newBlock;
        }
    }

    /*
    Extende a heap com um bloco de tamanho size.
    Se houve sucesso, retorna um ponteiro válido.
    Caso contrário, retorna NULL.
    */
    t_block extendHeap(t_block last, size_t size) {
        t_block newBlock = (t_block) sbrk(0);
        if (sbrk(BLOCK_SIZE + size) == (void *) -1) {
            return NULL;
        }
        newBlock->size = size;
        newBlock->next = NULL;
        newBlock->prev = last;
        newBlock->ptr = newBlock->data;
        if (last) {
            last->next = newBlock;
        }
        newBlock->free = false;
        return newBlock;
    }

    /*
    Retorna um bloco que tenha tamanho suficiente para caber um bloco de tamanho size.
    */
    t_block findFittingBlock(t_block *last, size_t size){
        t_block b = (t_block) base;
        while (b && !(b->free && b->size >= size)) {
            *last = b;
            b = b->next;
        }
        return b;
    }

    /* Aloca um ponteiro de tamanho size */
    void *malloc(size_t size){
        t_block b;
        if (base) {
            /* First find a block */
            t_block last = (t_block) base;
            b = findFittingBlock(&last, size); // tenta encontrar um bloco livre com tamanho >= size
            if (b) {
                /* se for possível dividir esse bloco */
                if ((b->size - size) >= (BLOCK_SIZE)) { // (BLOCK_SIZE + 4) == bloco simples com header + 4 bytes
                    splitBlock(b, size);
                }
                b->free = false;
            } else {
                /* No fitting block, extend the heap */
                b = extendHeap(last, size);
                if (!b) {
                    return NULL;
                }
            }
        } else {
            /* first time */
            b = extendHeap(NULL, size);
            if (!b) {
                return NULL;
            }
            base = b;
        }
        return b->data;
    }

    /* Une o bloco 'b' com o próximo bloco, se o próximo estiver livre. */
    t_block fusion(t_block b){
        if (b->next && b->next->free){
            b->size += BLOCK_SIZE + b->next->size;
            b->next = b->next->next;
            if (b->next) {
                b->next->prev = b;
            }
        }
        return b;
    }

    /* Obtém o bloco do endereço */
    t_block getBlock(void *p){
        char *tmp = (char*) p;
        return (t_block) (p = tmp - BLOCK_SIZE);
    }

    /* Verifica se ponteiro é um endereço válido */
    bool isValidAddress(void *ptr) {
        if (base) {
            if (ptr > base && ptr < sbrk (0)) {
                return ptr == (getBlock(ptr)->ptr);
            }
        }
        return false;
    }

    /* Desaloca memória do ponteiro */
    bool free(void *p) {
        if (isValidAddress(p)) {
            t_block b = getBlock(p);
            b->free = true;

            /* tenta fundir com o anterior */
            if(b->prev && b->prev->free) {
                b = fusion(b->prev);
            }
            /* tenta fundir com o próximo, se ele existir */
            if (b->next) {
                fusion(b);
            } else { // se for o ultimo da heap
                /* libera/troca o fim da heap */
                if (b->prev) {
                    b->prev->next = NULL;
                } else {
                    /* não tem mais bloco/era o ultimo da heap */
                    base = NULL;
                }
                if (brk(b) == -1) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
}