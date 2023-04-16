#include<iostream>
#include<iomanip>
#include<ctime>
#include <algorithm>
#include <vector>
#include<time.h>
#include"Sort.h"
#include"TaskList.h"

using namespace std;
class Task
{
private:
      int id;
      string Title;
      string Descrition;
      bool completed;
      tm date;
      static int priority;     
public:
   Task();
   void setId(int id1 );
   int getId();
   void setTitle(string tit);
   void setDescrption(string des);
   void setTask(string task);
   void toComplete();
   string getTitle();
   string getDescrption();
   void setTime(int,int,int);
   tm getTime();
   bool checkStatus();
   ~Task();
};
Task::Task() {
    Title="TITLE";
    Descrition="DESCRPTION";
    completed=false;
    priority++;
}
void Task::setTitle(string tit)
{
    Title=tit;
}
string Task::getTitle()
{
    return Title;
}
void Task::setId(int id1)
{
        id = id1;
}
int Task:: getId()
{
    return id;
}
void Task::setDescrption(string des){
     Descrition=des;
   }
   void Task::setTask(string task) {
      int count;
      while(1){
         count=0;
         for (int i = 0; i < task.length(); i++)
         {
            if (task[i]==' ')
            {
               count++;
            }
            
         }
         
      if (task.length()>256 || count>15)
      {
         cout<<"TITLE CANT BE GRETER THEN 256 WORD"<<endl;
         cout<<"enter title  again"<<endl;
         getline(cin>>ws,task);
      }
      else{
      this->Title=task;
        break;
      }
      }
   }
   void Task::toComplete() {
    completed=true;
   }
  
   string Task::getDescrption() {
    return Descrition;
   }
   void Task::setTime(int mon1,int day1, int year1) {
//      this->date=date;
		date.tm_year = year1 - 1900;
        date.tm_mon = mon1 - 1;
        date.tm_mday = day1;
   }
   tm Task::getTime() {
      
      return date;
   }
   bool Task::checkStatus() {
    return completed;
   }
   Task::~Task() {
      priority--;
   }
   int Task::priority = 0;

class view {
protected:
    vector<TaskList> tasks;

public:
    view(vector<TaskList>& tasks1 = {}) {
        tasks = tasks1;
    }

    void mainmenu() {
        int x = 0;
        do {
            cout << "1) View Menu\n2) Change Task\n3) Delete All Task\n4) Exit" << endl;
            cin >> x;
            switch (x) {
                case 1:
                	vector<Task> tasks;
                	
                	Sort obj;
                    cout << "1) Sort Id\n2) Sort Title\n3) Sort date\n4) Completed" << endl;
                    int y;
                    cin >> y;
                    switch (y) {
                        case 1:
                        	obj.sortid(tasks);
                            break;
                        case 2:
                        	obj.sortTitle(tasks);
                            break;
                        case 3:
                        	obj.sortDate(tasks);
                            break;
                        case 4:
                        	obj.completed(tasks);
                            break;
                        default:
                            cout << "enter number btw 1-4" << endl;
                            break;
                    }
                    break;
                case 2:
                    cout << "1) add Task\n2) update Task\n3) delete Task" << endl;
                    TaskList obj1;
                    int z;
                    cin >> z;
                    switch (z) {
                        case 1:
                            Task task;
                            cout<<"enter id"<<endl;
                            int e;
                            cin>>e;
                            task.setId(e);
                            cout << "enter title" << endl;
                            string title;
                            getline(cin >> ws, title);
                            task.setTitle(title);
                            cout << "enter description" << endl;
                            string des;
                            getline(cin >> ws, des);
                            task.setDescription(des);
                            cout << "enter date mm/dd/yy" << endl;
                            int day, month, year;
                            cin >> month >> day >> year;
                            task.setDueDate(month, day, year);
                            int index;
                            cout<<"enter index at which you want to add the task"<<endl;
                            cin>>index;
                            obj1.addTask(index,task);
                         //   tasks.push_back(task);
                            break;
                        case 2:
                        	int integer;
                        	cout<<"enter task number to be updated "<<endl;
                        	cin>>integer;
                        	Task *object=obj1.getTask(integer);
                        	cout<<"enter id"<<endl;
                            int e;
                            cin>>e;
                            task->setId(e);
                            cout << "enter title" << endl;
                            string title;
                            getline(cin >> ws, title);
                            task->setTitle(title);
                            cout << "enter description" << endl;
                            string des;
                            getline(cin >> ws, des);
                            task->setDescription(des);
                            cout << "enter date mm/dd/yy" << endl;
                            int day, month, year;
                            cin >> month >> day >> year;
                            task->setDueDate(month, day, year);
                            int index;
                            cout<<"enter index at which you want to add the task"<<endl;
                            cin>>index;
                            obj1->addTask(index,task);
                            // update task
                            
                            break;

                        case 3:
                            cout << "enter the index" << endl;
                            int ind;
                            cin >> ind;
                            obj1.deleteTask(ind);

                            break;
                    }
                    break;
                case 3:
                    tasks.clear();
                    break;
            }
        } while (x != 4);
    }
};



