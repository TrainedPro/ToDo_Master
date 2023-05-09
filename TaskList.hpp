#ifndef TASKLIST_H
#define TASKLIST_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Task.hpp"


class TaskList {
private:
    std::vector<Task> taskList;

public:
    TaskList();
    void addTask(int id = -1, Task task);
    void deleteTask(int id = 0);
    void printAllTasks();
    Task& getTask(int id = 0);
    void sortID();
    void TaskList::sortTitle();
    void TaskList::sortDueDate();
    void TaskList::sortDateAdded();
    ~TaskList();


};

TaskList::TaskList() {}

void TaskList::addTask(int id, Task task) {
	if(id < 0 || id > taskList.size()) taskList.push_back(task);
	else taskList.insert(taskList.begin() + id, task);
}

void TaskList::deleteTask(int id) {
	if(id >= 0 && id < taskList.size()) taskList.erase(taskList.begin() + id);
}

Task& TaskList::getTask(int id) {
    return taskList.at(id);
}

void TaskList::sortID(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getID() > taskList[j].getID()) std::swap(taskList[i], taskList[j]);
        }
    }
}

void TaskList::sortTitle(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getTitle() > taskList[j].getTitle()) std::swap(taskList[i], taskList[j]);
        }
    }
}

void TaskList::sortDueDate(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getDueDate() > taskList[j].getDueDate()) std::swap(taskList[i], taskList[j]);
        }
    }
}

void TaskList::sortDateAdded(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getDateAdded() > taskList[j].getDateAdded()) std::swap(taskList[i], taskList[j]);
        }
    }
}

TaskList::~TaskList() {}

#endif TASKLIST_H