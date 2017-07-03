#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "common.h"

int main() {
	MYSQL *conn;
	conn = mysql_init(NULL);
	if(conn==NULL) {
		printf("Error %u:%s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	if(mysql_real_connect(conn, DBHOST, DBUSERNAME, DBPASSWORD, NULL, 0, NULL, 0)==NULL) {
		printf("Error %u:%s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	if(mysql_query(conn, "create database xdisk;")) {
		printf("Error %u:%s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	mysql_close(conn);
}
