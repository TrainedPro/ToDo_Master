#ifndef DETAILEDTASKLIST_H
#define DETAILEDTASKLIST_H

#include "TaskList.hpp"

class DetailedTaskList : public TaskList{
protected:
    std::vector<std::vector<std::string>> subTasks;

public:
    void addTask(Task task, int id = -1);
    void addSubTask(std::string subTask, int id = -1, int subID = -1);
    void deleteTask(int id = -1);
    void deleteSubTask(int id = -1, int subID = -1);
    int getSubTaskLength(int)const;
    std::string getSubTask(int id = 0, int subID = 0);
    void sortID();
    void sortTitle();
    void sortDueDate();
    void sortDateAdded();
    virtual nlohmann::json getJson()const;
    virtual void setJson(const nlohmann::json &);
    void printTask(int);
};

void DetailedTaskList::addTask(Task task, int id) {
	if(id < 0 || id >= taskList.size()) {
        taskList.push_back(task);
        subTasks.push_back({});
    }
	else {
        taskList.insert(taskList.begin() + id, task);
        subTasks.insert(subTasks.begin() + id, {});
    }
}


void DetailedTaskList::addSubTask(std::string subTask, int id, int subID){
	if(id < 0 || id >= taskList.size()) return;

    else if(subID <= 0 || subID >= subTasks.at(id).size()){
        subTasks.at(id).push_back(subTask);
    }

	else subTasks.at(id).insert(subTasks.at(id).begin() + subID, subTask);
}

void DetailedTaskList::deleteTask(int id) {
	if(id >= 0 && id < taskList.size()){
        taskList.erase(taskList.begin() + id);
        subTasks.at(id).erase(subTasks.at(id).begin(), subTasks.at(id).end());
    }

}

void DetailedTaskList::deleteSubTask(int id, int subID){
    if(id < 0 || id > taskList.size()) return;

    else if(subID >= 0 || subID < subTasks.at(id).size()){
        subTasks.at(id).erase(subTasks.at(id).begin() + subID);
    }

    return;
}

int DetailedTaskList::getSubTaskLength(int id)const{
    return subTasks.at(id).size();
}

std::string DetailedTaskList::getSubTask(int id, int subID){
    if(id < 0 || id >= subTasks.size()) return "";
    if(subID < 0 || subID >= subTasks.at(id).size()) return "";
    return subTasks.at(id).at(subID);
}


void DetailedTaskList::sortID(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getID() > taskList[j].getID()){
                std::swap(taskList[i], taskList[j]);
                std::swap(subTasks.at(i), subTasks.at(j));
            }
        }
    }
}

void DetailedTaskList::sortTitle(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getTitle() > taskList[j].getTitle()) {
                std::swap(taskList[i], taskList[j]);
                std::swap(subTasks.at(i), subTasks.at(j));
            }
        }
    }
}

void DetailedTaskList::sortDueDate(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getDueDate() > taskList[j].getDueDate()) {
                std::swap(taskList[i], taskList[j]);
                std::swap(subTasks.at(i), subTasks.at(j));
            }
        }
    }
}

void DetailedTaskList::sortDateAdded(){
    for(int i = 0; i < taskList.size(); i++){
        for(int j = 0; j < taskList.size(); j++){
            if(taskList[i].getDateAdded() > taskList[j].getDateAdded()) {
                std::swap(taskList[i], taskList[j]);
                std::swap(subTasks.at(i), subTasks.at(j));
            }
        }
    }
}

nlohmann::json DetailedTaskList::getJson()const{
    nlohmann::json json;

    json.push_back({
        {"Type", "DetailedTaskList"},
    });

    for(int i = 0; i < taskList.size(); i++){
        json.push_back({
            {"title", taskList.at(i).getTitle()},
            {"subtasks: ", subTasks.at(i)},
            {"dueDate", taskList.at(i).getDueDate()},
            {"dateAdded", taskList.at(i).getDateAdded()},
            {"completed", taskList.at(i).isCompleted()}
        });
    }

    return json;
}

void DetailedTaskList::setJson(const nlohmann::json &json){
    Task currentTask;

    for(int i = 1; i < json.size(); i++){
        currentTask.setTitle(json.at(i)["title"]);
        subTasks.push_back(json.at(i)["subtasks"]);
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

void DetailedTaskList::printTask(int id){
    std::cout << "Task Title: " << taskList.at(id).getTitle() << std::endl;
    std::cout << "Due Date: " << taskList.at(id).epochToString(taskList.at(id).getDueDate()) << std::endl;
    std::cout << "Date Added: " << taskList.at(id).epochToString(taskList.at(id).getDateAdded()) << std::endl;
    std::cout << "SubTasks: ";
    if (subTasks.at(id).empty()) {
        std::cout << "No SubTasks Available" << std::endl;
    } else {
        for(int i = 0; i < subTasks.at(id).size(); i++){
            std::cout << i + 1 << ") " << subTasks.at(id).at(i) << std::endl;
        }
    }
}


#endif