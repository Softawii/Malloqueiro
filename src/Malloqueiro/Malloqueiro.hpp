#pragma once
#include <cstddef>

namespace Malloqueiro {
    int init(size_t size);
    void* malloc(size_t size);
    bool free(void *ptr);
}