
#ifndef MYSQLMANAGER_H_
#define MYSQLMANAGER_H_
#include <mysql/mysql.h>	
#include <string>		
#include <vector>	 
#include <string.h>    
#include "common.h"

using namespace std;


class dbManager
{

public:

static dbManager&  getManager();

void initConnection();

bool runSQLCommand(char* sql);

unsigned int insert(char* sql);

bool getConnectionStatus();
vector < vector<string> > getResult();


private:

dbManager();
~dbManager();

bool			isConnected;
vector < vector<string> > resultList;
MYSQL			mySQLClient;
void destroyConnection();
static dbManager manager;

};


#endif /* MYSQLMANAGER_H_ */

