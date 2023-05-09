/*

IOClass Documentation:

The IOClass is a class designed to handle input/output operations related to JSON files. It provides two main methods for these operations, readAll() and writeAll(), which respectively read all the data from a JSON file and write all the data to a JSON file.

To use the IOClass, follow these steps:

Create an instance of the IOClass by calling its constructor with the file name as its argument. For example, IOClass IOOperations("test.json");.
To read the data from the file, call the readAll() method on the IOClass object. This method will read all the data from the file and store it in the IOClass object's tasks vector.
To write the data to the file, call the writeAll() method on the IOClass object. This method will write all the data stored in the tasks vector to the file.
Optionally, you can test the read and write operations by calling the testReadOperations() and testWriteOperations() methods on the IOClass object, respectively. The testReadOperations() method reads data from a test JSON file, while the testWriteOperations() method generates random data and writes it to a test JSON file.


*/

#ifndef IOCLASS_H
#define IOCLASS_H

#include <iostream>
#include <vector>
#include <fstream>
#include "include/json/json.hpp"
#include "Task.hpp"
#include "TaskList.hpp"

class IOClass{
    std::string fileName;

    public:
    TaskList tasks;
    IOClass(std::string &);

    void setFileName(const std::string &fileName); // formatting and validating fileName
    std::string getFileName()const;
    bool readAll();
    bool writeAll() const;
    void testWriteOperations();
    void testReadOperations(std::string fileName = "test.json");
};

IOClass::IOClass(std::string &fileName){
    setFileName(fileName);
}

void IOClass::setFileName(const std::string &fileName) { // formatting and validating fileName
    this->fileName = fileName;
    
    this->fileName.erase(0, this->fileName.find_first_not_of(" ")); // Remove leading white spaces

    this->fileName.erase(this->fileName.find_last_not_of(" ") + 1); // Remove trailing white spaces

    if (this->fileName.length() < 6) {
        this->fileName += ".json";
    }
    else if(this->fileName.substr(this->fileName.length() - 5) != ".json"){
        std::string extension = this->fileName.substr(this->fileName.length() - 5);

        std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c){ return std::tolower(c); });

        if (extension == ".json") { // checks for cases such as ".JsOn" or other upper and lower case combinations
            this->fileName.replace(this->fileName.length() - 5, 5, ".json");
        }
        else{
            this->fileName += ".json";
        }
    }
}

std::string IOClass::getFileName()const{
    return fileName;
}

bool IOClass::readAll() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed To Open File " + fileName);
        return false;
    }

    nlohmann::json json;
    file >> json;

    int i = 0;
    for(const auto& jsonData: json){
        i++;
        Task currentTask;
        currentTask.setID(i);
        std::string strings = jsonData["title"]; // temporary variable to store all strings

        currentTask.setTitle(strings);
        strings = jsonData["description"];
        currentTask.setDescription(strings);
        currentTask.setDueDate(jsonData["dueDate"]);
        currentTask.setDateAdded(jsonData["dateAdded"]);
        currentTask.setCompleted(jsonData["completed"]);

        tasks.addTask(currentTask);
    }

    return true;
}

bool IOClass::writeAll() const {
    std::string tempFileName = "temp_" + fileName;

    if (std::filesystem::exists(tempFileName)) {
        
        if(std::filesystem::exists(fileName)){
            if (std::remove(tempFileName.c_str())) {
                throw std::runtime_error("Failed To Delete Old Temp File " + tempFileName);
                return false;
            }
        }
        else{
            if (std::rename(tempFileName.c_str(), fileName.c_str())) {
                throw std::runtime_error("Failed To Rename Temporary File At Start " + tempFileName + " To " + fileName);
                return false;
            }
        }
    }

    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open()) {
        throw std::runtime_error("Failed To Create Temporary File " + tempFileName);
        return false;
    }

    nlohmann::json json;
    for (const Task& currentTask : tasks.taskList) {
        json.push_back({
            {"title", currentTask.getTitle()},
            {"description", currentTask.getDescription()},
            {"dueDate", currentTask.getDueDate()},
            {"dateAdded", currentTask.getDateAdded()},
            {"completed", currentTask.isCompleted()}
        });
    }

    tempFile << std::setw(4) << json << std::endl;
    tempFile.close();

    // Replace old file with new one
    if (std::filesystem::exists(fileName)) {
        if (std::remove(fileName.c_str())) {
            throw std::runtime_error("Failed To Delete Old File " + fileName);
            return false;
        }
    }
    if (std::rename(tempFileName.c_str(), fileName.c_str())) {
        throw std::runtime_error("Failed To Rename Temporary File " + tempFileName + " To " + fileName);
        return false;
    }

    return true;
}

void IOClass::testWriteOperations(){
    srand(time(NULL)); // initialize random seed
    std::string tempFileName = fileName;
    fileName = "test.json";

    for (int i = 0; i < 100; i++)  {
        Task operations;
        operations.setTitle("Task " + std::to_string(i + 1));
        operations.setDescription("This is task number " + std::to_string(i + 1));
        operations.setDueDate(time(NULL) + (rand() % 128) * 86400); // set due date to be up to 128 days in the future
        operations.setDateAdded(time(NULL) - (rand() % 64) * 86400); // set date added to be up to 64 days in the past
        operations.setCompleted(rand() % 2 == 0); // set completed to be true or false randomly
        tasks.addTask(operations);
    }

    // write tasks to JSON file
    writeAll();
    fileName = tempFileName;
}

void IOClass::testReadOperations(std::string fileName = "test.json"){
    std::string tempFileName = this -> fileName;
    this -> fileName = fileName; 
    readAll();

    for(Task operation: tasks.taskList){
        std::cout << "ID: " << operation.getID() << std::endl 
        << "Title: " <<  operation.getTitle() << std::endl
        << "Description: " << operation.getDescription() << std::endl
        << "Due Date: " << operation.getDueDate() << std::endl
        << "Date Added: " << operation.getDateAdded() << std::endl << std::endl;

    }

    this->fileName = tempFileName;
}


#endif