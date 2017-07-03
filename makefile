all : db_createdb db_createtables test printLevelDB register.cgi login.cgi uploadtest.cgi listFiles.cgi download.cgi secUpload.cgi makedir.cgi \
	backParent.cgi deleteFileDir.cgi getRootid.cgi checkChunk.cgi getShareLink.cgi shareDownload.cgi renameFileDir.cgi
.PHONY : all

commonobj = dbUtils.o dbManager.o User.o utils.o Chunk.o EncapMysql.o ConnPool.o
LIBS = -lmysqlclient -lsodium -luuid -lleveldb -ljsoncpp -lfcgi -lpthread
db_createdb : db_createdb.o
	gcc -o db_createdb db_createdb.o -lmysqlclient

db_createtables : db_createtables.o
	gcc -o db_createtables db_createtables.o -lmysqlclient

db_createdb.o : common.h db_createdb.c
	gcc -c db_createdb.c

db_createtables.o : common.h db_createdb.c
	gcc -c db_createtables.c

test : test.o $(commonobj)
	g++ -o test test.o $(commonobj) $(LIBS)

test.o : test.cpp
	g++ -c test.cpp

dbUtils.o : dbUtils.cpp dbUtils.h common.h dbManager.h User.h Chunk.h
	g++ -c dbUtils.cpp

EncapMysql.o : EncapMysql.cpp
	g++ -c EncapMysql.cpp

ConnPool.o : ConnPool.cpp common.h
	g++ -c ConnPool.cpp

dbManager.o : dbManager.cpp dbManager.h common.h
	g++ -c dbManager.cpp

User.o : User.cpp User.h
	g++ -c User.cpp

utils.o : utils.h utils.cpp
	g++ -c utils.cpp

Chunk.o : Chunk.cpp Chunk.h
	g++ -c Chunk.cpp

printLevelDB : printLevelDB.o
	g++ -g -o printLevelDB printLevelDB.o -lleveldb -ljsoncpp

printLevelDB.o : printLevelDB.cpp common.h
	g++ -c printLevelDB.cpp

register.cgi : register.o $(commonobj)
	g++ -o register.cgi register.o $(commonobj) $(LIBS)

register.o : register/register.cpp dbUtils.h utils.h
	g++ -c register/register.cpp

login.cgi : login.o $(commonobj)
	g++ -o login.cgi login.o $(commonobj) $(LIBS)

login.o : login/login.cpp dbUtils.h utils.h
	g++ -c login/login.cpp

uploadtest.cgi : uploadtest.o $(commonobj)
	g++ -o uploadtest.cgi uploadtest.o $(commonobj) $(LIBS)

uploadtest.o : upload/uploadtest.cpp dbUtils.h utils.h
	g++ -c upload/uploadtest.cpp

download.cgi : download.o $(commonobj)
	g++ -o download.cgi download.o $(commonobj) $(LIBS)

download.o : download/download.cpp dbUtils.h utils.h
	g++ -c download/download.cpp

listFiles.cgi : listFiles.o $(commonobj)
	g++ -o listFiles.cgi listFiles.o $(commonobj) $(LIBS)

listFiles.o : showUI/listFiles.cpp dbUtils.h utils.h
	g++ -c showUI/listFiles.cpp

secUpload.cgi : secUpload.o $(commonobj)
	g++ -o secUpload.cgi secUpload.o $(commonobj) $(LIBS)

secUpload.o : upload/secUpload.cpp dbUtils.h utils.h
	g++ -c upload/secUpload.cpp

makedir.cgi : makedir.o $(commonobj)
	g++ -o makedir.cgi makedir.o $(commonobj) $(LIBS)

makedir.o : fileops/makedir.cpp dbUtils.h utils.h
	g++ -c fileops/makedir.cpp

backParent.cgi: backParent.o $(commonobj)
	g++ -o backParent.cgi backParent.o $(commonobj) $(LIBS)

backParent.o : fileops/backParent.cpp dbUtils.h utils.h
	g++ -c fileops/backParent.cpp

deleteFileDir.cgi : deleteFileDir.o $(commonobj)
	g++ -o deleteFileDir.cgi deleteFileDir.o $(commonobj) $(LIBS)

deleteFileDir.o : fileops/deleteFileDir.cpp dbUtils.h utils.h
	g++ -c fileops/deleteFileDir.cpp

getRootid.cgi : getRootid.o $(commonobj)
	g++ -o getRootid.cgi getRootid.o $(commonobj) $(LIBS)

getRootid.o : fileops/getRootid.cpp dbUtils.h utils.h
	g++ -c fileops/getRootid.cpp

checkChunk.cgi : checkChunk.o $(commonobj)
	g++ -o checkChunk.cgi checkChunk.o $(commonobj) $(LIBS)

checkChunk.o : upload/checkChunk.cpp dbUtils.h utils.h
	g++ -c upload/checkChunk.cpp

getShareLink.cgi : getShareLink.o $(commonobj)
	g++ -o getShareLink.cgi getShareLink.o $(commonobj) $(LIBS)

getShareLink.o : download/getShareLink.cpp dbUtils.h utils.h
	g++ -c download/getShareLink.cpp

shareDownload.cgi : shareDownload.o $(commonobj)
	g++ -o shareDownload.cgi shareDownload.o $(commonobj) $(LIBS)

shareDownload.o : download/shareDownload.cpp dbUtils.h utils.h
	g++ -c download/shareDownload.cpp

renameFileDir.cgi : renameFileDir.o $(commonobj)
	g++ -o renameFileDir.cgi renameFileDir.o $(commonobj) $(LIBS)

renameFileDir.o : fileops/renameFileDir.cpp dbUtils.h utils.h
	g++ -c fileops/renameFileDir.cpp

clean :
	rm db_createdb db_createdb.o db_createtables db_createtables.o test test.o printLevelDB printLevelDB.o uploadtest.cgi uploadtest.o register.cgi register.o \
		login.cgi login.o download.cgi download.o listFiles.cgi listFiles.o secUpload.cgi secUpload.o makedir.cgi makedir.o backParent.cgi backParent.o \
		deleteFileDir.cgi deleteFileDir.o getShareLink.cgi getShareLink.o shareDownload.cgi shareDownload.o renameFileDir.cgi renameFileDir.o \
		$(commonobj)
