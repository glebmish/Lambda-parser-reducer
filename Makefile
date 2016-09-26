all:
	g++ Main.cpp Entities/*.cpp Calculation/*.cpp MemoryManagement/*.cpp Parsing/*.cpp Tests/*.cpp Logger/*.cpp -o lbr.out

