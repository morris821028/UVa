#include <iostream>
#include <map>
#include <vector>
using namespace std;
int a[10001][6];
int masc[6];
int main(){
    int ntc,n,k;
    cin >> ntc;
    while(ntc--){
       cin >> n >> k;
       for(int i = 1;i<=n;i++)
          for(int j = 1; j<=5;j++)
                cin >> a[i][j];
       int  ans = 0 ; 
       masc[1]=masc[2]=masc[3]=masc[4]=masc[5]=0;   
       for(int j=1;j<=5;j++){
          int ma =0;
          for(int i=1;i<=n;i++)
             if(ma< a[i][j])
                   ma = a[i][j];
          masc[j]=ma;
        //  cout << ma << endl;
       }   
       if(1){
            int  ma  = 0; 
            for(int i=1;i<=n;i++)
              if(ma < a[i][1]+a[i][2]+a[i][3]+a[i][4]+a[i][5])
               ma = a[i][1]+a[i][2]+a[i][3]+a[i][4]+a[i][5];
                ans = ma;
       } 
       if(k>=5){
            
            ans =   masc[1]+masc[2]+masc[3]+masc[4]+masc[5];
       }
       if(k==2){
            for(int i=1;i<=5;i++)
               for(int j = i+1;j<=5;j++)
                 for(int k = j+1;k<=5;k++)
                   for(int l = k+1 ;l <=5;l++){
                         int ma = 0;
                        for(int q = 1;q<=n;q++)
                           if(ma <  a[q][i]+a[q][j]+a[q][k]+a[q][l])
                             ma = a[q][i]+a[q][j]+a[q][k]+a[q][l];
                        int t = 0;
                        for(int q =1;q<=5;q++)
                           if(q!=i && q!=j && q!=k && q!=l)
                                     t= q;
                        if(ans < ma + masc[t]){
                          ans = ma +masc[t];      
                       //   cout << ma << " " << i << " " << j << " " << k << " "<< l << endl;
                          }
                   }
                   
                            for(int i=1;i<=5;i++)
               for(int j = i+1;j<=5;j++){
                    int ma2 = 0;
                    for(int q = 1;q<=n;q++)
                       if(ma2 <  a[q][i]+a[q][j])
                            ma2 = a[q][i]+a[q][j];
                 
                 
                 
                 for(int k = 1;k<=5;k++)
                   if(k!=i && k!=j)
                   for(int l = k+1 ;l <=5;l++)
                     if(l!=i && l!=j)
                     for(int m = l+1 ;m <=5;m++)
                     if(m!=i && m!=j)
                      {
                         int ma = 0;
                        for(int q = 1;q<=n;q++)
                           if(ma <  a[q][k]+a[q][l]+a[q][m])
                             ma = a[q][k]+a[q][l]+a[q][m];
                        
                        if(ans < ma +ma2)
                          ans = ma +ma2;      
                   }
                }        
       }
       if(k>=3){
              for(int i=1;i<=5;i++)
               for(int j = i+1;j<=5;j++)
                 for(int k = j+1;k<=5;k++)
                  {
                        int ma = 0;
                        for(int q = 1;q<=n;q++)
                           if(ma <  a[q][i]+a[q][j]+a[q][k])
                             ma = a[q][i]+a[q][j]+a[q][k];
                        for(int q =1;q<=5;q++)
                           if(q!=i && q!=j)
                              ma= masc[q];
                        if(ans < ma)
                          ans = ma;      
                   }
                   
              for(int i=1;i<=5;i++)
               for(int j = i+1;j<=5;j++){
                    int ma2 = 0;
                    for(int q = 1;q<=n;q++)
                       if(ma2 <  a[q][i]+a[q][j])
                            ma2 = a[q][i]+a[q][j];
                 
                 
                 
                 for(int k = 1;k<=5;k++)
                   if(k!=i && k!=j)
                   for(int l = k+1 ;l <=5;l++)
                     if(l!=i && l!=j){
                         int ma = 0;
                        for(int q = 1;q<=n;q++)
                           if(ma <  a[q][k]+a[q][l])
                             ma = a[q][k]+a[q][l];
                        int t = 0;
                        for(int q =1;q<=5;q++)
                           if(q!=i && q!=j && q!=k && q!=l)
                                     t= q;
                        if(ans < ma + masc[t]+ma2)
                          ans = ma +masc[t]+ma2;      
                   }
                }
       }
       if(k>=4){
            for(int i=1;i<=5;i++)
               for(int j = i+1;j<=5;j++)
                  {
                        int ma = 0;
                        for(int q = 1;q<=n;q++)
                           if(ma <  a[q][i]+a[q][j])
                             ma = a[q][i]+a[q][j];
                        for(int q =1;q<=5;q++)
                           if(q!=i && q!=j)
                              ma= masc[q];
                        if(ans < ma)
                          ans = ma;      
                   }
       }  
       
       cout << ans << endl;
    }
}
