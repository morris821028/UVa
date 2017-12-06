#include<stdio.h>
#include"componentPart.h"
int main(){
    int N;
    scanf("%d",&N);
    ComponentPart list[N];
    for(int i=0;i<N;i++){
        scanf("%s%d",list[i].name,&list[i].numComponent);
        if(list[i].numComponent){
            for(int j=0;j<list[i].numComponent;j++)
                scanf("%d",&list[i].componentPartList[j]);
            list[i].price=0;
        }
        else
            scanf("%d",&list[i].price);
    }
    findPrice(N,list);
    return 0;
}
