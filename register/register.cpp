
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <fcgi_stdio.h>
#include <mysql/mysql.h>
#include "../common.h"
#include "../utils.h"
#include "../dbUtils.h"
#include "../User.h"


int main()
{
	while (FCGI_Accept() >= 0)
	{
		char *			method = getenv("REQUEST_METHOD");
		if(method==NULL) {
			printf("<p> Not Support  </p>");
		}
		else if (!strcmp(method, "POST"))
		{
			int 			ilen = atoi(getenv("CONTENT_LENGTH"));
			char *			bufp = (char*)malloc(ilen+1);

			fread(bufp, 1, ilen, stdin);
            bufp[ilen] = '\0';
            FILE *file = fopen("log", "w");
            char cc[128];
            sprintf(cc, "content:%s\n", bufp);
            fwrite(cc, 1, strlen(cc), file);
            const char* keys[] = {"username", "password1", "password2"};
			map<string, string> map = getQueryInfo(bufp, keys, 3);
			int res = isExistUser(map["username"].c_str());
            sprintf(cc, "res:%d\n", res);
            fwrite(cc, 1, strlen(cc), file);
			if(res<0) {
                User user(map["username"].c_str(), map["password1"].c_str(), time(NULL), getenv("REMOTE_ADDR"));
                int user_id = addUser(user);
                sprintf(cc, "user_id:%d, %s, %s, %s\n",user_id, map["username"].c_str(), map["password1"].c_str(), map["password2"].c_str());
                fwrite(cc, 1, strlen(cc), file);
                fclose(file);
                if(user_id<0) {
		            printf("Content-type: text/plain\r\n\r\n{\"status\":0}");
                }else {
                    string root_id = getRootid(user_id);
		            printf("Content-type: text/plain\r\n\r\n{\"status\":1, \"dir_id\":\"%s\", \"user_id\":%d}", root_id.c_str(), user_id);
			    }
            } else {
		        printf("Content-type: text/plain\r\n\r\n{\"status\":0}");
			}
			free(bufp);
		}else {
		    printf("Content-type: text/html\r\n\r\n{\"status\":2}");
		}
	}
}



