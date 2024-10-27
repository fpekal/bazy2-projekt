.PHONY: build clean

sources = src/pony.cpp src/app.cpp

libs = sqlite3
libs-flags != pkg-config --cflags --libs $(libs)

flags = $(libs-flags) -O3

build:
	g++ $(flags) -o pony $(sources)

clean:
	rm pony pony.db
