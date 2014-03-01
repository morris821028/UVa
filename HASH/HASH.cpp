#include <stdlib.h>
#include "HASH.h"
#include <string>
using namespace std;
void HASH::IniHash(int size) {
	static int i;
	
	for(i = 0; i < Mod; i++) {
		curr = hash[i], prev = NULL;
		while(curr != NULL) {
			prev = curr, curr = curr->next;
			free(prev);
		}
		hash[i] = NULL;
	}
	
	Mod = size;
}
int HASH::InsHash(int Num) {
	static int heap;
	heap = Num%Mod;
	
	temp = hash[heap], prev = NULL;
	
	while(temp != NULL) {
		if(temp->tag == Num)	return 0;
		if(temp->tag > Num)		break;
		else {
			prev = temp;
			temp = temp->next;
		}
	}
	
	curr = (struct list *)malloc(sizeof(struct list));
	curr->tag = Num, curr->next = temp;
	
	if(prev != NULL)	prev->next = curr;
	else				hash[heap] = curr;
	
	return 1;
}
int HASH::DelHash(int Num) {
	static int heap;
	heap = Num%Mod;
	
	curr = hash[heap], prev = NULL;
	
	while(curr != NULL) {
		if(curr->tag < Num)
			prev = curr, curr = curr->next;
		else if(curr->tag == Num) {
			if(prev != NULL)
				prev->next = curr->next;
			else
				hash[heap] = curr->next;
			free(curr);
			return 1;
		}
		else	return 0;
	}
	return 0;
}
void HASH::PrintHash() {
	puts("//======s======//");
	static int i;
	for(i = 0; i < Mod; i++) {
		printf("[%03d]:", i);
		curr = hash[i];
		while(curr != NULL) {
			printf("%d -> ", curr->tag);
			curr = curr->next;
		}
		puts("NULL");
	}
	puts("//======e======//");
}
void HASH::PrintHashList(int list) {
	curr = hash[list];
	puts("//======s======//");
	while(curr != NULL) {
		printf("%d -> ", curr->tag);
		curr = curr->next;
	} 
	puts("NULL");
	puts("//======e======//");
}
