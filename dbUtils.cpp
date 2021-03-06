
#include "dbUtils.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <sodium.h>
#include <leveldb/db.h>
#include "utils.h"

#define CMD_LEN 512

int isExistUser(const char * username)
{
	//dbManager		manager = dbManager::getManager();
	char			sql[CMD_LEN];

	sprintf(sql, "SELECT id FROM %s WHERE username='%s'", USERTABLE, username);
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector < vector<string> > res = conn->GetResult();
        if(res.size()>0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return atoi(res[0][0].c_str());
        }
    }

    ConnPool::GetInstance()->ReleaseConnection(conn);
    return -1;
}


int addUser(User &user)
{
	char sql[CMD_LEN];
	char hashed_password[crypto_pwhash_STRBYTES];
	if(crypto_pwhash_str(hashed_password, user.getPassword(), strlen(user.getPassword()), crypto_pwhash_OPSLIMIT_SENSITIVE,
		crypto_pwhash_MEMLIMIT_SENSITIVE)!=0) {
		return -1;
	}
	sprintf(sql, "INSERT INTO %s (username, password, ctime, create_ip, last_time, last_ip) "
            "VALUES ('%s', '%s', FROM_UNIXTIME(%ld), INET_ATON('%s'), FROM_UNIXTIME(%ld), INET_ATON('%s'))",
		    USERTABLE, user.getUsername(), hashed_password, user.getCtime(), user.getCreateIp(), user.getLastTime(), user.getLastIp());
    printf("sql:%s\n", sql);
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        int user_id = isExistUser(user.getUsername());
        string root_id = makeDir("root", string(), user_id);
        sprintf(sql, "UPDATE %s SET root='%s' WHERE id=%d", USERTABLE, root_id.c_str(), user_id);
        printf("update:%s\n", sql);
        if(conn->ModifyQuery(sql)==0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return user_id;
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return -1;
}


int varifyUser(const char * username, const char * password)
{
    char sql[CMD_LEN];
    sprintf(sql, "SELECT password,id FROM %s WHERE username='%s'", USERTABLE, username);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector < vector<string> > res = conn->GetResult();
        if(res.size()>0) {
            if(crypto_pwhash_str_verify(res[0][0].c_str(), password, strlen(password))==0) {
                ConnPool::GetInstance()->ReleaseConnection(conn);
                return atoi(res[0][1].c_str());
            }
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    return -1;
}


int varifyUser(int user_id, const char * password)
{
    char sql[CMD_LEN];
    sprintf(sql, "SELECT password FROM %s WHERE id=%s", USERTABLE, user_id);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector < vector<string> > res = conn->GetResult();
        if(res.size()>0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return user_id;
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    return -1;
}


int updateLoginInfo(int user_id, const char* ip)
{
    char sql[CMD_LEN];
    sprintf(sql, "UPDATE %s SET last_time=FROM_UNIXTIME(%ld), last_ip=INET_ATON('%s') WHERE id=%d", USERTABLE, time(NULL), ip, user_id);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return -1;

}

int updatePassword(int user_id, char * password, char * newPassword)
{
	return 0;
}

string isExistChunk(const char* md5) {
    char sql[CMD_LEN];
    sprintf(sql, "SELECT md5 FROM %s WHERE md5='%s' UNION SELECT md5 FROM %s WHERE md5='%s'",
            CHUNKTABLE1, md5, CHUNKTABLE0, md5);
    //sprintf(sql, "SELECT uuid FROM %s WHERE md5='%s'", CHUNKTABLE, md5);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector < vector<string> > res = conn->GetResult();
        if(res.size()>0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return res[0][0];
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    return string();
}

string addChunk(long int size, const char* path, const char* md5) {
    char sql[CMD_LEN];
    sprintf(sql, "INSERT INTO %s_%d (size, path, md5) VALUES (%ld, '%s', '%s')",
            CHUNKTABLE, getDBIndex(md5, 2), size, path, md5);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return string(md5);
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return string();
}

int updateChunkRef(string chunkid, int delta) {
    char sql[CMD_LEN];
    if(delta>0) {
        sprintf(sql, "UPDATE %s_%d SET ref=ref+%d WHERE md5='%s'",
            CHUNKTABLE, getDBIndex(chunkid, 2),delta, chunkid.c_str());
    } else {
        sprintf(sql, "UPDATE %s_%d SET ref=ref-%d WHERE md5='%s'",
            CHUNKTABLE, getDBIndex(chunkid, 2),-delta, chunkid.c_str());
    }
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        sprintf(sql, "SELECT ref FROM %s_%d WHERE md5='%s'", CHUNKTABLE, getDBIndex(chunkid, 2),chunkid.c_str());
        if(conn->SelectQuery(sql)==0){
            vector< vector<string> > res = conn->GetResult();
            if(res.size()>0) {
                ConnPool::GetInstance()->ReleaseConnection(conn);
                return atoi(res[0][0].c_str());
            }
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return -1;
}

int updateFileStatus(string file_id, int status) {
    char sql[CMD_LEN];
    sprintf(sql, "UPDATE %s_%d SET status=%d WHERE id='%s'",
            FILETABLE, getDBIndex(file_id, 2),status, file_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return -1;
}

int addChunkToFile(string chunk_id, string file_id, int chunkcnt, int chunknum) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, LVFILECHUNK, &db);
    if(status.ok()) {
        string str;
        status = db->Get(leveldb::ReadOptions(), file_id, &str);
        Json::Value jsonVal;
        if(status.ok()) {
            printf("getFromLevel:%s\n", str.c_str());
            Json::Reader reader;
            if(!reader.parse(str, jsonVal)){
                return -1;
            } else {
                int size = jsonVal["chunks"].size();
                for(int i=0; i<size; i++) {
                    if(i==chunkcnt) {
                        delete db;
                        return -1;
                    }
                }
            }
        } else {
            jsonVal["num"] = chunknum;
        }
        Json::Value tmp;
        tmp["chunkcnt"] = chunkcnt;
        tmp["chunkid"] = chunk_id;
        jsonVal["chunks"].append(tmp);
        FILE *file = fopen("run.log", "wa");
        char logs[128];
        sprintf(logs, "num:%d,chunks:%d\n,file_id:%s\n", jsonVal["num"].asInt(), jsonVal["chunks"].size(),file_id.c_str());
        fwrite(logs, 1, strlen(logs), file);
        if(jsonVal["chunks"].size()==jsonVal["num"].asInt()) {
            updateFileStatus(file_id, 1);
            fwrite("abc", 1, 3, file);
        }
        fclose(file);
        Json::FastWriter fast_writer;
        string logstr = fast_writer.write(jsonVal);
        printf(logstr.c_str());
        status = db->Put(leveldb::WriteOptions(), file_id, logstr);
        if(status.ok()) {
            updateChunkRef(chunk_id, 1);
            delete db;
            return 1;
        }
    }
    delete db;
    return -1;
}

string isExistFile(const char* filename, string dir_id, int status) {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status st = leveldb::DB::Open(options, LVFILEDIR, &db);
    if(st.ok()) {
        string str;
        st = db->Get(leveldb::ReadOptions(), dir_id, &str);
        Json::Reader reader;
        Json::Value jsonVal;
        if(st.ok()){
            if(!reader.parse(str, jsonVal)){
                delete db;
                return string();
            } else {
                int size = jsonVal["files"].size();
                for(int i=0; i<size; i++) {
                    string fname = getFilename(jsonVal["files"][i].asString(), status);
                    if(strcmp(filename, fname.c_str())==0) {
                        delete db;
                        return jsonVal["files"][i].asString();
                    }
                }
            }
        }
    }
    delete db;
    return string();
}

string isExistFile(const char* filename, string dir_id) {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status st = leveldb::DB::Open(options, LVFILEDIR, &db);
    if(st.ok()) {
        string str;
        st = db->Get(leveldb::ReadOptions(), dir_id, &str);
        Json::Reader reader;
        Json::Value jsonVal;
        if(st.ok()){
            if(!reader.parse(str, jsonVal)){
                delete db;
                return string();
            } else {
                int size = jsonVal["files"].size();
                for(int i=0; i<size; i++) {
                    string fname = getFilenameById(jsonVal["files"][i].asString());
                    if(strcmp(filename, fname.c_str())==0) {
                        delete db;
                        return jsonVal["files"][i].asString();
                    }
                }
            }
        }
    }
    delete db;
    return string();
}

string isExistFile(const char* md5) {
    char sql[CMD_LEN];
    sprintf(sql, "SELECT id FROM %s WHERE md5='%s' AND status=1 UNION SELECT id FROM %s WHERE md5='%s' AND status=1",
            FILETABLE0, md5, FILETABLE1, md5);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector < vector<string> > res = conn->GetResult();
        if(res.size()>0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return res[0][0];
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    return string();
}

string addFile(const char* filename, int user_id, string dir_id, long int size, const char* md5) {
    char sql[CMD_LEN];
    string file_id = genUUID();
    if(getDBIndex(file_id, 2)) {
        sprintf(sql, "INSERT INTO %s (id, filename, user_id, size, md5) VALUES ('%s', '%s', %d, %ld, '%s')",
                FILETABLE1, file_id.c_str(), filename, user_id, size, md5);

    } else {
        sprintf(sql, "INSERT INTO %s (id, filename, user_id, size, md5) VALUES ('%s', '%s', %d, %ld, '%s')",
                FILETABLE0, file_id.c_str(), filename, user_id, size, md5);

    }
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
    } else {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return string();
    }
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status st = leveldb::DB::Open(options, LVFILEDIR, &db);
    if(st.ok()) {
        string str;
        st = db->Get(leveldb::ReadOptions(), dir_id, &str);
        Json::Reader reader;
        Json::Value jsonVal;
        if(st.ok()){
            if(!reader.parse(str, jsonVal)){
                delete db;
                return string();
            }
        }
        jsonVal["files"].append(file_id);
        Json::FastWriter fast_writer;
        string logstr = fast_writer.write(jsonVal);
        printf(logstr.c_str());
        st = db->Put(leveldb::WriteOptions(), dir_id, logstr);
    }
    delete db;
    return file_id;
}

int secUpload(string new_file_id, string another_file_id) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, LVFILECHUNK, &db);
    if(status.ok()) {
        string str;
        status = db->Get(leveldb::ReadOptions(), another_file_id, &str);
        if(status.ok()) {
            status = db->Put(leveldb::WriteOptions(), new_file_id, str);
            Json::Value jsonVal;
            Json::Reader reader;
            if(!reader.parse(str, jsonVal)){
                delete db;
                return -1;
            }
            int size = jsonVal["chunks"].size();
            for(int i=0; i<size; i++) {
                updateChunkRef(jsonVal["chunks"][i]["chunkid"].asString(), 1 );
            }
            delete db;
            updateFileStatus(new_file_id, 1);
            return 1;
        }
    }
    delete db;
    return -1;

}

int renameFile(string file_id, const char* newName) {
    char sql[CMD_LEN];
    sprintf(sql, "UPDATE %s_%d SET filename='%s' WHERE id='%s'", FILETABLE, getDBIndex(file_id, 2),newName, file_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    } else {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return -1;
    }
}

int removeFile(string file_id, string parent_id) {
    char sql[CMD_LEN];
    sprintf(sql, "DELETE FROM %s_%d WHERE id='%s'", FILETABLE, getDBIndex(file_id, 2),file_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)!=0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return -1;
    }
    vector<Chunk> chunkVec = getFileChunks(file_id);
    for(int i=0; i<chunkVec.size(); i++) {
        int r = updateChunkRef(chunkVec[i].chunkid, -1);
        if(r==0) {
            sprintf(sql, "DELETE FROM %s_%d WHERE md5='%s'", CHUNKTABLE, getDBIndex(chunkVec[i].chunkid, 2),chunkVec[i].chunkid.c_str());
            if(conn->ModifyQuery(sql)==0) {
                remove(chunkVec[i].path.c_str());
            }
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, LVFILEDIR, &db);
    string str;
    status = db->Get(leveldb::ReadOptions(), parent_id, &str);
    Json::Value jsonVal;
    Json::Reader reader;
    if(!reader.parse(str, jsonVal)){
        delete db;
        return -1;
    }
    vector<string> rec;
    for(int i=0; i<jsonVal["files"].size(); i++) {
        if(file_id.compare(jsonVal["files"][i].asString())!=0){
            rec.push_back(jsonVal["files"][i].asString());
        }
    }
    jsonVal.removeMember("files");
    for(int i=0; i<rec.size(); i++) {
        jsonVal["files"].append(rec[i]);
    }
    Json::FastWriter fast_writer;
    string logstr = fast_writer.write(jsonVal);
    printf(logstr.c_str());
    status = db->Put(leveldb::WriteOptions(), parent_id, logstr);
    if(!status.ok()) {
        delete db;
        return -1;
    }
    delete db;


    status = leveldb::DB::Open(options, LVFILECHUNK, &db);
    if(status.ok()) {
        status = db->Delete(leveldb::WriteOptions(), file_id);
    } else {
        delete db;
        return -1;
    }
    delete db;
    return 1;
}

int moveFile(string file_id, int newDir) {
    char sql[CMD_LEN];
    sprintf(sql, "UPDATE %s_%d SET dir_id=%s WHERE id='%s'", FILETABLE, getDBIndex(file_id, 2),newDir, file_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    } else {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return -1;
    }
}

string makeDir(const char* dirname, string parent_id, int user_id) {
    char sql[CMD_LEN];
    string id = genUUID();
    sprintf(sql, "INSERT INTO %s (id, dirname, user_id, ctime, mtime) VALUES ('%s', '%s', %d, FROM_UNIXTIME(%ld), FROM_UNIXTIME(%ld))",
            USERDIRTABLE, id.c_str(), dirname, user_id, time(NULL), time(NULL));
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)!=0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return string();
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    if(parent_id.empty()) {
        return id;
    }
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, LVFILEDIR, &db);
    string str;
    status = db->Get(leveldb::ReadOptions(), parent_id, &str);
    Json::Value jsonVal;
    Json::Reader reader;
    if(status.ok()){
        if(!reader.parse(str, jsonVal)){
            delete db;
            return string();
        }
    }
    jsonVal["dirs"].append(id);
    Json::FastWriter fast_writer;
    string logstr = fast_writer.write(jsonVal);
    printf(logstr.c_str());
    status = db->Put(leveldb::WriteOptions(), parent_id, logstr);
    if(!status.ok()){
        delete db;
        return string();
    }
    delete db;


    return id;
}

