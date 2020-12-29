#ifndef PROJECT_1_HASHTABLE_H
#define PROJECT_1_HASHTABLE_H
#include <string>
#include "bucket.h"


using namespace std;

class hashTable {
public:
    bucket **table;
    int numBuckets, size;
    int hashFunction(string, int);
    hashTable(int);
    void insert(string, vertex*);
    vertex* search(string, string);
    ~hashTable();
};


#endif
