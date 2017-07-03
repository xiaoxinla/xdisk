#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"
#include "../dbUtils.h"

int main() {
    FILE *file = fopen("abc0", "r");
    char context[2048];
    int len = fread(context, 1, 2048, file);
    context[len] = '\0';
    printf("context:%s\n", context);
    const char *keystr[] = {"file_md5", "file_name", "total_size", "cur_dir", "user_id"};
    vector<string> keys(keystr, keystr+5);
    map<string, string> mmap = getFormData(context, keys);
    printf("isExist:%d\n", !isExistFile(mmap["file_md5"].c_str()).empty());
    addFile(mmap["file_name"].c_str(), atoi(mmap["user_id"].c_str()), atoi(mmap["cur_dir"].c_str()), atol(mmap["total_size"].c_str()), mmap["file_md5"].c_str());
    fclose(file);
}
