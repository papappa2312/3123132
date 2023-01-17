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
StopWatch::StopWatch(const StopWatch& other) {//����������� �����������

    sec = other.sec;
    start = other.start;
    value = other.value;
    start_time = other.start_time;
}
StopWatch::~StopWatch() {// ����������
    cout << "����� ���������� ���������: " << (clock() - start_time) / CLOCKS_PER_SEC << " ���" << endl;
}
void StopWatch::Start() {
    if (start) {
        return;
    }
    start_time = clock();
    start = true;

    while (!_kbhit()) {// �������� �� ������� ������� ��� ���������
        Sleep(1000);// �������� ���������� ��������� �� 1 ���

        sec++;
        cout << sec << endl;
    }

}
void StopWatch::Show() {
    if (start) {
        cout << "������ ������: " << sec << endl;

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

    /* cout << "1.�� ���������" << endl<< "2.�����������"<<endl<< "3.� ����������" << endl;
     cin >> i;*/
    StopWatch countdown;



    cout << "����� ������������ �� ���������" << endl;
    cout << "�����: " << endl;
    countdown.Start();
    countdown.Stop();
    cout << "����: " << endl;
    countdown.Show();
    int i;
    cin >> i;
    if (i == 0) {
        StopWatch countdown2(countdown);
        cout << "����� ������������ �����������" << endl;
        cout << "�����: " << endl;
        countdown2.Start();
        countdown2.Stop();
        cout << "����: " << endl;
        countdown2.Show();

    }

    cin >> i;
    if (i == 0) {
        StopWatch countdown3(5, false, 0, false);
        cout << "����� ������������ c ����������" << endl;
        cout << "�����: " << endl;
        countdown3.Start();
        countdown3.Stop();
        cout << "����: " << endl;
        countdown3.Show();
    }

    return 0;
}
