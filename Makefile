.PHONY: build clean

SRC_DIR := "src"
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

LIBS := sqlite3
LIBS_FLAGS != pkg-config --cflags --libs $(LIBS)

CXXFLAGS = -Wall

build:
	$(CXX) $(LIBS_FLAGS) $(CXXFLAGS) -o pony $(SRCS)

clean:
	rm pony pony.db
