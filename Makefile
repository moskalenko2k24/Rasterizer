# https://fedoraproject.org/wiki/MinGW
# https://fedoraproject.org/wiki/MinGW/Tutorial
# sudo dnf install wine mingw64-gcc mingw64-gcc-c++
# maybe wine-devel is also useful for LSP (not to show errors on <windows.h>)

# CC = g++ # on Windows
CC = x86_64-w64-mingw32-g++
CFLAGS = -Wall -Wextra -std=c++20 -static-libgcc -static-libstdc++

all:
	 $(CC) $(CFLAGS) -mwindows *.cpp algorithms/*.cpp -o main

build: all

.PHONY: clean

clean:
	rm -rf *.exe

run:
	wine main.exe

compile_commands:
	bear -- make
