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
    string stopwords[194], specialChars[34];
    fstream fin;
    fin.open("stopwords", ios::in);
    string line;
    int ind = 0;
    while (getline(fin, line)){
        stopwords[ind++] = line;
    }
    fin.close();

    fin.open("specialChars", ios::in);
    ind = 0;
    while (getline(fin, line)){
        specialChars[ind++] = line;
    }
    fin.close();

    int worlds=0;
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

    fin.open(argv[2], ios::in);
    string word, leftSpecId, rightSpecId, label;
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
        cout<<entry2->d_name<<endl;

        dirp3 = opendir(path);
        vertex* tmpvertex;
        while ((entry3 = readdir(dirp3)) != NULL) {
            specs="";
            strcpy(path2,path);
            strcpy(realPath,path3);
            if(entry3->d_name[0]=='.') continue;

            strcat(path2,entry3->d_name);
            strcat(realPath,entry3->d_name);


            string key = entry3->d_name;
            key = regex_replace(key, regex(".json"), "");
            //cout<<key<<endl;
            
            
        
            string searchPath;
            searchPath+=realPath;
            //cout<<searchPath<<endl;
            tmpvertex=hash->search(searchPath,key);

            fp = fopen(path2, "r");
            while (fgets(fline, sizeof(fline), fp))
            {
                int flineindex=-1;
                for(int i=0;i<strlen(fline);i++)
                {
                    if(fline[i]=='"' && fline[i+1]==':')
                    {
                        flineindex=i+1;
                        
                        break;
                    }
                }
                strcpy(fline,&fline[flineindex+1]);
                specs+=fline;
                
            }
            fclose(fp);
            int index=0;
            int vocIndex=-1;
            int flag=0, flag1 = 0;
            char* pch;
            char specs_string[specs.length()+1];
            strcpy(specs_string,specs.c_str());
            pch = strtok (specs_string," ");
            //cout<<searchPath<<endl;
            while (pch != NULL)
            {
                flag=0;
                flag1 = 0;
                string str;
                str+=pch;
                string chars;

                transform(str.begin(), str.end(), str.begin(), ::tolower);

                for(int i = 0; i < 34; i++) {
                    chars += specialChars[i];
                }

                str.erase(remove_if(str.begin(), str.end(), [&chars](const char& c) {
                    return chars.find(c) != string::npos;
                }), str.end());


                for(int i = 0; i < 195; i++) {
                    if(str == stopwords[i]){
                        flag1 = 1;
                        break;
                    }
                }

                if(flag1 || str == "\n") {
                    pch = strtok(NULL, " ");
                    continue;
                }

                if(!bf->find(pch))
                {
                    
                    index=voc.pushBack(str);
                    tmpvertex->jsonWords->pushBack(1,index);
                    //uniqueWords.pushBack(str,index);
                }
                else
                {
                    for(int i=0;i<voc.size;i++)
                    {
                        if(voc.buffer[i]==str)
                        {
                            flag=1;
                            vocIndex=i;
                            break;
                        }
                    }             
                    if(flag==0)
                    {
                        index=voc.pushBack(str);
                        tmpvertex->jsonWords->pushBack(1,index);
                    }
                    else
                    {
                        int flagjson=0;
                        for(int j=0;j<tmpvertex->jsonWords->size;j++)
                        {
                            if(tmpvertex->jsonWords->sBuffer[j][0]==vocIndex)
                            {
                                flagjson=1;
                                tmpvertex->jsonWords->sBuffer[j][1]++;
                            }
                            
                        }
                        if(flagjson==0)
                        {
                            tmpvertex->jsonWords->pushBack(1,vocIndex);
                        }
                    }
                    
                }
                
                
                
                bf->insert(pch);
                
                pch = strtok (NULL, " ");
            }
        }
        closedir(dirp3);
    }
    closedir(dirp2);

    


    /*if(bf->search("tsikitas")) cout << "TRUE" << endl;
    else cout<<"FALSE"<<endl;
    if(bf->search("second")) cout << "TRUE" << endl;
    else cout<<"FALSE"<<endl;
    if(bf->search("resolution")) cout << "TRUE" << endl;
    else cout<<"FALSE"<<endl;*/

    
    
    


    delete hash;
    return 0;
}
