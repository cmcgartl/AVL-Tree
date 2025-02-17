CXX := clang++
CXXFLAGS := -g -Wall -I.. -I. --std=c++17
GTESTINCL := -I /opt/homebrew/opt/googletest/include 
GTESTLIBS := -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: run_bst run_avl

valgrind: valgrind_bst valgrind_avl

run_bst: bst_test
	./bst_test

bst_test: test_bst.cpp
	$(CXX) $(CXXFLAGS) $(GTESTINCL) $^ -o $@ $(GTESTLIBS)

run_avl: avl_test
	./avl_test

avl_test: test_avl.cpp
	$(CXX) $(CXXFLAGS) $(GTESTINCL) $^ -o $@ $(GTESTLIBS)

valgrind_bst: bst_test
	$(VALGRIND) ./bst_test

valgrind_avl: avl_test
	$(VALGRIND) ./avl_test

clean:
	rm -f *.o bst_test avl_test *~

.PHONY: clean valgrind run_bst run_avl valgrind_bst valgrind_avl 