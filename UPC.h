#ifndef UPC_H
#define UPC_H
#include <iostream>

// Author: Derek Avery
// Version: 1
// Date: 2018/11/15

/*
 * This class represents an item represented by a Universal Product Code
 * (UPC).
 *
 * Each UPC object is uniquely identified by a 12-digit UPC code, and
 * will contain associated meta-data in String format. This class
 * contains two data fields: the UPC and meta-data strings. It
 * also contains accessors/modifiers for these fields, both
 * a default parameter-less constructor, and primary constructor
 * accepting two arguments specifying UPC and meta-data
 */
 class UPC {
  public:
    // CONSTRUCTORS //
    UPC();
    UPC(long long int&,
        std::string&);

    // ACCESSORS //
    long long int getUPC();
    std::string getData();

    // MODIFIERS //
    void setUPC(long long int&);
    void setData(std::string&);

    // FUNCTIONS //
    bool operator<(UPC&);
    bool operator==(UPC&);
    bool operator>(UPC&);
    int hash(int);

  private:
    // FIELDS //
    long long int code;
    std::string data;
};

#endif /* UPC_H */
