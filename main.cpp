#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include "hashTable.h"
#include "BF.h"


using namespace  std;

int main(int argc, char **argv){
    int worlds=0;
    myVector<string> uniqueWords(1, false);
    myVector<string> voc(100000, false);
    auto *hash = new hashTable(1000);
    FILE *fp;
    DIR *dirp2,*dirp3;
    struct dirent * entry2;
    struct dirent * entry3;
    string specs;
    char path[200],path2[200], path3[200], realPath[200], fline[100];
    if (argv[1] == nullptr){
        cout << "Please insert json files path!" << endl;
        exit(-1);
    }
    strcpy(path,argv[1]);
    strcat(path,"/");
    dirp2 = opendir(argv[1]);


    while ((entry2 = readdir(dirp2)) != NULL) {
        strcpy(path,argv[1]);

        if(entry2->d_name[0]=='.') continue;

        strcpy(path3, entry2->d_name);
        strcat(path3,"/");
        strcat(entry2->d_name,"/");
        strcat(path,entry2->d_name);

        dirp3 = opendir(path);
        while ((entry3 = readdir(dirp3)) != NULL) {
            specs="";
            strcpy(path2,path);
            strcpy(realPath,path3);

            if(entry3->d_name[0]=='.') continue;
            strcat(path2,entry3->d_name);
            strcat(realPath,entry3->d_name);

            fp = fopen(path2, "r");
            while (fgets(fline, sizeof(fline), fp))
            {
                specs+=fline;

            }
            fclose(fp);
            char* pch;
            char specs_string[specs.length()+1];
            strcpy(specs_string,specs.c_str());
            pch = strtok (specs_string," ,.-");
            while (pch != NULL)
            {
                string str;
                str+=pch;
                worlds++;

                pch = strtok (NULL, " ,.-");
            }

            //keep json file id as key for the hash table
            string key = entry3->d_name;
            key = regex_replace(key, regex(".json"), "");

            hash->insert(key, new vertex(key, realPath,specs));
        }
        closedir(dirp3);

    }
    closedir(dirp2);

    fstream fin;
    fin.open(argv[2], ios::in);
    string line, word, leftSpecId, rightSpecId, label;
    int count;
    while (getline(fin, line)){
        stringstream s(line);
        count = 0;
        while (getline(s, word, ',')) {
            count++;

            //split line by ',' and recognise leftSpecId, rightpecId and label
            switch (count) {
                case 1:
                    leftSpecId = word;
                    break;
                case 2:
                    rightSpecId = word;
                    break;
                default:
                    label = word;
            }
        }


        if (label == "1") {
            string key1 = leftSpecId, key2 = rightSpecId;
            key1 = regex_replace(key1, regex("[^0-9]"), "");
            key2 = regex_replace(key2, regex("[^0-9]"), "");


            //fix specId formats to match format in hashTable
            leftSpecId.append(".json");
            rightSpecId.append(".json");
            leftSpecId = regex_replace(leftSpecId, regex("//"), "/");
            rightSpecId = regex_replace(rightSpecId, regex("//"), "/");

            vertex *vert1, *vert2;
            vert1 = hash->search(leftSpecId, key1);
            vert2 = hash->search(rightSpecId, key2);
            //if leftSpecId and rightSpecId exist and are not already in the same list
            if (vert1 != nullptr && vert2 != nullptr && vert1->specList != vert2->specList) {
                //copy leftSpecId's list to rightSpecId's list
                vert1->copyList(vert2->specList);
            }

        }
    }
    fin.close();

    fin.open(argv[2], ios::in);
    while (getline(fin, line)){
        stringstream s(line);
        count = 0;
        while (getline(s, word, ',')) {
            count++;

            //split line by ',' and recognise leftSpecId, rightpecId and label
            switch (count) {
                case 1:
                    leftSpecId = word;
                    break;
                case 2:
                    rightSpecId = word;
                    break;
                default:
                    label = word;
            }
        }

        if(label == "0") {
            string key1 = leftSpecId, key2 = rightSpecId;
            key1 = regex_replace(key1, regex("[^0-9]"), "");
            key2 = regex_replace(key2, regex("[^0-9]"), "");


            //fix specId formats to match format in hashTable
            leftSpecId.append(".json");
            rightSpecId.append(".json");
            leftSpecId = regex_replace(leftSpecId, regex("//"), "/");
            rightSpecId = regex_replace(rightSpecId, regex("//"), "/");

            vertex *vert1, *vert2;
            vert1 = hash->search(leftSpecId, key1);
            vert2 = hash->search(rightSpecId, key2);

            if (vert1 != nullptr && vert2 != nullptr) {
                list *list1, *list2;
                list1 = vert1->specList;
                list2 = vert2->specList;
                if(list1->negList != list2->negList) {
                    list1->copyNegList(list2->negList);
                }
            }
        }
    }
    fin.close();

    //print every vertex's list in the hashable
    cout << "All positive connections\n" << endl;
    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                temp->records[j].spec->printList();
            }
            temp = temp->next;
        }
    }

    cout << "\n\nAll negative connections\n" << endl;
    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                temp->records[j].spec->specList->printNegList();
            }
            temp = temp->next;
        }
    }

    cout<<worlds<<endl;
    int numOfUpdates=5;
    BF* bf = new BF(worlds,numOfUpdates);

    dirp2 = opendir(argv[1]);
    while ((entry2 = readdir(dirp2)) != NULL) {
        strcpy(path,argv[1]);
        if(entry2->d_name[0]=='.') continue;

        strcpy(path3, entry2->d_name);
        strcat(path3,"/");
        strcat(entry2->d_name,"/");
        strcat(path,entry2->d_name);

        dirp3 = opendir(path);
        while ((entry3 = readdir(dirp3)) != NULL) {
            specs="";
            strcpy(path2,path);
            strcpy(realPath,path3);

            if(entry3->d_name[0]=='.') continue;
            strcat(path2,entry3->d_name);
            strcat(realPath,entry3->d_name);

            fp = fopen(path2, "r");
            while (fgets(fline, sizeof(fline), fp))
            {
                specs+=fline;
            }
            fclose(fp);
            char* pch;
            char specs_string[specs.length()+1];
            strcpy(specs_string,specs.c_str());
            pch = strtok (specs_string," ,.-");
            while (pch != NULL)
            {
                string str;
                str+=pch;
                if(!bf->find(pch))
                {
                    voc.pushBack(str);
                }
                bf->insert(pch);

                pch = strtok (NULL, " ,.-");
            }
        }
        closedir(dirp3);
    }
    closedir(dirp2);




    if(bf->search("tsikitas")) cout << "TRUE" << endl;
    else cout<<"FALSE"<<endl;
    if(bf->search("second")) cout << "TRUE" << endl;
    else cout<<"FALSE"<<endl;
    if(bf->search("resolution")) cout << "TRUE" << endl;
    else cout<<"FALSE"<<endl;

    delete hash;
    return 0;
}
