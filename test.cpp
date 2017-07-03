#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "dbUtils.h"
#include "utils.h"
#include "User.h"
#include <string.h>
#include <json/json.h>

int main()
{
    //User user("aaadawefaopwefjpawef", "123456", time(NULL), "127.0.0.1");
    //int res = addUser(user);
    //printf("add:%d\n",res);
    //string buf = isExistChunk("e0b6490a15815c69b42cfb35a299b5b8");
    //printf("uuid:[%s], len:%d\n", buf.c_str(), buf.length());
    //addChunkToFile("das", "123", 0, 1 );
    //string id = addFile("test.file", 1, 1, 234, "erqwroidslf");
    //printf("id=%s\n", id.c_str());

    string r = getRootid(15);
    printf("res:%s\n", r.c_str());
    /*vector<vector<string> > filedirs = getFileList(1);
    printf("vector size:%d, [0] size:%d\n", filedirs.size(), filedirs[0].size());
        Json::Value root;
        if(filedirs.size()) {
            root["status"] = 1;
        } else {
            root["status"] = 0;
        }
        for(int i=0; i<filedirs.size(); i++) {
            Json::Value tmp;
            tmp["file_id"] = filedirs[i][0];
            tmp["file_name"] = filedirs[i][1];
            tmp["ctime"] = filedirs[i][2];
            tmp["size"] = atol(filedirs[i][3].c_str());
            tmp["is_dir"] = atoi(filedirs[i][4].c_str());
            root["filedir"].append(tmp);
        }
        Json::FastWriter writer;
        string str = writer.write(root);
        cout << str << endl;
    printf("getFileList:%s\n", str.c_str());
    Json::Value aaa;
    printf("aaa.size():%d\n", aaa["fuck"].size());
    return 0;*/
    //int id = getParentId(11);
    //printf("id=%d\n",id);
    //int r = getRootid(12);
    //printf("%d\n", r);
    //int r = varifyUser("bbb", "bbbbbb");
    //cout << r << endl;
}
