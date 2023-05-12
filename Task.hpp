#ifndef TASK_H
#define TASK_H

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
   Task(std::string, std::string, time_t, time_t, bool);
   void setID(unsigned int);
   int getID()const;
   bool setTitle(const std::string &);
   std::string getTitle()const;
   void setDescription(const std::string &);
   std::string getDescription()const;
   void setDueDate(const time_t);
   time_t getDueDate()const;
   void setDateAdded(const time_t);
   time_t getDateAdded()const;
   void setCompleted(bool);
   bool isCompleted()const;
};

Task::Task(std::string title, std::string description, time_t dueDate, time_t dateAdded, bool completed) {
   setTitle(title);
   setDescription(description);
   setDueDate(dueDate);
   setDateAdded(dateAdded);
   setCompleted(completed);
}

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

int Task::getID()const {
   return id;
}

bool Task::setTitle(const std::string &title) {
   int words = 0;

   for (int i = 0; i < title.length(); i++) {
      if (title[i] == ' ') {
         words++;
      }
   }

   if (title.length() > 256 || words > 16) return false;
   else this->title = title;
   return true;
}

std::string Task::getTitle()const {
   return title;
}

void Task::setDescription(const std::string &description) {
   this -> description = description;
}

std::string Task::getDescription()const {
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
#endif