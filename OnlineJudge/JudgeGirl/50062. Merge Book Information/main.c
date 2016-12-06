#include <stdio.h>
#include <assert.h>
#include "book.h"
 
int main(){
    int N, M;
    BookAuthor authorArr[MAXN];
    BookSelling sellingArr[MAXN];
 
    assert(scanf("%d %d", &N, &M) == 2);
    for(int i = 0; i < N; i++)
        assert(scanf("%s %s", authorArr[i].book_title,
                              authorArr[i].author) == 2);
 
    for(int i = 0; i < M; i++)
        assert(scanf("%s %d %d", sellingArr[i].book_title,
                                 &sellingArr[i].selling,
                                 &sellingArr[i].date) == 3);
 
    BookInfoList result = merge(N, M, authorArr, sellingArr);
 
    for(int i = 0; i < result.num; i++)
        printf("%s %s %d %d\n", result.books[i].book_title,
                                result.books[i].author,
                                result.books[i].date, result.books[i].selling);
 
    return 0;
}
