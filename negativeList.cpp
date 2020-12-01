#include "negativeList.h"

negativeList::negativeList() {
    head = NULL;
    tail = NULL;
}

int negativeList::insert(list *name) {
    //create new node to insert
    lnode *newNode = new lnode;
    newNode->spec = name;

    if(head == NULL) {
        head = newNode;
        tail = newNode;
    }else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    return 0;
}

list *negativeList::pop() {
    if(head == NULL){
        return NULL;
    }
    list *returnList;
    if(head == tail){
        returnList = head->spec;
        delete head;
        head = NULL;
        tail = NULL;
        return returnList;
    }
    returnList = head->spec;
    head = head->next;
    delete head->prev;
    head->prev = NULL;
    return returnList;
}

negativeList::~negativeList() {
    lnode *temp;
    temp = head;
    while(temp != NULL){
        head = temp->next;
        delete temp;
        temp = head;
    }
}
