#include "Chunk.h"

bool chunkcmp(Chunk c1, Chunk c2) {
    return c1.chunkcnt < c2.chunkcnt;
}
