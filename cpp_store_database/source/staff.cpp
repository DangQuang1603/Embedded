/*
* File: store_database.cpp
* Author: Le Dang Quang
* Date: 25/09/2023
* Description: This file include details function for staff
*/
#include "store_database.h"


// -------------------------------Staff funcion--------------------------------------------------------

/*
Function: order
Description: Staff enter id and number of dish for order
Input: list of data menu, list of data table, table number, option enter from keyboard by staff
Output: No output
*/
void order(list<dishOnMenu>& databasedDishOnMenu, list<table>& databaseTable, int tableNumber){
        int dishId = 0;
        int numberOfDish = 0;
    while(1){
    // Print all dish on menu
        cout << "Table " << tableNumber << endl << endl
            << "------------MENU-------------\n"
            << "   ID   " << "|" << "   Name   " << "|" << "   Price   " << endl;

        list<dishOnMenu> :: iterator marklist = databasedDishOnMenu.begin();
        for(; marklist != databasedDishOnMenu.end(); marklist ++){
            cout << marklist->getDishId() <<  "|"
                << marklist->getDishName() <<  "|"
                << marklist->getDishPrice() << endl;
        }

    // Staff enter order from customer
        cout << "----------------------------\n"
             << "Enter dish ID:  ";
        cin  >> dishId;
        cout << "Enter number of dish:  ";
        cin  >> numberOfDish;

    // Find dish in menu
        list<dishOnMenu> :: iterator itMenu;
        for(itMenu = databasedDishOnMenu.begin(); itMenu != databasedDishOnMenu.end(); itMenu++){
            if(itMenu->getDishId() == dishId) break;
        }
    
    // Find specific table
        list<table> :: iterator itTable = databaseTable.begin();
        for(; itTable != databaseTable.end(); itTable++){
            if (tableNumber == itTable->getTableNumber()) break;
        }
    
    // Push dish into list of table
        dishOnTable dOT(numberOfDish, itMenu->getDishName(), itMenu->getDishPrice());
        itTable->getDataBaseDishOnTable().push_back(dOT);

        system("cls");
        cout << "-----------Order success---------------\n";
        ENDFUNC("Order more");
    }

}       

/*
Function: deleteList
Description: Staff enter id to delete dish from list
Input: list of data table, table number, option enter from keyboard by staff
Output: No output
*/
void deleteList(list<table>& databaseTable,int tableNumber){
    int sttOfDish = 0;
    while(1){
    // Show dish in list
        cout << "Table " << tableNumber << endl << endl
                << "------------Order list-------------\n"
                << " STT " << "|" << "  ID  " << "|" << " Name " << "|" << " Price " << endl;

            list<table> :: iterator itTable = databaseTable.begin();
            list<dishOnTable> :: iterator itDOT;
            for(; itTable != databaseTable.end(); itTable++){
                itDOT = itTable->getDataBaseDishOnTable().begin();
                cout << itDOT->getNumberOfDish() <<  "|"
                    << itDOT->getDishId() <<  "|"
                    << itDOT->getDishName() <<  "|"
                    << itDOT->getDishPrice() << endl;
            }
    // Enter Id to delete dish in list
        cout << "---------------------------------\n"
            << "Enter STT: ";
        cin  >> sttOfDish;

    // Delete dish in list
        for(itDOT = itTable->getDataBaseDishOnTable().begin(); itDOT != itTable->getDataBaseDishOnTable().end(); itDOT++){
            if(itDOT->getNumberOfDish() == sttOfDish){
                itTable->getDataBaseDishOnTable().erase(itDOT);
                break;
            }
        }

        system("cls");
        cout << "----------Delete success-------------\n";
        ENDFUNC("Delete more dish");
    }
}

/*
Function: showList
Description: show all dish in list
Input: list of data table, table number, option enter from keyboard by staff
Output: No output
*/
void showList(list<table>& databaseTable,int tableNumber){

    int showkey = 0;
    headOfFunction:

// Show dish in list
    cout << "Table " << tableNumber << endl << endl
            << "------------Order list-------------\n"
            << " STT " << "|" << "  ID  " << "|" << " Name " << "|" << " Price " << endl;

        list<table> :: iterator itTable = databaseTable.begin();
        list<dishOnTable> :: iterator itDOT;
        for(; itTable != databaseTable.end(); itTable++){
            itDOT = itTable->getDataBaseDishOnTable().begin();
            cout << itDOT->getNumberOfDish() <<  "|"
                 << itDOT->getDishId() <<  "|"
                 << itDOT->getDishName() <<  "|"
                 << itDOT->getDishPrice() << endl;
        }
    
// Print way to exit
    cout << "----------------------------\n"
         << "0. Exit\n"
         << "----------------------------\n"
         << "Enter choice: ";
    cin  >> showkey;
    if (showkey == 0) return;
    else{
        system("cls");
        goto headOfFunction;
    }
    
}