int renameDir(string dir_id, const char* newName) {
    char sql[CMD_LEN];
    sprintf(sql, "UPDATE %s SET dirname='%s' WHERE id='%s'", USERDIRTABLE, newName, dir_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    } else {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return -1;
    }
}

int removeDir(string dir_id, string parent_id) {
    //TODO remove files and dirs recursively
    vector<vector<string> > fileList = getFileList(dir_id);
    vector<vector<string> > dirList = getDirList(dir_id);
    for(int i=0; i<fileList.size(); i++) {
        removeFile(fileList[0][0], dir_id);
    }
    for(int i=0; i<dirList.size(); i++) {
        removeDir(dirList[0][0], dir_id);
    }
    char sql[CMD_LEN];
    sprintf(sql, "DELETE FROM %s WHERE id='%s'", USERDIRTABLE, dir_id.c_str());
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, LVFILEDIR, &db);
        status = db->Delete(leveldb::WriteOptions(), dir_id);
        if(!status.ok()) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            delete db;
            return -1;
        }
        ConnPool::GetInstance()->ReleaseConnection(conn);

        string str;
        status = db->Get(leveldb::ReadOptions(), parent_id, &str);
        Json::Value jsonVal;
        Json::Reader reader;
        if(!reader.parse(str, jsonVal)){
            delete db;
            return -1;
        }
        vector<string> rec;
        for(int i=0; i<jsonVal["dirs"].size(); i++) {
            if(dir_id.compare(jsonVal["dirs"][i].asString())!=0){
                rec.push_back(jsonVal["dirs"][i].asString());
            }
        }
        jsonVal.removeMember("dirs");
        for(int i=0; i<rec.size(); i++) {
            jsonVal["dirs"].append(rec[i]);
        }
        Json::FastWriter fast_writer;
        string logstr = fast_writer.write(jsonVal);
        printf(logstr.c_str());
        status = db->Put(leveldb::WriteOptions(), parent_id, logstr);
        if(!status.ok()) {
            delete db;
            return -1;
        }
        delete db;

        return 1;
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
    return -1;
}

