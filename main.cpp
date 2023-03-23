#include <iostream>
#include <list>
#include <string>
//#include <cstring>
using namespace std;


// Company class
class Company{

// private modifiers encapsulated
private:
    string Name;
    string Compny;
    int Age;
    string Id;

// protected modifier access through subclasses
protected:
    float Salary;

// public attributes
public:
    Company (string name, int age,float salary, string id = "-1", string company = "ABC Company"){
        Name = name;
        Age = age;
        Compny = company;
        Salary = salary;
        Id = id;
    }

    // Getters and Setters, Setters commented out no access from outside

    // void setName(string name){ // setter
    //     Name = name;
    // }

    string getName(){   // getter
        return Name;
    }

    string getCompany(){   // getter
        return Compny;
    }

    string getId(){   // getter
        return Id;
    }

    int getAge(){   // getter
        return Age;
    }

    float getSalary(){ // getter
        return Salary;
    }
};


// Hash map
class HashTable{
    private:
        static const int hashGroups = 100;          
        list<pair<int, Company>> table[hashGroups];

    public:
        // Hash Function
        int hashFunction(int key){
            return key%hashGroups;
        }

        // item remove
        void removeItem(int key){
            int hashValue = hashFunction(key);
            auto& cell = table[hashValue];
            auto bItr = begin(cell);
            bool keyExists = false;

            for (; bItr != end(cell); bItr++){
                if (bItr->first == key){
                    keyExists = true;
                    bItr = cell.erase(bItr);
                    cout << "value removed" << endl;
                    break;
                }
            }

            if (!keyExists){
                cout << "not found" << endl;
            }
            return;
        }

        // item search
        void searchItem(int key){
            int hashValue = hashFunction(key);
            auto& cell = table[hashValue];
            auto bItr = begin(cell);
            bool keyExists = false;

            for (; bItr != end(cell); bItr++){
                if (bItr->first == key){
                    keyExists = true;
                    cout << bItr->second.getId()<<" : "<<bItr->second.getName() << "\t Age - " << bItr->second.getAge() << "\t salary - LKR: " << bItr->second.getSalary()<< endl;
                    break;
                }
            }

            if (!keyExists){
                cout << "not found" << endl;
            }
            return;
        }

        // item insert
        void insertItem(int key, Company cp){         
            int hashValue = hashFunction(key);
            auto& cell = table[hashValue];
            auto bItr = begin(cell);
            bool keyExists = false;

            for (; bItr != end(cell); bItr++){
                if (bItr->first == key){
                    keyExists = true;
                    bItr->second = cp;
                    cout << "value replaced" << endl;
                    break;
                }
            }

            if (!keyExists){
                cell.emplace_back(key, cp);
            }
            return;
        }

        // all employees and trainees
        void print_list_all(){
            for (int i= 0; i < hashGroups; i++){
                for (auto pair : table[i]){
                    cout << pair.second.getId() << "\t" << pair.second.getName()<<endl;
                }
            }
            return;
        }

        // payment data
        void print_list_monthly_pay(){
            for (int i= 0; i < hashGroups; i++){
                for (auto pair : table[i]){
                    cout << pair.second.getId() << " : " << pair.second.getName() << "\t LKR: " << pair.second.getSalary()<<endl;
                }
            }
            return;
        }

        // total payment
        int print_get_total_pay(){
            long long sum;
            for (int i= 0; i < hashGroups; i++){
                for (auto pair : table[i]){
                    sum += pair.second.getSalary();
                }
            }
            return sum;
        }
};

// Employee class inherit from Company class
class Employee: public Company{
public:
    Employee (string id, string name, int age, float salary=0):Company(name, age, salary, id){
    }
};

// Salaried_Employee class inherit from Employee class
class Salaried_Employee: public Employee{
    public:
        Salaried_Employee(string id, string name, int age, float  salary):Employee(id, name, age, salary){
        }
};

// Hourly_paid_Employee class inherit from Employee class
class Hourly_Paid_Employee: public Employee{
    private:
        float HourlyRate;
        int HoursWorked;

    public:  
        Hourly_Paid_Employee(string id, string name, int age, float hourlyrate, int hoursworked):Employee(id, name, age){
            HourlyRate = hourlyrate;
            HoursWorked = hoursworked;
            Salary = HourlyRate*HoursWorked;
        }
};

// Trainee class inherit from Company class
class Trainee: public Company{
private:
    int Duration;

public:
    Trainee (string id, string name, int age, float salary, int duaration):Company(name, age, salary, id){
        Duration = duaration;
    }
};

// Commands
void list_all(HashTable ht1, HashTable ht2){
    ht1.print_list_all();
    ht2.print_list_all();
}

void list_monthly_pay(HashTable ht1, HashTable ht2){
    ht1.print_list_monthly_pay();
    ht2.print_list_monthly_pay();
}

void get_details(HashTable ht1, HashTable ht2, string id){
    int ident = stoi(id.substr(2));
    if (id[0]=='E') ht1.searchItem(ident);
    else ht2.searchItem(ident);
}

void remove(HashTable &ht1, HashTable &ht2, string id){
    int ident = stoi(id.substr(2));
    if (id[0]=='E') ht1.removeItem(ident);
    else if (id[0 == 'T']) ht2.removeItem(ident);
    else cout << "Please check ID again" << endl;
    cout << endl;
}

void get_total_pay(HashTable ht1, HashTable ht2){
   cout << "LKR: "<< ht1.print_get_total_pay() + ht2.print_get_total_pay() << endl;

}

// main method
int main(){
    int option;
    string ident;
    HashTable ht1, ht2;
    ht1.insertItem(201, Salaried_Employee("EM201","Madusanka", 25, 800000));
    ht1.insertItem(202, Salaried_Employee("EM202","Sunil", 30, 600000));
    ht1.insertItem(103, Hourly_Paid_Employee("EM103","Sidath", 32, 6000, 12));
    ht1.insertItem(105, Hourly_Paid_Employee("EM105","Kasun", 23, 5000, 20));

    ht2.insertItem(25, Trainee("TR25","Kamal", 18, 6000, 5));
    ht2.insertItem(30, Trainee("TR30","Sirimath", 15, 3200, 12));

    do{
        cout << "Select Option Number" << endl;
        cout << "1 - list_all" << endl;
        cout << "2 - list_monthly_pay" << endl;
        cout << "3 - get_total_pay" << endl;
        cout << "4 - get_details" << endl;
        cout << "5 - remove" << endl;
        cout << "6 - clear screen" << endl;
        cout << "0 - exit" << endl;

        cin >> option;

        switch (option){
        case 0:
            break;

        case 1:
            list_all(ht1, ht2);
            cout << endl;
            break;

        case 2:
            list_monthly_pay(ht1, ht2);
            cout << endl;
            break;

        case 3:
            get_total_pay(ht1, ht2);
            cout << endl;
            break;

        case 4:
            cout << "Id Number : " ;
            cin >> ident;
            get_details(ht1, ht2, ident);
            cout << endl;
            break;

        case 5:
            cout << "Id Number : " ;
            cin >> ident;
            remove(ht1, ht2, ident);
            cout << endl;
            break;

        case 6:
            system("clear");
            break;

        default:
            cout << "Enter proper option number" << endl;
        }
    }
    while(option != 0);
    return 0;
}
