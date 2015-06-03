<script src="http://yandex.st/highlightjs/7.3/highlight.min.js"></script>
<link rel="stylesheet" href="http://jmblog.github.io/color-themes-for-highlightjs/css/themes/tomorrow-night-eighties.css">
<script>
hljs.initHighlightingOnLoad();
</script> 

# 爆搜就是正義 #

## Description ##

> 爆搜才不是正義呢 >_< – 球球

以下為無關題目的廢話 (以下廢話純屬虛構，若有相似的部分純屬巧合)

「你是在問球球，爆搜是正義嗎？不！絕不！爆搜才不是正義呢！」

故事先從自我介紹開始吧。

我是球球，是個正值青春年華的大學生，平日的休閒是解競賽題、電電同學。座右銘是「演算法即正義」，最擅長的演算法領域是網路流，所以在組隊比賽時，球球總是充當隊花 (Team Flower) 的角色。

在演算法競賽界中『球球』還算小有名氣，所以常常有人來找球球組隊，但球球已有志同道合的夥伴了，於是球球總是開玩笑地說：「對不起球球已名球有主了 >_< 」(球球可是別人專屬的隊花嘛 XD)。由於球球常常這麼說，於是球球又多了一個綽號，有些人也會從 「名球有主」 取其中兩個字，用 ** 球主 ** 來稱呼 ** 球球 **。球球本人則這麼說「『球球』聽起來比較可愛，況且球球可是正義的好夥伴，大家還是叫我『球球』吧。」

俗話說：「可愛和演算法皆為正義」再強調一次，球球可是正義的好夥伴，擁有路見不平拔刀相助的熱血心腸，所以當有人在 FB 或 BBS 發違背演算法的正義的言論時，球球往往會表達我的看法以伸張正義。而在今天球球又看到了一篇有違球球的正義感的發言，小月發了一篇文章說：

「爆搜就是正義！小月今天又在 Codechef 使用爆搜就把一題看似很難的題目給 AC 了！」

看到這樣的發文豈不是很令人火大嗎？明明那題就有一個美妙的演算法啊！解不出題目並不可恥，可恥的是不明不白地 AC 了卻還自鳴得意。球球可是正義的好夥伴，於是向小月要了他的程式碼，請大家一起幫忙生出讓它 TLE 的測資，使得小月不得不承認自己的錯誤！
### Original Description ###
給 $$$N$$$ 個非負整數 $$$a_1, a_2, \text{...},a_N$$$，請把它分成 $$$K$$$ 組，每組 ** 至少 ** 包含一個數，並且每組的數值總和都一樣。
## Original Input Format ##
輸入第一行有一個正整數 $$$T$$$，代表共有幾組測試資料。每組測試資料有兩行，第一行有兩個正整數 $$$N$$$ 和 $$$K$$$，第二行有 $$$N$$$ 個非負整數 $$$a_1,a_2, \text{...},a_N$$$

* $$$1 \le T \le 10$$$
* $$$1 \le N \le 21$$$
* $$$1 \le K \le 8$$$
* $$$0 \le a_i \le 10^{10}$$$ 

## Original Output Format ##￼
每組測試資料請輸出一行，若存在合法的分組方式，輸出 `yes`，否則輸出 `no`。
## Sample Input ##

```2
5 3
1 2 4 5 6
5 3
1 2 4 5 7
```

## Sample Output ##

```yes
no
```

## Hacked Program ##

小月的程式碼如下：

```
#include <bits/stdc++.h>
using namespace std;
#define LL long long
int n;
LL d[22];
LL need;
int used[22];
bool dfs(int x,LL r,int K){
    if(K==0)return 1;
    if(r==0)return dfs(0,need,K-1);
    if(x>=n)return 0;
    if(r==need){
        while(used[x])x++;
        used[x]=1;
        if(dfs(x+1,need-d[x],K))return 1;
        used[x]=0;
    }
    else{
        if(used[x])return dfs(x+1,r,K);
        if(r>=d[x]){
            used[x]=1;
            if(dfs(x+1,r-d[x],K))return 1;
            used[x]=0;
        }
        if(dfs(x+1,r,K))return 1;
    }
    return 0;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int K;
        scanf("%d%d",&n,&K);
        LL sum=0,ma=0;
        for(int i=0;i<n;i++){
            cin>>d[i];
            sum+=d[i];
            ma=max(ma,d[i]);
        }
        if(sum%K||ma>sum/K)puts("no");
        else if(sum==0&&K>n)puts("no");
        else{
            for(int i=0;i<n;i++)used[i]=0;
            need=sum/K;
            if(dfs(0,need,K))puts("yes");
            else puts("no");
        }
    }
    return 0;
}
```

## Judge Method ##

雖然原題的 $$$T$$$ 的範圍限制高達 $$$10$$$，但為了彰顯球球的正義，請輸出一個 $$$T=1$$$ 的合法測資，使得小月的程式碼中 `dfs()` 這個函式至少被呼叫了 $$$10^9$$$ 次。

## Sample Program ##

以下程式碼能產生本題合法但不一定 AC 的測試資料

```
#include<cstdio>
#include<cstdlib>
int main(){
    int T=1;
    printf("%d\n",T);
    while(T--){
        puts("21 8");
        for(int i=0;i<21;i++){
            if(i)printf(" ");
            printf("%d",i);
        }
        puts("");
    }
    return 0;
}
```
