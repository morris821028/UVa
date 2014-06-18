#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    bool boolnum = true;
    cout << boolnum << endl;
    cout << boolalpha << boolnum << endl;

    double doublenum = 999.569875;
    cout << setprecision(8) << doublenum << endl;
    return 0;
}
