#include <iostream>
#include <ctime>

class Task {
   int id;
   std::string title;
   std::string description;
   tm date;
   bool completed;

public:
   Task(tm date = {0}, std::string title = "Null Title", std::string description = "Null Description", bool completed = false);
   void setID(unsigned int);
   int getID();
   void setTitle(std::string &);
   std::string getTitle();
   void setDescription(std::string &);
   std::string getDescription();
   void setDate(tm &);
   tm getDate()const;
   void setCompleted(bool);
   bool isCompleted()const;
};

Task::Task(tm date, std::string title, std::string description, bool completed) {
   setTitle(title);
   setDescription(description);

   time_t currentTime;
   time(&currentTime);
   tm *dateCopy = localtime(&currentTime);
   setDate(*dateCopy);
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

void Task::setDate(tm &date) {
   this->date = date;
}

tm Task::getDate()const{
   return date;
}

int main() {
   Task a1;
   return 0;
}