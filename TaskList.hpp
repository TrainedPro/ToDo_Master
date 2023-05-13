#ifndef TASKLIST_H
#define TASKLIST_H

#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Task.hpp"
#include "include/json/json.hpp"

class TaskList{
public:
    std::vector<Task> taskList;
    TaskList();
    virtual void addTask(Task task, int id = -1);
    virtual void deleteTask(int id = -1);
    Task getTask(int id = -1);
    virtual void sortID();
    virtual void sortTitle();
    virtual void sortDueDate();
    virtual void sortDateAdded();
    
    friend std::ostream& operator<<(std::ostream&, TaskList);

    virtual nlohmann::json getJson()const;
    virtual void setJson(const nlohmann::json &);
    ~TaskList();
};

TaskList::TaskList() {}

void TaskList::addTask(Task task, int id) {
	if(id < 0 || id >= taskList.size()) taskList.push_back(task);
	else taskList.insert(taskList.begin() + id, task);
}

void TaskList::deleteTask(int id) {
	if(id >= 0 && id < taskList.size()) taskList.erase(taskList.begin() + id);
}

Task TaskList::getTask(int id) {
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

std::ostream& operator<<(std::ostream& cout, TaskList allTasks){
    cout << "#      Due Date     Title\n";
    cout << "------------------------------------\n";
    for (int i = 0; i < allTasks.taskList.size(); ++i) {
        cout << std::setw(4) << std::left << i + 1 << " | ";
        cout << allTasks.taskList.at(i).epochToString(allTasks.taskList.at(i).getDueDate()) << " | ";
        cout << std::setw(12) << allTasks.taskList.at(i).getTitle() << std::endl;
    }
    return cout;
}

nlohmann::json TaskList::getJson()const{
    nlohmann::json json;

    json.push_back({
        {"Type", "TaskList"},
    });

    for(const Task& currentTask : taskList){
        json.push_back({
            {"title", currentTask.getTitle()},
            {"description", currentTask.getDescription()},
            {"dueDate", currentTask.getDueDate()},
            {"dateAdded", currentTask.getDateAdded()},
            {"completed", currentTask.isCompleted()}
        });
    }

    return json;
}

void TaskList::setJson(const nlohmann::json &json){
    Task currentTask;
    for(int i = 1; i < json.size(); i++){
        currentTask.setTitle(json.at(i)["title"]);
        currentTask.setDescription(json.at(i)["description"]);
        currentTask.setDueDate(json.at(i)["dueDate"]);
        currentTask.setDateAdded(json.at(i)["dateAdded"]);
        currentTask.setCompleted(json.at(i)["completed"]);
        taskList.push_back(currentTask);
    }
    this->sortDueDate();

    for(int i = 0; i < taskList.size(); i++){
        taskList[i].setID(i + 1);
    }
}

TaskList::~TaskList() {}

#endif