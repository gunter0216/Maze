.PHONY: all clean default install uninstall dvi dist tests check clean rebuild gcov_report

CC=g++ -std=c++17
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all

all: clean install tests

build: clean
	@-mkdir ./build
	@-mkdir ./build/View
	@-mkdir ./build/headers
	@-mkdir ./build/Auxiliary
	@cp *.cpp *.pro ./build
	@cp ./View/* ./build/View
	@cp ./headers/* ./build/headers
	@cp ./Auxiliary/* ./build/Auxiliary
	@-cd ./build; qmake Maze.pro
	@-make -C build
	@rm -rf ./build/*.cpp ./build/*h ./build/*.ui ./build/*.pro ./build/*.o ./build/Makefile ./build/View ./build/headers ./build/Auxiliary

install:build
	@-cp -rf build/*.app $(HOME)/Applications/

uninstall:
	@rm -rf $(HOME)/Applications/Maze.app

dvi:
	open ./Documentation/index.html

dist: clean
	mkdir -p dist
	tar --totals -cvf dist/Maze.tar .

tests: clean
ifeq ($(OS), Darwin)
	$(CC) Test/test.cpp Auxiliary/FileController.cpp Auxiliary/Labyrinth.cpp Auxiliary/Cave.cpp -lcheck -lgtest -lgtest_main -lpthread -o tests
else
	$(CC) -o test Auxiliary/Labyrinth.cpp Auxiliary/Cave.cpp Test/test.cpp -lm -lgtest -lpthread
endif
	./tests
test: tests

gcov_report:
	$(CC) --coverage -o testresult Test/test.cpp Auxiliary/FileController.cpp Auxiliary/Labyrinth.cpp Auxiliary/Cave.cpp -lcheck -lgtest -lgtest_main -lpthread
	./testresult
	lcov -t "testresult" -o testresult.info -c -d .
	genhtml -o report testresult.info
	open ./report/index.html

lint:
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extension=cpp *.cpp ./*/*.cpp
	@python3 ../materials/linters/cpplint.py --extension=h ./*/*.h
	@rm CPPLINT.cfg

clean:
	rm -rf *.cfg calculator tests testresult* report dist/*.tar build dist
	rm -rf doc/*.dvi doc/*.cps doc/*.cp doc/*.aux doc/*.log doc/*.toc doc/*.pdf *.gcda *.gcno
 
rebuild: clean uninstall all
