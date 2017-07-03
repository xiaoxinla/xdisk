#include <fcgi_stdio.h>
#include <stdlib.h>
#include "../dbUtils.h"
#include "../utils.h"

int main() {
    while(FCGI_Accept()>=0) {
        int len = atoi(getenv("CONTENT_LENGTH"));
        char content[1024];
        fread(content, sizeof(char), len, stdin);
        char * queryStr = getenv("QUERY_STRING");
        content[len] = '\0';
        const char *keys[] = {"md5", "file_id", "chunks", "chunkcnt"};
        map<string, string> mmap = getQueryInfo(queryStr, keys, 4);
        string chunkid = isExistChunk(mmap["md5"].c_str());
        if(chunkid.empty()) {
            printf("Content-type: text/plain\r\n\r\n{\"isExist\":0, \"status\":1}");
        }else {
            addChunkToFile(chunkid, mmap["file_id"], atoi(mmap["chunkcnt"].c_str()), atoi(mmap["chunks"].c_str()));
            printf("Content-type: text/plain\r\n\r\n{\"isExist\":1, \"status\":1, \"chunkid\":\"%s\"}", chunkid.c_str());
        }
    }
}
