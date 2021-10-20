#pragma once

namespace Malloqueiro {
    int init(int size);
    void* malloc(int size);
    int free(void *ptr);
}