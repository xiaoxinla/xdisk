#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../dbUtils.h"
#include "../utils.h"

int main() {
    FILE *file = fopen("header.txt", "r");
    char buf[2048];
    fread(buf, 1, 2048, file);
    printf("content:%s\n", buf);
    const char *keystr[] = {"file_id", "file_path", "file_size", "file_md5", "chunks", "chunkcnt"};
    vector<string> keys(keystr, keystr+6);
    map<string, string> mmap = getFormData(buf, keys);
    string chunkid = addChunk(atoi(mmap["file_size"].c_str()), mmap["file_path"].c_str(), mmap["file_md5"].c_str());
    printf("chunkid:%s\n", chunkid.c_str());
    int rst = addChunkToFile(chunkid, mmap["file_id"], atoi(mmap["chunkcnt"].c_str()), atoi(mmap["chunks"].c_str()));
    printf("rst:%d\n",rst);
}
