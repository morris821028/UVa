#ifndef _BOOK_H
#define _BOOK_H
 
#define MAXN 100
#define MAXL 25
 
typedef struct {
    char book_title[MAXL], author[MAXL];
}BookAuthor;
 
typedef struct {
    char book_title[MAXL];
    int selling, date;
}BookSelling;
 
typedef struct {
    char book_title[MAXL], author[MAXL];
    int selling, date;
}BookInfo;
 
typedef struct {
    int num; // the number of books
    BookInfo books[MAXN];
}BookInfoList;
 
BookInfoList merge(int N, int M, BookAuthor authorArr[], BookSelling sellingArr[]);
 
#endif