int moveDir(string dir_id, string parent_id) {
    char sql[CMD_LEN];
    sprintf(sql, "UPDATE %s SET parent_id='%s' WHERE id='%s'", USERDIRTABLE, parent_id.c_str(), dir_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->ModifyQuery(sql)==0) {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    } else {
        ConnPool::GetInstance()->ReleaseConnection(conn);
        return 1;
    }
}

string getRootid(int user_id) {
    char sql[CMD_LEN];
    sprintf(sql, "SELECT root FROM %s WHERE id=%d", USERTABLE, user_id);
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector<vector<string> > res = conn->GetResult();
        if(res.size()) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return res[0][0];
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return string();

}

string getParentId(string dir_id){
    char sql[CMD_LEN];
    sprintf(sql, "SELECT parent_id FROM %s WHERE id='%s'", USERDIRTABLE, dir_id.c_str());
    printf(sql);
    printf("\n");
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        vector<vector<string> > res = conn->GetResult();
        if(res.size()) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return res[0][0];
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return string();
}

vector<vector<string> > getFileList(string dir_id) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    vector<vector<string> > ans;
    leveldb::Status status = leveldb::DB::Open(options, LVFILEDIR, &db);
    if(!status.ok()) {
        delete db;
        return ans;
    }
    string str;
    status = db->Get(leveldb::ReadOptions(), dir_id, &str);
    if(!status.ok()) {
        delete db;
        return ans;
    }
    Json::Value jsonVal;
    Json::Reader reader;
    reader.parse(str, jsonVal);
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    for(int i=0; i<jsonVal["files"].size(); i++){
        string file_id = jsonVal["files"][i].asString();
        char sql[CMD_LEN];
        vector<vector<string> > res;
        sprintf(sql, "SELECT filename, ctime, size, status FROM %s_%d WHERE id='%s'", FILETABLE, getDBIndex(file_id, 2), file_id.c_str());
        printf(sql);
        printf("\n");
        vector<string> row;
        if(conn->SelectQuery(sql)==0) {
            row.push_back(file_id);
            res = conn->GetResult();
            if(res.size()<=0) continue;
            for(int j=0; j<res[0].size(); j++) {
                row.push_back(res[0][j]);
            }
            row.push_back("0");
        }
        ans.push_back(row);
    }
    delete db;
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return ans;

}

