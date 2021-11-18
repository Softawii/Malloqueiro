#include "Malloqueiro.hpp"
#include "LowLevel/MalloqueiroLowLevel.hpp"
#include <cassert>
#include <unistd.h>
#include <mutex>

std::mutex mtx;

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
        mtx.lock();
        void *ptr = MalloqueiroLowLevel::malloc(size);
        mtx.unlock();
        return ptr;
    }

    /*
    Libera espaço de memória alocado pelo ponteiro.
    Retorna true se houve sucesso e false se ocorreu alguma falha.
    */
    bool free(void *ptr) {
        mtx.lock();
        bool success = MalloqueiroLowLevel::free(ptr);
        mtx.unlock();
        return success;
    }

}