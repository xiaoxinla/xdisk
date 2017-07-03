#ifndef UTILS_H
#define UTILS_H
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string, string> getQueryInfo(char* query_info, const char *keys[], int len);

map<string, string> getFormData(char *form, vector<string> keys);

string genUUID();

string getFileDirListJson(vector<vector<string> > filedirs);

string URLDecode(const string &sIn);

int getDBIndex(string str, int total);

string encryptWithAES(const char* data, const char* key);

string decryptWithAES(const char* data, const char* key);
size_t Base64_Decode(char *pDest, const char *pSrc, size_t srclen);
size_t Base64_Encode(char *pDest, const char *pSrc, size_t srclen);
#endif
