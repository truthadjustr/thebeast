LOG = /tmp/compile.log

test1: test1.cpp Makefile
	g++ -std=c++17 -o test1 test1.cpp 2>&1 | tee $(LOG)
	#g++ -o test1 test1.cpp

clean:
	@rm -f *.o test1

.PHONY: clean
