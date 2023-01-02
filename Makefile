CC=gcc
CFLAGS=-lstdc++ -std=c++17 -Wall -Wextra -Werror -g
FLAGS_TEST_LIBS =-lgtest -lstdc++ -lpthread -std=c++17

SRC=model.cc model_bonus.cc controller.cc

HEADER=model.h controller.h
NAME=model.a
OBJ=$(patsubst %.cc, %.o, $(SRC))
OS = $(shell uname)

.PHONY: all build static install uninstall rebuild dist test gcov_report clean m

all: clean build static test

build:
	$(CC) $(CFLAGS) -c $(SRC)

static:
	ar rc model.a $(OBJ)
	ranlib model.a

test: clean build static
	$(CC) $(FLAGS_TEST_LIBS) s21_test.cc model.a -o test
	./test

gcov_report: all
	$(CC) $(CFLAGS) --coverage s21_test.cc $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html


install: build
	make clean
	mkdir build
	cd view && qmake && make && make clean && rm Makefile && cd ../ && mv view/Qt.app/Contents/MacOs/Qt build

uninstall:
	rm -rf build*

dvi:
	open readme.html

dist:
	rm -rf Archive_calc_v2.0/
	mkdir Archive_calc_v2.0/
	mkdir Archive_calc_v2.0/src
	mv ./build/Qt.app Archive_calc_v2.0/src/
	tar cvzf Archive_calc_v2.0.tgz Archive_calc_v2.0/
	rm -rf Archive_calc_v2.0/

clean:
	rm -rf *.{a,o,dSYM,out}
	rm -rf $(EXECUTABLE)
	rm -rf gcov_report
	rm -rf report
	rm -rf CPPLINT.cfg
	rm -rf *.gcda
	rm -rf *.gch
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf Archive_calc_v1.0 
	rm -rf *tgz
	rm -rf build
	rm -rf gcov_test s21_calc
	rm -rf *.o


rebuild: clean all

check:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c *.c
	python3 ../materials/linters/cpplint.py --extensions=c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	leaks --atExit -- test

m:
	g++ -lstdc++ -std=c++17 model.cc model.h m.cc -g && ./a.out