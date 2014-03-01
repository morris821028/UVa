#include <iostream>
#include <dirent.h>
using namespace std;

int main() {
    DIR *dirp;
    struct dirent *entry;
    if(dirp = opendir("C:\\")) {
        while(entry = readdir(dirp))
            cout << entry->d_name << endl;
        closedir(dirp);
    }
    return 0;
}
