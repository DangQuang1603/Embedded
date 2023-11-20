/*
    1. Add student
    2. Update student information wiht id.
    3. Delete student information with id.
    4. Find specifier student with name (print all information of this student).
    5. Soft student with average score.
    6. Soft student with name.
    7. Show list of student.
*/

#include "student_database.h"
int main(int argc, char const *argv[])
{
    list<sinhVien> studentDatabase;
    int key;
    do{
        cout << "Main menu:\n"
             << "1. Add student.\n"
             << "2. Update student information wiht id.\n"
             << "3. Delete student information with id.\n"
             << "4. Find specifier student with name (print all information of this student).\n"
             << "5. Soft student with average score.\n"
             << "6. Soft student with name.\n"
             << "7. Show list of student.\n"
             << "Enter choice:";
        cin >> key;
        cout << endl;
        if (key > 1 && key > 7){
            system("cls");
            cout << "Enter choice again!" << endl;
        } 

    }while (key < 1 || key > 7);
    
    switch (key)
    {
    case ADD:
        system("cls");
        addStudent(studentDatabase);
        break;
    case UPDATE:
        system("cls");
        updateInformation(studentDatabase);
        break;
    case DELETE:
        system("cls");
        deleteStudent(studentDatabase);
        break;
    case FIND:
        system("cls");
        findStudent(studentDatabase);
        break;
    case SOFT_AVERAGE_SCORE:
        system("cls");
        studentDatabase.sort(compareAverageScore);
        break;
    case SOFT_NAME:
        system("cls");
        studentDatabase.sort(compareName);
        break;
    case SHOW_STUDENT:
        system("cls");
        showAllStudent(studentDatabase);
        break;
    default:
        break;
    }

    return 0;
}
