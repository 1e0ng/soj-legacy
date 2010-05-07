CC=g++
CFLAGS=-g -O2 -Wall -m32 -DNDEBUG -DTRACE_SYSCALL -D_CONTROLLER -pipe
CXXFLAGS=$(CFLAGS)
INCPATHS=-I/usr/include/mysql
LIBPATHS=-L/usr/lib/mysql
LIBS=-static -lmysqlclient 
SOURCES:=$(wildcard *.cpp) $(wildcard ../common/*.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCES))
#DEPS:=$(patsubst %.o, %.d, $(OBJS))

all:controller

controller:$(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LIBPATHS) $(LIBS) -o $% 

$(OBJS):$(SOURCES)
	$(CC) $(CXXFLAGS) $(INCPATHS) -c $< -o $%

clean:
	rm -f *.o ../common/*.o controller
