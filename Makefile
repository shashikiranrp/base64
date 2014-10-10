CLANG_CXX = $(shell which clang++)

C++11=$(CLANG_CXX) -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat

all: link 

compile: Base64CharMap.h Base64CharMap.cpp
	$(C++11) -c -I. *.cpp 

link: compile
	$(C++11) *.o -o b64

clean:
	rm -f *.o b64
