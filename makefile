CC = g++
CFLAGS = -g -std=c++11 -Wall -I$(CURDIR)
LFLAGS = #-L/usr/class/cs107/lib -lgraph
FLGS = $(CFLAGS) $(LFLAGS)

main:
	# Build the application.
	$(CC) $(FLGS) src/*.cpp -o bin/main
	# Build the unit tests.
	$(CC) $(FLGS) test/test_driver.o `ls test/*.cpp | grep -v driver` `ls src/*.cpp | grep -v main` -o bin/test_driver

catch:
	# Build the unit test driver.
	$(CC) $(FLGS) -c test/test_driver.cpp -o test/test_driver.o

clean: 
	rm -rf bin/*

