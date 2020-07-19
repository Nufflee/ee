# Experimental, haven't verified yet
CXX:=clang++
CXXFLAGS:=-Wall -Wextra -Isrc/ -std=c++17 -ggdb
CXXLIBS:=-lSDL2 -lSDL2_ttf
SRCFILES := $(shell find src/ -type f -name "*.cpp")

.PHONY: build
build:
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $(SRCFILES) -o build/editor

