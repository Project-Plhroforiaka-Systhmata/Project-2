#include <sstream>
#include <iostream>
#include "hashTable.h"

hashTable::hashTable(int buckets) : numBuckets(buckets) {
    table = new bucket*[numBuckets];
    //create the requested number of buckets
    for (int i = 0; i < numBuckets; i++) {
        table[i] = new bucket;
    }
}

int hashTable::hashFunction(string key, int buckets) {
    stringstream num(key);
    int hashKey;
    num >> hashKey;
    return hashKey % buckets;
}

void hashTable::insert(string key, vertex *vertSpec) {
    int index = hashFunction(key, numBuckets);
    bucket *temp = table[index];

    //go to last bucket in the list
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->records[temp->currentRecords].spec = vertSpec;       //change record's data
    temp->currentRecords++;         //increase current records counter
    if (temp->currentRecords == temp->maxRecords) {
        temp->next = new bucket;

    }
}

vertex* hashTable::search(string searchStr) {
    int index = hashFunction(searchStr, numBuckets);
    bucket *temp = table[index];
    while(temp != NULL) {
        for(int j = 0; j < temp->currentRecords; j++){
            //operate search
            if (temp->records[j].spec->spec == searchStr)
                return temp->records[j].spec;
        }
        temp = temp->next;
    }
    return NULL;
}

hashTable::~hashTable() {
    //delete all buckets
    for (int i = 0; i < numBuckets; i++) {
        bucket *temp = table[i];
        bucket *temp2;
        while(temp != NULL) {
            temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }
    delete []table;
    table = nullptr;
}
