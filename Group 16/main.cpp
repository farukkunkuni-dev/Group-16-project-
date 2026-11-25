#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CourseSystem {
private:

    vector<string> courses;
    vector<vector<int> > graph;

    // Find a course
    int findCourse(string name) {
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i] == name) {
                return i;
            }
        }
        return -1;
    }

public:

    // Addind of a course
    void addCourse() {
        string name;

        cout << "Enter course name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Course name cannot be empty." << endl;
            return;
        }

        if (findCourse(name) != -1) {
            cout << "Course already exists." << endl;
            return;
        }

        courses.push_back(name);
        graph.push_back(vector<int>());

        cout << "Course added successfully" << endl;
    }

    // Add a prerequisite
    void addPrerequisite() {
        string prerequisite, course;

        cout << "Enter prerequisite course: ";
        getline(cin, prerequisite);

        cout << "Enter course that depends on it: ";
        getline(cin, course);

        int p = findCourse(prerequisite);
        int c = findCourse(course);

        if (p == -1 || c == -1) {
            cout << "Course not found. Add the courses first." << endl;
            return;
        }

        if (p == c) {
            cout << "A course cannot be its own prerequisite." << endl;
            return;
        }

        for (int i = 0; i < graph[p].size(); i++) {
            if (graph[p][i] == c) {
                cout << "Prerequisite already exists." << endl;
                return;
            }
        }

        graph[p].push_back(c);

        cout << "Prerequisite added successfully!" << endl;
    }

    // Remove a course
    void removeCourse() {
        string name;

        cout << "Enter course to remove: ";
        getline(cin, name);

        int position = findCourse(name);

        if (position == -1) {
            cout << "Course not found." << endl;
            return;
        }

        courses.erase(courses.begin() + position);
        graph.erase(graph.begin() + position);

        // Update the remaining course positions
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {

                if (graph[i][j] == position) {
                    graph[i].erase(graph[i].begin() + j);
                    j--;
                }
                else if (graph[i][j] > position) {
                    graph[i][j]--;
                }
            }
        }

        cout << "Course removed successfully!" << endl;
    }

    // Display prerequisites
    void displayPrerequisites() {
        string name;

        cout << "Enter course name: ";
        getline(cin, name);

        int position = findCourse(name);

        if (position == -1) {
            cout << "Course not found." << endl;
            return;
        }

        cout << "Prerequisites for " << name << ":" << endl;

        bool found = false;

        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {

                if (graph[i][j] == position) {
                    cout << "- " << courses[i] << endl;
                    found = true;
                }
            }
        }

        if (found == false) {
            cout << "No prerequisites found." << endl;
        }
    }

    // Display dependent courses
    void displayDependents() {
        string name;

        cout << "Enter course name: ";
        getline(cin, name);

        int position = findCourse(name);

        if (position == -1) {
            cout << "Course not found." << endl;
            return;
        }

        cout << "Courses dependent on " << name << ":" << endl;

        if (graph[position].empty()) {
            cout << "No dependent courses Is found." << endl;
            return;
        }

        for (int i = 0; i < graph[position].size(); i++) {
            cout << "- " << courses[graph[position][i]] << endl;
        }
    }

    // Display all courses
    void displayCourses() {
        cout << "Available Courses:" << endl;

        if (courses.empty()) {
            cout << "No courses available." << endl;
            return;
        }

        for (int i = 0; i < courses.size(); i++) {
            cout << i + 1 << ". " << courses[i] << endl;
        }
    }
};

// Main function
int main() {

    CourseSystem system;
    int choice;

    do {
        cout << endl;
        cout << "UNIVERSITY COURSE PREREQUISITE SYSTEM " << endl;
        cout << "1. Add Course" << endl;
        cout << "2. Add Prerequisite" << endl;
        cout << "3. Remove Course" << endl;
        cout << "4. Display Prerequisites" << endl;
        cout << "5. Display Dependent Courses" << endl;
        cout << "6. Display All Courses" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {

            case 1:
                system.addCourse();
                break;

            case 2:
                system.addPrerequisite();
                break;

            case 3:
                system.removeCourse();
                break;

            case 4:
                system.displayPrerequisites();
                break;

            case 5:
                system.displayDependents();
                break;

            case 6:
                system.displayCourses();
                break;

            case 0:
                cout << "Thank you for using the system" << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
