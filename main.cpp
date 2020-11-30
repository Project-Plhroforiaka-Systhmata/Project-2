#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <filesystem>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include "hashTable.h"


using namespace  std;

int main(int argc, char **argv){


    auto *hash = new hashTable(1000);
    char ch;
    FILE *fp;
    DIR *dirp2,*dirp3;
    struct dirent * entry2;
    struct dirent * entry3;
    string specs;
    char path[200],path2[200], path3[200], realPath[200];
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
            while ((ch = fgetc(fp)) != EOF)
            {
                specs+=ch;
            }
            fclose(fp);
            hash->insert(realPath,new vertex(realPath,specs));
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


        if(label == "1"){

            //fix specId formats to match format in hashTable
            leftSpecId.append(".json");
            rightSpecId.append(".json");
            leftSpecId = regex_replace(leftSpecId, regex("//"), "/");
            rightSpecId = regex_replace(rightSpecId, regex("//"), "/");

            vertex *vert1, *vert2;
            vert1 = hash->search(leftSpecId);
            vert2 = hash->search(rightSpecId);

            //if leftSpecId and rightSpecId exist and are not already in the same list
            if(vert1 != nullptr && vert2 != nullptr && vert1->specList != vert2->specList) {
                //copy leftSpecId's list to rightSpecId's list
                vert1->copyList(vert2->specList);
            }
        }
    }

    //print every vertex's list in the hashable
    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                temp->records[j].spec->printList();
            }
            temp = temp->next;
        }
    }

    delete hash;
    return 0;
}
