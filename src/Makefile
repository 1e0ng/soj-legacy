MAKE=make

all:controller/controller judger/judger

controller/controller:
	$(MAKE) -C controller

judger/judger:
	$(MAKE) -C judger

clean:
	rm -rf *.o controller/*.o judger/*.o common/*.o common/Packet/*.o bin/controller bin/judger
