#include"filesearch.h"
void FileNode::GenerateInfo()
{
    int length = this->Info.fileaddress.length();
    for (int i = length - 1; i >= 0; i--)
     {
        if (this->Info.fileaddress[i] == '/')
         {   for (int j = i + 1; j < length; j++)
             {
                this->Filename+= this->Info.fileaddress[j];
             }
            break;
        }
    }
    return;
}

status FileList::ManualSearch(string target)
{
    FileNode *p;
    p=this->Locate(target);
    if (p->is_over)
        return 0;
    if (p != NULL)
    {
        FatherFile *q;
        q = p->Info.next;
        while (q != NULL)
        {
            FileNode *t;
            t = this->Locate(q->name);
            if (t != NULL)
            {
                FatherNode *temp = new(nothrow)FatherNode;
                temp->NodeName = q->name;
                temp->Type = FileDoc;
                if (p->FatherNext == NULL)
                {
                    p->FatherNext = temp;
                    temp->next = NULL;
                }
                else
                {
                    temp->next = p->FatherNext;
                    p->FatherNext = temp;
                }
                ChildNode *tempc = new(nothrow)ChildNode;
                tempc->NodeName = p->Filename;
                tempc->Type = FileDoc;
                if (t->ChildNext == NULL)
                {
                    t->ChildNext = tempc;
                    tempc->next = NULL;
                }
                else
                {
                    tempc->next = t->ChildNext;
                    t->ChildNext = tempc;
                }
                if(!t->is_over)
                    ManualSearch(t->Filename);
            }
            else
            {
                FatherNode *temp = new(nothrow)FatherNode;
                temp->NodeName = q->name;
                temp->Type = Is_String;
                if (p->FatherNext == NULL)
                {
                    p->FatherNext = temp;
                    temp->next = NULL;
                }
                else
                {
                    temp->next = p->FatherNext;
                    p->FatherNext = temp;
                }
            }
            q = q->next;

        }
        p->is_over = true;
        return 1;
    }
    else
    {
        return 0;
    }
}
void FileList::StartSearch()
{
    FileNode *p;
    p = head;
    while (p != NULL)
    {
        ManualSearch(p->Filename);
        p = p->next;
    }
    return;
}
FileNode* FileList::Locate(string target)
{
    FileNode *p;
    p = head;
    while (p != NULL)
    {
        if (p->Filename == target)
            return p;
        p = p->next;
    }
    return NULL;
}
void FileList::ShowList()
{
    FileNode *p;
    p = head;
    while (p != NULL)
    {
        cout << "\nFileName:" ;
        cout << p->Filename << endl;
        cout << "Father:" << endl;
        FatherNode *q;
        q = p->FatherNext;
        while (q != NULL)
        {
            cout << "NodeName:" << q->NodeName << endl;
            cout << "Type:" << q->Type << endl;
            q = q->next;
        }
        cout << "Child:" << endl;
        ChildNode *t;
        t = p->ChildNext;
        while (t != NULL)
        {
            cout << "NodeName:" << t->NodeName << endl;
            cout << "Type:" << t->Type << endl;
            t = t->next;
        }
        p = p->next;
    }
    return;
}

