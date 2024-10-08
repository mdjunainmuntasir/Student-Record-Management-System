#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    string name;
    string program;
    string email;
    string phone;
    int attendance;
    float gpa;
    Student(int i, string n, string p, string e, string ph, int a, float g)
        : id(i), name(n), program(p), email(e), phone(ph), attendance(a), gpa(g) {}
    Student() {}
};

vector<Student> students;
string savedUsername, savedPassword;

void saveToFile() {
    ofstream file("students.txt");
    for (const auto& student : students) {
        file << student.id << ' '
            << student.name << ' '
            << student.program << ' '
            << student.email << ' '
            << student.phone << ' '
            << student.attendance << ' '
            << student.gpa << '\n';
    }
    file.close();
}

void loadFromFile() {
    ifstream file("students.txt");
    if (file.is_open()) {
        students.clear();
        Student student;
        while (file >> student.id >> student.name >> student.program >> student.email >> student.phone >> student.attendance >> student.gpa) {
            students.push_back(student);
        }
        file.close();
    }
}

void saveUserData(const string& username, const string& password) {
    ofstream file("user.txt");
    file << username << ' ' << password << '\n';
    file.close();
}

bool loadUserData() {
    ifstream file("user.txt");
    if (file.is_open()) {
        file >> savedUsername >> savedPassword;
        file.close();
        return true;
    }
    return false;
}

void addStudent() {
    int id, attendance;
    char name[100], program[100], email[100], phone[100];
    float gpa;
    printf("Please enter student's ID: ");
    scanf("%d", &id);
    printf("Please enter student's Name: ");
    scanf("%s", name);
    printf("Please enter student's Program: ");
    scanf("%s", program);
    printf("Please enter student's Email: ");
    scanf("%s", email);
    printf("Please enter student's Phone Number: ");
    scanf("%s", phone);
    printf("Please enter student's Attendance: ");
    scanf("%d", &attendance);
    printf("Please enter student's GPA: ");
    scanf("%f", &gpa);
    students.push_back(Student(id, name, program, email, phone, attendance, gpa));
    printf("Student added successfully!\n");
}

void listAllStudents() {
    printf("%-10s %-10s %-10s %-20s %-15s %-12s %-5s\n", "Student ID", "Name", "Program", "Email", "Phone Number", "Attendance", "GPA");
    for (const auto& student : students) {
        printf("%-10d %-10s %-10s %-20s %-15s %-12d %-5.2f\n", student.id, student.name.c_str(), student.program.c_str(), student.email.c_str(), student.phone.c_str(), student.attendance, student.gpa);
    }
}

void listStudentsByProgram() {
    char program[100];
    printf("Please enter the program: ");
    scanf("%s", program);
    printf("%-10s %-10s %-10s %-20s %-15s %-12s %-5s\n", "Student ID", "Name", "Program", "Email", "Phone Number", "Attendance", "GPA");
    for (const auto& student : students) {
        if (student.program == program) {
            printf("%-10d %-10s %-10s %-20s %-15s %-12d %-5.2f\n", student.id, student.name.c_str(), student.program.c_str(), student.email.c_str(), student.phone.c_str(), student.attendance, student.gpa);
        }
    }
}

void searchStudentByID() {
    int id;
    printf("Please enter the student ID: ");
    scanf("%d", &id);
    auto it = find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
    if (it != students.end()) {
        printf("Student found:\n");
        printf("%-10s %-10s %-10s %-20s %-15s %-12s %-5s\n", "Student ID", "Name", "Program", "Email", "Phone Number", "Attendance", "GPA");
        printf("%-10d %-10s %-10s %-20s %-15s %-12d %-5.2f\n", it->id, it->name.c_str(), it->program.c_str(), it->email.c_str(), it->phone.c_str(), it->attendance, it->gpa);
    }
    else {
        printf("Student with ID %d not found.\n", id);
    }
}

