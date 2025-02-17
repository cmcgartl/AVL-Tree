CC = g++
CPPFLAGS = -g -Wall -std=c++17

all: Scheduling

Scheduling: Scheduling.cpp avlbst.h bst.h print_bst.h
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f scheduling