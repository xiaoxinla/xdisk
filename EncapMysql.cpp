
#include "EncapMysql.h"

using namespace std;

EncapMysql::EncapMysql()
{
	SetConnected(false);
	m_result			= NULL;
	resultList.clear();
	mysql_init(&m_connection);
}


EncapMysql::~EncapMysql()
{
	FreePreResult();
	CloseConnect();
}


int EncapMysql::Connect(const char * szDbIp, const char * szUser,
	const char * szPassword, const char * szName, const int szPort)
{

    SaveParam(szDbIp, szUser, szPassword, szName, szPort);
	if (IsConnected())
		return 0;

	if (mysql_real_connect(&m_connection, szDbIp, szUser, szPassword, szName, szPort,
		NULL, 0) == NULL)
	{
        printf("EncapMysql:szDbIp=%s, szUser=%s, szPassword=%s, szname=%s, szPort=%d\n", szDbIp, szUser, szPassword, szName, szPort);
		ERRMSG2("%s", mysql_error(&m_connection));
        printf("%s", m_szErrMsg);
		return - 1;
	}

	printf("[mysql] conn to %s [user:%s] succ!\r\n", szDbIp, szUser);
    SetIdle();
	SetConnected(true);
	return 0;
}


void EncapMysql::CloseConnect()
{
	mysql_close(&m_connection);
	SetConnected(false);
}


int EncapMysql::SelectQuery(const char * szSQL)
{
	if (szSQL == NULL)
	{
		ERRMSG2("%s", "szSQL==NULL");
		return - 1;
	}

	if (!IsConnected())
	{
		ERRMSG2("%s", "还没有建立连接");
		return - 2;
	}

	try
	{

		if (mysql_real_query(&m_connection, szSQL, strlen(szSQL)) != 0)
		{
			ERRMSG2("%s", mysql_error(&m_connection));
			printf("%s", mysql_error(&m_connection));
			printf("ReConnect()  is called, select111  !!!***\r\n");
			int 			nRet = ReConnect();

			if (nRet != 0)
				return - 3;

			//
			if (mysql_real_query(&m_connection, szSQL, strlen(szSQL)) != 0)
				return - 33;

			//
		}

		FreePreResult();
		m_result			= mysql_store_result(&m_connection);

		if (m_result == NULL)
		{
			ERRMSG2("%s", mysql_error(&m_connection));
			return - 4;
		}
	}

	catch (...)
	{
		printf("ReConnect()  is called, select	!!!***\r\n");
		ReConnect();
		return - 5;
	}

	vector < string > objectValue;
    MYSQL_ROW row;
	while ((row = mysql_fetch_row(m_result)))
	{ //	遍历结果集
		objectValue.clear();

		for (int j = 0; j < mysql_num_fields(m_result); j++)
		{
			objectValue.push_back(row[j]);
		}

		this->resultList.push_back(objectValue);
	}

	return 0;
}


int EncapMysql::ModifyQuery(const char * szSQL)
{

	if (szSQL == NULL)
	{
		ERRMSG2("%s", "szSQL==NULL");
		return - 1;
	}

	if (!IsConnected())
	{
		ERRMSG2("%s", "还没有建立连接");
		return - 2;
	}
	try
	{

		if (mysql_real_query(&m_connection, szSQL, strlen(szSQL)) != 0)
		{
			ERRMSG2("%s", mysql_error(&m_connection));
			return - 3;
		}
	}

	catch (...)
	{
		printf("ReConnect()  is called	,modify!!!***\r\n");
		ReConnect();
		return - 5;
	}

	return 0;
}


void EncapMysql::FreePreResult()
{

	if (m_result != NULL)
	{
		mysql_free_result(m_result);
		m_result			= NULL;
	}

	this->resultList.clear();
}


const char * EncapMysql::GetErrMsg()
{
	return m_szErrMsg;
}

vector< vector<string> > EncapMysql::GetResult(){
    return resultList;
}


bool EncapMysql::IsConnected()
{
	return m_bConnected;
}


void EncapMysql::SetConnected(bool bTrueFalse)
{
	m_bConnected		= bTrueFalse;
}


void EncapMysql::SaveParam(const char * szDbIp, const char * szUser,
	const char * szPassword, const char * szName, const int szPort)
{
	m_sDbIp 			= szDbIp;					//数据库服务器IP
	m_sUser 			= szUser;					//用户名
	m_sPassword 		= szPassword;				//口令
    m_sName             = szName;
    m_sPort             = szPort;
}


int EncapMysql::ReConnect()
{
	CloseConnect();

	//连接数据库
	if (mysql_real_connect(&m_connection, m_sDbIp.c_str(), m_sUser.c_str(),
		m_sPassword.c_str(), NULL, 0, NULL, 0) == NULL)
	{
		ERRMSG2("%s", mysql_error(&m_connection));
		return - 1;
	}

	//设置连接标志为 true
	SetConnected(true);
	return 0;
}


/////////////////////////  连接池那个类需要用到这3个函数。
void EncapMysql::SetUsed()
{
	m_bUseIdle			= true;
}


void EncapMysql::SetIdle()
{
	m_bUseIdle			= false;
}


//如果空闲，返回true
bool EncapMysql::IsIdle()
{
	return ! m_bUseIdle;
}