void modifyStudentByID() {
    int id, option;
    printf("Please enter the student ID: ");
    scanf("%d", &id);
    auto it = find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
    if (it != students.end()) {
        do {
            printf("Modifying student with ID %d:\n", id);
            printf("Select the attribute you want to modify:\n");
            printf("1. Program\n");
            printf("2. Email\n");
            printf("3. Phone Number\n");
            printf("4. Attendance\n");
            printf("5. GPA\n");
            printf("6. Exit\n");
            printf("Please enter your choice: ");
            scanf("%d", &option);
            switch (option) {
            case 1:
                printf("Please enter new Program: ");
                scanf("%s", it->program.c_str());
                printf("Program updated successfully!\n");
                break;
            case 2:
                printf("Please enter new Email: ");
                scanf("%s", it->email.c_str());
                printf("Email updated successfully!\n");
                break;
            case 3:
                printf("Please enter new Phone Number: ");
                scanf("%s", it->phone.c_str());
                printf("Phone Number updated successfully!\n");
                break;
            case 4:
                printf("Please enter new Attendance: ");
                scanf("%d", &it->attendance);
                printf("Attendance updated successfully!\n");
                break;
            case 5:
                printf("Please enter new GPA: ");
                scanf("%f", &it->gpa);
                printf("GPA updated successfully!\n");
                break;
            case 6:
                printf("Exiting modification menu.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
            }
        } while (option != 6);
    }
    else {
        printf("Student with ID %d not found.\n", id);
    }
}

void deleteStudentByID() {
    int id;
    printf("Please enter the student ID: ");
    scanf("%d", &id);
    auto it = find_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; });
    if (it != students.end()) {
        students.erase(it);
        printf("Student record deleted successfully!\n");
    }
    else {
        printf("Student with ID %d not found.\n", id);
    }
}

int main() {
    loadFromFile(); // Load student data from file at the start
    loadUserData(); // Load user data from file at the start
    int choice;
    char cont;
    char username[100], password[100];
    printf("---------------------------------\n");
    printf("|                               |\n");
    printf("|       Student Database Menu   |\n");
    printf("|                               |\n");
    printf("----------------------------------\n");
    printf("| 1-Existing User               |\n");
    printf("| 2-New User                    |\n");
    printf("---------------------------------\n");
    printf("\nPlease enter an option: ");
    scanf("%d", &choice);
    if (choice == 2) {
        printf("Please enter your user name without any space: ");
        scanf("%s", username);
        printf("Please enter your Password without any space: ");
        scanf("%s", password);
        saveUserData(username, password);
        printf("\nLogin Created Successfully!\n");
    }
    else {
        bool loginSuccessful = false;
        while (!loginSuccessful) {
            printf("Please enter your user name without any space: ");
            scanf("%s", username);
            printf("Please enter your Password without any space: ");
            scanf("%s", password);
            if (username == savedUsername && password == savedPassword) {
                loginSuccessful = true;
                printf("\nLogin Successful!\n");
            }
            else {
                printf("\nUsername or passcode incorrect. Please try again.\n");
            }
        }
    }
    do {
        printf("---------------------------------\n");
        printf("|                               |\n");
        printf("|              Menu             |\n");
        printf("|                               |\n");
        printf("----------------------------------\n");
        printf("| 1-List All Students           |\n");
        printf("| 2-List Students by Program    |\n");
        printf("| 3-Add a New Student           |\n");
        printf("| 4-Search a Student            |\n");
        printf("| 5-Modify Data of a Student    |\n");
        printf("| 6-Delete a Student            |\n");
        printf("---------------------------------\n");
        printf("\nPlease enter an option: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            listAllStudents();
            break;
        case 2:
            listStudentsByProgram();
            break;
        case 3:
            addStudent();
            break;
        case 4:
            searchStudentByID();
            break;
        case 5:
            modifyStudentByID();
            break;
        case 6:
            deleteStudentByID();
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
        printf("\nDo you have another operation? (y/n): ");
        scanf(" %c", &cont); // Note the space before %c to consume any newline character
    } while (cont == 'y');
    saveToFile(); // Save student data to file before exiting
    return 0;
}
