CC=g++
CFLAGS=-g -Wall -m32 -DNDEBUG -DTRACE_SYSCALL -D_JUDGER
CXXFLAGS=$(CFLAGS)
SOURCES:=$(wildcard *.cpp) $(wildcard ../common/*.cpp) $(wildcard ../common/Packet/*.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCES))
BINPATH=../bin/
#DEPS:=$(patsubst %.o, %.d, $(OBJS))

all:judger

judger:$(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $@ && mv $@ $(BINPATH)

$(OBJS):$(SOURCES)

clean:
	rm -f *.o ../common/*.o ../common/Packet/*.o $(BINPATH)judger
