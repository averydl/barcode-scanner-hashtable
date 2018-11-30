#include "UPC.h"
#include <iostream>

// Author: Derek Avery
// Version: 1
// Date: 2018/11/15

/*
 * This class provides the implementation of the
 * UPC class, which represents an item with a Universal
 * Product Code (UPC) and its corresponding meta-data.
 * This class can be used as a wrapper for UPC codes
 * and their corresponding data as obtained from a
 * .csv file of UPC's and item descriptions.
 */

// CONSTRUCTORS //

UPC::UPC(){}
UPC::UPC(long long int& _code, std::string& _data) : code(_code), data(_data){}

// ACCESSORS //

long long int UPC::getUPC() {
  return code;
}

std::string UPC::getData() {
  return data;
}

// MODIFIERS //

void UPC::setUPC(long long int& _code) {
  code = _code;
}

void UPC::setData(std::string& _data) {
  data = _data;
}

// FUNCTIONS //

/*
 * Override less-than operator; returns
 * true if the @param upc argument has a
 * UPC code lower than this instance
 */
bool UPC::operator<(UPC& upc) {
  return code < upc.getUPC();
}

/*
 * Override the equals operator; returns true
 * if the @param upc argument has the same
 * UPC code as this instance
 */
bool UPC::operator==(UPC& upc) {
  return upc.getUPC() == code;
}

/*
 * Override the greater-than operator; returns
 * true if the @param upc argument has a higher
 * UPC code than this instance
 */
bool UPC::operator>(UPC& upc) {
  return code > upc.getUPC();
}

/*
 * Return a hash code for this UPC
 * object, evaluated relative to the
 * UPC code of this instance, and the
 * @param table_size
 */
int UPC::hash(int table_size) {
    return (code / 7) % table_size;
}
