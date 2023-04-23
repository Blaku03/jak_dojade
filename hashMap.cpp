#include "hashMap.h"

unsigned int hashMap::hash(vstring key) const {

    const unsigned int fnvPrime = 0x811C9DC5;
    unsigned int hash = 0;
    for (int i = 0; i < key.size(); i++) {
        hash *= fnvPrime;
        hash ^= (unsigned int) key[i];
    }

    return hash % sizeOfTable;
}

void hashMap::insert(const vstring &key, int value) {
    numberOfElements++;
    unsigned int index = hash(key);

    pair<vstring, int> newPair(key, value);
    mainTable.i_element(index, true).push_back(newPair);
}

int hashMap::get(const vstring &key) {
    unsigned int index = hash(key);

    for (int i = 0; i < mainTable.i_element(index, true).number_of_nodes; i++) {
        if (mainTable.i_element(index, true)[i]->first == key) {
            return mainTable.i_element(index, true)[i]->second;
        }
    }

    return -sizeOfTable;
}

void hashMap::remove(const vstring &key) {
    unsigned int index = hash(key);

    for (int i = 0; i < mainTable.i_element(index, true).number_of_nodes; i++) {

        if (mainTable.i_element(index, true)[i]->first == key) {
            mainTable.i_element(index, true).pop_index(i);
            numberOfElements--;
            return;
        }
    }
}

bool hashMap::contains(const vstring &key) {
    unsigned int index = hash(key);

    for (int i = 0; i < mainTable.i_element(index, true).number_of_nodes; i++) {
        if (mainTable.i_element(index, true)[i]->first == key) {
            return true;
        }
    }

    return false;
}

unsigned int hashMap::size() const {
    return numberOfElements;
}
