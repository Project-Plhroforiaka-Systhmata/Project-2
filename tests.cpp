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
}

void test_insertlist(void){
    list *mylist = new list();
    mylist->insert(new vertex("lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal"));
    TEST_ASSERT(mylist->head != nullptr);
    TEST_ASSERT(mylist->head == mylist->tail);
    TEST_ASSERT(mylist->head->spec->spec == "lalalalalalalalallalalalalalallalalalalalalallal");
    
}

void test_poplist(void){
    list *mylist = new list();
    mylist->insert(new vertex("lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal"));
    vertex *tmp = mylist->pop();
    TEST_ASSERT(tmp != nullptr);
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    mylist->insert(new vertex("lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal"));
    mylist->insert(new vertex("lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal","lalalalalalalalallalalalalalallalalalalalalallal"));
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
}


void test_destroylist(void){
    list *tmp = new list();
    tmp->insert(new vertex("test","test","test"));
    delete tmp;
    TEST_ASSERT(sizeof(tmp) == 8);
}


void test_createhash(void){
    hashTable *table = new hashTable(150);
    TEST_ASSERT(table->numBuckets == 150);
    table = new hashTable(9999999);
    TEST_ASSERT(table->numBuckets == 9999999);
    table = new hashTable(0);
    TEST_ASSERT(table->numBuckets == 0);
}

void test_inserthash(void){
    hashTable *table = new hashTable(300);
    table->insert("test",new vertex("test","test","test"));
    table->insert("test1",new vertex("test1","test1","test1"));
    table->insert("test2",new vertex("test2","test2","test2"));
    table->insert("SDXCV",new vertex("SDXCV","SDXCV","SDXCV"));
    table->insert("lala",new vertex("lala","lala","lala"));
    TEST_ASSERT(table->search("test","test") != nullptr);
    TEST_ASSERT(table->search("test1","test1") != nullptr);
    TEST_ASSERT(table->search("test2","test2") != nullptr);
    TEST_ASSERT(table->search("sdfsdfsdf","sdfsdfsdf") == nullptr);
    TEST_ASSERT(table->search("lala","lala") != nullptr);
    //overflow test below
    long int before = time(0);
    long int now = 0;
    while (true){
        table->insert("test",new vertex("test1","test","test"));
        now = time(0);
        if ((now - before) > 5){
            break;
        }
    }
}



void test_vertexcopy(void){
    vertex *one = new vertex("test","test","test");
    list *tmp = new list();
    tmp->insert(new vertex("1","1","1"));
    tmp->insert(new vertex("2","2","2"));
    tmp->insert(new vertex("3","3","3"));
    one->specList = tmp;
    vertex *two = new vertex("test","test","test");
    tmp = new list();
    tmp->insert(new vertex("4","4","4"));
    tmp->insert(new vertex("5","5","5"));
    tmp->insert(new vertex("6","6","6"));
    two->specList = tmp;
    two->copyList(one->specList);
    TEST_ASSERT(one->specList->head != nullptr);
    int counter = 0;
    while (counter <= 5){
        vertex *test = one->specList->pop();
        TEST_ASSERT(test != nullptr);
        if (counter == 0){
            TEST_ASSERT(test->spec == "1");
        }else if(counter == 1)
        {
            TEST_ASSERT(test->spec == "2");
        }else if(counter == 2)
        {
            TEST_ASSERT(test->spec == "3");
        }else if(counter == 3)
        {
            TEST_ASSERT(test->spec == "4");
        }else if(counter == 4)
        {
            TEST_ASSERT(test->spec == "5");
        }else if(counter == 5)
        {
            TEST_ASSERT(test->spec == "6");
        }
        counter++;
        
    } 
}

void test_destroyhash(void){
    hashTable *test = new hashTable(9999);
    delete test;
    TEST_ASSERT(test->table == nullptr);
    
}

void test_search(void){
    hashTable *test = new hashTable(4);
    test->insert("test",new vertex("test","test","test"));
    test->insert("test",new vertex("test","test","test"));
    test->insert("test",new vertex("test","test","test"));
    test->insert("test",new vertex("test","test","test"));
    test->insert("test",new vertex("test","test","test"));
    test->insert("test",new vertex("test","test","test"));
    test->insert("test",new vertex("test","test","test"));
    test->insert("test1",new vertex("test1","test","test"));
    
    TEST_ASSERT(test->search("test","test") != nullptr);
    TEST_ASSERT(test->search("xcxcv","xcxcv") == nullptr);
}

void test_BF_create(){
    BF *ligma;
    for (int i = -1; i < 10000; i++){
        ligma = new BF(11111,i);
    }
}

void test_BF_insert(){
    BF *ligma = new BF(11111,10);
    for (int i = -1; i < 10000; i++){
        ligma->insert("lalalalallalalalalal");
    }
}

void test_BF_search(char *str){
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
}

void vector_test_insert(){
    myVector<int> *vec = new myVector<int>(150,false);
    for (int i = 0; i < 100000; i++){
        vec->pushBack(i,true);
    }
    TEST_ASSERT(vec->size == 100000);

    myVector<int> *vec1 = new myVector<int>(150,true);
    for (int i = 0; i < 100001; i++){
        vec1->pushBack(i,true);
    }
    TEST_ASSERT(vec1->size == 100001);
}

void test_createnlist(void){
    negativeList *mylist = new negativeList();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
}

void test_insertnlist(void){
    negativeList *mylist = new negativeList();
    mylist->insert(new list());
    TEST_ASSERT(mylist->head != nullptr);
    TEST_ASSERT(mylist->head == mylist->tail);
    
}

void test_popnlist(void){
    negativeList *mylist = new negativeList();
    mylist->insert(new list());
    mylist->pop();
    TEST_ASSERT(mylist->head == nullptr);
    TEST_ASSERT(mylist->tail == nullptr);
    mylist->insert(new list());
    mylist->insert(new list());
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
}


void test_destroynlist(void){
    negativeList *tmp = new negativeList();
    tmp->insert(new list());
    delete tmp;
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
    {"Hash Table Destroy",test_destroyhash},
    {"Vertex List Copy",test_vertexcopy},
    {"Bloom Filter Create",test_BF_create},
    {"Bloom Filter Insert",test_BF_insert},
    {"Bloom Filter Check Bit is 1",test_BF_insert},
    {"Vector Insert",test_vertexcopy},
    {"negativelist_create",test_createnlist},
    {"negativelist_insert",test_insertnlist},
    {"negativelist_pop",test_popnlist},
    {"negativelist_destroy",test_destroynlist},
    {nullptr,nullptr},
};
