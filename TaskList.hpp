#ifndef TASKLIST_H
#define TASKLIST_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Task.hpp"


class TaskList{
public:
    std::vector<Task> taskList;
    TaskList();
    void addTask(Task task, int id = -1);
    void deleteTask(int id = 0);
    Task& getTask(int id = 0);
    void sortID();
    void sortTitle();
    void sortDueDate();
    void sortDateAdded();
    ~TaskList();
};

TaskList::TaskList() {}

void TaskList::addTask(Task task, int id) {
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

#endif