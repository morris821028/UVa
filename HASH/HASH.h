#include <stdio.h> 
#include <stdlib.h>
#include <string>
using namespace std;
class HASH {
	public:
		void IniHash(int);
		int InsHash(int);
		int DelHash(int);
		void PrintHash();
		void PrintHashList(int);
	private:
		int Mod;
		struct list {
    		int tag;
    		struct list *next;
		}*hash[100000], *curr, *prev, *temp;
};
