#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Student {
private:
    string name;
    string branch;
    int rollNumber;

public:
    Student(string name, string branch, int rollNumber) {
        this->name = name;
        this->branch = branch;
        this->rollNumber = rollNumber;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    string getName() const {
        return name;
    }

    string getBranch() const {
        return branch;
    }

    void display() const {
        cout << "\n----------------------\n";
        cout << "Name       : " << name << endl;
        cout << "Branch     : " << branch << endl;
        cout << "Roll No.   : " << rollNumber << endl;
        cout << "----------------------\n";
    }

    void edit(string newName, string newBranch, int newRoll) {
        name = newName;
        branch = newBranch;
        rollNumber = newRoll;
    }
};

class College {
private:
    vector<Student> students;

public:
    void addStudent() {
        string name, branch;
        int roll;

        cout << "Enter Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Enter Branch: ";
        getline(cin, branch);

        cout << "Enter Roll Number: ";
        cin >> roll;

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
        int choice;
        while (true) {
            cout << "\n--- Remove Student ---\n";
            cout << "1. Remove by Roll Number\n";
            cout << "2. Remove by Name\n";
            cout << "0. Go back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 0) {
                cout << "Returning to main menu...\n";
                return;
            }

            if (choice == 1) {
                int roll;
                cout << "Enter roll number of student to remove: ";
                cin >> roll;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                auto it = find_if(students.begin(), students.end(),
                                [roll](const Student& s) { return s.getRollNumber() == roll; });

                if (it != students.end()) {
                    cout << "Student found:\n";
                    it->display();
                    cout << "Press ENTER to confirm deletion, or type 0 and press ENTER to cancel: ";
                    string confirm;
                    getline(cin, confirm);
                    if (confirm == "0") {
                        cout << "Deletion canceled.\n";
                    } else {
                        students.erase(it);
                        cout << "Student removed successfully.\n";
                    }
                } else {
                    cout << "No student found with that roll number.\n";
                }
                return;

            } else if (choice == 2) {
                string name;
                cout << "Enter name of student to remove: ";
                getline(cin, name);

                auto it = find_if(students.begin(), students.end(),
                                [name](const Student& s) { return s.getName() == name; });

                if (it != students.end()) {
                    cout << "Student found:\n";
                    it->display();
                    cout << "Press ENTER to confirm deletion, or type 0 and press ENTER to cancel: ";
                    string confirm;
                    getline(cin, confirm);
                    if (confirm == "0") {
                        cout << "Deletion canceled.\n";
                    } else {
                        students.erase(it);
                        cout << "Student removed successfully.\n";
                    }
                } else {
                    cout << "No student found with that name.\n";
                }
                return;

            } else {
                cout << "Invalid choice. Please select 0, 1 or 2.\n";
            }
        }
    }


    void editStudent() {
        int roll;
        cout << "Enter roll number of student to edit (or 0 to cancel): ";
        cin >> roll;

        if (roll == 0) {
            cout << "Returning to main menu...\n";
            return;
        }

        for (auto& s : students) {
            if (s.getRollNumber() == roll) {
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                            int newRoll;
                            cout << "Enter new roll number: ";
                            cin >> newRoll;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

        cout << "Student with roll number " << roll << " not found.\n";
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

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 0) {
                cout << "Returning to main menu...\n";
                return;
            }

            bool found = false;

            if (choice == 1) {
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (const auto& s : students) {
                    if (s.getRollNumber() == roll) {
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

                for (const auto& s : students) {
                    if (s.getName() == name) {
                        s.display();
                        found = true;
                    }
                }
                if (!found) cout << "No student found with that name.\n";

            } else if (choice == 3) {
                string branch;
                cout << "Enter branch: ";
                getline(cin, branch);

                for (const auto& s : students) {
                    if (s.getBranch() == branch) {
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