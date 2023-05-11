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

int main(void){
    DetailedTaskList longTask;
    Task task1;
    longTask.addTask(task1, 0);
    longTask.addSubTask("Hello World!", 0);
    longTask.addSubTask("Hello World 2", 0);

    std::cout << "Main Task: " << longTask.getTask(0).getTitle() << std::endl;
    for(int i = 0; i < longTask.getSubTaskLength(0); i++){
        std::cout << "  SubTask:" << longTask.getSubTask(0, i) << std::endl;
    }

    return 0;
    
}


#endif