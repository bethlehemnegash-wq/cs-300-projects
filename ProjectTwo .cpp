// Bethlehem Negash
// CS 300 Project Two - Advising Assistance Program

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

vector<Course> courses;

string toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

string trim(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

const Course* findCourse(const string& courseId) {
    string id = toUpperCase(courseId);
    for (const Course& c : courses) {
        if (c.courseId == id) return &c;
    }
    return nullptr;
}

void loadCourses(const string& filename) {
    courses.clear();
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: File not found. Please try again." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course c;

        getline(ss, token, ',');
        c.courseId = toUpperCase(trim(token));

        getline(ss, token, ',');
        c.title = trim(token);

        while (getline(ss, token, ',')) {
            token = trim(token);
            if (!token.empty()) {
                c.prerequisites.push_back(toUpperCase(token));
            }
        }

        courses.push_back(c);
    }

    cout << "Data loaded successfully." << endl;
}

void printCourseList() {
    if (courses.empty()) {
        cout << "No data loaded." << endl;
        return;
    }

    vector<Course> sorted = courses;
    sort(sorted.begin(), sorted.end(),
         [](Course a, Course b) { return a.courseId < b.courseId; });

    cout << "Here is a sample schedule:" << endl;
    for (Course c : sorted) {
        cout << c.courseId << ", " << c.title << endl;
    }
}

void printCourseInfo(const string& id) {
    const Course* c = findCourse(id);

    if (!c) {
        cout << "Course not found." << endl;
        return;
    }

    cout << c->courseId << ", " << c->title << endl;

    if (c->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites: ";
    for (size_t i = 0; i < c->prerequisites.size(); i++) {
        cout << c->prerequisites[i];
        if (i < c->prerequisites.size() - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    int choice = 0;
    string filename, courseId;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> filename;
            loadCourses(filename);
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseId;
            printCourseInfo(courseId);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << "Invalid option." << endl;
        }
    }

    return 0;
}
