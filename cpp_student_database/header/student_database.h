#ifndef STUDENT_DATABASE_H_
#define STUDENT_DATABASE_H_

#include<iostream>
#include<string>
#include<list>

using namespace std;

typedef enum{
    ADD                 = 1,
    UPDATE              = 2,
    DELETE              = 3,
    FIND                = 4,
    SOFT_AVERAGE_SCORE  = 5,
    SOFT_NAME           = 6,
    SHOW_STUDENT        = 7,
} dataBaseFunction;

typedef enum{
    MALE    = 1,
    FEMALE  = 2,
}gender;

class sinhVien
{
private:
    int ID;
    string NAME;
    int AGE;
    gender GENDER;
    int MATHSCORE;
    int PHYSICSORE;
    int CHEMISTRYSCORE;
    int AVERAGESCORE;
public:
    sinhVien(string name, int age, gender genDer, int mathScore, int physicScore, int chemistryScore);

    int getId(){return ID;}
    string getName() {return NAME;}
    int getAge() {return AGE;}
    gender getGender() {return GENDER;}
    int getMathscore() {return MATHSCORE;}
    int getPhysicscore() {return PHYSICSORE;}
    int getChemistryscore() {return CHEMISTRYSCORE;}
    int getAveragescore() {return AVERAGESCORE;}

    void updateName(string updateName){NAME =  updateName;}
    void updateAge(int updateAge){AGE =  updateAge;}
    void updateGender(gender updateGenDer){GENDER =  updateGenDer;}
    void updateMathscore(int updateMathScore){MATHSCORE =  updateMathScore;}
    void updatePhysicscore(int updatePhysicScore){PHYSICSORE =  updatePhysicScore;}
    void updateChemistryscore(int updateChemistryScore){CHEMISTRYSCORE =  updateChemistryScore;}
};

void addStudent (list<sinhVien>& database);
void updateInformation (list<sinhVien>& database);
void deleteStudent (list<sinhVien>& database);
void findStudent (list<sinhVien> database);
void softByAverageScore (list<sinhVien>& database);
void softByName (list<sinhVien>& database);
void showAllStudent (list<sinhVien> database);
bool compareName (sinhVien sv1, sinhVien sv2);
bool compareAverageScore (sinhVien sv1, sinhVien sv2);




#endif