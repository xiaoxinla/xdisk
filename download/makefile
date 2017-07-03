all : download.cgi
.PHONY : all

download_obj = download.o dbManager.o dbUtils.o utils.o User.o Chunk.o
LIBS = -lfcgi -lleveldb -lmysqlclient -luuid -ljsoncpp -lsodium

download.cgi : $(download_obj)
	g++ -o download.cgi $(download_obj) $(LIBS)

download.o : download.cpp
	g++ -c download.cpp

dbManager.o : ../dbManager.cpp ../dbManager.h
	g++ -c ../dbManager.cpp

utils.o : ../utils.cpp ../utils.h
	g++ -c ../utils.cpp

dbUtils.o : ../dbUtils.cpp ../dbUtils.h ../common.h
	g++ -c ../dbUtils.cpp

User.o : ../User.cpp ../User.h
	g++ -c ../User.cpp

Chunk.o : ../Chunk.cpp ../Chunk.h
	g++ -c ../Chunk.cpp

clean :
	rm download.cgi $(download_obj)
