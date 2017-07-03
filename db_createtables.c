#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main() {
	MYSQL *conn;
	conn = mysql_init(NULL);
	mysql_real_connect(conn, DBHOST, DBUSERNAME, DBPASSWORD, DBNAME, DBPORT, NULL, 0);
	mysql_query(conn, "CREATE TABLE xdisk_user(id int NOT NULL AUTO_INCREMENT,"
		"username varchar(64) NOT NULL,"
		"password varchar(100) NOT NULL,"
		"ctime timestamp NOT NULL DEFAULT '1990-01-01 00:00:01',"
		"create_ip int unsigned NOT NULL ,"
		"last_time timestamp NOT NULL DEFAULT '1990-01-01 00:00:01',"
		"last_ip int unsigned NOT NULL,"
		"PRIMARY KEY (id))ENGINE=InnoDB CHARSET=utf8;");
	mysql_query(conn, "CREATE TABLE xdisk_file(uuid varchar(40) NOT NULL,"
		"filename varchar(128) NOT NULL,"
		
"server_id int NOT NULL,"
		"path varchar(128) NOT NULL,"
		"type tinyint NOT NULL,"
		"size bigint NOT NULL,"
		"ctime timestamp NOT NULL,"
		"sha1hash varchar(40) NOT NULL,"
		"ref int NOT NULL,"
		"PRIMARY KEY (uuid))ENGINE=InnoDB CHARSET=utf8;");
	mysql_query(conn, "CREATE INDEX file_sha ON xdisk_file(sha1hash);");
	mysql_query(conn, "CREATE TABLE xdisk_filesrv(id int NOT NULL AUTO_INCREMENT,"
		"srvname varchar(64) NOT NULL,"
		"ip int unsigned NOT NULL,"
		"status tinyint NOT NULL,"
		"space bigint NOT NULL,"
		"PRIMARY KEY (id))ENGINE=InnoDB CHARSET=utf8;");
	mysql_query(conn, "CREATE TABLE xdisk_userdir(id int NOT NULL AUTO_INCREMENT,"
		"dirname varchar(128) NOT NULL,"
		"user_id int NOT NULL,"
		"ctime timestamp NOT NULL DEFAULT '1990-01-01 00:00:01',"
		"mtime timestamp NOT NULL DEFAULT '1990-01-01 00:00:01',"
		"status tinyint NOT NULL,"
		"PRIMARY KEY (id))ENGINE=InnoDB CHARSET=utf8;");
	mysql_query(conn, "CREATE INDEX user_dir_uid ON xdisk_userdir(user_id);");
	mysql_query(conn, "CREATE TABLE xdisk_userfile(id int NOT NULL AUTO_INCREMENT,"
		"filename varchar(128) NOT NULL,"
		"type tinyint NOT NULL,"
		"user_id int NOT NULL,"
		"ctime timestamp NOT NULL DEFAULT '1990-01-01 00:00:01',"
		"mtime timestamp NOT NULL DEFAULT '1990-01-01 00:00:01',"
		"status tinyint NOT NULL,"
		"file_id varchar(40) NOT NULL,"
		"PRIMARY KEY (id))ENGINE=InnoDB CHARSET=utf8;");
	mysql_query(conn, "CREATE INDEX user_file_uid ON xdisk_userfile(user_id);");
	mysql_close(conn);
}
