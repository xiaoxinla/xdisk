#include <fcgi_stdio.h>
#include <stdlib.h>
#include "../dbUtils.h"
#include "../utils.h"

int main() {
    while(FCGI_Accept()>=0) {
        char context[1024];
        int len = atoi(getenv("CONTENT_LENGTH"));
        fread(context, sizeof(char), len, stdin);
        context[len] = '\0';
        const char *keys[] = {"user_id"};
        map<string, string> mmap = getQueryInfo(context, keys, 1);
        string id = getRootid(atoi(mmap["user_id"].c_str()));
        printf("Content-type: text/plain\r\n\r\n{\"dir_id\":\"%s\"}", id.c_str());
    }
}
