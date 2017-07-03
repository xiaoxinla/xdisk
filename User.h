#ifndef USER_H
#define USER_H
#include <time.h>
#include <string.h>

class User{
private:
	char username[64];
	char password[100];
	time_t ctime;
	time_t last_time;
	char create_ip[16];
	char last_ip[16];
public:
	User() ;
	User(const char *username, const char *password, time_t ctime, const char* create_ip);
	User(const char *username, const char *password, time_t ctime, const char* create_ip, time_t last_time, const char* last_ip);
	void setUsername(const char *username);
	char* getUsername();
	void setPassword(const char *password);
	char* getPassword();
	void setCtime(time_t ctime);
	time_t getCtime();
	void setLastTime(time_t last_time);
	time_t getLastTime();
	void setCreateIp(const char* create_ip);
	char* getCreateIp();
	void setLastIp(const char* last_ip);
	char* getLastIp();
};

#endif
