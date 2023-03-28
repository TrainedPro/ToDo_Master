#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Sort {
    std::string name[3];
    std::vector<std::string> dates;

public:
    Sort() {
        storename();
        storeDates();
        sortname();
        sortDates();
        printNames();
        printDates();
    }
    void sortname() {
        int Fletter;
        int Sletter;
        std::string temp;
        for (int i = 0; i < 2; i++) {
            if (name[i][0] > name[i + 1][0]) {
                temp = name[i + 1];
                name[i + 1] = name[i];
                name[i] = temp;
            }
        }
    }
    void printNames() {
        for (int i = 0; i < 3; i++) {
            std::cout << "name of persn " << i + 1 << " " << name[i] << std::endl;
        }
    }
    void storename() {
        std::cout << "enetr names " << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "enetr name of person " << i + 1 << std::endl;
            std::getline(std::cin >> std::ws, name[i]);
        }
    }
    void sortDates() {
        sort(dates.begin(), dates.end(), std::greater<std::string>());
    }

    void printDates() {
        for (int i = 0; i < dates.size(); i++) {
            std::cout << dates[i] << std::endl;
        }
    }
    void storeDates() {
        std::cout << "Enter dates (in any format):" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::string date;
            std::getline(std::cin >> std::ws, date);
            dates.push_back(date);
        }
    }
};
int main() {
    Sort object;
}
