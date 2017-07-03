

#ifndef ENCAP_MYSQL_H
#define ENCAP_MYSQL_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <mysql/mysql.h>

using namespace std;

#define ERRMSG1(fmt, ...)		; sprintf(m_szErrMsg, fmt, __VA_ARGS__);
#define ERRMSG2(fmt, args ...)	; sprintf(m_szErrMsg, "[%s 第 %d 行 ]; "fmt"\r\n" , __FILE__, __LINE__, ##args);


class EncapMysql
{



public:

EncapMysql();
~EncapMysql();



public:

int Connect(const char * szDbIp, const char * szUser, const char * szPassword, const char * szName, const int szPort);

void CloseConnect();

int SelectQuery(const char * szSQL);

int ModifyQuery(const char * szSQL);

const char * GetErrMsg();

vector < vector < string > > GetResult();





public:

void SetUsed();
void SetIdle();
bool IsIdle();										//返回 true 标识 Idle



private:

bool			m_bUseIdle; 						// true: use;	false:idle




private:

bool IsConnected();

void SetConnected(bool bTrueFalse);

void FreePreResult();

int ReConnect();

void SaveParam(const char* szDbIp, const char* szUser,
        const char* szPassword, const char* szName, const int szPort);




public:

MYSQL			m_connection;						//连接
MYSQL_RES * 	m_result;							//结果集指针




private:

string			m_sDbIp;							//数据库服务器IP
string			m_sUser;							//用户名
string			m_sPassword;						//口令
string          m_sName;
int             m_sPort;
vector < vector < string > > resultList;
bool			m_bConnected;						//数据库连接了吗?   true--已经连接;	false--还没有连接
char			m_szErrMsg[1024];					//函数出错后, 错误信息放在此处


};


#endif

