
#include <iomanip>
#include <iostream>
#include "IOClass.hpp"

class View {
private:
    TaskList* tasks;
    IOClass IO;
    std::string type;
    
public:
    View();
    void mainMenu();
    void subMenu(); // TODO: Do the add task
    void viewTasks();
    void sortTasks();
    void addTasks();
    // void deletetask();
    // void clearall();
    ~View();
};

View::View(){}

void View::mainMenu() {
    tasks = new TaskList;
    int choice;
	std::string name;

    do {
        std::cout << "\n1) Enter Your Username\n2) Quit\nEnter Your Choice: ";
        std::cin >> choice;

		switch(choice){
		case 1:
			std::cout << "Enter Your Username: ";
			std::getline(std::cin >> std::ws, name);
            std::cout << std::endl;
			IO.setFileName(name);
            if(!IO.fileExists()) {
                do{
                    std::cout << "1) Simple Task List\n2) Detailed Task List\nChoose One Of The Above Types: ";
                    std::cin >> choice;
                
                    switch(choice){
                    case 1:
                        type = "TaskList";
                        break;
                    
                    case 2:
                        type = "DetailedTaskList";
                        tasks = new DetailedTaskList;
                        break;

                    default:
                        std::cout << "Please Enter A Correct Option!" << std::endl;
                    }

                } while(choice < 1 || choice > 2);
            }
            else{
                type = IO.getFileType();
                if(type == "DetailedTaskList") tasks = new DetailedTaskList;
                IO.readJson(*tasks);
            }
            subMenu();
			break;

		case 2:
			break;

		default:
			std::cout << "Please Enter A Correct Choice!" << std::endl;
			break;
		}

    } while (choice != 2);

    IO.writeJson(*tasks);

    return;
}

void View::subMenu() {
    int choice;
	int taskChoice;
    std::string confirm;
    do {
        std::cout << "\n1) View Tasks\n2) Add Task\n3) Delete Task\n4) Delete All Tasks\n5) Go Back\nEnter Your Choice: ";
        std::cin >> choice;

		switch(choice){
		case 1:
            std::cout << std::endl;
			viewTasks();
			break;

		case 2:
			addTasks();
            break;

		case 3:

			std::cout << *tasks << std::endl;
            
            while(1){
                std::cout << "Enter Task To Delete Or 0 To Cancel: ";
                std::cin >> taskChoice;

                if(taskChoice >= 0 && taskChoice <= tasks->taskList.size()) break;
                std::cout << "Please Enter A Number Between 0 and " << tasks->taskList.size() << std::endl << std::endl;
            }

            if(taskChoice == 0) break;

            tasks->deleteTask(taskChoice - 1);
            break;

        case 4:
            std::cout << std::endl;
            while(1){
                std::cout << "Please Type CONFIRM Or 0 To Exit: ";
                std::getline(std::cin >> std::ws, confirm);
                if(confirm == "CONFIRM" || confirm == "0") break;
                std::cout << "Invalid Value" << std::endl << std::endl;
            }

            if(confirm == "0") break;

            tasks->deleteAll();
            std::cout << "DELETED ALL TASKS!" << std::endl;
            break;

        case 5:
            return;

        default:
            std::cout << "Incorrect Choice! Please Enter A Valid Option" << std::endl;
            break;
			
		}
    } while(choice != 5);

	return;
}

