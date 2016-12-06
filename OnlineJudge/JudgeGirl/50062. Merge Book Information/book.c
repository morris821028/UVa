#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int cmp(int x, int y) {
	if (x < y)	return -1;
	if (x > y)	return 1;
	return 0;
}
static int cmpAuthor(const void *x, const void *y) {
	BookAuthor *a = (BookAuthor*) x;
	BookAuthor *b = (BookAuthor*) y;
	int t = strcmp(a->book_title, b->book_title);
	if (t)	return t;
	t = strcmp(a->author, b->author);
	return t;
}
static int cmpSelling(const void *x, const void *y) {
	BookSelling *a = (BookSelling*) x;
	BookSelling *b = (BookSelling*) y;
	int t = strcmp(a->book_title, b->book_title);
	if (t)	return t;
	t = cmp(a->date, b->date);
	if (t)	return t;
	return cmp(a->selling, b->selling);
}
BookInfoList merge(int N, int M, 
		BookAuthor authorArr[], BookSelling sellingArr[]) {
	qsort(authorArr, N, sizeof(BookAuthor), cmpAuthor);
	qsort(sellingArr, M, sizeof(BookSelling), cmpSelling);
	BookInfoList ret;
	ret.num = 0;
	for (int i = 0, j = 0; i < M; i++) {
		while (j < N && strcmp(sellingArr[i].book_title, authorArr[j].book_title) > 0)	
			j++;
		if (j < N && !strcmp(sellingArr[i].book_title, authorArr[j].book_title)) {
			BookInfo t;
			strcpy(t.book_title, sellingArr[i].book_title);
			strcpy(t.author, authorArr[j].author);
			t.selling = sellingArr[i].selling;
			t.date = sellingArr[i].date;
			ret.books[ret.num++] = t;
		}
	}
	return ret;
}
