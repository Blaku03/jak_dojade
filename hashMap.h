#ifndef MY_STL_HASHMAP_H
#define MY_STL_HASHMAP_H

#include "linkedList.hxx"
#include "vstring.h"
#include "vector.hxx"
#include "pair.hxx"

using my_stl::linkedList;
using my_stl::vstring;
using my_stl::vector;
using my_stl::pair;

class hashMap {

    int sizeOfTable = 1'000'000'0;
    unsigned int numberOfElements = 0;
    vector<linkedList<pair<vstring, int>>> mainTable;

public:

    hashMap() : mainTable(sizeOfTable) {}

    ~hashMap() = default;

    [[nodiscard]] unsigned int hash(vstring key) const;

    void insert(const vstring &key, int value);

    int get(const vstring &key);

    void remove(const vstring &key);

    bool contains(const vstring &key);

    [[nodiscard]] unsigned int size() const;
};


#endif //MY_STL_HASHMAP_H
