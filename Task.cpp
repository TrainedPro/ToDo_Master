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
      int id;     
public:
   Task();
   void setDescrption(string des);
   void setTitle(string title);
   void toComplete();
   string getTitile();
   string getDescrption();
   void setTime(tm date);
   tm getTime();
   void set_id(int id);
   int get_id();
   bool checkStatus();
   ~Task();
};
Task::Task() {
    Title="TITLE";
    Descrition="DESCRPTION";
    completed=false;
    id++;
}
void Task::setDescrption(string des){
     Descrition=des;
   }
   void Task::setTitle(string title) {
      int count;
      while(1){
         count=0;
         for (int i = 0; i < title.length(); i++)
         {
            if (title[i]==' ')
            {
               count++;
            }
            
         }
         
      if (title.length()>256 || count>15)
      {
         cout<<"TITLE CANT BE GRETER THEN 256 WORD"<<endl;
         cout<<"enter title  again"<<endl;
         getline(cin>>ws,title);
      }
      else{
      this->Title=title;
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
   void Task::set_id(int id) {
      if (id<0)
      {
         cout<<"ID CANT BE NEGATIVE "<<endl;
      }
      else{

         this->id=id;
      }
      
   }
   int Task::get_id() {
      return id;
   }
   bool Task::checkStatus() {
      return completed;
   }
   Task::~Task() {
      id--;
   }
   int main() {
      Task a1;
      a1.setTitle("AAIS   ");
    return 0;
}
