#ifndef FILESEARCH_H
#define FILESEARCH_H

#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<cstring>
#include"fileinfo.h"
using namespace std;

#define Is_String 1
#define FileDoc 2

typedef int Nodetype;
struct FatherNode
{
    Nodetype Type;
    FatherNode *next;
    string NodeName;
};
struct ChildNode
{
    ChildNode *next;
    Nodetype Type;
    string NodeName;
};

struct FileNode {
    string Filename;
    FileInfo Info;
    ChildNode *ChildNext = NULL;
    FatherNode *FatherNext = NULL;
    FileNode *next;
    bool is_over = false;
    void GenerateInfo();
};

class FileList
{
public:
    FileNode * head;
    void AddNode(string address)
    {
        FileNode *p = new (nothrow) FileNode;
        p->Info.fileaddress = address;
        p->GenerateInfo();
        p->Info.InputFile();
        p->next = NULL;
        if (head == NULL)
            head = p;
        else
        {
            p->next = head->next;
            head->next = p;
        }
    };

    void show()
    {
        FileNode *p;
        p = head;
        while (p != NULL)
        {
            p->Info.ShowFile();
            p = p->next;
        }
    }

    FileList()
    {
        head = NULL;
    }

    status ManualSearch(string);
    FileNode* Locate(string);
    void StartSearch();
    void ShowList();

    void clear()
    {
        FileNode *p;
        p = head;
        while (p != NULL)
        {
            FatherFile *q;
            q=p->Info.next;
            while(q!=NULL)
            {
                FatherFile *temp;
                temp=q;
                q=q->next;
                delete temp;
            }

            FatherNode *f;
            f=p->FatherNext;
            while(f!=NULL)
            {
                FatherNode *temp;
                temp=f;
                f=f->next;
                delete temp;
            }

            ChildNode *c;
            c=p->ChildNext;
            while(f!=NULL)
            {
                ChildNode *temp;
                temp=c;
                c=c->next;
                delete temp;
            }

            FileNode *temp;
            temp=p;
            p=p->next;
            delete p;
        }
        head=NULL;
    }
};
#endif // FILESEARCH_H