vector<vector<string> > getDirList(string dir_id) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    vector<vector<string> > ans;
    leveldb::Status status = leveldb::DB::Open(options, LVFILEDIR, &db);
    if(!status.ok()) {
        delete db;
        return ans;
    }
    string str;
    status = db->Get(leveldb::ReadOptions(), dir_id, &str);
    if(!status.ok()) {
        delete db;
        return ans;
    }
    Json::Value jsonVal;
    Json::Reader reader;
    reader.parse(str, jsonVal);
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    for(int i=0; i<jsonVal["dirs"].size(); i++){
        string did = jsonVal["dirs"][i].asString();
        char sql[CMD_LEN];
        vector<vector<string> > res;
        vector<string> row;
        sprintf(sql, "SELECT dirname, ctime FROM %s WHERE id='%s'", USERDIRTABLE, did.c_str());
        printf(sql);
        printf("\n");
        if(conn->SelectQuery(sql)==0) {
            row.push_back(did);
            res = conn->GetResult();
            if(res.size()<=0) continue;
            for(int j=0; j<res[0].size(); j++) {
                row.push_back(res[0][j]);
            }
            row.push_back("0");
            row.push_back("0");
            row.push_back("1");
        }
        ans.push_back(row);
    }
    delete db;
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return ans;
}

