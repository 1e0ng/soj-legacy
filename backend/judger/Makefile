CC=g++
CFLAGS=-g -O2 -Wall -m32
CXXFLAGS=$(CFLAGS)
SOURCES:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCES))
#DEPS:=$(patsubst %.o, %.d, $(OBJS))

all:soj testee

testee:testee.o
	$(CC) $(CXXFLAGS) testee.o -o testee

soj:$(filter-out teste.o, $(OBJS))
	$(CC) $(CXXFLAGS) $(filter-out testee.o, $(OBJS)) -o soj

$(OBJS):$(SOURCES)

clean:
	rm -f *.o testee soj
