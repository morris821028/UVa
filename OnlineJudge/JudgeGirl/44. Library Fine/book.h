#ifndef BOOK_H
#define BOOK_H

enum Type {NOVEL, COMICS, MANUAL, TEXTBOOK};

struct Book {
    char title[128];
    enum Type type;
    char ISBN[128];
    char authors[128];
    unsigned int importance;
};

#endif
