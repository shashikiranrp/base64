CLANG_CXX = $(shell which clang++)

C++11=$(CLANG_CXX) -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat

all: clean run

compile: 
	$(C++11) -c -I. *.cpp 

link: compile
	$(C++11) *.o -o b64

run: link
	test "$(shell echo "Hello, World!" | ./b64)" = "$(shell echo "Hello, World!" | base64)" && ( echo "ENCODE SUCCESS" ) || ( echo "ENCODE FAILED"; exit 1; )
	test "$(shell echo "SGVsbG8sIFdvcmxkIQo=" | ./b64 -d)" = "$(shell echo "SGVsbG8sIFdvcmxkIQo=" | base64 -D)" && ( echo "DECODE SUCCESS" ) || ( echo "DECODE FAILED"; exit 1; )
	test "$(shell echo "Hello, World!" | ./b64 | ./b64 -d)" = "$(shell echo "Hello, World!")" && ( echo "EN/DE CODE SUCCESS" ) || ( echo "EN/DE CODE FAILED"; exit 1; )
clean:
	rm -f *.o b64
