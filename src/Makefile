CXX := g++
CXX_FLAGS := -Wall -Werror -Wextra -std=c++17
GCOVFLAGS := -L. --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
 TEST_FLAGS := $(shell pkg-config --libs gtest)
else
 TEST_FLAGS := -lgtest
endif

LIB_SRC_MOD := $(wildcard model/*.cc)
LIB_SRC_CON := $(wildcard controller/*.cc)
LIB_SRC_VIE := $(wildcard view/*.cc)
LIB_HDR_MOD := $(wildcard model/*.h)
LIB_HDR_CON := $(wildcard controller/*.h)
LIB_HDR_VIE := $(wildcard view/*.h)
LIB_HDR_OBS := $(wildcard observer/*.h)

ifeq ($(OS), Linux)
 MEM_CHECK := valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./test
else
 MEM_CHECK := CK_FORK=no leaks --atExit -- ./test
endif

all: tests

tests: clean
	$(CXX) $(CXX_FLAGS) test.cc model/parser.cc -o test $(TEST_FLAGS)
	./test

install: uninstall
	cd view/; cmake .; make;
	cp -R view/3DViewer_v2.app ~/Desktop/

uninstall:
	rm -rf ~/Desktop/3DViewer_v2.app
	rm -rf ~/Desktop/options.json

dist:
	rm -rf ../Archive/
	mkdir ../Archive/
	cp -r ../src ../Archive/
	tar -C ../ -czvf Archive.tgz Archive/
	mv Archive.tgz ~/Desktop/
	rm -rf ../Archive/

gcov_report: clean
	$(CXX) $(CXX_FLAGS) model/parser.cc test.cc $(TEST_FLAGS) $(GCOVFLAGS) -o $@
	./$@
	lcov -t $@ -o rep.info -c -d . --ignore-errors mismatch
	genhtml -o report rep.info
	open ./report/index.html

dvi:
	open doc/html/index.html

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(LIB_SRC_MOD) $(LIB_SRC_CON) $(LIB_SRC_VIE) \
	$(LIB_HDR_MOD) $(LIB_HDR_CON) $(LIB_HDR_VIE) $(LIB_HDR_OBS) test.cc
	rm .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++11 --language=c++ $(LIB_SRC_MOD) $(LIB_SRC_CON) $(LIB_SRC_VIE) \
	# $(LIB_HDR_MOD) $(LIB_HDR_CON) $(LIB_HDR_VIE) $(LIB_HDR_OBS)

clean:
	rm -rf *.a *.o .clang-format test *.out gcov_report* *.info report *.gcno tests.out.dSYM
	rm -rf view/3DViewer_v2.app
	rm -rf view/3DViewer_v2_autogen
	rm -rf view/CMakeCache.txt
	rm -rf view/CMakeFiles
	rm -rf view/Makefile
	rm -rf view/cmake_install.cmake
	rm -rf view/.qmake.stash
	rm -rf view/*.o
	rm -rf view/moc_*
	rm -rf view/.qtc_clangd
	rm -rf ~/Desktop/Archive.tgz
	rm -rf tests_sanitiz*
	rm -rf *.gcda
	# rm -rf ~/Desktop/options.json
