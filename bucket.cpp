#include "bucket.h"
#include <iostream>

bucket::bucket() : currentRecords(0), maxRecords(4) {
    records = new record[maxRecords];
    next = NULL;
}

bucket::~bucket() {
    //delete all records of the bucket
    for (int i = 0; i < currentRecords; i++) {
        delete records[i].spec;
    }
    delete []records;
}