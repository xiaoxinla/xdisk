#include <fcgi_stdio.h>
#include <stdlib.h>
#include "../dbUtils.h"
#include "../utils.h"

int main() {
    while(FCGI_Accept() >= 0) {
        char content[1024];
        int len = atoi(getenv("CONTENT_LENGTH"));
        fread(content, sizeof(char), len, stdin);
        content[len] = '\0';
        const char *keys[] = {"cur_dir"};
        map<string, string> mmap = getQueryInfo(content, keys, 1);
        string id = getParentId(mmap["cur_dir"]);
        printf("Content-type:text/plain\r\n\r\n{\"dir_id\":\"%s\"}", id.c_str());
    }
}
