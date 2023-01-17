#include <iostream>
#include <ctime>
#include "windows.h"
#include <ctype.h>
#include <conio.h>
using namespace std;

class StopWatch {

    int sec;
    bool start;
    clock_t start_time;
    int value;

public:
    StopWatch();
    StopWatch(int sec, bool start, clock_t start_time, int value);
    StopWatch(const StopWatch& other);
    ~StopWatch();
    void Start();
    void Stop();
    void Show();
};
StopWatch::StopWatch() {
    sec = 0;
    start = false;
    value = 0;
    start_time = false;
}
StopWatch::StopWatch(int sec, bool start, clock_t start_time, int value) {
    this->sec = sec;
    this->start = start;
    this->value = value;
    this->start_time = start_time;
}
StopWatch::StopWatch(const StopWatch& other) {//конструктор копирования

    sec = other.sec;
    start = other.start;
    value = other.value;
    start_time = other.start_time;
}
StopWatch::~StopWatch() {// деструктор
    cout << "Время выполнения программы: " << (clock() - start_time) / CLOCKS_PER_SEC << " сек" << endl;
}
void StopWatch::Start() {
    if (start) {
        return;
    }
    start_time = clock();
    start = true;

    while (!_kbhit()) {// проверка на нажатие клавиши для остановки
        Sleep(1000);// задержка выполнения программы на 1 сек

        sec++;
        cout << sec << endl;
    }

}
void StopWatch::Show() {
    if (start) {
        cout << "Секунд прошло: " << sec << endl;

    }


}
void StopWatch::Stop() {
    if (!start) {
        return;
    }

    value += (clock() - start_time) / CLOCKS_PER_SEC;
    start = false;

}


int main() {
    setlocale(LC_ALL, "ru");

    /* cout << "1.по умолчанию" << endl<< "2.копирование"<<endl<< "3.с параметром" << endl;
     cin >> i;*/
    StopWatch countdown;



    cout << "Вызов конструктора по умолчанию" << endl;
    cout << "Старт: " << endl;
    countdown.Start();
    countdown.Stop();
    cout << "Стоп: " << endl;
    countdown.Show();
    int i;
    cin >> i;
    if (i == 0) {
        StopWatch countdown2(countdown);
        cout << "Вызов конструктора копирования" << endl;
        cout << "Старт: " << endl;
        countdown2.Start();
        countdown2.Stop();
        cout << "Стоп: " << endl;
        countdown2.Show();

    }

    cin >> i;
    if (i == 0) {
        StopWatch countdown3(5, false, 0, false);
        cout << "Вызов конструктора c параметром" << endl;
        cout << "Старт: " << endl;
        countdown3.Start();
        countdown3.Stop();
        cout << "Стоп: " << endl;
        countdown3.Show();
    }

    return 0;
}
