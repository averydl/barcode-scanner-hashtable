#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "LinkedList.h"


template <class T>
class HashTable {
    LinkedList<T>* table;      // hash table with linked lists of T objects
    int size;                   // size of the hash table
    
public:
    // CONSTRUCTOR //
    HashTable(int _size=1000) : size(_size) {
        table = new LinkedList<T>[size];
    }
    
    // DESTRUCTOR //
    ~HashTable() {
        delete[] table;
    }
    
    /*
     * insert the specified object
     * into the hash table
     */
    void insert(T& item) {
        table[item.hash(size)].insertFirst(item);
    }
    
    /*
     * remove the specified object
     * from the hash table
     */
    void remove(T& item) {
        table[item.hash(size)].deleteNode(item);
    }
    
    /*
     * find and return the specified object
     * from the hash table
     */
    T search(T& item) {
        return table[item.hash(size)].search(item);
    }
    
//    /*
//     * print the full contents of the
//     * hash table to standard out
//     */
//    void print() {
//        for(int i = 0; i < size; i++) {
//            std::cout << table[i] << "\n";
//        }
//    }
};

//int main() {
//    HashTable<UPC>* ht = new HashTable<UPC>(20);
//    std::string input = "123958295844";
//    long long upc_code = std::stoll(input);
//    UPC* upc1 = new UPC();
//    upc1 -> setUPC(upc_code);
//    ht->print();
//}

#endif /* HASHTABLE_H */


