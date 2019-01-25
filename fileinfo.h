#ifndef FILEINFO_H
#define FILEINFO_H
#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<cstring>

#define ERROR -1
#define OK    0

typedef int status;

using namespace std;

struct FatherFile {
    string name;
    FatherFile *next;
};

struct FileInfo {
    string name;
    string fileaddress;
    FatherFile *next = NULL;

    status AddFatherFile(string name);
    status InputFile();
    status ShowFile();
};


#endif // FILEINFO_H
