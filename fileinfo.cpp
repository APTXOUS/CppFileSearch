#include"FileInfo.h"


status FileInfo::AddFatherFile(string name)
{
    FatherFile *p = new (nothrow) FatherFile;
    if (p == NULL)
        return ERROR;
    p->name = name;
    p->next = this->next;
    this->next = p;
    return OK;
}

status FileInfo::InputFile()
{

    ifstream fin;
    fin.open(this->fileaddress, ios::in);
    char temp[1000];
    if (fin.is_open())
        while (!fin.eof())
        {
            fin.getline(temp, 1000, '\n');
            char* location = strstr(temp, "#include");
            if (location != NULL)
            {
                char * location_first;
                location_first = strchr(location + 8, '<');
                if (location_first != NULL)
                {
                    char * location_last;
                    location_last = strchr(location_first+1, '>');
                    int length = location_last - location_first;
                    location_last[0] = '\0';
                    string tempname = location_first + 1;
                    this->AddFatherFile(tempname);

                }
                else
                {
                    location_first = strchr(location + 8, '\"');
                    if (location_first != NULL)
                    {
                        char * location_last;
                        location_last = strchr(location_first+1, '\"');
                        int length = location_last - location_first;
                        location_last[0] = '\0';
                        string tempname = location_first + 1;
                        this->AddFatherFile(tempname);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
                continue;
        }
    fin.close();
    return true;
}

status FileInfo::ShowFile()
{
    cout << "Name:    " << this->name << endl;
    cout << "Filename:" << this->fileaddress << endl;
    cout << "Father:" << endl;
    FatherFile *p = this->next;
    while (p != NULL)
    {
        cout << "|-" << p->name << endl;
        p = p->next;
    }
    return OK;
}

