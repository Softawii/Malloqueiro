#include "Malloqueiro.h"
#include "LowLevel/MalloqueiroLowLevel.h"
#include <cassert>
#include <unistd.h>

namespace Malloqueiro {

    int init(size_t size) {
        assert(false && "init(int size) is not implemented");
        return -1;
    }
    /*
    Dado o tamanho da memória solicitada pelo processo do usuário.
    Retorna um ponteiro de tamanho size.        
    */
    void* malloc(size_t size) {
        return MalloqueiroLowLevel::malloc(size);
    }

    /*
    Libera espaço de memória alocado pelo ponteiro.
    Retorna true se houve sucesso e false se ocorreu alguma falha.
    */
    bool free(void *ptr) {
        return MalloqueiroLowLevel::free(ptr);
    }

}