void payMeal(list<table>& databaseTable, int tableNumber){
    int totalDue = 0;
    int payKey = 0;
// Find table have pay require
    list<table> :: iterator itTable;
    for(itTable = databaseTable.begin(); itTable != databaseTable.end(); itTable++){
        if(itTable->getTableNumber() == tableNumber) break;
    }

printbill:
// print bill 
    cout << "----------Table " << tableNumber << " bill----------\n\n"
         << "Bill:\n"
         << " STT |  ID  | Name | Number | Price\n";
    list<dishOnTable> :: iterator itDOS;
    for(itDOS = itTable->getDataBaseDishOnTable().begin(); itDOS != itTable->getDataBaseDishOnTable().end(); itDOS++){
        cout << itDOS->getTableDishId() << " |"
             << itDOS->getDishId() << " |"
             << itDOS->getDishName() << " |"
             << itDOS->getNumberOfDish() << " |"
             << itDOS->getDishPrice()
             << endl;
    }

// Caculate total due
    totalDue = 0;
    for(itDOS = itTable->getDataBaseDishOnTable().begin(); itDOS != itTable->getDataBaseDishOnTable().end(); itDOS++){
        totalDue += itDOS->getDishPrice() * itDOS->getNumberOfDish();
    }
    cout <<"Total due: " << totalDue << endl;

// Print option for customer pay
    cout << "---------------------\n"
         << "1. Pay\n"
         << "0. Exit\n"
         << "---------------------\n"
         << "Enter choice: ";
    cin  >> payKey;

    if(payKey == 1){
        itTable->setTableStatus(false);
        itTable->getDataBaseDishOnTable().clear();
        cout << "-----------Pay success----------\n";
        return;
    }else if(payKey == 0){
        return;
    }else{
        system("cls");
        goto printbill;
    }

}

/*
Function: serveTable
Description: Staff enter option from key board follow customer requires
Input: list of data menu, list of data table, table number, option enter from keyboard by user
Output: No output
*/
void serveTable (list<dishOnMenu>& databasedDishOnMenu, list<table>& databaseTable, int tableNumber){
    do
    {
        cout << "Table " << tableNumber << endl << endl
             << "----------------------------\n"
             << "1. Order\n"
             << "2. Delete in list\n"
             << "3. Show list of disdes\n"
             << "4. Pay for meals\n"
             << "0. Back\n"
             << "----------------------------\n"
             << "Enter choice: ";
        int key = 0;
        cin >> key;
        switch (key)
        {
        case 1:
            system("cls");
            order(databasedDishOnMenu, databaseTable, tableNumber);
            break;
        case 2:
            system("cls");
            deleteList( databaseTable, tableNumber);
            break;
        case 3:
            system("cls");
            showList(databaseTable, tableNumber);
            break;
        case 4:
            system("cls");
            payMeal(databaseTable, tableNumber);
            break;
        case 0:
            return;
            break;
        default:
            system("cls");
            break;
        }
    } while (1);
}

/*
Function: staffFunction
Description: Staff enter option from key board to access function
Input: list of data menu, list of data table, option enter from keyboard by staff
Output: No output
*/
void staffFunction (list<dishOnMenu>& databasedDishOnMenu, list<table>& databaseTable){
    int tableNumber = 0;

    // Print number of table and status
    cout << "<Staff>\n"
         << "-----------List Of Table----------\n"
         << "Talbe number ";
    list<table> :: iterator marktablelist;
    for (marktablelist = databaseTable.begin(); marktablelist != databaseTable.end(); marktablelist++){
        cout << "| " << marktablelist->getTableNumber() << " ";
    }
    cout << endl
         << "Table status ";
    for (marktablelist = databaseTable.begin(); marktablelist != databaseTable.end(); marktablelist++){
        if (marktablelist->getTableNumber() > 9){
            cout << "| " << marktablelist->getTableStatus() << " ";
        }else{
            cout << "| " << marktablelist->getTableStatus() << "  ";
        }
    }

    // Choose table to serve
    cout << endl
         << "---------------------------------\n"
         << "Enter table number: ";
    cin  >> tableNumber;
    system("cls");
    serveTable (databasedDishOnMenu, databaseTable, tableNumber);

}