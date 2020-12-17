#include "list.h"
#include "vertex.h"
#include <iostream>
#include <unistd.h>

using namespace std;

list::list(): printed(0) {
    head = NULL;
    tail = NULL;
    negList = new negativeList;
    negList->insert(this);
}

int list::insert(vertex *name) {
    //create new node to insert
    node *newNode = new node;
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

vertex* list::pop() {
    if(head == NULL){
        return NULL;
    }
    vertex *returnVert;
    if(head == tail){
        returnVert = head->spec;
        delete head;
        head = NULL;
        tail = NULL;
        return returnVert;
    }
    returnVert = head->spec;
    head = head->next;
    delete head->prev;
    head->prev = NULL;
    return returnVert;
}

int list::copyNegList(negativeList *cpList) {
    if(negList->head == NULL){
        return 1;
    }
    //keep specList address
    negativeList *tempList = negList;
    list *temp;
    temp = tempList->pop();
    while(temp != NULL){
        cpList->insert(temp);       //insert popped vertex to cpList
        temp->negList = cpList;    //change popped vertex's specList pointer to cpList
        temp = tempList->pop();     //pop next vertex
    }
    delete tempList;    //delete the empty tempList
    return 0;
}

void list::printNegList() {
    if(printed) return;
    node *temp = head;
    while(temp != NULL) {
        lnode *temp2 = negList->head;
        while (temp2 != NULL){
            if(temp2->spec == this || temp2->spec->printed){
                temp2 = temp2->next;
                continue;
            }
            node *temp3 = temp2->spec->head;
            while(temp3 != NULL){
                cout << temp->spec->spec << " " << temp3->spec->spec << endl;
                temp3 = temp3->next;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    printed = 1;
}

list::~list() {
    node *temp;
    temp = head;
    while(temp != NULL){
        head = temp->next;
        delete temp;
        temp = head;
    }
    if (negList != NULL){
        lnode *temp;
        temp = negList->head;
        while(temp != NULL){
            //change all other vertexes specLists in this list to point to NULL
            if(temp->spec != this) {
                temp->spec->negList = NULL;
            }
            temp = temp->next;
        }
        delete negList;    //delete the list
    }
}


