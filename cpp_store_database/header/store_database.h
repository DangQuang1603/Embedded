/*
* File: store_database.h
* Author: Le Dang Quang
* Date: 25/09/2023
* Description: This file declare variable, array and function name
*/



#ifndef  __STORE_DATABASE_H_
#define  __STORE_DATABASE_H_

#include<iostream>
#include<string>
#include<list>

using namespace std;

// This macro will be declared in the end of function to print option continue function or exit 
#define ENDFUNC(...)                       \
cout     << "1." << __VA_ARGS__  << endl   \
         << "0. Exit\n"                    \
         << "---------------\n"            \
         << "Enter choice: ";              \
int key;                                   \
do                                         \
{                                          \
    cin >> key;                            \
    if (key == 0) {                        \
        system("cls");                     \
        return;}                           \
    if (key != 0 && key != 1){             \
        system("cls");                     \
        cout << "1." << __VA_ARGS__  << endl \
             << "0. Exit\n"                \
             << "---------------\n"        \
             << "Enter choice: ";          \
            }                              \
} while (key != 1);                        \
system("cls");                       

class dishOnMenu
{
private:
    int ID;
    string NAME;
    int PRICE;
public:
    dishOnMenu(string name = "", int price = 0){   
    static int menuIndex = 0;
    ID = ++menuIndex;

    NAME = name;
    PRICE = price;
    };
    void setDishName(string name) {NAME = name;}
    void setDishPrice(int price) {PRICE = price;}

    string getDishName() {return NAME;}
    int getDishPrice() {return PRICE;}
    int getDishId() {return ID;}

};

class dishOnTable : public dishOnMenu
{
private:
    int NUMBEROFDISH;
    int TABLEDISHID;
public:
    dishOnTable(int numberOfDish, string name, int price){
        static int tableIndex = 0;
        TABLEDISHID = ++tableIndex;

        NUMBEROFDISH = numberOfDish;
        setDishName(name);
        setDishPrice(price);
    };

    void setNumberOfDish (int numberOfDish) {NUMBEROFDISH = numberOfDish;}
    int  getNumberOfDish () {return NUMBEROFDISH;}
    int  getTableDishId  () {return TABLEDISHID;}

};

class table
{
private:
    int TABLENUMBER;
    bool TABLESTATUS;
    list<dishOnTable> databaseDishOnTable;
public:
    table(int tableNUMBER){
    TABLENUMBER = tableNUMBER;
    TABLESTATUS = false;
    };

    void setTableNumber (int tableNumber) {TABLENUMBER = tableNumber;};
    void setTableStatus (bool tableStatus){TABLESTATUS = tableStatus;};

    int  getTableNumber () {return TABLENUMBER;};
    bool getTableStatus () {return TABLESTATUS;};
    list<dishOnTable>& getDataBaseDishOnTable(){
        return databaseDishOnTable;
    }
};

void managerFunction (list<dishOnMenu>& databasedDishOnMenu, list<table>& databaseTable);
void staffFunction (list<dishOnMenu>& databasedDishOnMenu, list<table>& databaseTable);
void setNumberOfTable(list<table>& databaseTable);




#endif