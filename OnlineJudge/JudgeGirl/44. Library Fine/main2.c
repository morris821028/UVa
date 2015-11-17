#include <stdio.h>
#include "book.h"
#include "date.h"

unsigned int library_fine(struct Book book, struct Date date_borrowed, struct Date date_returned);

int main(){
    struct Book book = {
        "Neon Genesis Evangelion",
        COMICS,
        "978-159-116-400-5",
        "Yoshiyuki Sadamoto",
        17
    };
    struct Date date_borrowed, date_returned;
    date_borrowed.year  = 2007;
    date_borrowed.month = 11;
    date_borrowed.day   = 14;
    date_returned.year  = 2007;
    date_returned.month = 12;
    date_returned.day   = 3;
    printf("The fine is $%d.\n", library_fine(book, date_borrowed, date_returned));
    return 0;
}
