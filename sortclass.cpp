#include <iostream>
#include <algorithm>
#include <vector>
#include<ctime>
using namespace std;

class task {
    int id;
    string title;
    string description;
 //   bool string s=comleted;
public:
    task(int id1 = 0, string s="", string d="") {
        setid(id1);
        setitle(s);
        setdes(d);
    }
    void setdes(string d)
    {
    description = d;
}
string getdes()
{
return description;
}
    void setitle(string s)
    {
    title=s;
}
string getitle()
{
return title;
}
    void setid(int id1) {
        id = id1;
    }
    int getid() {
        return id;
    }
    void print()
    {
    cout<<id<<endl;
    cout<<title<<endl;
    cout<<description<<endl;
}
};

class Sortid {
    task obj1[3];
public:
    Sortid() {
    cout<<"enter ids with title"<<endl;
    for(int i=0; i<3;i++)
    {
    int x;
    cin>>x;
    obj1[i].setid(x);
    string s;
    getline(cin>>ws,s);
    obj1[i].setitle(s);
    string d;
    getline(cin>>ws,d);
    obj1[i].setdes(d);
}
    }
   void sortid() {
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (obj1[i].getid() < obj1[j].getid()) {
                task temp=obj1[i];
                obj1[i]=obj1[j];
                obj1[j]=temp;
            }
        }
    }
}
void sortdate() {
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            time_t time = obj1[i].getDate();
            time_t time1 = obj1[j].getDate();
            double diff = difftime(time1, time);
            if (diff < 0 ) {
                task temp = obj1[i];
                obj1[i] = obj1[j];
                obj1[j] = temp;
            }
        }
    }
}
void sortitle()
{
for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
        string var=obj1[i].getitle();
        string var1=obj1[j].getitle();
            if (var>var1) {
                task temp=obj1[i];
                obj1[i]=obj1[j];
                obj1[j]=temp;
            }
        }
    }
}


void print()
{
cout << "Sorted IDs (from greatest to smallest):" << endl;
for(int i=0;i<3;i++)
{
obj1[i].print();

}
}

};
int main()
{
Sortid obj;
// obj.sortid();
obj.sortitle();
obj.print();
}