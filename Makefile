LOG = /tmp/compile.log

test1: test1.cpp test2.cpp test3.cpp Makefile
	g++ -std=c++17 -o test1 test1.cpp test2.cpp test3.cpp 2>&1 | tee $(LOG)

clean:
	@rm -f *.o test1

.PHONY: clean
