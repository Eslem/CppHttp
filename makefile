CC=g++
GDB=gdb

CFLAGS=-Wall --std=c++0x -O3
LIBS=-lcurl
TESTLIBS=-lcppunit

TESTS = Http.test.cpp
TEST_EXES = $(TESTS:.cpp=.out)
TEST_XMLS = $(TESTS:.cpp=.xml)

all:
	@echo Header Library, nothing to do

clean:
	rm -rf $(TEST_EXES) $(TEST_XMLS)


test:$(TEST_EXES)


%.out : %.cpp 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(TESTLIBS)
	/usr/bin/time ./$@