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
   Task(/* args */);
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
      this->Title=task;
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

    return 0;
}
