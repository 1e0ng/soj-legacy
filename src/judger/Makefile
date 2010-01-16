CC=g++
CFLAGS=-g -O2 -Wall -m32 -D_DEBUG -DTRACE_SYSCALL  -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient_r
CXXFLAGS=$(CFLAGS)
SOURCES:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCES))
#DEPS:=$(patsubst %.o, %.d, $(OBJS))

all:soj

soj:$(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o soj

$(OBJS):$(SOURCES)

clean:
	rm -f *.o soj
