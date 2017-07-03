#ifndef CHUNK_H
#define CHUNK_H
#include <string>
struct Chunk{
    int chunkcnt;
    long size;
    std::string chunkid;
    std::string path;
};

bool chunkcmp(Chunk c1, Chunk c2) ;

#endif
