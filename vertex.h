#ifndef PROJECT_1_VERTEX_H
#define PROJECT_1_VERTEX_H
#include <string>
#include "list.h"
#include "vector.h"

using namespace std;

class vertex {
public:
    int printed;
    string spec, itemSpecs;
    myVector<int> *jsonWords;
    list *specList;
    vertex(string, string);
    int copyList(list*);
    void printList();
    ~vertex();
};


#endif
