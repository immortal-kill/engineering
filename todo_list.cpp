#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <limits>
#include <fstream>

using namespace std;

struct Task {
    string task_name;
    bool completed;

};



void showMenu(){
    cout<<"====Todo List===="<<endl;
    cout<<"1.添加任务"<<endl;
    cout<<"2.查看任务"<<endl;
    cout<<"3.完成任务"<<endl;
    cout<<"4.删除任务"<<endl;
    cout<<"5.退出"<<endl;
    cout<<"请选择:";

}


void addTask(vector<Task>&tasks) {        // vector<Task>是参数类型     &引用  tasks是参数名
    Task t;

    cout<<"请输入任务名称："<<endl;
    getline(cin,t.task_name);

    t.completed = false;

    tasks.push_back(t);

    cout<<"添加成功！"<<endl;

}

void showTasks(const vector<Task>&tasks){
    if (tasks.empty()) {
        cout << "暂无任务。" << endl;
        return;
    }

    cout << "==== 当前任务 ====" << endl;
    for (size_t i = 0; i < tasks.size() ;i++) {
        cout<<i+1<<".";
        if (tasks[i].completed) {
            cout<<"[x]";
        }else {
            cout<<"[ ]";
        }
        cout << tasks[i].task_name << endl;
    }


}

void completeTask(vector<Task>&tasks){
    if (tasks.empty()) {
        cout<<"暂无任务："<<endl;
        return;
    }
    showTasks(tasks);

    int number;
    cout<<"请输入要完成的任务编号:";
    cin>>number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    if (number < 1 || number > tasks.size()) {
        cout<<"无效的任务编号"<<endl;
        return;
    }

    tasks[number - 1].completed = true;

    cout<<"任务已完成："<<endl;
}

void deleteTask(vector<Task>&tasks){
    if (tasks.empty()) {
        cout<<"暂无任务，无法删除。"<<endl;
        return;
    }

    showTasks(tasks);
    int number;
    cout<<"请输入要删除的任务编号·：";
    cin>>number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (number < 1 || number > tasks.size()) {
        cout<<"无效的任务编号"<<endl;
        return;
    }
    tasks.erase(tasks.begin()+number-1);
    cout<<"任务删除完成!"<<endl;
}

void saveTasks(const vector<Task>& tasks) {           //数据持久化
    ofstream file("tasks.txt");

    for (const Task& task : tasks) {
        file << task.completed << "|"
             << task.task_name << endl;
    }
}

void loadTasks(vector<Task>& tasks) {
    ifstream file("tasks.txt");

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        Task task;
        task.completed = line[0] == '1';
        task.task_name = line.substr(2);

        tasks.push_back(task);
    }
}

    int main()  {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        vector<Task> tasks;

        loadTasks(tasks);

        int choice;

        while(true) {
            showMenu();
            cin>>choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(choice) {
                case 1:
                    addTask(tasks);
                    break;

                case 2:
                    showTasks(tasks);
                    break;

                case 3:
                    completeTask(tasks);
                    break;

                case 4:
                    deleteTask(tasks);
                    break;


                case 5:
                    saveTasks(tasks);
                    cout<<"程序退出："<<endl;
                    return 0 ;

                default:
                    cout<<"无效选项。"<<endl;
                    break;
            }
        }
    }


