/**********************************************************************************/
/*  Problem: d228 "kill man" from                                                 */
/*  Language: CPP (573 Bytes)                                                     */
/*  Result: AC judge by zeroserver@ZeroJudge                                      */
/*  Author: nanj0178 at 2009-04-27 21:02:54                                       */
/**********************************************************************************/


#include <iostream>  
#include <queue>  
using namespace std;  
queue <int > q;  
int main(){  
    int ntc,i,j,n,k,ans,tmp,a[100001],t,par,m;
    int hh,mm,ss;
    int *c[100001];
    cin >> ntc;  
    for(int ca=1;ca<=ntc;ca++){  
       cin >> n >> hh >> mm >> ss;
       m=n;
       for(i=1;i<=n;i++)  
         a[i]=i,c[i]=&a[i];  

        mm = mm*mm*mm;
        ss = ss*ss*ss;
	    t=hh;

        int take = hh;
       while(1){
             for(i=t;i<n;i++)
	         	  c[i]=c[i+1];
             n--;	
           if(take%2) take = (mm)%n;
           else take = (ss)%n;       
           t+=take;
           if(t>n)t-=n;
           if(!(n-1)){
		   printf("%d\n",*c[t]);
		   break;
		   }
           
		   
           //cout << *c[t] << " " << endl;
           take = *c[t];
        } 
       
    }  
} 

