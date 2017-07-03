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
        const char *keys[] = {"cur_dir", "user_id", "dirname"};
        map<string, string> res = getQueryInfo(content, keys, 3);
        res["dirname"] = URLDecode(res["dirname"]);
        string dir_id = makeDir(res["dirname"].c_str(), res["cur_dir"], atoi(res["user_id"].c_str()));
        if(!dir_id.empty()) {
            printf("Content-type: text/plain\r\n\r\n{\"status\":1, \"dir_id\":\"%s\"}", dir_id.c_str());
        } else {
            printf("Content-type: text/plain\r\n\r\n{\"status\":0}");
        }
    }
}
