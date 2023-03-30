#include<iostream>
#include<iomanip>
#include<ctime>
using namespace std;
class Task
{
private:
      string Title;
      string Descrition;
      bool completed;
      tm date;
      static int priority;     
public:
   Task();
   void setDescrption(string des);
   void setTask(string task);
   void toComplete();
   string getTitile();
   string getDescrption();
   void setTime(tm date);
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
   string Task::getTitile() {
    return Title;
   }
   string Task::getDescrption() {
    return Descrition;
   }
   void Task::setTime(tm date) {
      this->date=date;
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
   int main() {
      Task a1;
      a1.setTask("AAIS   ");
    return 0;
}
