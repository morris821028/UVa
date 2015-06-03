<script src="http://yandex.st/highlightjs/7.3/highlight.min.js"></script>
<link rel="stylesheet" href="http://jmblog.github.io/color-themes-for-highlightjs/css/themes/tomorrow-night-eighties.css">
<script>
hljs.initHighlightingOnLoad();
</script> 

# 浮點數真是 IMBA #

## Description ##

> Random 感覺起來好牛逼呀！ – 小月
> 
> *** 作者註：「牛逼」是某國用語，意思是「厲害」、「強」的意思。***

以下為無關題目的廢話 (以下廢話純屬虛構，若有相似的部分純屬巧合)

在培訓班資格賽初賽結束後，下個重要的事件就是培訓班隊伍資格賽。看在小月最近略有成長上，於是球球就把其中一題難題的出題額度讓給他。對小月來說，這件工作的難度和出簡單題比起來有如三級跳，每隔幾天問他想到要出什麼題目時，他總是回覆我一句：「抱歉，再給我一點時間。」

當這個工作交給小月三個月後的某天，他終於興高采烈的跑來和球球說：「小月想到一題絕妙好題！」(註：隊伍資格賽早就結束，最後把小月這題改成出在其他比賽。)

球球看一下這題目後發現，雖然題目是不錯，但球球眼睛一瞇，發現案情並不單純，測試資料依舊太弱。

「小月，你這題的理念是不錯，但容我把他退貨，因為測試資料太弱了啦！我隨便寫個使用 Random 的方法，就可以 AC！而且 Random 方法還存在嚴重的漏洞！」

「咦！？真的喔！Random 感覺起來好牛逼呀！讓我研究一番。」

「快回去加強測試資料吧！如果你能成功找到一組幾乎會讓我的程式得到 WA 的測資，就勉為其難的把這題出在下一次的練習賽。」

若問球球為什麼不幫小月生測資就好，想必就是以後為人父母後，就能體會這種把小獅子推入山谷的心情，這是所謂的「愛之深，責之切」吧。### Original Description ###
球球和小月是非常要好的朋友。
有天他們各自蒐集了一些卡片，每張卡片上都寫了一個非負整數。定義兩群卡片的差異度為 $$$\sum_{i \in Z} |x_i - y_i|$$$，其中 $$$x_i$$$ 代表數字 $$$i$$$ 在第一群卡片裡的個數，數字 $$$y_i$$$ 代表數字 $$$i$$$ 在第二群卡片裡的個數。

球球和小月想要找一個大於一的整數 $$$m$$$ ，使得把所有卡片的數改成 $$$\text{mod }m$$$ 的結果後，他們的卡片群差異度最小，請求出最小的差異度值。
## Original Input Format ##
輸入的第一行有兩個正整數 $$$N$$$ 和 $$$M$$$。

輸入的第二行有 $$$N$$$ 個數 $$$A_1,A_2, \text{...},A_N$$$。

輸入的第三行有 $$$N$$$ 個數 $$$numA_1,numA_2, \text{...},numA_N$$$。

輸入的第四行有 $$$M$$$ 個數 $$$B_1,B_2, \text{...},B_M$$$。

輸入的第五行有 $$$M$$$ 個數 $$$numB_1,numB_2, \text{...},numB_M$$$。

以上這些數的意思為：球球的卡片中，原本數字為 $$$A_i$$$ 的有 $$$numA_i$$$ 張，而小月的卡片中，原本數字為 $$$B_i$$$ 的有 $$$numB_i$$$ 張。
    
* $$$1 \le N,M \le 1000$$$
* $$$0 \le A_i,B_i \le 10^9$$$
* $$$1 \le numA_i,numB_i \le 10^5$$$


## Original Output Format ##￼
每組測試資料請輸出答案於一行。
## Sample Input ##

