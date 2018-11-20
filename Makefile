all: main clean

main: Main.o Passenger.o
	g++ Main.cpp Passenger.cpp -o main

Main.o: Main.cpp LinkedList.h OrderedLinkedList.h ElementNotFoundException.h Passenger.h  
	g++ -c Main.cpp

Benchmark.o: Benchmark.cpp BST.h UPC.h
	cc -c Benchmark.cpp

clean:
	rm *.o
	rm benchmark
	rm BarcodeBSTScanner