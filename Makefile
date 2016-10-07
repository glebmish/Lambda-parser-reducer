all:
	g++ Main.cpp Entities/*.cpp CLI/*.cpp MemoryManagement/*.cpp Parsing/*.cpp -o lpr.o

test:
	g++ Tests/Tests.cpp Entities/*.cpp MemoryManagement/*.cpp Parsing/*.cpp -o test.o

clean:
	rm *.o
