#include<stdio.h>
#include<stdlib.h>
#include"trace.h"
Node* newNode()
{
	Node* ret=malloc(sizeof(Node));
	ret->list=NULL;
	return ret;
}
ChildList* newList(Node* node,ChildList* next)
{
	ChildList* ret=malloc(sizeof(ChildList));
	ret->node=node;
	ret->next=next;
	return ret;
}
int main()
{
	//sample input
	Node* root=newNode();
	Node* n1=newNode(),*n2=newNode(),*n3=newNode(),*n4=newNode(),*n5=newNode(),*n6=newNode();
	ChildList *l3=newList(n3,NULL),*l2=newList(n2,l3),*l1=newList(n1,l2),*l5=newList(n5,NULL),*l4=newList(n4,l5),*l6=newList(n6,NULL);
	root->list=l1;
	n2->list=l4;
	n4->list=l6;
	//end
	Answer* ans=calloc(1,sizeof(Answer));
	trace(root,ans);
	printf("%d %d %d %d\n",ans->InternalNode,ans->Leaf,ans->MaxBranchFactor,ans->Depth);
	return 0;
}
