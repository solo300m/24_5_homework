#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

struct man
{
    string name;
    string lastName;
    int birthDay;
    int birthMonth;
    int birthYear;
};
void display(vector<man> &ptr)
{
    for (man m : ptr)
    {
        cout << m.name << " " << m.lastName << " " << m.birthDay << "/" << m.birthMonth << "/" << m.birthYear << endl;
    }
}
void newBirthday(vector<man> &ptr)
{
    cout << "Новый день рождения" << endl;
    string newName, newLastName;
    int day, month, year;
    cout << "Введите имя - ";
    cin >> newName;
    cout << "Введите фамилию - ";
    cin >> newLastName;
    cout << "Введите дату рождения в формате \"YYYY MM DD\", год, месяц, день. " << endl;
    cin >> year >> month >> day;
    man newM;
    newM.name = newName;
    newM.lastName = newLastName;
    newM.birthDay = day;
    newM.birthMonth = month;
    newM.birthYear = year;
    ptr.push_back(newM);
}
vector<man> sortVector(vector<man> &ptrVector)
{
    vector<man> clone;
    for (man t : ptrVector)
    {
        clone.push_back(t);
    }
    vector<man> rez;

    int count = clone.size();
    while (count != 0)
    {
        int idx = 0;
        int day = clone[0].birthDay;
        for (int i = 0; i < clone.size(); i++)
        {
            if (clone[i].birthDay <= day)
            {
                day = clone[i].birthDay;
                idx = i;
            }
        }
        count--;
        rez.push_back(clone[idx]);
        vector<man>::iterator it = clone.begin();
        clone.erase(it + idx);
    }
    return rez;
}
void nearestBirthday(vector<man> &ptr)
{
    time_t now = time(nullptr);
    tm *local = localtime(&now);
    int year = (local->tm_year == 123) ? 2023 : 0;
    int month = local->tm_mon + 1;
    int day = local->tm_mday;
    cout << "Now " << day << "/" << month << "/" << year << endl;
    int minDelta = 12;
    int idx = 0;
    int count = 0;

    vector<man> nearest;
    vector<man> &ptrVector = nearest;
    set<int> counters;
    bool start = false;
    for (man m : ptr)
    {
        if (((m.birthMonth - month) >= 0 && (m.birthMonth - month) < minDelta) && m.birthDay >= day)
        {
            minDelta = m.birthMonth - month;
            idx = count;
            start = true;
        }
        count++;
    }
    if (!start)
    {
        minDelta = 12;
        idx = 0;
        count = 0;
        for (man m : ptr)
        {
            if ((m.birthMonth - month) < minDelta)
            {
                minDelta = (m.birthMonth - month);
                idx = count;
                start = true;
            }
            count++;
        }
    }
    nearest.push_back(ptr[idx]);
    counters.insert(idx);
    month = nearest[0].birthMonth;
    count = 0;
    for (man m : ptr)
    {
        if (((m.birthMonth == month) && counters.count(count) == 0) && m.birthDay >= day)
        {
            idx = count;
            nearest.push_back(m);
            counters.insert(idx);
        }
        count++;
    }

    vector<man> sotr = sortVector(ptrVector);
    for (man m : sotr)
    {
        cout << m.name << " " << m.lastName << " " << m.birthDay << "/" << m.birthMonth << "/" << m.birthYear << endl;
    }
}
int main()
{
    vector<man> birthday;
    vector<man> &ptr = birthday;
    char oper = ' ';
    while (oper != '0')
    {
        cout << "Ввести тип операции. '1' - ввод нового дня рождения, '2' - завершение ввода, '0'- выити из программы" << endl;
        cin >> oper;
        if (oper == '1')
        {
            newBirthday(ptr);
            display(ptr);
        }
        else if (oper == '2')
        {
            nearestBirthday(ptr);
        }
        else if (oper == '0')
        {
            cout << "Завершение работы программы" << endl;
        }
    }
}