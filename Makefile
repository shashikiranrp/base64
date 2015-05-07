CLANG_CXX = $(shell which clang++)

C++11=$(CLANG_CXX) -std=c++11 -stdlib=libc++ -Weverything -Wno-c++98-compat

all: clean run

compile: 
	$(C++11) -c -I. *.cpp 

link: compile
	$(C++11) *.o -o b64

test: link
	@test "$(shell echo "Hello, World!" | ./b64)" = "$(shell echo "Hello, World!" | base64)" && ( echo "ENCODE SUCCESS" ) || ( echo "ENCODE FAILED"; exit 1; )
	@test "$(shell echo "SGVsbG8sIFdvcmxkIQo=" | ./b64 -d)" = "$(shell echo "SGVsbG8sIFdvcmxkIQo=" | base64 -D)" && ( echo "DECODE SUCCESS" ) || ( echo "DECODE FAILED"; exit 1; )
	@test "$(shell echo "Hello, World!" | ./b64 | ./b64 -d)" = "$(shell echo "Hello, World!")" && ( echo "EN/DE CODE SUCCESS" ) || ( echo "EN/DE CODE FAILED"; exit 1; )
	@test "$(shell shasum -a 256 -b ./b64 | cut -d' ' -f1)" = "$(shell ./b64 -i ./b64 | ./b64 -d | shasum -a 256 -b | cut -d' ' -f1)" && ( echo "BIN EN/DE CODE SUCCESS" ) || ( echo "BIN EN/DE CODE FAILED"; exit 1; )

run: test
	@echo "***********************************"
	@echo "******** BUILD SUCCESSFULL ********"
	@echo "***********************************"

clean:
	@echo "cleaning old build"
	rm -f *.o b64
