#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    vector<int> vector;
    Graph main;
    main.showMatrix();

    int countComponents = main.findCountComponents();
    cout << "���������� ���������� ��������� = " << countComponents << endl;

    auto path = main.findEulerPath();
    if (path.empty()) {
        cout << endl << "���� �� ����������" << endl << endl;
    }
    else {
        cout << path[0];
        for (auto i : path) {
            cout << " -> " << i + 1;
        }
    }
    return 0;
}