void View::viewTasks() {

    std::cout << *tasks;

    int choice;
    do {
        std::cout << "\n1) Show Task\n2) Change Task Completion Status\n3) Sort Task\n4) See Incomplete Tasks\n5) Go Back\nEnter Your Choice: ";

        std::cin >> choice;
        std::cout << std::endl;
        
        switch(choice){
        case 1:
            while(1){
                std::cout << "Enter Task Number Or 0 To Exit: ";
                std::cin >> choice;

                if(choice >= 0 && choice <= tasks->taskList.size()) break;
                std::cout << "Please Enter A Number Between 0 and " << tasks->taskList.size() << std::endl << std::endl;
            }

            if (choice == 0) break;

            tasks->printTask(choice - 1);
            break;

        case 2:
            while(1){
                std::cout << "Enter Task Number Or 0 To Exit: ";
                std::cin >> choice;

                if(choice >= 0 && choice <= tasks->taskList.size()) break;
                std::cout << "Please Enter A Number Between 0 and " << tasks->taskList.size() << std::endl << std::endl;
            }

            if (choice == 0) break;

            tasks->taskList.at(choice - 1).setCompleted(!(tasks->taskList.at(choice - 1).isCompleted()));

            break;

        case 3:
            sortTasks();
            break;

        case 4:
            std::cout << "#      Due Date     Title\n";
            std::cout << "------------------------------------\n";
            for(int i = 0; i < tasks->taskList.size(); i++){
                if(!tasks->taskList.at(i).isCompleted()){
                    std::cout << std::setw(4) << std::left << i + 1 << " | ";
                    std::cout << tasks->taskList.at(i).epochToString(tasks->taskList.at(i).getDueDate()) << " | ";
                    std::cout << std::setw(12) << tasks->taskList.at(i).getTitle() << std::endl;
                }
            }
            break;

        case 5:
            return;

        default:
            std::cout << "Incorrect Choice! Please Enter A Valid Option" << std::endl;
            break;
        }

    } while(choice != 4);
}

void View::sortTasks() {
    int choice;

    do {
        std::cout << "\n1) Sort By ID\n2) Sort By Title\n3) Sort By Due Date\n4) Sort By Date Added\n5) Go Back\nEnter Your Choice: ";

        std::cin >> choice;
        std::cout << std::endl;

        switch(choice){
        case 1:
            tasks->sortID();
            std::cout << *tasks << std::endl;
            break;

        case 2:
            tasks->sortTitle();
            std::cout << *tasks << std::endl;
            break;

        case 3:
            tasks->sortDueDate();
            std::cout << *tasks << std::endl;
            break;

        case 4:
            tasks->sortDateAdded(); 
            std::cout << *tasks << std::endl;
            break;

        case 5:
            return;

        default:
            std::cout << "Incorrect Choice! Please Enter A Valid Option" << std::endl;
            break;
        }

    } while(choice != 5);
}

void View::addTasks(){
    Task temp;
    std::string sTemp;
    int choice;

    if(type == "TaskList"){
        std::cout << "\nPlease Enter A Title: ";
        std::getline(std::cin >> std::ws, sTemp);
        temp.setTitle(sTemp);

        std::cout << "Please Enter A Description: ";
        std::getline(std::cin >> std::ws, sTemp);
        temp.setDescription(sTemp);

        while(1){
            std::cout << "Please Enter A Due Date (DD/MM/YYYY): ";
            std::cin >> sTemp;

            if(temp.isValidDateFormat(sTemp)) break;
            std::cout << "Please Enter A Date After Today In The Format Of DD/MM/YYYY." << std::endl << std::endl;
        }

        temp.setDueDate(temp.stringToEpoch(sTemp));
        tasks->taskList.push_back(temp);
    } else {

        do{
            std::cout << "\n1) Add Task\n2) Add SubTask\nEnter A Choice: ";
            std::cin >> choice;

            switch(choice){
            case 1:
                std::cout << "\nPlease Enter A Title: ";
                std::getline(std::cin >> std::ws, sTemp);
                temp.setTitle(sTemp);

                while(1){
                    std::cout << "Please Enter A Due Date (DD/MM/YYYY): ";
                    std::cin >> sTemp;

                    if(temp.isValidDateFormat(sTemp)) break;
                    std::cout << "Please Enter A Date After Today In The Format Of DD/MM/YYYY." << std::endl << std::endl;
                }

                temp.setDueDate(temp.stringToEpoch(sTemp));
                tasks->taskList.push_back(temp);
                break;
            case 2:
                while(1){
                    std::cout << "\nEnter Task Number For SubTask Or 0 To Exit: ";
                    std::cin >> choice;

                    if(choice >= 0 && choice <= tasks->taskList.size()) break;
                    std::cout << "Please Enter A Number Between 0 and " << tasks->taskList.size() << std::endl << std::endl;
                }

                if (choice == 0) return;

                std::cout << "Enter The SubTask: ";
                std::getline(std::cin >> std::ws, sTemp);

                tasks->addSubTask(sTemp, choice - 1);
                break;

            default:
                std::cout << "Incorrect Choice! Please Enter A Valid Option" << std::endl;
                break;
            }
        } while(choice < 1 || choice > 2 );
    }
}

View::~View() {
    delete tasks;
}

int main() {
    View a;
    a.mainMenu();
}
