
#include <stdexcept>
#include <exception>
#include <stdio.h>
#include "ConnPool.h"


ConnPool * ConnPool::connPool = new ConnPool(DBHOST, DBUSERNAME, DBPASSWORD, DBNAME, DBPORT, 50);

//连接池的构造函数
ConnPool::ConnPool(string host, string userName, string password,
	string dbname, int port, int maxSize)
{
    pthread_mutex_init(&lock, NULL);
	this->maxSize		= maxSize;
	this->username		= userName;
	this->password		= password;
	this->host			= host;
	this->dbname		= dbname;
	this->port			= port;
	this->InitConnection(maxSize / 20);
}


//获取连接池对象，单例模式
ConnPool * ConnPool::GetInstance()
{
	/*if (connPool == NULL)
	{
		connPool			= new ConnPool(DBHOST, DBUSERNAME, DBPASSWORD, DBNAME, DBPORT, 50);
	}
*/
	return connPool;
}


//初始化连接池，创建最大连接数的一半连接数量
void ConnPool::InitConnection(int iInitialSize)
{
	EncapMysql *	conn;

	pthread_mutex_lock(&lock);

	for (int i = 0; i < iInitialSize; i++)
	{
		conn				= this->CreateConnection();

		if (conn)
		{
			connList.push_back(conn);
		}
		else
		{
			perror("创建CONNECTION出错");
		}
	}

	pthread_mutex_unlock(&lock);
}


//创建连接,返回一个Connection
EncapMysql * ConnPool::CreateConnection()
{
	EncapMysql *	conn = new EncapMysql();

	if (conn->Connect(this->host.c_str(), this->username.c_str(), this->password.c_str(),
		this->dbname.c_str(), this->port) == 0)
	{
		return conn;
	}
	else
	{
		perror("连接错误\n");
		return NULL;
	}
}


//在连接池中获得一个连接
EncapMysql * ConnPool::GetConnection()
{
	EncapMysql *	conn;

	pthread_mutex_lock(&lock);

	for (int i = 0; i < connList.size(); i++)
	{
		if (connList[i]->IsIdle())
		{
            printf("connection [%d] is used\n", i);
			connList[i]->SetUsed();
			conn				= connList[i];
			pthread_mutex_unlock(&lock);
			return conn;
		}
	}

	if (connList.size() < maxSize)
	{
		conn				= this->CreateConnection();

		if (conn)
		{
			connList.push_back(conn);
		}

		pthread_mutex_unlock(&lock);
        printf("create new connection\n");
		return conn;
	}
	else
	{
		pthread_mutex_unlock(&lock);
        printf("error");
		return NULL;
	}
}


//回收数据库连接
void ConnPool::ReleaseConnection(EncapMysql * conn)
{
	if (conn)
	{
		pthread_mutex_lock(&lock);
		conn->SetIdle();
		pthread_mutex_unlock(&lock);
	}
}


//连接池的析构函数
ConnPool::~ConnPool()
{
	this->DestoryConnPool();
}


//销毁连接池,首先要先销毁连接池的中连接
void ConnPool::DestoryConnPool()
{
	vector <EncapMysql*>::iterator icon;
	pthread_mutex_lock(&lock);

	for (icon = connList.begin(); icon != connList.end(); ++icon)
	{
		this->DestoryConnection(*icon); 			//销毁连接池中的连接
	}

	connList.clear();								//清空连接池中的连接
	pthread_mutex_unlock(&lock);
}


//销毁一个连接
void ConnPool::DestoryConnection(EncapMysql * conn)
{
	if (conn)
	{
		conn->CloseConnect();
		delete conn;
	}
}


