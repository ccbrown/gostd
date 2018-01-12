.PHONY: cx

all: cx

cx:
	$(CXX) -nostdlib -fno-exceptions -lSystem -std=c++1z -o $@ -I./include main.cpp src/os.cpp src/allocation.cpp
