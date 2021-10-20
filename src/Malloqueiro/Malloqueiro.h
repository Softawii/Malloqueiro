#pragma once

namespace Apenas {
    class Malloqueiro {
        public:
            static int init(int size);
            static void* malloc(int size);
            static int free(void *ptr);
    };
}