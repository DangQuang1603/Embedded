#include"parking.h"


// test main
int main(int argc, char const *argv[])
{
    // Declare 100 slot in park area
    parkingLot pLot(10);

    //Assume some parking slot are taken
    list<parkingSlot> :: iterator itSlot;
    for (itSlot = pLot.getSlotParkingdata().begin(); itSlot != pLot.getSlotParkingdata().begin(); itSlot++){
        if(itSlot->getSlotNumber() > 19 && itSlot->getSlotNumber() < 50){
            itSlot->setIsOccupied(true);
        }
    }

    // declare a car with license plate, map location and size
    vehicle car("abc 123", CAR, 3, 2);

    // find emty spot for car
    cout << "Spot number " << car.findParkingSpot(pLot) << "  is emty.\n";
    // Print total number of parking spot
    cout << pLot.getTotalSlots() << endl;

    // get car information
    cout << car.getLicenseTemplate() << endl;
    pLot.parking(2);
    pLot.parking(3);
    display(pLot);
    return 0;
}


// test parkingSlot
// int main(int argc, char const *argv[])
// {
//     // Create a parking spot for car 
//     parkingSlot pCar(CAR, 4, 3);

//     // check type of vehicle from newest parking spot
//     cout << "this spot only use for ";
//     if(pCar.getVehicleType() == CAR) cout << "CAR \n";
//     else cout << "BYKE\n" << endl;

//     // check status of newest parking spot
//     cout << "This parking spot is "
//          << (pCar.getIsOccupied() ?  "FULL" : "EMPTY") 
//          << endl;

//     //  reverse the status of parking spot
//     pCar.setIsOccupied(true);

//     // // check again status of newest parking spot
//     cout << "This parking spot is "
//          << (pCar.getIsOccupied() ?  "FULL" : "EMPTY") 
//          << endl;


//     return 0;
// }

// test parkingLot
// int main(int argc, char const *argv[])
// {
//     // create a parkingLot include 10 slot
//     parkingLot lot(10);
//     // Print how many slot in parkingLot
//     cout << "Total spot: " << lot.getTotalSlots() << endl;
//     // Print how many empty slot of parkingLot
//     cout << "Available spot: " << lot.getAvailableSlots() << endl;
//     // Assume slot number 5 is taken by a car
//     list<parkingSlot> :: iterator itPKS;
//     for(itPKS = lot.getSlotParkingdata().begin(); itPKS != lot.getSlotParkingdata().end(); itPKS++){
//         if(itPKS->getSlotNumber() == 5){
//             itPKS->setIsOccupied(true);
//         }
//     }
//     // Print how many empty slot left in parkingLot
//     cout << "Available spot: " << lot.getAvailableSlots() << endl;
//     return 0;
// }

//  test vehicle
// int main(int argc, char const *argv[])
// {
//     // create parking slots with different size
//     parkingSlot pkSlot1 (CAR, 4.2, 3.0);
//     parkingSlot pkSlot2 (CAR, 4.8, 4.1);
//     parkingSlot pkSlot3 (BYKE, 1, 0.5);

//     parkingLot lot(0);
//     lot.getSlotParkingdata().push_back(pkSlot1);
//     lot.getSlotParkingdata().push_back(pkSlot2);
//     lot.getSlotParkingdata().push_back(pkSlot3);
//     // craete a vehicle  with specific dimension
//     vehicle carr("60A 1234", CAR, 4.3, 3.5);
//     // require:
//     // Any slot fit with this vehicle?
//     // Print dimension of the fit slot
//     if (carr.findParkingSpot(lot) == 0) {
//         cout << "No spot available!" <<endl;
//     }
//     else{
//         cout << "This vehicle can park at spot number " << carr.findParkingSpot(lot) << endl;
//         list<parkingSlot> :: iterator itpkSlot;
//         for(itpkSlot = lot.getSlotParkingdata().begin(); itpkSlot != lot.getSlotParkingdata().end(); itpkSlot++){
//             if (itpkSlot->getSlotNumber() == carr.findParkingSpot(lot)){
//                 dimension sizeOfSpot = itpkSlot->getSize();
//                 cout<< "dimension: " << sizeOfSpot.getLenght() << "  " << sizeOfSpot.getWidth() << endl;
//             }
//         }
//     } 
    
    
//     return 0;
// }


