/*
* File: store_database.cpp
* Author: Le Dang Quang
* Date: 25/09/2023
* Description: This file include details function for manage
*/

#include "store_database.h"





//-------------------------------------Manage function----------------------------------------------------

/*
Function: setNumberOfTable
Description: User enter input from key board then this function will set number of table into list table
Input: list of data table, number enter from keyboard by user
Output: No output
*/
void setNumberOfTable(list<table>& databaseTable){
  while(1){  
    int tableNum = 0;
    cout << "<Manager>\n"
         << "----------------------------\n"
         << "Enter number of table: ";
    cin  >> tableNum;

    databaseTable.clear();
    list<table> :: iterator markListOfTable;
    for(int i = 1; i <= tableNum; i++){
        table tb(i);
        databaseTable.push_back(tb);
    }
    system("cls");
    cout << "<Manager>\n"
         << "-----------Success----------\n";
    ENDFUNC("Change number of table");
  }
}

/*
Function: addDishToMenu
Description: User enter option from key board to add dish into menu
Input: list of data menu, option enter from keyboard by user
Output: No output
*/
void addDishToMenu(list<dishOnMenu>& databasedDishOnMenu){
    string dishName;
    while (1)
    {
        int  dishPrice;
        cout << "<Manager>\n"
            << "----------------------------\n"
            << "Enter dish name: ";
        cin  >> dishName;
        cout << "Enter dish price: ";
        cin  >> dishPrice;
        dishOnMenu dOS (dishName, dishPrice);
        databasedDishOnMenu.push_back(dOS);

        system("cls");
        list<dishOnMenu> :: iterator marklist = databasedDishOnMenu.end();
        marklist --;
        cout << "<Manager>\n"
            << "-----------Success----------\n"
            << "ID" << "|" << "Name" << "|" << "Price" << endl
            << marklist->getDishId() << "|"
            << marklist->getDishName() << "|"
            << marklist->getDishPrice()
            << endl;
        
        ENDFUNC("Add another dish")
    }
    
}


/*
Function: changeDishInfor
Description: User enter option from key board to change dish information in menu
Input: list of data menu, option enter from keyboard by user
Output: No output
*/
void changeDishInfor(list<dishOnMenu>& databasedDishOnMenu){
    int changekey = 0;
    int dishPrice = 0;
    string dishName = "";
    int dishIndex = 0;
    
    while (1){
        showMenu:
        cout << "<Manager>\n"
            << "----------------------------\n"
            << "   ID   " << "|" << "   Name   " << "|" << "   Price   " << endl;

        list<dishOnMenu> :: iterator marklist = databasedDishOnMenu.begin();
        for(; marklist != databasedDishOnMenu.end(); marklist ++){
            cout << marklist->getDishId() <<  "|"
                << marklist->getDishName() <<  "|"
                << marklist->getDishPrice() << endl;
        }
        cout << "----------------------------\n"
            << "Enter dish ID: ";
        cin  >> dishIndex;
        int dishIndexCount = 1;
        for (marklist = databasedDishOnMenu.begin(); marklist != databasedDishOnMenu.end(); marklist++){
            if (dishIndex == dishIndexCount) break;
            else dishIndexCount++;
        }


        system("cls");
        cout << "<Manager>\n"
            << "----------------------------\n"
            << " ID " << "|" << " Name " << "|" << " Price " << endl
            << marklist->getDishId() << "|" 
            << marklist->getDishName() << "|" 
            << marklist->getDishPrice()
            << endl
            << "----------------------------\n"
            << "0. Exit\n"
            << "1. Change dish name\n"
            << "2. Change dish price\n"
            << "3. Back\n"
            << "----------------------------\n"
            << "Enter choice: ";
        cin >> changekey;
        switch (changekey)
        {
        case 0:
            system("cls");
            return;
            break;
        case 1:
            cout << "Enter dish name: ";
            cin  >> dishName;
            marklist->setDishName(dishName);
            break;
        case 2:
            cout << "Enter dish price: ";
            cin  >> dishPrice;
            marklist->setDishPrice(dishPrice);
            break;
        case 3:
            system("cls");
            goto showMenu;
            break;
        default:
            break;
        }

        system("cls");
        cout << "<Manager>\n"
         << "-----------Success----------\n"
         << "ID" << "|" << "Name" << "|" << "Price" << endl
         << marklist->getDishId() << marklist->getDishName() << marklist->getDishPrice()
         << endl;

        ENDFUNC("Change more dish information");
    }

}


