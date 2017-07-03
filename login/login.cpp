#include <stdlib.h>
#include <fcgi_stdio.h>
#include "../utils.h"
#include "../dbUtils.h"


int main()
{
    while (FCGI_Accept() >= 0)
    {
        char *          method = getenv("REQUEST_METHOD");

        if (strcmp(method, "POST") == 0)
        {
            int             ilen = atoi(getenv("CONTENT_LENGTH"));
            char *          bufp = new char[ilen];

            fread(bufp, 1, ilen, stdin);
            const char* keys[] = {"username", "password"};
            map <string, string> map = getQueryInfo(bufp, keys, 2);
            char            sql[1024];
            int             res = varifyUser(map[string("username")].c_str(), map[string("password")].c_str());

            if (res > 0)
            {
                string rootid = getRootid(res);
                printf("Content-type: text/plain\r\n\r\n{\"status\":1, \"dir_id\":\"%s\", \"user_id\":%d}", rootid.c_str(), res);
                updateLoginInfo(res, getenv("REMOTE_ADDR"));
            }
            else
            {
                printf("Content-type: text/plain\r\n\r\n{\"status\":0}");
            }
        }
        else
        {
            printf("Content-type: text/plain\r\n\r\n{\"status\":0}");
        }
    }
}