class Sort : public View{

public:
   void sortid(vector<Task> &tasks);
   void sortDate(vector<Task> &tasks);
   void sortitle(vector<Task> &tasks);
   void completed(vector<Task> &tasks);
};
void Sort::sortid(vector<Task> &tasks) {
    // make vector of Task class protected in TaskList, so it can be use by sort class
    for (int i = 0; i < tasks.size(); i++) {
        for (int j = i + 1; j < tasks.size(); j++) {
            if (tasks[i].getId() < tasks[j].getId()) {
                Task temp=tasks[i];
                tasks[i]=tasks[j];
                tasks[j]=temp;
            }
        }
    }
}
void Sort::sortDate(vector<Task> &tasks) {
    for (int i = 0; i < tasks.size(); ++i) {
        for (int j = i; j < tasks.size() - 1; ++j) {
            tm temp = tasks[j].getTime();
            time_t seconds = mktime(&temp);
            tm temp1 = tasks[j + 1].getTime();
            time_t seconds1 = mktime(&temp1);
            if (seconds < seconds1) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}
void Sort::sortitle(vector<Task> &tasks)
{
 for (int i = 0; i < tasks.size(); i++) {
         for (int j = i + 1; j < tasks.size(); j++) {
         string var = tasks[i].getTitle();
         string var1 = tasks[j].getTitle();
             if (var > var1) {
                 Task temporary = tasks[i];
                 tasks[i] = tasks[j];
                 tasks[j] = temporary;
             }
         }
     }
}
 void Sort::completed(vector<Task> &tasks)
 {
     for(int i=0;i<tasks.size();i++)
     {
         if(tasks[i].checkStatus != completed)
     {
     	 cout<<tasks[i].getId()<<endl;
         cout<<tasks[i].getTitle()<<endl;
         cout<<tasks[i].getDescription()<<endl;
         cout << tasks[i].getTime().tm_mon + 1 << "/"
             << tasks[i].getTime().tm_mday << "/"
             << tasks[i].getTime().tm_year + 1900 << endl;
     }
  }
    
 }
 
 
int main()
{
	View obj;
	obj.mainmenu();
    // for printing
    vector<Task> tasks;
    for(int i=0; i<tasks.size(); i++)
    {
        cout<<tasks[i].getId()<<endl;
        cout<<tasks[i].getTitle()<<endl;
        cout<<tasks[i].getDescrption()<<endl;
         // Print the sorted dates
    
        cout << "Date " << i + 1 << ": "
             << tasks[i].getTime().tm_mon + 1 << "/"
             << tasks[i].getTime().tm_mday << "/"
             << tasks[i].getTime().tm_year + 1900 << endl;
    
    }
    return 0;
}