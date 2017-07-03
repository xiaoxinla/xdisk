#include "User.h"

User::User() {
	this->username[0]='\0';
	this->password[0] = '\0';
}

User::User(const char* username, const char* password, time_t ctime, const char* create_ip) {
	strcpy(this->username, username);
	strcpy(this->password, password);
	this->ctime = ctime;
	this->last_time= ctime;
    strcpy(this->create_ip, create_ip);
    strcpy(this->last_ip, create_ip);
}

User::User(const char* username, const char* password, time_t ctime, const char* create_ip, time_t last_time, const char* last_ip) {
	strcpy(this->username, username);
	strcpy(this->password, password);
	this->ctime = ctime;
	this->last_time = last_time;
    strcpy(this->create_ip, create_ip);
    strcpy(this->last_ip, last_ip);
}

void User::setUsername(const char* username) {
	strcpy(this->username, username);
}
char* User::getUsername() {
	return this->username;
}
void User::setPassword(const char* password) {
	strcpy(this->password, password);
}
char* User::getPassword() {
	return this->password;
}
void User::setCtime(time_t ctime) {
	this->ctime = ctime;
}
time_t User::getCtime() {
	return this->ctime;
}
void User::setLastTime(time_t last_time) {
	this->last_time = last_time;
}
time_t User::getLastTime() {
	return this->last_time;
}
void User::setCreateIp(const char* create_ip) {
    strcpy(this->create_ip, create_ip);
}
char* User::getCreateIp() {
	return this->create_ip;
}
void User::setLastIp(const char* last_ip) {
    strcpy(this->last_ip, last_ip);
}
char* User::getLastIp() {
	return this->last_ip;
}



