typedef unsigned long long Set;
void init(Set *set);
void add(Set *set, int i);
void has(Set set, int i);
Set setUnion(Set a, Set b);
Set setIntersect(Set a, Set b);
Set setDifference(Set a, Set b);
