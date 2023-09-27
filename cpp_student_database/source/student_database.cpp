#include "student_database.h"

sinhVien::sinhVien(string name, int age, gender genDer, int mathScore, int physicScore, int chemistryScore)
{
    static int index = 1;
    ID = index;
    index++;

    NAME = name;
    AGE = age;
    GENDER = genDer;
    MATHSCORE = mathScore;
    PHYSICSORE = physicScore;
    CHEMISTRYSCORE = chemistryScore;
    AVERAGESCORE = (MATHSCORE+PHYSICSORE+CHEMISTRYSCORE)/3;
}


void addStudent (list<sinhVien>& studentDatabase){
    string name;
    int age;
    int genDerKey;
    gender genDer;
    int mathScore;
    int physicScore;
    int chemistryScore;

    addstudent:

        cout << "Name: ";
        cin  >> name;

        cout << "Age: ";
        cin  >> age;

        cout << "Male:1 Female:2\n" << "Enter gender:";
        cin  >> genDerKey;
        switch (genDerKey)
        {
        case 1:
            genDer = MALE;
            break;
        case 2:
            genDer = FEMALE;
            break;
        default:
            break;
        }

        cout << "Mathscore: ";
        cin  >> mathScore;

        cout << "Physicscore: ";
        cin  >> physicScore;

        cout << "Chemistryscore: ";
        cin  >> chemistryScore;

        sinhVien sv(name, age, genDer, mathScore, physicScore, chemistryScore);
        studentDatabase.push_back(sv);
        cout << "Add student success!\n";
    choice:
        cout <<"-----------------------------\n"
             << "Press 1 to add more student.\n"
             << "Press 2 to exit.\n"
             << endl;
        cin >> genDerKey;
        switch (genDerKey)
        {
        case 1:
            goto addstudent;
            break;
        case 2:
            return;
            break;
        default:
            goto choice;
            break;
        }
}

void updateInformation(list<sinhVien>& studentDatabase){
    int stuId = 0;
    int key = 0;

    string name;
    int age;
    int genDer;
    int mathScore;
    int physicScore;
    int chemistryScore;

    cout << "Enter student ID:";
    cin  >> stuId;

    list<sinhVien> :: iterator marklist;
    for (marklist = studentDatabase.begin(); marklist != studentDatabase.end(); marklist++){
        if (marklist->getId() == stuId){
        loop:
            cout << "Main update information menu:\n"
                 << "1. update student'name.\n"
                 << "2. update student'age.\n"
                 << "3. update student'gender.\n"
                 << "4. update student'math score.\n"
                 << "5. update student'physics score.\n"
                 << "6. update student'chemistry score.\n"
                 << "7. Exit.\n"
                 << "Enter choice:";
            cin  >> key;
            cout << endl;

            switch (key)
            {
            case 1:
                cout << "Change student'name:";
                cin  >> name;
                marklist->updateName(name);
                cout << "Update success!";
                break;
            case 2:
                cout << "Change student'age:";
                cin  >> age;
                marklist->updateAge(age);
                cout << "Update success!";
                break;
            case 3:
                cout << "Male:1 Female:2\n" << "Enter gender:";
                cin  >> genDer;
                switch (genDer)
                {
                case 1:
                    marklist->updateGender(MALE);
                    break;
                case 2:
                    marklist->updateGender(FEMALE);
                    break;
                }
                break;
            case 4:
                cout << "Change student'math score:";
                cin  >> mathScore;
                marklist->updateMathscore(mathScore);
                cout << "Update success!";
                break;
            case 5:
                cout << "Change student'physics score:";
                cin  >> physicScore;
                marklist->updatePhysicscore(physicScore);
                cout << "Update success!";
                break;
            case 6:
                cout << "Change student'chemistry score:";
                cin  >> chemistryScore;
                marklist->updateChemistryscore(chemistryScore);
                cout << "Update success!";
                break;
            case 7:
                return;
                break;
            default:
                break;
            }
            goto loop;
        }
    }
}

void deleteStudent(list<sinhVien>& studentDatabase){
    int stuID;
    int checkDelete;
    deleteagain:
    cout << "Enter student'id:";
    cin  >> stuID;
    list<sinhVien> :: iterator marklist;
    for(marklist = studentDatabase.begin(); marklist != studentDatabase.end(); marklist++){
        if (marklist->getId() == stuID){
            studentDatabase.erase(marklist);
            break;
        }
    }
    cout <<"-----------------------------\n"
             << "Press 1 to delete more student.\n"
             << "Press 2 to exit.\n"
             << "Enter choice: ";
    cin  >> checkDelete;
    switch (checkDelete)
    {
    case 1:
        goto deleteagain;
        break;
    case 2:
        return;
        break;
    default:
        break;
    }
}

void findStudent(list<sinhVien> studentDatabase){
    string name;
    int checkFind;
    Findagain:
    cout << "Enter student'name: ";
    cin  >> name;
    list<sinhVien> :: iterator marklist;
    for(marklist = studentDatabase.begin(); marklist != studentDatabase.end(); marklist++){
        if(marklist->getName() == name){
            cout << "Name: " << marklist->getName() << endl;
            cout << "Age: " << marklist->getAge() << endl;
            if (marklist->getGender() == MALE) cout << "Gender: MALE " << endl;
            if (marklist->getGender() == FEMALE) cout << "Gender: FEMALE " << endl;
            cout << "Math score: " << marklist->getMathscore() << endl;
            cout << "Physics score: " << marklist->getPhysicscore() << endl;
            cout << "Chemistry score: " << marklist->getChemistryscore() << endl;
        }
    }
    cout <<"-----------------------------\n"
             << "Press 1 to find more student.\n"
             << "Press 2 to exit.\n"
             << "Enter choice: ";
    cin  >> checkFind;
    switch (checkFind)
    {
    case 1:
        goto Findagain;
        break;
    case 2:
        return;
        break;
    default:
        break;
    }
}

void showAllStudent(list<sinhVien> studentDatabase){
    int Quantity = 1;
    cout << "Number"  << "   " << "Ten" << endl;
    for(list<sinhVien> :: iterator marklist = studentDatabase.begin();marklist != studentDatabase.end();marklist++){
        cout << "  " << Quantity << "      " << marklist ->getName() << endl;
        Quantity++;
    }
}

bool compareName (sinhVien sv1, sinhVien sv2){
    return sv1.getName() < sv2.getName();
}

bool compareAverageScore (sinhVien sv1, sinhVien sv2){
    return sv1.getAveragescore() < sv2.getAveragescore();
}

