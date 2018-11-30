all: BSTScanner ArrayScanner Benchmark

#
# Executable file dependencies
#
Benchmark : Benchmark.o UPC.o 
	g++ Benchmark.o UPC.o -o Benchmark

BSTScanner : BarcodeBSTScanner.o UPC.o
	g++ BarcodeBSTScanner.o UPC.o -o BSTScanner

ArrayScanner : BarcodeArrayScanner.o UPC.o
	g++ BarcodeArrayScanner.o UPC.o -o ArrayScanner

#
# Object file dependencies
#

Benchmark.o : Benchmark.cpp UPC.h SearchArray.h HashTable.h LinkedList.h
	gcc -c Benchmark.cpp

UPC.o : UPC.cpp UPC.h
	gcc -c UPC.cpp

BarcodeArrayScanner.o : BarcodeArrayScanner.cpp UPC.h BST.h 
	gcc -c BarcodeArrayScanner.cpp

BarcodeBSTScanner.o : BarcodeBSTScanner.cpp UPC.h BST.h 
	gcc -c BarcodeBSTScanner.cpp

#
# make clean commands
#
clean :
	rm Benchmark BSTScanner ArrayScanner *.o Benchmark.txt