/*
Function: deleteDishInMenu
Description: User enter option from key board to delete dish in menu
Input: list of data menu, option enter from keyboard by user
Output: No output
*/
void deleteDishInMenu(list<dishOnMenu>& databasedDishOnMenu){
    int deletekey = 0;
    int dishIndex = 0;

    while(1){
        deletedish:

        // Print all dish on menu
        cout << "<Manager>\n"
            << "----------------------------\n"
            << "   ID   " << "|" << "   Name   " << "|" << "   Price   " << endl;

        list<dishOnMenu> :: iterator marklist = databasedDishOnMenu.begin();
        for(; marklist != databasedDishOnMenu.end(); marklist ++){
            cout << marklist->getDishId() <<  "|"
                << marklist->getDishName() <<  "|"
                << marklist->getDishPrice() << endl;
        }
        cout << "----------------------------\n"
            << "Enter dish ID: ";
        cin  >> dishIndex;

        // Find dish in menu through id
        int dishIndexCount = 1;
        for (marklist = databasedDishOnMenu.begin(); marklist != databasedDishOnMenu.end(); marklist++){
            if (dishIndex == dishIndexCount) break;
            else dishIndexCount++;
        }


        //  Show option and wait for user respond
        system("cls");
        cout << "<Manager>\n"
            << "----------------------------\n"
            << " ID " << "|" << " Name " << "|" << " Price " << endl
            << marklist->getDishId() << "|" 
            << marklist->getDishName() << "|" 
            << marklist->getDishPrice()
            << endl
            << "----------------------------\n"
            << "Are you sure?\n"
            << "1. Delete\n"
            << "0. Back\n"
            << "----------------------------\n"
            << "Enter choice: ";
        cin >> deletekey;
        switch (deletekey)
        {
        case 0:
            system("cls");
            goto deletedish; // go to head of this function
            break;
        case 1:
            system("cls");
            databasedDishOnMenu.erase(marklist);// delete dish in list of dishOnMenu
            break;
        default:
            break;
        }
        system("cls");
        cout << "<Manager>\n"
         << "-----------Success----------\n";
        ENDFUNC("Delete more dish");
    }
}


/*
Function: showMenu
Description: show all dish in menu
Input: list of data menu, option enter from keyboard by user
Output: No output
*/
void ShowMenu(list<dishOnMenu> databasedDishOnMenu){
    int showkey = 0;

    headOfFunction:
    // Print all dish on menu
        cout << "<Manager>\n"
            << "------------MENU-------------\n"
            << "   ID   " << "|" << "   Name   " << "|" << "   Price   " << endl;

        list<dishOnMenu> :: iterator marklist = databasedDishOnMenu.begin();
        for(; marklist != databasedDishOnMenu.end(); marklist ++){
            cout << marklist->getDishId() <<  "|"
                << marklist->getDishName() <<  "|"
                << marklist->getDishPrice() << endl;
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

/*
Function: managerFunction
Description: Manager enter option from key board to access function
Input: list of data menu, list of data table, option enter from keyboard by manager
Output: No output
*/
void managerFunction (list<dishOnMenu>& databasedDishOnMenu, list<table>& databaseTable){
    do
    {
        cout << "<Manager>\n"
             << "----------------------------\n"
             << "1. Set number of table\n"
             << "2. Add dishes to the menu\n"
             << "3. Update dished in menu\n"
             << "4. Delete dished in menu\n"
             << "5. Show menu\n"
             << "0. Exit\n"
             << "----------------------------\n"
             << "Enter choice: ";
        int key = 0;
        cin >> key;

        switch (key)
        {
        case 1:
            system("cls");
            setNumberOfTable(databaseTable);
            break;
        case 2:
            system("cls");
            addDishToMenu(databasedDishOnMenu);
            break;
        case 3:
            system("cls");
            changeDishInfor(databasedDishOnMenu);
            break;
        case 4:
            system("cls");
            deleteDishInMenu(databasedDishOnMenu);
            break;
        case 5:
            system("cls");
            ShowMenu(databasedDishOnMenu);
            break;
        case 0:
            return;
            break;
        default:
            break;
        }
    } while (1);
    
}
