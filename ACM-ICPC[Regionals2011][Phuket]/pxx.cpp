#include<iostream>
using namespace std;



int main(){

    for(int i=2;i<100;i++)
    {
        int cnt = 0;
        for(int j=1;j<=i;j++)
        {
            cnt+=bool(i%j==0);
        }
        cout<<cnt<<' ';
    }
}
