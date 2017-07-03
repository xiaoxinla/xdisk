#!/bin/sh
spawn-fcgi -a 127.0.0.1 -p 9001 -f /usr/local/xdisk/register.cgi
spawn-fcgi -a 127.0.0.1 -p 9002 -f /usr/local/xdisk/login.cgi
spawn-fcgi -a 127.0.0.1 -p 9003 -f /usr/local/xdisk/listFiles.cgi
spawn-fcgi -a 127.0.0.1 -p 9010 -f /usr/local/xdisk/uploadtest.cgi
spawn-fcgi -a 127.0.0.1 -p 9011 -f /usr/local/xdisk/secUpload.cgi
spawn-fcgi -a 127.0.0.1 -p 9012 -f /usr/local/xdisk/checkChunk.cgi
spawn-fcgi -a 127.0.0.1 -p 9020 -f /usr/local/xdisk/download.cgi
spawn-fcgi -a 127.0.0.1 -p 9021 -f /usr/local/xdisk/getShareLink.cgi
spawn-fcgi -a 127.0.0.1 -p 9022 -f /usr/local/xdisk/shareDownload.cgi
spawn-fcgi -a 127.0.0.1 -p 9030 -f /usr/local/xdisk/makedir.cgi
spawn-fcgi -a 127.0.0.1 -p 9031 -f /usr/local/xdisk/backParent.cgi
spawn-fcgi -a 127.0.0.1 -p 9032 -f /usr/local/xdisk/deleteFileDir.cgi
spawn-fcgi -a 127.0.0.1 -p 9033 -f /usr/local/xdisk/getRootid.cgi
spawn-fcgi -a 127.0.0.1 -p 9034 -f /usr/local/xdisk/renameFileDir.cgi

