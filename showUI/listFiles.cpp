#include <fcgi_stdio.h>
#include <stdlib.h>
#include "../dbUtils.h"
#include "../utils.h"

int main() {
    while(FCGI_Accept() >=0) {
        char content[1024];
        int len = atoi(getenv("CONTENT_LENGTH"));
        fread(content, sizeof(char), len, stdin);
        content[len] = '\0';
        const char * keys[] = {"cur_dir"};
        map<string, string> mmap = getQueryInfo(content, keys, 1);
        if(mmap.empty()) {
            printf("Content-type:text/plain\r\n\r\n{}");
            continue;
        }
        if(mmap["cur_dir"].empty()) {
            printf("Content-type:text/plain\r\n\r\n{}");
            continue;
        }
        vector<vector<string> > filedirs = getFileDirList(mmap["cur_dir"]);
        string str = getFileDirListJson(filedirs);
        if(str.empty()) {
            printf("Content-type:text/plain\r\n\r\n{}");
            continue;
        }
        printf("Content-type:text/plain\r\n\r\n%s", str.c_str());
    }
}
