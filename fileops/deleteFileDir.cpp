#include <fcgi_stdio.h>
#include <stdlib.h>
#include "../dbUtils.h"
#include "../utils.h"

int main() {
    while(FCGI_Accept()>=0) {
        int len = atoi(getenv("CONTENT_LENGTH"));
        char content[1024];
        fread(content, sizeof(char), len, stdin);
        content[len] = '\0';
        FILE *file = fopen("run.log", "w");
        fwrite(content, 1, strlen(content), file);
        fclose(file);
        const char *keys[] = {"is_dir", "id", "dir_id"};
        map<string, string> mmap = getQueryInfo(content, keys, 3);
        int r = 0;
        if(mmap["is_dir"].empty()) {
            printf("Content-type:text/plain\r\n\r\n{\"status\":%d}", r);
            continue;
        }
        if(mmap["is_dir"].compare("1")==0) {
            if(mmap["id"].empty()) {
                printf("Content-type:text/plain\r\n\r\n{\"status\":%d}", r);
                continue;
            }
            r = removeDir(mmap["id"], mmap["dir_id"]);
        } else {
            if(mmap["id"].empty()) {
                printf("Content-type:text/plain\r\n\r\n{\"status\":%d}", r);
                continue;
            }
            r = removeFile(mmap["id"], mmap["dir_id"]);
        }
        printf("Content-type:text/plain\r\n\r\n{\"status\":%d}", r);
    }
}
