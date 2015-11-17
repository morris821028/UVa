#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "date.h"

unsigned int library_fine(struct Book book, struct Date date_borrowed, struct Date date_returned);

static unsigned int importance_factor(unsigned int importance){
    int lower = importance & -importance;
    int upper = importance ^ lower;
    int factor;
    for(factor = 0; (lower <<= 1) != upper; ++factor)
    	;
    return factor;
}

int main(){
    unsigned int i, j;

    unsigned int importance[32 * 31 / 2];
    int n_importance = 0;
    for(i = 0; i < 32; ++i)
    	for(j = 0; j < i; ++j)
	    importance[n_importance++] = (1 << i) | (1 << j);

    const char title[4][128]   = {"Fundation",         "Neon Genesis Evangelion, Vol. 1", "Programming Perl (3rd Edition)", "C How to Program (5th Edition)"};
    const char ISBN[4][128]    = {"978-055-380-371-6", "978-159-116-400-5",               "978-059-600-027-1",              "978-013-240-416-7"};
    const char authors[4][128] = {"Isaac Asimov",      "Yoshiyuki Sadamoto",              "Larry Wall",                     "Harvey Deitel & Paul Deitel"};
    struct Book books[32 * 31 / 2 * 4];
    int n_book = 0;
    for(i = NOVEL; i <= TEXTBOOK; ++i)
    	for(j = 0; j < n_importance; ++j){
    	    strcpy(books[n_book].title, title[i]);
    	    books[n_book].type = i;
    	    strcpy(books[n_book].ISBN, ISBN[i]);
	    sprintf(books[n_book].authors, "%s", authors[i]);
	    books[n_book].importance = importance[j];
	    ++n_book;
	}

    struct Date date_borrowed, date_returned;
    scanf("%d %d %d %d %d %d",
    	    &date_borrowed.year, &date_borrowed.month, &date_borrowed.day,
    	    &date_returned.year, &date_returned.month, &date_returned.day);

    printf("+---------------------------------+----------------+----------+\n");
    printf("|              Title              |   Importance   |   Fine   |\n");
    printf("+---------------------------------+----------------+----------+\n");
    for(i = 0; i < n_book; ++i){
	printf("| %-31.31s | %#010x(%2u) | %8u |\n",
	    books[i].title,
	    books[i].importance,
	    importance_factor(books[i].importance),
	    library_fine(books[i], date_borrowed, date_returned));
    }
    printf("+---------------------------------+----------------+----------+\n");
    return 0;
}
