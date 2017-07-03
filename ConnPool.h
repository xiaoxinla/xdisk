

#ifndef CONN_POOL_H
#define CONN_POOL_H
#include <pthread.h>
#include "common.h"
#include "EncapMysql.h"

using namespace std;


class ConnPool
{

private:

int 			maxSize;							//连接池中定义的最大数据库连接数
string			username;
string			password;
string			host;
string			dbname;
int 			port;
vector <EncapMysql*> connList;						//连接池的容器队列
pthread_mutex_t lock;								//线程锁
static ConnPool * connPool;

EncapMysql * CreateConnection();					//创建一个连接
void InitConnection(int iInitialSize);				//初始化数据库连接池
void DestoryConnection(EncapMysql * conn);			//销毁数据库连接对象
void DestoryConnPool(); 							//销毁数据库连接池
ConnPool(string url, string user, string password, string dbname,
	int port, int maxSize); 						//构造方法

public:

~ConnPool();
EncapMysql * GetConnection();						//获得数据库连接
void ReleaseConnection(EncapMysql * conn);			//将数据库连接放回到连接池的容器中
static ConnPool * GetInstance();					//获取数据库连接池对象
};


#endif /*_CONNECTION_POOL_H */

