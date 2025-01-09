.PHONY: build install clean test debug

SRC_DIR := "src"
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

LIBS := sqlite3
LIBS_FLAGS != pkg-config --cflags --libs $(LIBS)

TEST_SRCS_SRC != find src/ -name '*.cpp' ! -name app.cpp
TEST_SRCS_TESTS != find tests/ -name '*.cpp'
TEST_SRCS := $(TEST_SRCS_SRC) $(TEST_SRCS_TESTS)

CXXFLAGS = -Wall -std=c++23

build:
	$(CXX) $(LIBS_FLAGS) $(CXXFLAGS) -o pony $(SRCS)

install:
	mkdir -p $(out)/bin
	cp pony $(out)/bin/pony

test:
	$(CXX) $(LIBS_FLAGS) -lboost_unit_test_framework $(CXXFLAGS) -Isrc/ -o pony_test $(TEST_SRCS)
	./pony_test

debug:
	$(CXX) $(LIBS_FLAGS) $(CXXFLAGS) -ggdb -o pony $(SRCS)

clean:
	rm pony pony.db pony.db-journal
