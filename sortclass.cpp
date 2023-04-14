#include <iostream>
#include <algorithm>
#include <vector>
#include<ctime>
#include"Task.cpp"
using namespace std;

// class Task {
//     int id;
//     string title;
//     string description;
//  //   bool string s=comleted;
// public:
//     task(int id1 = 0, string s="", string d="") {
//         setid(id1);
//         setitle(s);
//         setdes(d);
//     }
//     void setdes(string d)
//     {
//     description = d;
// }
// string getdes()
// {
// return description;
// }
//     void setitle(string s)
//     {
//     title=s;
// }
// string getitle()
// {
// return title;
// }
//     void setid(int id1) {
//         id = id1;
//     }
//     int getid() {
//         return id;
//     }
//     void print()
//     {
//     cout<<id<<endl;
//     cout<<title<<endl;
//     cout<<description<<endl;
// }
// };

class Sort{
  //  task obj1[3];
public:
//     Sortid() {
//     cout<<"enter ids with title"<<endl;
//     for(int i=0; i<3;i++)
//     {
//     int x;
//     cin>>x;
//     obj1[i].setid(x);
//     string s;
//     getline(cin>>ws,s);
//     obj1[i].setitle(s);
//     string d;
//     getline(cin>>ws,d);
//     obj1[i].setdes(d);
// }
//     }
   void sortid() {
    for (int i = 0; i < tasks.length(); i++) {
        for (int j = i + 1; j < 3; j++) {
            if (tasks[i].getid() < tasks[j].getid()) {
                Task temp=tasks[i];
                tasks[i]=tasks[j];
                tasks[j]=temp;
            }
        }
    }
}
void sortdate {
for (int i = 0; i < task.length(); ++i) {
        for (int j = 0; j < 1; ++j) {
            tm temp = tasks[j].getdate();
            time_t seconds = mktime(&temp);
            tm temp1 = tasks[j + 1].getdate();
            time_t seconds1 = mktime(&temp1);
            if (seconds < seconds1) {
                tasks[j].setdate(temp1.tm_mon + 1, temp1.tm_mday, temp1.tm_year + 1900);
                tasks[j + 1].setdate(temp.tm_mon + 1, temp.tm_mday, temp.tm_year + 1900);
            }
        }
    }
}

void sortitle()
{
for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
        string var=tasks[i].getitle();
        string var1=tasks[j].getitle();
            if (var>var1) {
                task temp=tasks[i];
                tasks[i]=tasks[j];
                tasks[j]=temp;
            }
        }
    }
}


void print()
{
cout << "Sorted IDs (from greatest to smallest):" << endl;
for(int i=0;i<3;i++)
{
obj1[i].print();

}
}

};
int main()
{
Sortid obj;
Task obj2;

// obj.sortid();
obj.sortitle();
obj.print();
}