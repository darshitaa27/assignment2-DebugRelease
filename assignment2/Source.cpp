#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA
{
    string lastName;
    string firstName;
};

int main()
{
    vector<STUDENT_DATA> students;

    ifstream file("StudentData.txt");

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    string line;

    while (getline(file, line))
    {
        size_t comma = line.find(',');

        if (comma != string::npos)
        {
            STUDENT_DATA student;

            student.lastName = line.substr(0, comma);
            student.firstName = line.substr(comma + 1);

            // Remove the space after the comma
            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            students.push_back(student);
        }
    }

    file.close();

    return 0;
}