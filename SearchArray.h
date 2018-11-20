#include "UPC.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*
 * This template class uses a dynamically allocated array
 * to store objects of the specified type T, and allows addition
 * and search functions to add or find objects stored in the array
 */
template <class T>
class SearchArray {
  int size;	  // size of the storage array
  T* items;	  // array to store elements
  int count;	// number of items in the array

  public:
    SearchArray(int _size=1000) : size(_size), count(0) {
      items = new T[_size];
    }

    /*
     * This function adds a UPC object to
     * the @param items array
     */
     void add(T& item) {
    	if(count > size/2) {
    		upsize();
    	}
    	items[count] = item;
      count++;
    }

    /*
     * This function will double the capacity of the
     * @param items array and copy existing elements over
     * to the new upsized array. This function should be
     * called to accommodate more UPC elements as needed
     */
     void upsize() {
    	// create enlarged array (double size)
    	T* copy = new T[size*2];

    	// copy over all UPC's to new array element-by-element
        for(int i = 0; i < size; i++) {
            copy[i] = items[i];
        }

      // reassign @param items to the new copy
    	// and free memory from the old array
    	size *= 2;
    	delete[] items;
    	items = copy;
    }

    /*
     * This function removes all items from the
     * @param items array and frees its memory
     */
    void empty() {
    	delete[] items;
    	items = new T[size];
    	count = 0;
    }

    /*
     * This function returns the specified item if
     * it is found in the @param items array, or
     * throws an exception otherwise
     */
    T search(T& item) {
      int index = 0;
      while(index < count) {
        if(items[index] == item) {
          return items[index];
        }
        index++;
      }
      throw std::exception();
    }

    /*
     * Return the element at the specified index
     * or throw an exception if it is out of bounds
     */
     T get(int index) {
       if(index > count-1) {
         throw std::exception();
       } else {
         return items[index];
       }
     }

    /*
     * Returns the number of items in the
     * @param items array
     */
     int getCount() {
       return count;
     }
};
