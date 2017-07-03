#ifndef DBUTILS_H
#define DBUTILS_H
#include <string>
//#include "dbManager.h"
#include "ConnPool.h"
#include "User.h"
#include <uuid/uuid.h>
#include <vector>
#include <json/json.h>
#include "Chunk.h"
#include "common.h"

int isExistUser(const char *username) ; //是否存在用户，存在返回id，不存在返回-1
int addUser(User &user);		//新建用户
int varifyUser(const char *username, const char* password);	//验证用户，通过返回用户id，没通过返回-1
int varifyUser(const int user_id, const char *password);	//验证用户，通过返回用户id，没通过返回-1
int updateLoginInfo(int user_id, const char* ip);	//更新登陆信息，成功返回1，没成功返回-1
int updatePassword(int user_id, char *password, char *newPassword);	//更新用户密码，成功返回1，没成功返回-1
string isExistChunk(const char *md5);//根据md5判断是否存在文件块，存在返回uuid，不存在返回空串
string addChunk(long int size, const char* path, const char* md5); //添加文件块信息，成功返回文件块的uuid，失败返回空串
string isExistFile(const char *filename, string dir_id, int status);   //根据文件名，文件夹以及文件状态判断是否存在文件，存在返回文件id，不存在返回-1
string isExistFile(const char *filename, string dir_id);               //在所有文件中,根据文件名和文件目录判断是否存在文件，存在返回id，不存在返回-1
string isExistFile(const char *md5);                                //检查是否已经有文件上传
string addFile(const char* filename, int user_id, string dir_id, long int size, const char* md5); //添加文件，成功返回文件的id，失败返回-1
int updateChunkRef(string chunkid, int delta) ;
int updateFileStatus(string file_id, int status);
int secUpload(string new_file_id, string another_file_id);
int addChunkToFile(string chunk_id, string file_id, int chunkcnt, int chunknum);
int renameFile(string file_id, const char* newName);               //重命名文件
int removeFile(string file_id, string parent_id);                                    //删除文件
int moveFile(string file_id, string newDir);                  //移动文件
string makeDir(const char* dirname, string parent_id, int user_id);                //新建目录
int renameDir(string dir_id, const char* newName);                //重命名文件夹
int removeDir(string dir_id, string parent_id);                                      //删除文件夹
int moveDir(string dir_id, string newDir);                    //移动文件夹
string getRootid(int user_id);
string getParentId(string dir_id);
string getFilenameById(string file_id);
string getFilename(string file_id, int status);
vector<vector<string> > getFileList(string dir_id);        //根据目录id获取其下的文件, 0 id, 1 name, 2 ctime, 3 size, 4 status, 5 isDir
vector<vector<string> > getDirList(string dir_id);         //根据目录id获取其下的目录
vector<vector<string> > getFileDirList(string dir_id);     //根据目录id获取其下的文件和目录
vector<Chunk> getFileChunks(string file_id);           //返回排好序的文件块id

#endif
