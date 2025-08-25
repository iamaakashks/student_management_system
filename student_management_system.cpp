#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

string toCapitalized(const string& input) {
    string result = input;
    bool cap = true;
    for (char& ch : result) {
        if (isspace(ch)) {
            cap = true;
        } else if (cap) {
            ch = toupper(ch);
            cap = false;
        } else {
            ch = tolower(ch);
        }
    }
    return result;
}

string toUpper(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

string normalize(const string& input) {
    string result;
    for (char ch : input) {
        if (isalnum(ch)) result += tolower(ch);
    }
    return result;
}

class Student {
private:
    string name;
    string branch;
    string rollNumber;

public:
    Student(string name, string branch, string rollNumber) {
        this->name = toCapitalized(name);
        this->branch = toUpper(branch);
        this->rollNumber = toUpper(rollNumber);
    }

    string getRollNumber() const { return rollNumber; }
    string getName() const { return name; }
    string getBranch() const { return branch; }

    void display() const {
        cout << "\n----------------------\n";
        cout << "Name       : " << name << endl;
        cout << "Branch     : " << branch << endl;
        cout << "Roll No.   : " << rollNumber << endl;
        cout << "----------------------\n";
    }

    void edit(string newName, string newBranch, string newRoll) {
        name = toCapitalized(newName);
        branch = toUpper(newBranch);
        rollNumber = toUpper(newRoll);
    }
};

class College {
private:
    vector<Student> students;

public:
    void addStudent() {
        string name, branch, roll;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Branch: ";
        getline(cin, branch);

        cout << "Enter Roll Number: ";
        getline(cin, roll);

        students.emplace_back(name, branch, roll);
        cout << "Student added successfully!\n";
    }

    void displayAll() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        cout << "\n--- All Students ---\n";
        for (const auto& student : students) {
            student.display();
        }
    }

    void removeStudent() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }
        int choice;
        while (true) {
            cout << "\n--- Remove Student ---\n";
            cout << "1. Remove by Roll Number\n";
            cout << "2. Remove by Name\n";
            cout << "0. Go back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 0) {
                cout << "Returning to main menu...\n";
                return;
            }

            if (choice == 1) {
                string roll;
                cout << "Enter roll number of student to remove: ";
                getline(cin, roll);
                roll = normalize(roll);
                int index = -1;
                for(int i = 0; i < students.size(); i++){
                    if(normalize(students[i].getRollNumber()) == roll){
                        index = i;
                        break;
                    }
                }
                if(index != -1){
                    cout << "Student found:\n";
                    students[index].display();
                    cout << "Press ENTER to confirm deletion, or type 0 then press ENTER to cancel: ";
                    string confirm;
                    getline(cin, confirm);
                    if (confirm == "0") {
                        cout << "Deletion canceled.\n";
                    } else {
                        students.erase(students.begin()+index);
                        cout << "Student removed successfully.\n";
                    } 
                }else{
                    cout << "No student found with that roll number.\n";
                }
                return;

            } else if (choice == 2) {
                string name;
                cout << "Enter name of student to remove: ";
                getline(cin, name);
                name = normalize(name);
                int index = -1;
                for(int i = 0; i < students.size(); i++){
                    if(normalize(students[i].getName()) == name){
                        index = i;
                        break;
                    }
                }

                if(index != -1){
                    cout << "Student found:\n";
                    students[index].display();
                    cout << "Press ENTER to confirm deletion, or type 0 then press ENTER to cancel: ";
                    string confirm;
                    getline(cin, confirm);
                    if (confirm == "0") {
                        cout << "Deletion canceled.\n";
                    } else {
                        students.erase(students.begin()+index);
                        cout << "Student removed successfully.\n";
                    } 
                }else{
                    cout << "No student found with that name.\n";
                }
                return;

            } else {
                cout << "Invalid choice. Please select 0, 1 or 2.\n";
            }
        }
    }

    void editStudent() {
        string roll;
        cout << "Enter roll number of student to edit (or 0 to cancel): ";
        cin.ignore();
        getline(cin, roll);

        if (roll == "0") {
            cout << "Returning to main menu...\n";
            return;
        }
        roll = normalize(roll);

        for (auto& s : students) {
            if (normalize(s.getRollNumber()) == roll) {
                cout << "\nFound student:\n";
                s.display();

                int choice;
                do {
                    cout << "\nWhich field do you want to edit?\n";
                    cout << "1. Name\n";
                    cout << "2. Branch\n";
                    cout << "3. Roll Number\n";
                    cout << "0. Go back to main menu\n";
                    cout << "Enter choice: ";
                    cin >> choice;
                    cin.ignore();

                    switch (choice) {
                        case 1: {
                            string newName;
                            cout << "Enter new name: ";
                            getline(cin, newName);
                            s.edit(newName, s.getBranch(), s.getRollNumber());
                            cout << "Name updated successfully.\n";
                            break;
                        }
                        case 2: {
                            string newBranch;
                            cout << "Enter new branch: ";
                            getline(cin, newBranch);
                            s.edit(s.getName(), newBranch, s.getRollNumber());
                            cout << "Branch updated successfully.\n";
                            break;
                        }
                        case 3: {
                            string newRoll;
                            cout << "Enter new roll number: ";
                            getline(cin, newRoll);
                            s.edit(s.getName(), s.getBranch(), newRoll);
                            cout << "Roll number updated successfully.\n";
                            break;
                        }
                        case 0:
                            cout << "Returning to main menu...\n";
                            return;
                        default:
                            cout << "Invalid choice. Please enter 0-3.\n";
                    }

                } while (choice != 0);

                return;
            }
        }

        cout << "Student with that roll number not found.\n";
    }

    void searchStudent() {
        int choice;

        while (true) {
            cout << "\n--- Search Student ---\n";
            cout << "1. Search by Roll Number\n";
            cout << "2. Search by Name\n";
            cout << "3. Search by Branch\n";
            cout << "0. Go back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 0) {
                cout << "Returning to main menu...\n";
                return;
            }

            bool found = false;

            if (choice == 1) {
                string roll;
                cout << "Enter roll number: ";
                getline(cin, roll);
                roll = normalize(roll);

                for (const auto& s : students) {
                    if (normalize(s.getRollNumber()) == roll) {
                        s.display();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Student not found.\n";

            } else if (choice == 2) {
                string name;
                cout << "Enter name: ";
                getline(cin, name);
                name = normalize(name);

                for (const auto& s : students) {
                    if (normalize(s.getName()) == name) {
                        s.display();
                        found = true;
                    }
                }
                if (!found) cout << "No student found with that name.\n";

            } else if (choice == 3) {
                string branch;
                cout << "Enter branch: ";
                getline(cin, branch);
                branch = normalize(branch);

                for (const auto& s : students) {
                    if (normalize(s.getBranch()) == branch) {
                        s.display();
                        found = true;
                    }
                }
                if (!found) cout << "No student found in that branch.\n";

            } else {
                cout << "Invalid choice. Please select from 0 to 3.\n";
            }
        }
    }
};

int main() {
    College c;
    int option;

    do {
        cout << "\n====== College Management System ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Remove Student\n";
        cout << "4. Edit Student\n";
        cout << "5. Search Student\n";
        cout << "0. Exit\n";

        int attempts = 0;
        bool validInput = false;

        while (attempts < 4) {
            cout << "Choose an option: ";

            if (cin >> option) {
                validInput = true;
                break;
            } else {
                cin.clear();
                cin.ignore(1000, '\n');
                attempts++;
                cout << "Invalid input! Please enter a valid number (0–5). Attempts left: " << (4 - attempts) << "\n";
            }
        }

        if (!validInput) {
            cout << "\nToo many invalid attempts. Exiting program.\n";
            break;
        }

        switch (option) {
            case 1: c.addStudent(); break;
            case 2: c.displayAll(); break;
            case 3: c.removeStudent(); break;
            case 4: c.editStudent(); break;
            case 5: c.searchStudent(); break;
            case 0: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid option. Please select from 0 to 5.\n";
        }

    } while (option != 0);

    return 0;
}