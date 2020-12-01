#ifndef PROJECT_1_LIST_H
#define PROJECT_1_LIST_H

#include <string>
#include "negativeList.h"

using namespace std;

class vertex;

struct node {
    vertex *spec = NULL;
    node *next = NULL, *prev = NULL;
};

class list {
public:
    node *head, *tail;
    negativeList *negList;
    list();
    int insert(vertex*);
    vertex* pop();
    int copyNegList(negativeList*);
    ~list();
};


#endif
