#include <iostream>
#include <cmath>
using namespace std;
class eq {
public:
    void set(float k, float b);
    float get_k();
    float get_b();
    float root();
private:
    float k, b;
};
void eq::set(float kk, float bb) {
    k = kk;
    b = bb;
}
float eq::get_b() {
    return b;
}
float eq::get_k() {
    return k;
}
float eq::root() {
    float res;
    res = b / -k;
    cout << res;
    return res;
};


int main()

{
    system("color F0");
    setlocale(LC_ALL, "Russian");
    eq test;
    float k, b;
    cout << "¬ведите k" << endl;
    cin >> k;
    cout << "¬ведите b" << endl;
    cin >> b;
    cout << endl;
    cout << b << '/' << "-" << k << "=";

    test.set(k, b);
    test.root();


}
