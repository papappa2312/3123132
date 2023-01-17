#ifndef SAOD7LAB_GRAPH_H
#define SAOD7LAB_GRAPH_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph {
public:
    int** matrix = nullptr;// —троки матрицы-это вершины, столбцы - это ребра
    int countNode; // количество вершин
    int countEdge; // количество ребер
    int countOddNode = 0;
    int oddNode = 0;

    Graph() {
        cout << "¬ведите количество вершин: ";
        cin >> countNode;
        cout << "¬ведите количество ребер: ";
        cin >> countEdge;

        //инициализаци€
        matrix = new int* [countEdge];
        for (int i = 0; i < countEdge; i++) {
            matrix[i] = new int[countNode];
        }

        // заполнение
        cout << '\n';
        for (int i = 0; i < countNode; i++) {
            for (int j = 0; j < countEdge; j++) {	// заполн€ем столбец
                cout << "[" << i + 1 << "][" << j + 1 << "] = ";
                cin >> matrix[j][i];
                cout << '\n';
            }
        }
    }
    bool checkForEulerPath() { // ѕроверка: может ли сущетсвовать Ёйлеров путь или нет
        for (int i = 0; i < countNode; i++) {
            int powNode = 0;
            for (int j = 0; j < countEdge; j++) {
                if (matrix[j][i] > 0) { powNode++; }
            }
            if (powNode % 2 == 1) { countOddNode++; oddNode = i; }
        }
        if (countOddNode > 2 || findCountComponents() > 1) {
            return false;
        }
        return true;
    }
    vector <int> findEulerPath() {
        vector<int> res;
        if (!checkForEulerPath()) {
            return res;
        }

        int start;
        if (countOddNode != 0) {
            start = oddNode;
        }
        else {
            start = 0;
        }

        vector<int> neighbour;
        stack<int> stack;
        stack.push(start);
        int u;
        while (!stack.empty()) {
            int node = stack.top();
            neighbour = findNeighbour(node);

            if (!neighbour.empty()) {
                u = neighbour[neighbour.size() - 1];
                neighbour.pop_back();
                stack.push(u);
                deleteEdge(edgeBetweenNode(node, u)); // удалить св€зь между вершинами
            }
            else {
                stack.pop();
                res.push_back(node);
            }
        }
        return res;
    }

    void deleteEdge(int numV) { //удаление ребра
        int i = numV;
        for (int k = 0; k < countNode; k++) { // пройти этот слолбец
            if (matrix[i][k] == 1) { matrix[i][k] = 0; } // и добавить соседей
        }
    }

    int edgeBetweenNode(int v, int u) {
        for (int i = 0; i < countEdge; i++) {
            if (matrix[i][v] == 1 && matrix[i][u] == 1) { return i; }
        }
        return 0;
    }

    int findCountComponents() {
        vector<bool> vizited;
        vector<int> components;
        int componentCount = 0;
        int start;
        int tmp;

        for (int i = 0; i < countNode; i++) {
            components.push_back(0);
            vizited.push_back(0);
        }

        queue <int> queue;
        vector <int> neighbour;
        while (findZeroVal(components) != countNode) {
            start = findZeroVal(components);
            componentCount += 1;

            queue.push(start); //закидываем вершину
            while (!queue.empty()) {
                tmp = queue.front(); // достать вершину
                components[tmp] = componentCount; // обработка вершины
                neighbour = findNeighbour(tmp); // найти соседей
                vizited[tmp] = 1;
                queue.pop(); // удалить обработанную вершину
                for (int i : neighbour) {
                    if (vizited[i] != 1) {
                        queue.push(i); // добавить соседей в очередь
                    }
                }
                neighbour.clear(); // отчистить список соседей
            }
        }
        return componentCount;
    }

    vector <int> findNeighbour(int numV) { // nоиск вершины, св€занной с данным ребром
        vector<int> neighbour;
        int i = numV;
        for (int j = 0; j < countEdge; j++) { // пройти по строке
            if (matrix[j][i] == 1) { // если найдена 1
                for (int k = 0; k < countNode; k++) { // пройти этот слолбец
                    if (matrix[j][k] == 1 && k != i) { neighbour.push_back(k); } // и добавить соседей
                }
            }
        }
        return neighbour;
    }

    int findZeroVal(vector<int> arr) { // ѕроходит по вектору и ищет индекс первое нулевое значение
        int i = 0;
        while (i < arr.size()) {
            if (arr[i] == 0) { return i; }
            i++;
        }
        return i;
    }

    void showMatrix() {
        cout << endl << "ћатрица : " << endl;
        for (int i = 0; i < countNode; i++) {
            cout << i + 1;
            for (int j = 0; j < countEdge; j++) {
                cout << "|" << setw(2) << matrix[j][i] << " ";
            }
            cout << "| \n";
        }
    }

    ~Graph() {
        // устранение утечек пам€ти
        for (int i = 0; i < countEdge; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

#endif //SAOD7LAB_GRAPH_H


