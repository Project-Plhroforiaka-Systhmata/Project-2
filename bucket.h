#ifndef PROJECT_1_BUCKET_H
#define PROJECT_1_BUCKET_H
#include <string>
#include "vertex.h"

using namespace std;

struct record {
    vertex *spec;
};

class bucket {
public:
    int currentRecords, maxRecords;
    record *records;
    bucket *next;
    bucket();
    ~bucket();
};


#endif
