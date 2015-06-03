<script src="http://yandex.st/highlightjs/7.3/highlight.min.js"></script>
<link rel="stylesheet" href="http://jmblog.github.io/color-themes-for-highlightjs/css/themes/tomorrow-night-eighties.css">
<script>
hljs.initHighlightingOnLoad();
</script> 

# 出題是種態度  #

## Description ##

> 「過去的小月是個常常寫假解 AC 後還暗自竊喜的小廢物，直到小月和球球相遇，小月才知道何謂 ** 演算法的正義 ** 」– 小月
大家好，我是小月，正在辛苦的出題中唷！大家可能會想「出一個 debug 的比賽不是很簡單嘛？」去 Codeforces 或一些競賽網站上找一些簡單題，看看有哪些人在短時間內從 WA 變成 AC，把那些程式碼抓下來，再複製一下測試資料，最後把題目翻譯成中文，就完成了！
這樣子就輕鬆出完一場比賽不是？過去的小月或許會這麼做，但直到了小月與球球相遇。
記得小月和球球第一次相遇是在國中二年級的暑假。那時小月匆匆忙忙地上了火車，準備遠赴台北這個大都市參加一個學術活動。火車的門關上後不久卻又重新打開，只見一個全身散發出霸氣的人走了進來，大家都因為他帥氣的身影吸走了目光。這次是小月第一次體會到，英雄總是在最後一刻登場的涵義。
相信認識球球的人一定都心有戚戚焉，小月很高興那時有鼓起勇氣去和球球交談，在那之後也從球球身上學到許多東西。時隔好多年的今日，和球球分開已久，但小月相信球球一定還是在世界某個角落發光發熱。
球球有一個座右銘：「演算法即正義」這同時也是球球的生活態度，小月想要把他的態度，傳達給在座的每一位。請大家原諒小月，在出題過程塞了那麼多話在題目敘述裡，小月只是希望大家能想想看球球說過的話有什麼涵義。請大家在思考題目的同時也看看小月與球球的故事吧！在故事開始前，先給大家看看球球給小月的第一個教訓：「若平常習慣靠些偷吃步 AC，在關鍵時刻遇到擁有演算法的正義的出題者時，一定會後悔莫及。」例如小月以前在寫最遠點對的問題時，都會先使用凸包模版刷掉一些不須要考慮的點，之後直接枚舉所有點對計算距離。因為小月在還未與球球相遇前，總是相信大多數出題者測資大概都隨便亂生吧。球球在知道這件事後，立刻給小月一個當頭棒喝，生出了一個讓小月 TLE 的測資。
請大家重現球球當初對小月做的事吧!
### Original Description ###
給 $$$N$$$ 個平面座標上的點，請求出當中相距最遠的兩個點的距離。為了方便起見，請輸出距離的平方。
## Original Input Format ##
測試資料共有 $$$N + 1$$$ 行。第一行有一個正整數 $$$N$$$，代表平面上點的個數。接下來的 $$$N$$$ 行，每行有兩個整數 $$$x_i$$$, $$$y_i$$$,代表第 $$$i$$$ 個點的座標是 $$$(x_i, y_i)$$$。* $$$2 \le N \le 1,000,000$$$ 
* $$$−10^9 \le x_i,y_i \le 10^9$$$

## Original Output Format ##￼
對於每組測資輸出一行答案，最遠點距離的平方。
## Sample Input ##

### 範例 1 ###

```
2 
0 0 
10 0
```

### 範例 2 ###

```4-1000000000 -1000000000 
-1000000000 1000000000
1000000000 -1000000000
1000000000 1000000000
```

## Sample Output ##

### 範例 1 ###

```100
```

### 範例 2 ###

```8000000000000000000
```

## Hacked Program ##

```
//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
// Let's Fight! }}}

const int MXN = 1000005;

struct Point{
  typedef long long T;
  T x, y;
  
  Point() : x(0), y(0) {}
  Point(T _x, T _y) : x(_x), y(_y) {}

  bool operator < (const Point &b) const{
    return tie(x,y) < tie(b.x,b.y);
  }
  bool operator == (const Point &b) const{
    return tie(x,y) == tie(b.x,b.y);
  }
  Point operator + (const Point &b) const{
    return Point(x+b.x, y+b.y);
  }
  Point operator - (const Point &b) const{
    return Point(x-b.x, y-b.y);
  }
  T operator * (const Point &b) const{
    return x*b.x + y*b.y;
  }
  T operator % (const Point &b) const{
    return x*b.y - y*b.x;
  }
  Point operator * (const T &b) const{
    return Point(x*b, y*b);
  }
  double abs(){
    return sqrt(abs2());
  }
  T abs2(){
    return x*x + y*y;
  }
};

long long cross(Point o, Point a, Point b){
  return (a-o) % (b-o);
}
vector<Point> convex_hull(vector<Point> pt){
  sort(pt.begin(),pt.end());
  int top=0;
  vector<Point> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}

int main(){
    int N;
    while (~scanf("%d", &N) && N){
        vector<Point> ip, ret;
        for (int i=0,x,y; i<N; i++){
            scanf("%d%d", &x, &y);
            ip.PB(Point(x,y));
        }
        ret = convex_hull(ip);
        long long ans = 0;
        for (auto p1 : ret)
            for (auto p2: ret)
                ans = max(ans, (p1-p2).abs2());
        printf("%lld\n", ans);
    }
    return 0;
}
```

## Judge Method ##

請構造出一組測試資料，使得使用上述程式碼凸包後，點數仍至少有 $$$1,000,000$$$ 個點。

## Sample Program ##

以下程式碼能產生本題合法但不一定 AC 的測試資料

```
#include<cstdio>
#include<cstdlib>
#define LL long long
const int MAX = 1000000000;
LL myrand(){
    LL res = ((LL)rand()<<48)^((LL)rand()<<32)^((LL)rand()<<16)^rand();
    if(res<0)res=-(res+1);
    return res;
}
int main(){
    int N = 1000000;
    printf("%d\n",N);
    for(int i=0;i<N;i++){
        printf("%d %d\n",(int)(myrand()%(2*MAX+1)-MAX),(int)(myrand()%(2*MAX+1)-MAX));
    }
    return 0;
}
```
