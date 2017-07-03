#include <fcgi_stdio.h>
#include "../dbUtils.h"
#include "../utils.h"
#include <stdlib.h>
#include <string>

int main() {
    while(FCGI_Accept() >= 0 ) {
        int len = atoi(getenv("CONTENT_LENGTH"));
        char content[1024];
        fread(content, 1, len, stdin);
        content[len] = '\0';
        FILE *file = fopen("secUpload.log", "w");
        fwrite(content, 1, strlen(content), file);
        fclose(file);
        const char *keystr[] = {"file_md5", "file_name", "total_size", "cur_dir", "user_id"};
        map<string, string> mmap = getQueryInfo(content, keystr, 5);
        mmap["file_name"] = URLDecode(mmap["file_name"]);
        string res = isExistFile(mmap["file_name"].c_str(), mmap["cur_dir"]);
        if(!res.empty()) {
            string tmp = isExistFile(mmap["file_name"].c_str(), mmap["cur_dir"], 1);
            if(tmp.empty()) {
                printf("Content-Type:text/plain\r\n\r\n{\"secUpload\":0, \"isExist\":1, \"finished\":0, \"file_id\":\"%s\"}", res.c_str());
            } else {
                printf("Content-Type:text/plain\r\n\r\n{\"secUpload\":1, \"isExist\":1, \"finished\":1, \"file_id\":\"%s\"}", res.c_str());
            }
            continue;
        }
        res = isExistFile(mmap["file_md5"].c_str());
        string file_id  = addFile(mmap["file_name"].c_str(), atoi(mmap["user_id"].c_str()), mmap["cur_dir"], atol(mmap["total_size"].c_str()), mmap["file_md5"].c_str());
        if(!res.empty()) {
            secUpload(file_id, res);
            printf("Content-Type:text/plain\r\n\r\n{\"secUpload\":1, \"isExist\":0, \"finished\":0, \"file_id\":\"%s\"}", file_id.c_str());
        } else {
            printf("Content-Type:text/plain\r\n\r\n{\"secUpload\":0, \"isExist\":0, \"finished\":0, \"file_id\":\"%s\"}", file_id.c_str());
        }
    }
}

