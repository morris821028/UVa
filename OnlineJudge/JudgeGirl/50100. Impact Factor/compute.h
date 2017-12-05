#ifndef COMPUTE
#define COMPUTE
typedef struct {
    char journalName[64];
    int numCitedPaper;
    int citedPaperIndex[1024];
} paper;
void compute(paper P[], int N);
#endif
