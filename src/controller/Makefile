CC=g++
CFLAGS=-g -Wall -DNDEBUG -DTRACE_SYSCALL -D_CONTROLLER -pipe -fPIC \
	   -fno-strict-aliasing   -DUNIV_LINUX -DUNIV_LINUX
CXXFLAGS=$(CFLAGS)
INCPATHS=-I/usr/include/mysql/
LIBPATHS=-L/usr/lib64/mysql/
LIBS=-Wl,--hash-style=gnu -Wl,--as-needed -rdynamic  -lmysqlclient -lpthread -lz -lcrypt -lnsl -lm
SOURCES:=$(wildcard *.cpp) $(wildcard ../common/*.cpp) $(wildcard ../common/Packet/*.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCES))
BINPATH=../../bin/
#DEPS:=$(patsubst %.o, %.d, $(OBJS))

all:controller

controller:$(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LIBPATHS) $(LIBS) -o $@ && mv $@ $(BINPATH)

$(OBJS):%.o:%.cpp
	$(CC) $(CXXFLAGS) $(INCPATHS) -c $< -o $@

clean:
	rm -f *.o ../common/*.o ../common/Packet/*.o $(BINPATH)controller
