#include "list.h"
#include "acutest.h"
#include "hashTable.h"
#include "vertex.h"
#include "string.h"
#include "vector.h"
#include "BF.h"
#include <ctime>
#include <iostream>


void test_createlist(void){
    list *mylist = new list();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    delete mylist;
}

void test_insertlist(void){
    list *mylist = new list();
    vertex *tmp = new vertex("lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal");
    mylist->insert(tmp);
    TEST_ASSERT(mylist->head != nullptr);
    TEST_ASSERT(mylist->head == mylist->tail);
    TEST_ASSERT(mylist->head->spec->spec == "lalalalalalalalallalalalalalallalalalalalalallal");
    delete tmp;
    delete mylist;
    
    
}

void test_poplist(void){
    vertex *tmp1 = new vertex("lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal");

    list *mylist = new list();
    mylist->insert(tmp1);
    vertex *tmp = mylist->pop();
    TEST_ASSERT(tmp != nullptr);
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    mylist->insert(tmp);
    mylist->insert(tmp);
    mylist->pop();
    TEST_ASSERT(mylist->head == mylist->tail);
    mylist->pop();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    mylist->pop();
    mylist->pop();
    mylist->pop();
    mylist->pop();
    mylist->pop();
    mylist->pop();
    delete mylist;
    delete tmp1;
}


void test_destroylist(void){
    list *tmp = new list();
    vertex *tmp1 = new vertex("test","test");
    tmp->insert(tmp1);
    delete tmp;
    TEST_ASSERT(sizeof(tmp) == 8);
    delete tmp1;
}


void test_createhash(void){
    hashTable *table = new hashTable(150);
    TEST_ASSERT(table->numBuckets == 150);
    delete table;
    table = new hashTable(0);
    TEST_ASSERT(table->numBuckets == 0);
    delete table;
}

void test_inserthash(void){
    hashTable *table = new hashTable(300);
    table->insert("test1",new vertex("test1","test1"));
    table->insert("test2",new vertex("test2","test2"));
    table->insert("SDXCV789",new vertex("SDXCV789","SDXCV789"));
    table->insert("lala789",new vertex("lala789","lala789"));
    TEST_ASSERT(table->search("test1") != nullptr);
    TEST_ASSERT(table->search("test2") != nullptr);
    TEST_ASSERT(table->search("sdfsdfsdf") == nullptr);
    TEST_ASSERT(table->search("lala789") != nullptr);
    //overflow test below
    long int before = time(0);
    long int now = 0;
    while (true){
        table->insert("test666",new vertex("test666","test666"));
        now = time(0);
        if ((now - before) > 5){
            break;
        }
    }
    delete table;
}


void test_search(void){
    hashTable *test = new hashTable(4);
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    test->insert("test69",new vertex("test69","test69"));
    
    TEST_ASSERT(test->search("test69") != nullptr);
    TEST_ASSERT(test->search("xcxcv") == nullptr);
    delete test;
}

void test_BF_create(){
    
    for (int i = -1; i < 10000; i++){
        BF *ligma = new BF(11111,i);
        delete ligma;
    }
}

void test_BF_insert(){
    BF *ligma = new BF(11111,10);
    for (int i = -1; i < 10000; i++){
        ligma->insert("lalalalallalalalalal");
    }
    delete ligma;
}

void test_BF_search(){
    char str[20] = "lala";
    BF *ligma = new BF(11111,10);
    ligma->insert(str);
    TEST_ASSERT(ligma->search(str));

    for (int i = -1; i < 10000; i++){
        ligma->insert("lalalalallalalalalal");
    }
    int allones = 1;
    for (int i = 0 ; i < ligma->size; i++){
        if (ligma->array[i]==0){
            allones = 0;
            break;
        }
    }
    TEST_ASSERT(allones == 0);
    delete ligma;
}

void vector_test_insert(){
    myVector<int> *vec = new myVector<int>(150,false);
    for (int i = 0; i < 10000; i++){
        vec->pushBack(i,true);
    }
    TEST_ASSERT(vec->size == 10000);
    delete vec;
    myVector<int> *vec1 = new myVector<int>(150,true);
    for (int i = 0; i < 10001; i++){
        vec1->pushBack(i,true);
    }
    TEST_ASSERT(vec1->size == 10001);
    delete vec1;
}

void test_createnlist(void){
    negativeList *mylist = new negativeList();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    delete mylist;
}

void test_insertnlist(void){
    negativeList *mylist = new negativeList();
    list *mlist = new list();
    mylist->insert(mlist);
    TEST_ASSERT(mylist->head != nullptr);
    TEST_ASSERT(mylist->head == mylist->tail);
    
    delete mylist;
    delete mlist;
    
}

void test_popnlist(void){
    negativeList *mylist = new negativeList();
    list *mlist = new list();
    list *mlist1 = new list();
    list *mlist2 = new list();
    mylist->insert(mlist);
    mylist->pop();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    mylist->insert(mlist1);
    mylist->insert(mlist2);
    mylist->pop();
    TEST_ASSERT(mylist->head == mylist->tail);
    mylist->pop();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    mylist->pop();
    mylist->pop();
    mylist->pop();
    mylist->pop();
    mylist->pop();
    mylist->pop();
    delete mylist;
    delete mlist;
    delete mlist1;
    delete mlist2;
}


void test_destroynlist(void){
    negativeList *tmp = new negativeList();
    list *mlist = new list();
    tmp->insert(mlist);
    delete tmp;
    delete mlist;
    TEST_ASSERT(sizeof(tmp) == 8);
}


TEST_LIST = {
    {"list_create",test_createlist},
    {"list_insert",test_insertlist},
    {"list_pop",test_poplist},
    {"list_destroy",test_destroylist},
    {"Hash Table Create",test_createhash},
    {"Hash Table Insert",test_inserthash},
    {"Hash Table Search",test_search},
    {"Bloom Filter Create",test_BF_create},
    {"Bloom Filter Insert",test_BF_insert},
    {"Bloom Filter Check Bit is 1",test_BF_search},
    {"Vector Insert",vector_test_insert},
    {"negativelist_create",test_createnlist},
    {"negativelist_insert",test_insertnlist},
    {"negativelist_pop",test_popnlist},
    {"negativelist_destroy",test_destroynlist}, 
    {nullptr,nullptr},
};
