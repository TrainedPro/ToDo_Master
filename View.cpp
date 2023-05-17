
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
    // void deletetask();
    // void clearall();
    ~View();
};

View::View(){}

void View::mainMenu() {
    int choice;
	std::string name;

    do {
        std::cout << "1) Enter Your Username\n2) Quit\nEnter Your Choice: " << std::endl;
        std::cin >> choice;

		switch(choice){
		case 1:
			std::cout << "Enter Your Username: ";
			std::getline(std::cin >> std::ws, name);
			IO.setFileName(name);
            if(!IO.fileExists()) {
                do{
                    std::cout << "1) Simple Task List\n2) Detailed Task List\nChoose One Of The Above Types: ";
                    std::cin >> choice;
                
                    switch(choice){
                    case 1:
                        type = "TaskList";
                    
                    case 2:
                        type = "DetailedTaskList";

                    default:
                        std::cout << "Please Enter A Correct Option!" << std::endl;
                    }

                } while(choice < 1 || choice > 2);
            }
            else{
                type = IO.getFileType();
            }

            subMenu();
			break;

		case 2:
			return;
			break;

		default:
			std::cout << "Please Enter A Correct Choice!" << std::endl;
			break;
		}

    } while (choice != 2);
}

void View::subMenu() {
    if(type == "DetailedTaskList") tasks = new DetailedTaskList;

    int choice;
	int taskChoice;
    std::string confirm;
    do {
        std::cout << "1) View Tasks\n2) Add Task\n3) Delete Task\n4) Delete All Tasks\n5) Go Back\nEnter Your Choice: " << std::endl;
        std::cin >> choice;

		switch(choice){
		case 1:
			viewTasks();
			break;

		case 2:
			// addTasks();

		case 3:

			std::cout << *tasks << std::endl;
            
            while(1){
                std::cout << "Enter Task To Delete Or 0 To Cancel: ";
                std::cin >> taskChoice;

                if(taskChoice >= 0 && taskChoice <= tasks->taskList.size()) break;
                std::cout << "Please Enter A Number Between 0 and " << tasks->taskList.size() << std::endl;
            }

            if(taskChoice == 0) break;

            tasks->deleteTask(taskChoice - 1);
            break;

        case 4:
            while(1){
                std::cout << "Please Type CONFIRM Or 0 To Exit: ";
                std::getline(std::cin >> std::ws, confirm);
                if(confirm == "CONFIRM" || confirm == "0") break;
                std::cout << "Invalid Value" << std::endl;
            }

            if(confirm == "0") break;

            tasks->deleteAll();
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

    std::cout << *tasks << std::endl;

    int choice;
    do {
        std::cout << "1) Show Task\n2) Change Task Completion Status\n3) Sort Task\n4) See Incomplete Tasks\n5) Go Back\nEnter Your Choice: " << std::endl;

        std::cin >> choice;
        
        switch(choice){
        case 1:
            while(1){
                std::cout << "Enter Task Number: ";
                std::cin >> choice;

                if(choice > 0 && choice <= tasks->taskList.size()) break;
                std::cout << "Please Enter A Number Between 1 and " << tasks->taskList.size() << std::endl;
            }
            tasks->printTask(choice - 1);
            break;

        case 2:
            while(1){
                std::cout << "Enter Task Number: ";
                std::cin >> choice;

                if(choice > 0 && choice <= tasks->taskList.size()) break;
                std::cout << "Please Enter A Number Between 1 and " << tasks->taskList.size() << std::endl;
            }

            tasks->taskList.at(choice - 1).setCompleted(!(tasks->taskList.at(choice - 1).isCompleted()));

            break;

        case 3:
            sortTasks();
            break;

        case 4:
            for(int i = 0; i < tasks->taskList.size(); i++){
                if(tasks->taskList.at(i).isCompleted()) tasks->printTask(i);
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
        std::cout << "1) Sort By ID\n2) Sort By Title\n3) Sort By Due Date\n4) Sort By Date Added\n5) Go Back\nEnter Your Choice: " << std::endl;

        std::cin >> choice;

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

View::~View() {
    delete tasks;
    tasks = NULL;
}

int main() {
    View a;
    a.mainMenu();
}