### 範例一 ###
```4 4
1 2 3 4
2 1 1 1
5 6 7 8
1 1 1 2
```
### 範例二 ###
```
2 2
5 7
1 1
12 14
1 1
```
### 範例三 ###
```
1 1
100
2
1
1
```
### 範例四 ###
```
1 1
1
1
1
1
```
### 範例五 ###
```
1 1
5
1
6
1
```
### 範例六 ###
```
10 10
733815053 566264976 984867861 989991438 407773802 701974785 599158121 713333928 530987873 702824160
8941 4607 1967 2401 495 7654 7078 4213 5485 1026
878175560 125398919 556001255 570171347 643069772 787443662 166157535 480000834 754757229 101000799
242 6538 7921 2658 1595 3049 655 6945 7350 6915
```

## Sample Output ##

### 範例一 ###
```
2
```

### 範例二 ###
```
0
```

### 範例三 ###
```
1
```

### 範例四 ###
```
0
```

### 範例五 ###
```
2
```

### 範例六 ####
```
7
```

## Hacked Program ##

小月原本的官方解答如下：

```
#include<bits/stdc++.h>
using namespace std;
const int SIZE = 1011;
const int MAX = 1e9;
const int MM = 31623;
vector<int>p;
void init_prime(){
    p.push_back(2);
    for(int i=3;i<MM;i+=2){
        bool prime=1;
        for(int j=3;j*j<=i;j+=2){
            if(i%j==0){
                prime=0;
            }
        }
        if(prime)p.push_back(i);
    }
}
int A[SIZE],B[SIZE],numA[SIZE],numB[SIZE];
int N,M;
int sum[2]={};
void input(){
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;i++)scanf("%d",&A[i]);
    for(int i=0;i<N;i++)scanf("%d",&numA[i]),sum[0]+=numA[i];
    for(int i=0;i<M;i++)scanf("%d",&B[i]);
    for(int i=0;i<M;i++)scanf("%d",&numB[i]),sum[1]+=numB[i];
}
bool used[MM];
int myrand(){
    int res = (rand()<<16)^rand();
    if(res<0)res=-(res+1);
    return res;
}
int choose(int C[],int numC[],int sumC){
    int id=myrand()%sumC+1;
    int it=0;
    while(id>numC[it]){
        id-=numC[it];
        it++;
    }
    return C[it];
}
pair<int,int>tmp[2000];
int get(int v){
    int tn=0;
    for(int i=0;i<N;i++)tmp[tn++]=make_pair(A[i]%v,numA[i]);
    for(int i=0;i<M;i++)tmp[tn++]=make_pair(B[i]%v,-numB[i]);
    sort(tmp,tmp+tn);
    int res=0;
    for(int i=0,j;i<tn;i=j){
        int ha=0;
        for(j=i;j<tn&&tmp[j].first==tmp[i].first;j++)ha+=tmp[j].second;
        res+=abs(ha);
    }
    return res;
}
void check_min(int &x,int v){x=min(x,v);}
int solve(){
    srand(time(NULL));
    int an=MAX;
    int times=0;
    while(times<10000){
        int v1=choose(A,numA,sum[0]);
        int v2=choose(B,numB,sum[1]);
        if(v1==v2){
            times++;
            continue;
        }
        int v=abs(v1-v2);
        for(int i=0;i<(int)p.size()&&p[i]*p[i]<=v;i++){
            if(v%p[i]==0){
                v/=p[i];
                while(v%p[i]==0)v/=p[i];
                if(used[p[i]]++)continue;
                check_min(an,get(p[i]));
            }
        }
        if(v!=1){
            if(v<MM){
                if(!used[v]){
                    check_min(an,get(v));
                    used[v]=1;
                }
            }
            else check_min(an,get(v));
        }
        times++;
    }
    check_min(an,get(MAX+1));
    return an;
}
int main(){
    init_prime();
    input();
    printf("%d\n",solve());
    return 0;
}
```

## Judge Method ##

請輸出一組測資，使得球球的程式碼執行 $$$10$$$ 次中至少錯 $$$9$$$ 次。為了張顯球球的正義，我們要求測試資料中的 $$$N,M$$$ 的值都不超過 $$$10$$$，來凸顯出此份含 Random 的解法仍有嚴重錯誤。

## Sample Program ##

以下程式碼能產生本題合法但不一定 AC 的測試資料

```
#include<cstdio>
int main(){
    puts("1 1\n1\n1\n1\n1");
    return 0;
}
```
