CC=g++
CFLAGS=-g -O2 -Wall -m32 -D_DEBUG -DTRACE_SYSCALL  -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient_r
CXXFLAGS=$(CFLAGS)
SOURCES:=$(wildcard *.cpp) $(wildcard ../common/*.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCES))
#DEPS:=$(patsubst %.o, %.d, $(OBJS))

all:controller

controller:$(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o controller 

$(OBJS):$(SOURCES)

clean:
	rm -f *.o ../common/*.o controller
