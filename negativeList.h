#ifndef PROJECT_2_NEGATIVELIST_H
#define PROJECT_2_NEGATIVELIST_H

#include <string>

using namespace std;

class list;

struct lnode {
    list *spec = NULL;
    lnode *next = NULL, *prev = NULL;
};

class negativeList {
public:
    lnode *head, *tail;
    negativeList();
    int insert(list*);
    list* pop();
    ~negativeList();
};


#endif
