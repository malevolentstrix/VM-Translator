#include<iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string Name;
    string OutFile;
    getline(cin, Name);
    char Name_arr[100];
    strcpy(Name_arr, Name.c_str());

    string Extension = (Name.substr(Name.length()-3));
    if(boost::iequals(Extension, ".vm") == true)
    {
        char* ptr = strrchr(Name_arr, '.');
        OutFile = Name.substr(0, ptr-Name_arr+1);
        cout << OutFile + "asm";
    }
    return 0;
}