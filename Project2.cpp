#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Course class
class Course {
public:
    string courseNumber;
    string name;
    vector<string> prerequisites;

    Course(string number, string courseName) : courseNumber(number), name(courseName) {}
};

//load course data from a file into the data structure
void loadDataStructure(map<string, Course>& courses) {
    string fileName;
    cout << "Enter the file name that contains the course data: ";
    cin >> fileName;

    ifstream inputFile(fileName);
    if (!inputFile) {
        cout << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string courseNumber, courseName;
        getline(iss, courseNumber, ',');
        getline(iss, courseName, ',');

        Course course(courseNumber, courseName);
        string prerequisite;
        while (getline(iss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courses.insert({courseNumber, course});
    }

    inputFile.close();
    cout << "Data structure loaded successfully." << endl;
}

//print the course list in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    for (const auto& course : courses) {
        cout << course.second.courseNumber << ", " << course.second.name << endl;
    }
}

//print course information given a course number
void printCourse(const map<string, Course>& courses) {
    string courseNumber;
    cout << "Enter the course number: ";
    cin >> courseNumber;

    if (courses.count(courseNumber) == 0) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = courses.at(courseNumber);
    cout << course.courseNumber << ", " << course.name << endl;
    cout << "Prerequisites: ";
    if (course.prerequisites.empty()) {
        cout << "None" << endl;
    } else {
        for (const string& prerequisite : course.prerequisites) {
            cout << prerequisite << ", ";
        }
        cout << endl;
    }
}

//display the menu and handle user input
void displayMenu() {
    map<string, Course> courses;
    int choice;

    while (true) {
        cout << endl;
        cout << "Welcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
            case 1:
                loadDataStructure(courses);
                break;
            case 2:
                cout << "Here is a sample schedule:" << endl;
                printCourseList(courses);
                break;
            case 3:
                printCourse(courses);
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                return;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}