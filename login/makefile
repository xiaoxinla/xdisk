loginobj = login.o User.o dbManager.o dbUtils.o utils.o Chunk.o
LIBS = -lmysqlclient -lsodium -lfcgi -luuid -lleveldb -ljsoncpp

login.cgi : $(loginobj)
	g++ -o login.cgi $(loginobj) $(LIBS)

login.o : login.cpp
	g++ -c login.cpp

User.o : ../User.cpp ../User.h
	g++ -c ../User.cpp

dbManager.o : ../dbManager.cpp ../dbManager.h
	g++ -c ../dbManager.cpp

dbUtils.o : ../dbUtils.cpp ../dbUtils.h ../dbManager.h ../common.h ../Chunk.h
	g++ -c ../dbUtils.cpp

utils.o : ../utils.cpp ../utils.h
	g++ -c ../utils.cpp

Chunk.o : ../Chunk.cpp ../Chunk.h
	g++ -c ../Chunk.cpp

clean : 
	rm login.cgi $(loginobj)
