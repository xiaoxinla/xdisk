all : listFiles.cgi
.PHONY : all

listfilesobj = listFiles.o dbManager.o dbUtils.o utils.o User.o Chunk.o
LIBS = -lfcgi -lmysqlclient -luuid -lleveldb -ljsoncpp -lsodium

listFiles.cgi : $(listfilesobj)
	g++ -o listFiles.cgi $(listfilesobj) $(LIBS)

listFiles.o : listFiles.cpp
	g++ -c listFiles.cpp

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
	rm listFiles.cgi $(listfilesobj)