vector<vector<string> > getFileDirList(string dir_id) {
    vector<vector<string> > fileVec = getFileList(dir_id);
    vector<vector<string> > dirVec = getDirList(dir_id);
    for(int i=0; i<dirVec.size(); i++) {
        fileVec.push_back(dirVec[i]);
    }
    return fileVec;
}

vector<Chunk> getFileChunks(string file_id){
    char sql[CMD_LEN];
    vector<vector<string> > res;
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, LVFILECHUNK, &db);
    vector<Chunk> ans;
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(status.ok()) {
        string str;
        status = db->Get(leveldb::ReadOptions(), file_id, &str);
        if(status.ok()) {
            Json::Value jsonVal;
            Json::Reader reader;
            reader.parse(str, jsonVal);
            int size = jsonVal["chunks"].size();
            for(int i=0; i<size; i++) {
                Chunk chunk;
                chunk.chunkcnt = jsonVal["chunks"][i]["chunkcnt"].asInt();
                chunk.chunkid = jsonVal["chunks"][i]["chunkid"].asString();
                sprintf(sql, "SELECT path, size FROM %s_%d WHERE md5='%s'",CHUNKTABLE,getDBIndex(chunk.chunkid, 2),chunk.chunkid.c_str());
                if(conn->SelectQuery(sql)==0) {
                    res = conn->GetResult();
                    if(res.size()>0) {
                        chunk.path = res[0][0];
                        chunk.size = atol(res[0][1].c_str());
                    }
                }
                ans.push_back(chunk);
            }
        }
    }
    sort(ans.begin(), ans.end(), chunkcmp);
    delete db;
    ConnPool::GetInstance()->ReleaseConnection(conn);
    return ans;
}

string getFilenameById(string file_id) {
    char sql[CMD_LEN];
    sprintf(sql, "SELECT filename FROM %s_%d WHERE id='%s'", FILETABLE,getDBIndex(file_id, 2), file_id.c_str());
    printf(sql);
    printf("\n");
	vector < vector<string> > res;
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        res = conn->GetResult();
        if(res.size()>0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return res[0][0];
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return string();
}

string getFilename(string file_id, int status) {
    char sql[CMD_LEN];
    sprintf(sql, "SELECT filename FROM %s_%d WHERE id='%s' AND status=%d", FILETABLE,getDBIndex(file_id, 2), file_id.c_str(), status);
    printf(sql);
    printf("\n");
	vector < vector<string> > res;
    EncapMysql* conn = ConnPool::GetInstance()->GetConnection();
    if(conn->SelectQuery(sql)==0) {
        res = conn->GetResult();
        if(res.size()>0) {
            ConnPool::GetInstance()->ReleaseConnection(conn);
            return res[0][0];
        }
    }
    ConnPool::GetInstance()->ReleaseConnection(conn);
	return string();
}
