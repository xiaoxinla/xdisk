#include <fcgi_stdio.h>
#include <stdlib.h>
#include "../dbUtils.h"
#include "../utils.h"

#define BUF_SIZE 1024*1024


int main() {
    while(FCGI_Accept()>=0) {
        char* queryStr = getenv("QUERY_STRING");
        const char *keys[] = {"file_id", "filename"};
        map<string, string> mmap = getQueryInfo(queryStr, keys, 2);
        vector<Chunk> res = getFileChunks(mmap["file_id"]);
        printf("Content-type: application/octet-stream\r\nContent-Disposition :attachment; filename=%s\r\n\r\n",mmap["filename"].c_str());
        char buf[BUF_SIZE];
        int total = 0;
        for(int i=0; i<res.size(); i++) {
            FILE *file = fopen(res[i].path.c_str(), "r");
            int len = 0;
            while((len=fread(buf, sizeof(char), BUF_SIZE, file))>0) {
                //printf(buf);
                fwrite(buf, sizeof(char), len, stdout);
                total+=len;
            }
            fclose(file);
        }
    }
}
