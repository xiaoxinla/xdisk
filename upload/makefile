all: uploadtest.cgi test secUpload.cgi chunkTest
.PHONY : all

objs = utils.o dbUtils.o dbManager.o User.o Chunk.o
LIBS = -lfcgi -luuid -lmysqlclient -lsodium -ljsoncpp -lleveldb

uploadtest.cgi : uploadtest.o $(objs)
	g++ -o uploadtest.cgi uploadtest.o $(objs) $(LIBS)

uploadtest.o : uploadtest.cpp ../utils.h
	g++ -c uploadtest.cpp

utils.o : ../utils.cpp ../utils.h
	g++ -c ../utils.cpp

dbUtils.o : ../dbUtils.cpp ../dbUtils.h ../common.h ../User.h
	g++ -c ../dbUtils.cpp

dbManager.o : ../dbManager.cpp ../dbManager.h ../common.h
	g++ -c ../dbManager.cpp

User.o : ../User.h ../User.cpp
	g++ -c ../User.cpp

Chunk.o : ../Chunk.cpp ../Chunk.h
	g++ -c ../Chunk.cpp

test : test.o $(objs)
	g++ -o test test.o $(objs) $(LIBS)

test.o : test.cpp ../utils.h
	g++ -c test.cpp

secUpload.cgi : secUpload.o $(objs)
	g++ -o secUpload.cgi secUpload.o $(objs) $(LIBS)

chunkTest : chunkTest.o $(objs)
	g++ -o chunkTest chunkTest.o $(objs) $(LIBS)

clean :
	rm uploadtest.cgi uploadtest.o test test.o secUpload.cgi secUpload.o $(objs)
