
#include "dbManager.h"	  
#include <stdio.h>

dbManager dbManager::manager;

dbManager::dbManager() {
	isConnected = false;
	this->initConnection();
}

dbManager& dbManager::getManager() {
	return manager;
}

dbManager::~dbManager()
{
	this->destroyConnection();
}


void dbManager::initConnection()
{
	if (isConnected)
	{ //	已经连接到服务器		
		return;
	}

	mysql_init(&mySQLClient);						//	  初始化相关对象    
	mysql_real_connect(&mySQLClient, DBHOST, DBUSERNAME, DBPASSWORD, DBNAME, DBPORT, NULL, 0);
	isConnected 		= true; 					//	  修改连接标识	
}


bool dbManager::runSQLCommand(char * sql)
{
	resultList.clear();

	if (!isConnected)
	{ //	没有连接到服务器	  
		return false;
	}

	if (sql==NULL)
	{ //	SQL语句为空 	 
		return false;
	}

	MYSQL_RES * 	res;
	MYSQL_ROW		row;

	unsigned int	i, j = 0;

	i					= mysql_real_query(&mySQLClient, sql, strlen(sql)); //	  执行查询	  

	if (i < 0)
	{
		return false;
	}

	res 				= mysql_store_result(&mySQLClient);
	if(res==0) {
		return false;
	}
	vector <string> objectValue;
	while ((row = mysql_fetch_row(res)))
	{ //	遍历结果集    
		objectValue.clear();
		for (j = 0; j < mysql_num_fields(res); j++)
		{
			objectValue.push_back(row[j]);
		}

		this->resultList.push_back(objectValue);
	}
	mysql_free_result(res); 						//free result after you get the result	  

	return true;
}


unsigned int dbManager::insert(char* sql)
{
	if (!isConnected)
	{
		return - 1;
	}

	if (sql==NULL)
	{
		return - 1;
	}

	int 			rows = -1;
	int 			res = mysql_query(&mySQLClient, sql);

	if (res >= 0)
	{
		// 返回受影响的行数
		rows				= mysql_affected_rows(&mySQLClient);
		return rows;
	}
	else 
	{
		return - 1;
	}
}


vector < vector<string> > dbManager::getResult()
{
	return resultList;
}


void dbManager::destroyConnection()
{
	mysql_close(&mySQLClient);
	this->isConnected	= false;
}


bool dbManager::getConnectionStatus()
{
	return isConnected;
}



