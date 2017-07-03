
#include <fcgi_stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../dbUtils.h"
#include "../utils.h"

#define BUF_SIZE 1024*1024


int main() {
    while(FCGI_Accept()>=0) {
        char* queryStr = getenv("QUERY_STRING");
        const char *keys[] = {"token"};
        map<string, string> mmap = getQueryInfo(queryStr, keys, 1);
        int keyint = time(NULL) / ONE_DAY;
        char key[24];
        sprintf(key, "%s%d", PROJECT_NAME, keyint);
        string decrypted = decryptWithAES(mmap["token"].c_str(), key);
        if(decrypted.empty()){
            sprintf(key, "%s%d", PROJECT_NAME, keyint-1);
            decrypted = decryptWithAES(mmap["token"].c_str(), key);
            if(decrypted.empty()) {
                printf("Content-type: text/html\r\n\r\n<h2>The Link is Invalid!</h2>");
                continue;
            }
        }
        vector<Chunk> res = getFileChunks(decrypted);
        string filename = getFilenameById(decrypted);
        printf("Content-type: application/octet-stream\r\nContent-Disposition :attachment; filename=%s\r\n\r\n", filename.c_str());
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
