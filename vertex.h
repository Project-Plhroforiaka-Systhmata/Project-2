#ifndef PROJECT_1_VERTEX_H
#define PROJECT_1_VERTEX_H
#include <string>
#include "list.h"

using namespace std;

class vertex {
public:
    int printed;
    string spec, itemSpecs;
    list *specList;
    vertex(string, string);
    int copyList(list*);
    void printList();
    ~vertex();
};


#endif
