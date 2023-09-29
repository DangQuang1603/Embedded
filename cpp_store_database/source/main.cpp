#include "store_database.h"

int main(int argc, char const *argv[])
{
    list<dishOnMenu> databaseDisOnMenu;
    list<table> databaseTable;

    do
    {
        cout << "----------\n"
             << "1. Manager\n"
             << "2. Staff\n"
             << "----------\n"
             << "Enter choice: ";
        int key = 0;
        cin >> key;

        switch (key)
        {
        case 1:
            system("cls");
            managerFunction(databaseDisOnMenu, databaseTable);
            break;
        case 2:
            system("cls");
            staffFunction (databaseDisOnMenu, databaseTable);
            break;
        default:
            break;
        }
    } while (1);
    
    return 0;
}
