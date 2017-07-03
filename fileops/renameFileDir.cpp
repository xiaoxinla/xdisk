
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
        const char *keys[] = {"is_dir", "id", "name"};
        map<string, string> mmap = getQueryInfo(content, keys, 3);
        mmap["name"] = URLDecode(mmap["name"]);
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
            r = renameDir(mmap["id"], mmap["name"].c_str());
        } else {
            if(mmap["id"].empty()) {
                printf("Content-type:text/plain\r\n\r\n{\"status\":%d}", r);
                continue;
            }
            r = renameFile(mmap["id"], mmap["name"].c_str());
        }
        printf("Content-type:text/plain\r\n\r\n{\"status\":%d}", r);
    }
}
