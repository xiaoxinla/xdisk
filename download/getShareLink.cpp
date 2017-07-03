
#include <fcgi_stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../dbUtils.h"
#include "../utils.h"

#define BUF_SIZE 1024*1024


int main() {
    while(FCGI_Accept()>=0) {
        int len = atoi(getenv("CONTENT_LENGTH"));
        char content[1024];
        fread(content, sizeof(char), len, stdin);
        content[len] = '\0';
        const char *keys[] = {"file_id"};
        map<string, string> mmap = getQueryInfo(content, keys, 1);
        time_t now = time(NULL);
        int keyint = now / ONE_DAY;
        char key[24];
        sprintf(key, "%s%d", PROJECT_NAME, keyint);
        string encrypted = encryptWithAES(mmap["file_id"].c_str(), key);
        printf("Content-type: text/plain\r\n\r\n{\"token\":\"%s\", \"status\":1}", encrypted.c_str());
    }
}
