#include <iostream>
#include <ctime>

class Task {
   int id;
   std::string title;
   std::string description;
   time_t dueDate;
   time_t dateAdded;
   bool completed;

public:
   Task(std::string title = "Null Title", std::string description = "Null Description", time_t dueDate = 0, bool completed = false);
   void setID(unsigned int);
   int getID();
   void setTitle(std::string &);
   std::string getTitle();
   void setDescription(std::string &);
   std::string getDescription();
   void setDueDate(const time_t);
   time_t getDueDate()const;
   void setDateAdded(const time_t);
   time_t getDateAdded()const;
   void setCompleted(bool);
   bool isCompleted()const;
};

Task::Task(std::string title, std::string description, time_t dueDate, bool completed) {
   setTitle(title);
   setDescription(description);

   time(&dueDate); // set the time to current time in epoch

   setDueDate(dueDate);
   setDateAdded(dueDate);

   setCompleted(completed);
}

void Task::setID(unsigned int id) {
   this->id = id;
}

int Task::getID() {
   return id;
}

void Task::setTitle(std::string &title) {
   int words;

   while (1) {
      words = 0;
      for (int i = 0; i < title.length(); i++) {
         if (title[i] == ' ') {
            words++;
         }
      }

      if (title.length() > 256 || words > 15) {
         std::cout << "Make Title Fewer Than 16 Words And 256 Characters: " << std::endl;
         getline(std::cin >> std::ws, title);
      } else {
         this->title = title;
         break;
      }
   }
}

std::string Task::getTitle() {
   return title;
}

void Task::setDescription(std::string &description) {
   this -> description = description;
}

std::string Task::getDescription() {
   return description;
}

void Task::setCompleted(bool completed){
   this -> completed = completed;
}

bool Task::isCompleted()const{
   return completed;
}

void Task::setDueDate(const time_t dueDate) {
   this->dueDate = dueDate;
}

time_t Task::getDueDate()const{
   return dueDate;
}

void Task::setDateAdded(const time_t dateAdded) {
   this->dateAdded = dateAdded;
}

time_t Task::getDateAdded()const{
   return dateAdded;
}

int main() {
   Task a1;
   return 0;
}