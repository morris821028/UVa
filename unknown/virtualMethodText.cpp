#include <iostream>

class A {
    public:
        virtual void f() {
            std::cout << "a";
        }
};
class B: public A {
    public:
        void f() {
            std::cout << "b";
        }
};

int main() {
    A a;
    B b;
    A *aptr = &b;
    B *bptr = &b;
    (*aptr).f();
    (*bptr).f();
    aptr->f();
    bptr->f();
    return 0;
}
