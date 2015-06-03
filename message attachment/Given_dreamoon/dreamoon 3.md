<script src="http://yandex.st/highlightjs/7.3/highlight.min.js"></script>
<link rel="stylesheet" href="http://jmblog.github.io/color-themes-for-highlightjs/css/themes/tomorrow-night-eighties.css">
<script>
hljs.initHighlightingOnLoad();
</script> 

# 耍小聰明是罪過 #

## Description ##

> 我要代替小月來懲罰你 ～ – 球球

以下為無關題目的廢話 (以下廢話純屬虛構，若有相似的部分純屬巧合)

「哦？小月你是在說偶爾耍耍小聰明也不錯？但我認為，耍小聰明是種罪過。」

「你想想看，聰明就是聰明嘛！何必多一個 **小** 字去修飾它呢？你會多使用這個小字，不就代表還不足以使用聰明兩個字來形容自己的所作所為？」

今天球球正在一如往常的逛 FB 和 BBS，發現小月在他的個版上抱怨上禮拜所參加的台大培訓班比賽。有一題很奇怪，小月他看了好多份獲得 AC 的程式碼，卻無法理解為什麼那些程式碼會對，但小月似乎放棄理解那些程式碼了。

球球身為正義的夥伴，在這篇抱怨文中聞到了罪惡的氣息，因為那是道關於平面圖的題目，球球心想「該不會大家都仗著平面圖的測試資料很難出，於是耍小聰明寫假解法來竊取 AC 吧」於是球球看一看這些程式碼，發現其中確實有詐，這怎麼行呢？就讓球球代替小月來懲罰你們吧！之後球球把這件事上報給培訓班的助教蚯蚓，最終這題被 rejudge，八個原本 AC 這題的隊伍中只剩兩隊還存活著。

球球身為小月的知心好友，也是正義的夥伴，當然要教教小月那些錯誤的程式碼到底發生什麼事，於是就挑了一份似乎最好讀懂的程式碼來強迫小月練習 hack 它。

大家也跟著小月的步伐一起 hack 這份程式碼吧！
### Original Description ###
給一無向平面圖 $$$G=(V,E)$$$，求 $$$G$$$ 的最大團 (clique)。
## Original Input Format ##
輸入第一行有一個正整數 $$$T$$$，代表共有幾組測試資料。每組測試資料共有 $$$M+1$$$ 行。每組第一行有兩個正整數 $$$N$$$ 和 $$$M$$$，分別代表圖 $$$G$$$ 的點數和邊數。接下來 $$$M$$$ 行中，每行包含兩個數 $$$A_i,B_i$$$，代表 $$$G$$$ 的第 $$$i$$$ 條邊連接點 $$$A_i$$$ 和 $$$B_i$$$。
* $$$1 \le T \le 20$$$
* $$$1 \le N \le 200,000$$$
* $$$0 \le A_i,B_i < N,A_i \neq B_i $$$
* $$$G$$$ 是個簡單平面圖


## Original Output Format ##￼
每組測試資料請輸出一個數於一行，代表最大團的數目。
## Sample Input ##

```2
5 6
0 1
1 2
2 0
2 3
3 4
4 2
10 6
0 1
0 2
0 3
1 2
1 3
2 3
```

## Sample Output ##

```3
4
```

## Hacked Program ##

給小月的程式碼如下：

```
// written by tenyoku8478
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n, m;
vector<int> G[200010];

int ans;
int st[200010];
bool used[200010];
void dfs(int root, int lev = 0, int num = 0)
{
    used[root] = true;
    st[lev] = root;
    int tmp = 1;
    for(; tmp<=num; ++tmp)
    {
        int i = lower_bound(G[root].begin(), G[root].end(), st[lev-tmp]) - G[root].begin();
        if(i==G[root].size() || G[root][i] != st[lev-tmp])
            break;
    }
    ans = max(ans, tmp);
    for(int i=0; i<G[root].size(); ++i)
        if(!used[G[root][i]])
            dfs(G[root][i], lev+1, tmp);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T-->0)
    {
        scanf("%d %d", &n, &m);
        for(int i=0; i<n; ++i) G[i].clear();
        while(m-->0)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        ans = 0;
        for(int i=0; i<n; ++i)
        {
            used[i] = false;
            sort(G[i].begin(), G[i].end());
        }
        for(int i=0; i<n; ++i)
            if(!used[i]) dfs(i);
        printf("%d\n", ans);
    }
}
```

## Judge Method ##

會 WA 的測試資料就是會 WA，要張顯球球的正義，只需要一組測資就夠了，所以請輸出一個 $$$T=1$$$ 的合法測資，使得此份程式碼 WA 掉。

## Sample Program ##

以下程式碼能產生本題合法但不一定 AC 的測試資料

```
#include<cstdio>
int main(){
    int T=1;
    printf("%d\n",T);
    while(T--){
        puts("3 3");
        for(int i=0;i<3;i++)printf("%d %d\n",i,(i+1)%3);
    }
    return 0;
}
```
