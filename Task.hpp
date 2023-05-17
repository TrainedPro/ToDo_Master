#ifndef TASK_H
#define TASK_H

#include <ctime>
#include <iostream>
#include <ostream>

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
    int getID() const;
    bool setTitle(const std::string &);
    std::string getTitle(bool strikethrough = true) const;
    void setDescription(const std::string &);
    std::string getDescription() const;
    void setDueDate(const time_t);
    time_t getDueDate() const;
    std::string epochToString(time_t epochTime);
    time_t stringToEpoch(const std::string& input);
    void setDateAdded(const time_t);
    time_t getDateAdded() const;
    void setCompleted(bool);
    bool isCompleted() const;
    bool isValidDateFormat(const std::string&);
    friend std::ostream& operator<<(std::ostream&, Task);
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

int Task::getID() const {
    return id;
}

bool Task::setTitle(const std::string &title) {
    int words = 0;

    for (int i = 0; i < title.length(); i++) {
        if (title[i] == ' ') {
            words++;
        }
    }

    if (title.length() > 256 || words > 16)
        return false;
    else
        this->title = title;
    return true;
}

std::string Task::getTitle(bool strikethrough) const {
    if (completed && strikethrough) {
        std::string temp("\e[9m" + title + "\e[m");
        return temp;
    }
    return title;
}

void Task::setDescription(const std::string &description) {
    this->description = description;
}

std::string Task::getDescription() const {
    return description;
}

void Task::setCompleted(bool completed) {
    this->completed = completed;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setDueDate(const time_t dueDate) {
    this->dueDate = dueDate;
}

time_t Task::getDueDate() const {
    return dueDate;
}

std::string Task::epochToString(time_t epochTime) {
    std::tm *timeInfo = std::localtime(&epochTime);
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << timeInfo->tm_mday << "/"
         << std::setfill('0') << std::setw(2) << timeInfo->tm_mon + 1 << "/"
         << timeInfo->tm_year + 1900;
    return oss.str();
}

time_t Task::stringToEpoch(const std::string& input) {
    std::tm timeInfo = {};
    std::istringstream ss(input);
    
    std::string token;
    std::getline(ss, token, '/');
    timeInfo.tm_mday = std::stoi(token);
    
    std::getline(ss, token, '/');
    timeInfo.tm_mon = std::stoi(token) - 1;
    
    std::getline(ss, token, '/');
    timeInfo.tm_year = std::stoi(token) - 1900;
    
    timeInfo.tm_hour = 0;
    timeInfo.tm_min = 0;
    timeInfo.tm_sec = 0;
    
    std::time_t epochTime = std::mktime(&timeInfo);
    
    if (epochTime == -1) {
        // Conversion failed
        // You can handle the error here or return an error value
        // For example, you can throw an exception or return a special value like -1
        throw std::runtime_error("Invalid date value");
    }
    
    return epochTime;
}

void Task::setDateAdded(const time_t dateAdded) {
    this->dateAdded = dateAdded;
}

time_t Task::getDateAdded() const {
    return dateAdded;
}

bool Task::isValidDateFormat(const std::string& input) {
    std::stringstream ss(input);
    int day, month, year;
    char delimiter1, delimiter2;
    ss >> day >> delimiter1 >> month >> delimiter2 >> year;

    // Check that all three parts were read correctly and that delimiters are correct
    if (ss.fail() || !ss.eof() || delimiter1 != '/' || delimiter2 != '/') {
        return false;
    }

    // Check if the day, month, and year values are within range
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return false;
    }

    // Check if the month has 30 or 31 days
    if ((day == 31) && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) {
        return false;
    }

    // Check if it's a leap year
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    // Check if February has 29 days for leap year
    if (month == 2 && day > 29) {
        return false;
    } else if (month == 2 && day == 29 && !isLeapYear) {
        return false;
    }

    // Get the current date and time
    std::time_t t = std::time(nullptr);
    std::tm* currentDate = std::localtime(&t);

    // Compare the input date with the current date
    if (year < currentDate->tm_year + 1900 ||
        (year == currentDate->tm_year + 1900 && month < currentDate->tm_mon + 1) ||
        (year == currentDate->tm_year + 1900 && month == currentDate->tm_mon + 1 && day < currentDate->tm_mday)) {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& cout, Task task){
    cout << "Title: " << task.title << std::endl;
    cout << "Due Date: " << task.epochToString(task.dueDate) << std::endl;
    cout << "Date Added: " << task.epochToString(task.dateAdded) << std::endl;
    cout << "Description: ";
    if (task.description.empty()) {
        cout << "No Description Available" << std::endl;
    } else {
        cout << task.description << std::endl;
    }
    cout << "Completed: " << (task.completed ? "Yes" : "No") << std::endl;
    return cout;
}

#endif