#include <stdlib.h>
#include <string.h>
#include "../utils.h"
#include "../dbUtils.h"
#include <fcgi_stdio.h>

int main() {
    int cnt = 0;
    while(FCGI_Accept()>=0) {
        if(strcmp("POST", getenv("REQUEST_METHOD"))==0) {
            char buf[2048];
            int len = 0;
            int total = 0;
            while((len=fread(buf, sizeof(char), sizeof(buf), stdin))>0) {
                total+=len;
            }
            buf[total]='\0';
            FILE *file = fopen("header.txt", "w");
            fwrite(buf, 1, total, file);
            fclose(file);
            const char *keystr[] = {"file_id", "file_path", "file_size", "file_md5", "chunks", "chunkcnt"};
            vector<string> keys(keystr, keystr+6);
            map<string, string> mmap = getFormData(buf, keys);
            char retstr[1024];
            string chunkid = addChunk(atoi(mmap["file_size"].c_str()), mmap["file_path"].c_str(), mmap["file_md5"].c_str());
            char str[1024];
            sprintf(str, "chunkid:%s\n", chunkid.c_str());
            int rst = addChunkToFile(chunkid, mmap["file_id"], atoi(mmap["chunkcnt"].c_str()), atoi(mmap["chunks"].c_str()));
            sprintf(retstr, "{\"file_md5\" : \"%s\", \"file_id\" : \"%s\", \"file_path\":\"%s\", \"size\":%s, \"chunkid\":%s, \"rst\":%d}",
                    mmap["file_md5"].c_str(), mmap["file_id"].c_str(), mmap["file_path"].c_str(),mmap["total_size"].c_str(), chunkid.c_str(),rst);
            printf("Content-type:text/plain\r\n\r\n%s", retstr);
        }
    }
}
