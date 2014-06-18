#include <iostream>
#include <dirent.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;

int main() {
    //system("cd C:\\Program Files (x86)\\WinRAR");
    //system("cd C:\\Users\\owner\\Desktop\\Dolls");
    char unrar_target[] = "C:\\Users\\owner\\Desktop\\Dolls";
    while(1) {
        DIR *dirp;
        struct dirent *entry;
        set<string> rarDoc;
        int has = 0;
        if(dirp = opendir(unrar_target)) {
            while(entry = readdir(dirp)) {
                if(strlen(entry->d_name) > 4) {
                    int len = strlen(entry->d_name);
                    if(!strcmp(entry->d_name+len-4, ".rar")) {
                        //cout << entry->d_name << endl;
                        if(rarDoc.find(entry->d_name) == rarDoc.end()) {
                            rarDoc.insert(entry->d_name);
                            has = 1;
                        }
                    }
                }
            }
            closedir(dirp);
        }
        if(has == 0)
            break;
        chdir("C:\\Program Files (x86)\\WinRAR");
        //system("dir");
        string path(unrar_target);
        string cmd = "rar e -o- -mt6 " + path + "\\*.rar " + path;
        cout << cmd << endl;
        system(cmd.c_str());
        /*for(set<string>::iterator i = rarDoc.begin(); i != rarDoc.end(); i++) {
            string unrar_cmd = "unrar e " + path + "\\" + *i + " " + path;
            cout << unrar_cmd << endl;
            system(unrar_cmd.c_str());
        }*/
        chdir(unrar_target);
        for(set<string>::iterator i = rarDoc.begin(); i != rarDoc.end(); i++) {
            string cmd = "DEL " + path + "\\" + *i;
            //cout << cmd << endl;
            system(cmd.c_str());
        }
    }
    return 0;
}
