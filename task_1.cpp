#include <iostream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <map>

using namespace std;
struct task
{
    string name;
    time_t start;
    time_t finish;
    bool todo = false;
};
int begin(map<int, task> &tsk, int key)
{
    task ts;
    ts.start = time(nullptr);
    ts.todo = true;
    string taskName;
    cout << "Ввести наименование задачи. ";
    cin >> taskName;
    ts.name = taskName;
    int numberTask = key + 1;
    pair<int, task> oP(key, ts);
    tsk.insert(oP);
    return numberTask;
}
int end(map<int, task> &tsk, int key)
{
    if (tsk.count(key) != 0)
    {
        tsk[key].finish = time(nullptr);
        tsk[key].todo = false;
        int endTask = key;
        return endTask;
    }
    return 0;
}
void status(map<int, task> &tsk)
{
    for (pair<int, task> t : tsk)
    {
        if (t.second.todo == false)
        {
            cout << "Задание № - " << t.first << " " << t.second.name << endl;
            cout << "Время начала - " << asctime(localtime(&t.second.start)) << endl;
            cout << "Время завершения - " << asctime(localtime(&t.second.finish)) << endl;
            cout << "Продолжительность - " << difftime(t.second.finish, t.second.start) << " сек." << endl;
            cout << endl;
        }
        else
        {
            cout << "Задание № - " << t.first << " " << t.second.name << endl;
            cout << "Время начала - " << asctime(localtime(&t.second.start)) << endl;
            cout << "Задача в настоящее время выполняется" << endl;
        }
    }
    cout << endl;
}
void startGame(map<int, task> &tsk)
{
    int lastTask = 0;
    int actualTask = 1;
    string choice;
    while (choice != "exit")
    {
        cout << "Стартовать новыю задачу? Ответ \"begin\" - старт новой задачи, ответ \"end\" - завершение сопровождения незакрытой задачи." << endl;
        cout << "Для получения информации о текущем статусе ввести \"status\"" << endl;
        cout << "Для выхода из программы - \"exit\"" << endl;
        cout << "Ввод -> ";
        cin >> choice;
        if (choice == "begin")
        {
            if (tsk.size() != 0)
            {
                for (pair<int, task> t : tsk)
                {
                    lastTask = t.first;
                }
                lastTask = end(tsk, lastTask);
                actualTask = begin(tsk, (lastTask + 1));
            }
            else
            {
                actualTask = begin(tsk, actualTask);
            }
        }
        else if (choice == "status")
        {
            status(tsk);
        }
        else if (choice == "end")
        {
            if (tsk.size() != 0)
            {
                for (pair<int, task> t : tsk)
                {
                    lastTask = t.first;
                }
                lastTask = end(tsk, lastTask);
            }
            status(tsk);
        }
    }
}

int main()
{
    map<int, task> tasks;
    map<int, task> &ptr = tasks;
    cout << "Программа учета времени, потраченного на выполнение задач." << endl;
    startGame(ptr);
}