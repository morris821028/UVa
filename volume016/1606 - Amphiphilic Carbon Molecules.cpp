#include<iostream>  
#include<algorithm>      
#include<cmath>     
using namespace std;   
  
const int N=1001;  
  
class Point{  
public:
    int x,y,color;  
    double rad;  
    bool operator<(const Point &rhs)const{  
        return rad<rhs.rad;  
    }  
}dot[N],tempDot[N];  
  
int n, num; 
  
bool isInArea(Point A,Point B){  
    return A.x*B.y-A.y*B.x>=0;  
}  
  
int main(){  
	ios::sync_with_stdio(false);
	cin.tie(0);
	
    while(cin>>n && n){  
        for(int i=0;i<(n);i++)    
			cin >> dot[i].x >> dot[i].y >> dot[i].color;  
        if(n<=2) return 2;  
		int ans=0;  
  
		for(int i=0;i<n;i++){  
			num=0;  
			for(int j=0;j<n;j++){ 
				if(j == i) continue;   
				tempDot[num].x=dot[j].x-dot[i].x;  
				tempDot[num].y=dot[j].y-dot[i].y;  
				if(dot[j].color){
					tempDot[num].x=-tempDot[num].x;
					tempDot[num].y=-tempDot[num].y;
				} 
				tempDot[num].rad=atan2(tempDot[num].y,tempDot[num].x);  
				num++;  
			}  
			sort(tempDot,tempDot+num);  
  
			int divi=0,scani=0,cnt=2;  
			while(divi<num){  
            if(scani==divi){
				scani=scani+1; 
				if(scani >= num) scani = scani-num;
				cnt++;
			}  
            while(scani!=divi && isInArea(tempDot[divi],tempDot[scani])){  
                scani=scani+1; 
				if(scani >= num) scani = scani-num;
                cnt++;  
            }  
            cnt--;
            divi++;   
            ans=max(ans,cnt); 
			}  
		}  
		cout << ans << '\n';  
	}
	return 0;	
}
