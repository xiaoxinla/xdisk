registerobj = register.o utils.o User.o dbManager.o dbUtils.o Chunk.o
LIBS = -lfcgi -lmysqlclient -lsodium -luuid -ljsoncpp -lleveldb

register.cgi : $(registerobj)
	g++ -o register.cgi $(registerobj) $(LIBS)

register.o : register.cpp ../common.h ../User.h
	g++ -c register.cpp

utils.o : ../utils.cpp ../utils.h
	g++ -c ../utils.cpp
User.o : ../User.cpp ../User.h
	g++ -c ../User.cpp

dbManager.o : ../dbManager.cpp ../dbManager.h
	g++ -c ../dbManager.cpp

dbUtils.o : ../dbUtils.cpp ../dbUtils.h ../dbManager.h ../Chunk.h
	g++ -c ../dbUtils.cpp

Chunk.o : ../Chunk.cpp ../Chunk.h
	g++ -c ../Chunk.cpp

clean :
	rm register.cgi $(registerobj)
