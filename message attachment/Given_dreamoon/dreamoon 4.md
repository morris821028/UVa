<script src="http://yandex.st/highlightjs/7.3/highlight.min.js"></script>
<link rel="stylesheet" href="http://jmblog.github.io/color-themes-for-highlightjs/css/themes/tomorrow-night-eighties.css">
<script>
hljs.initHighlightingOnLoad();
</script> 

# 浮點數真是 IMBA #

## Description ##

> 浮點數什麼的最討厭了！– 小月

以下為無關題目的廢話 (以下廢話純屬虛構，若有相似的部分純屬巧合)

距離平面圖 rejudge 事件過了一年後，原台大培訓班助教蚯蚓和 Shik 鑒於球球和小月在維護演算法的正義立了大功，決定把培訓班助教的棒子傳給球球我和小月。

我們遇到了第一個難關就是幫培訓班準備培訓班資格賽初賽。這對球球和我來說真的是一個非常困難的事情，畢竟這只是個初賽，必須幾乎所有題目都很簡單的。但身為一個強者，信手拈來全是難題 (雖然以球球的角度來看，這些仍是簡單題，但身為正義的夥伴，必須以超然物外的角度來審視這些題目，必須客觀的說這些題目是難題)。

於是和小月討論後，除了唯一的一題防破台題由球球出外，其它題目皆由小月出。當小月出完他的那些簡單題後，球球幫他驗了所有題目，題目大致完善，但仍有美中不足的部分。有一題使用到了浮點數，若使用小月的官方解答，將會產生超乎想像的誤差，並且小月所生的測試資料也無法看出這樣異常的誤差存在。

身為正義的夥伴，絕不允許如此不公不義的事發生，於是球球找了小月出來質問。

「小月！這樣的簡單題，你怎麼會寫出這樣的程式碼！」

「咦？怎麼了嗎？我覺得很好啊」

「小月你啊 ... 去年我在 ioicamp 講的關於浮點數誤差分析的授課內容，你到底有沒有仔細在聽呀！」

「唔 ... 那堂課我好像不小心睡過頭了，你想想看那堂課的前一晚是 debug 賽，那場比賽我一題 Extreme 都寫不出來。最後助教們公佈的參考答案宛如超強咖啡因，這令小月晚上沒睡好 ...」

「好吧，聽起來還算情有可原。那趕快複習一下浮點數誤差分析的部分，在今年的 ioicamp 講義裡也有，請去翻開 9.5 章來參考，來想想看你這題的這份程式碼到底會發生什麼事情吧！」

「謝謝球球大人賜教 m(_ _)m，小的知錯了，嗚嗚嗚 ... 浮點數什麼的最討厭了！」

在小月忙著修正該題的測試資料的強度與官方解答之餘，大家也許等的不耐煩，那麼就讓大家先來玩玩看，要如何 hack 小月原本的官方解答！### Original Description ###
給 $$$n$$$ 個正整數 $$$v_1,v_2, \text{...},v_n$$$ 以及另外 $$$n$$$ 個正整數 $$$w_1,w_2, \text{...},w_n$$$。

請輸出一個實數 $$$x$$$，使得 $$$\sum|v_i \times x−w_i|$$$ 最小。若有多個實數能使得此式結果最小，請輸出最小的那個。
## Original Input Format ##
輸入僅有三行。

第一行有一個整數 $$$n$$$。第二行有 $$$n$$$ 個正整數 $$$v_1,v_2, \text{...},v_n$$$。第三行也有 $$$n$$$ 個正整數 $$$w_1,w_2, \text{...},w_n$$$。

* $$$1 \le n \le 50$$$
* $$$1 \le v_i,w_i \le 1000000000(10^9)$$$


## Original Output Format ##￼
請輸出答案於一行，絕對或相對誤差不超過 $$$10^{−9}$$$。
## Sample Input ##

### 範例一 ###
```1
5
1000
```
### 範例二 ###
```
2
10 10
1000 2000
```
### 範例三 ###
```
3
10 20 40
4000 2000 1000
```
### 範例四 ###
```
15
1234 1541 3321 1234 123 123 3414 123 12 2442 1421 1223 3232 1123 2121
3213 1231 232143 44312 132132 142424 123123 41341 41244 21312 232131 2312 2322 11 2223
```

## Sample Output ##

### 範例一 ###
```200
```

### 範例二 ###
```
100
```
### 範例三 ###
```
25
```
### 範例四 ###
```
8.727273
```

## Hacked Program ##

小月原本的官方解答如下：

```
//edited from Topcoder user: vinamilk
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
double findSuitableDensity(vector <int> v, vector <int> w) {
    int n=v.size();
    int i,j;double d,tg,ans,kq=1E18;
    for(i=0;i<n;++i) {
        d=double(w[i])/double(v[i]);
        tg=0;
        for(j=0;j<n;++j) tg+=fabs(d*v[j]-w[j]);
        if(tg<kq||(tg==kq&&d<ans)){
            kq=tg;
            ans=d;
        }
    }
    return ans;
}
int main() {
    int i,x,n;
    scanf("%d",&n);
    vector <int> v,w;
    for(i=0;i<n;++i) {
        scanf("%d",&x);
        v.push_back(x);
    }
    for(i=0;i<n;++i) {
        scanf("%d",&x);
        w.push_back(x);
    }
    printf("%.9f\n",findSuitableDensity(v, w));
    return 0;
}
```

## Judge Method ##

為了彰顯球球的正義，請輸出一個能使得小月的官方解答程式碼產生絕對誤差大於 $$$1000$$$ 的測資。

## Sample Program ##

以下程式碼能產生本題合法但不一定 AC 的測試資料

```
#include<cstdio>
#include<cstdlib>
int main(){
    int n=5;
    printf("%d\n",n);
    for(int i=0;i<n;i++){
        if(i)printf(" ");
        printf("%d",i+10);
    }
    puts("");
    for(int i=0;i<n;i++){
        if(i)printf(" ");
        printf("%d",i+20);
    }
    puts("");
    return 0;
}
```
