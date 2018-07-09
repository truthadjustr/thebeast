LOG = /tmp/compile.log

test1: test1.cpp test2.cpp test3.cpp Makefile
	g++ -std=c++17 -o test1 test1.cpp test2.cpp test3.cpp 2>&1 | tee $(LOG)

procon: procon.cpp
	g++ -std=c++17 -lpthread -o procon procon.cpp 

ub: ub.cpp
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o ub ub.cpp
else
	g++ -std=c++17 -O2 -Wall -Wextra -pedantic -fsanitize=address -o ub ub.cpp
endif

controller: controller.cpp
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o controller controller.cpp
else
	g++ -std=c++17 -O2 -Wall -Wextra -pedantic -fsanitize=address -o controller controller.cpp
endif

cppthreads: cppthreads.cpp
	g++ -std=c++17 -o cppthreads cppthreads.cpp

ambi: ambi.cpp
	g++ -o ambi ambi.cpp

clean:
	@rm -f *.o test1 procon ub ambi controller cppthreads

.PHONY: clean
