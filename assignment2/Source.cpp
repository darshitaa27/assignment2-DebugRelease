#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA
{
    string lastName;
    string firstName;
    string email;
};

int main()
{
    vector<STUDENT_DATA> students;

#ifdef PRE_RELEASE
    cout << "Running Pre-Release Version" << endl;
    ifstream file("StudentData_Emails.txt");
#else
    cout << "Running Standard Version" << endl;
    ifstream file("StudentData.txt");
#endif

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    string line;

    while (getline(file, line))
    {
        size_t firstComma = line.find(',');

        if (firstComma != string::npos)
        {
            STUDENT_DATA student;

            student.lastName = line.substr(0, firstComma);

#ifdef PRE_RELEASE

            size_t secondComma = line.find(',', firstComma + 1);

            if (secondComma != string::npos)
            {
                student.firstName = line.substr(
                    firstComma + 1,
                    secondComma - firstComma - 1
                );

                student.email = line.substr(secondComma + 1);
            }

#else

            student.firstName = line.substr(firstComma + 1);

#endif

            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            students.push_back(student);
        }
    }

    file.close();

#ifdef _DEBUG

    cout << "Student Information:" << endl;
    cout << "--------------------" << endl;

    for (const STUDENT_DATA& student : students)
    {
        cout << student.lastName << ", "
            << student.firstName;

#ifdef PRE_RELEASE
        cout << " - " << student.email;
#endif

        cout << endl;
    }

#endif

    return 0;
}