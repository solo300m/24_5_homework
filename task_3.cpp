#include <iostream>
#include <ctime>
#include <iomanip>
#include <windows.h>

using namespace std;
void timer(int min, int sec)
{
    int secAll = sec + (min * 60);
    while (secAll != 0)
    {
        cout << secAll / 60 << ":" << secAll % 60 << endl;
        Sleep(1000);
        secAll--;
    }
}
int main()
{
    int minute;
    int secunde;
    cout << "Таймер" << endl;
    cout << "Введите через пробел количество минут и секунд и нажмите Enter." << endl;
    cin >> minute >> secunde;
    timer(minute, secunde);
    cout << "DING, DING, DING!" << endl;
}