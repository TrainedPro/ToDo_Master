#include <iomanip>
#include <iostream>
#include <ctime>

using namespace std;

class Task {
    static int ID;
    string title;
    string description;
    tm date;
    bool completed;

public:
    Task(/* args */);
    void ADDtask();
    void setDescription(string des);
    void set_Task(string task);
    void to_complete();
    string get_titile();
    string get_descrption();
    bool check_status();
    void print();
    void del_task();
};

Task::Task() {
    title = "TITLE";
    description = "DESCRPTION";
    completed = false;
    size = 0;
}

void Task::ADDtask() {
    string title;
    string description;
    Task *temp = new Task[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = no_of_task[i];
    }
    cout << "ENTER TITLE: " << endl;
    cin >> title;
    cout << "ENTER DESCRPTION : " << endl;
    cin >> description;
    temp[size].set_Task(title);
    temp[size].setDescription(description);
    size++;
    no_of_task = temp;
}

void Task::setDescription(string des) {
    description = des;
}

void Task::set_Task(string task) {
    this->title = task;
}

void Task::to_complete() {
    completed = true;
}

string Task::get_titile() {
    return title;
}

string Task::get_descrption() {
    return description;
}

bool Task::check_status() {
    return completed;
}

void Task::print() {

    for (int i = 0; i < size; i++) {
        cout << "TITLE : " << no_of_task[i].title << endl;
        cout << "DESCRPTION : " << endl
             << "            " << no_of_task[i].description << endl;
        if (no_of_task[i].check_status()) {
            cout << "TASK : "
                 << "TASK COMPLETED" << endl;
        } else {
            cout << "TASK   : "
                 << "TASK UNCOMPLETED" << endl;
        }
    }
}
void Task::del_task() {
    int index;

    cout << "ENTER NO YOU WANT TO DELETE: ";
    cin >> index;
    if (index > size || index < 1) {
        cout << "TASK DOESNOT EXIST " << endl;
    } else {
        index = index - 1;
        Task *temp;
        temp = new Task[size - 1];
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (i == index) {
                continue;
            } else {
                temp[j++] = no_of_task[i];
            }
        }
        //   delete []no_of_task;
        //   no_of_task=NULL;
        no_of_task = temp;
        delete[] temp;
        size--;
    }
}
int main() {

    Task a1;
    a1.ADDtask();
    a1.ADDtask();
    a1.del_task();
    a1.print();

    return 0;
}
