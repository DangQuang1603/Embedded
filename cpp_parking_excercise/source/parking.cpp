/*
* File: parking.cpp
* Author: Le Dang Quang
* Date: 30/09/2023
* Description: This file declare detail function
*/

#include"parking.h"

void display(parkingLot myParking){
    cout << "Spot   | ";
    list<parkingSlot> :: iterator itDisplay;
    for(itDisplay = myParking.getSlotParkingdata().begin(); itDisplay != myParking.getSlotParkingdata().end(); itDisplay++){
        cout << itDisplay->getSlotNumber() << " | ";
    }

    cout << endl
         << "Status | ";
    for(itDisplay = myParking.getSlotParkingdata().begin(); itDisplay != myParking.getSlotParkingdata().end(); itDisplay++){
        cout   << itDisplay->getIsOccupied() << " | ";
    }
    cout << endl;
}