/*
* File: parking.h
* Author: Le Dang Quang
* Date: 30/09/2023
* Description: This file declare class and function name
*/

#include<iostream>
#include<string>
#include<list>

using namespace std;

typedef enum{
    CAR,
    BYKE
} vehicleType;

// Class dimension for vehicle and parking slot
class dimension
{
private:
    float LENGHT;
    float WIDTH;
public:
    dimension(float lengt, float width){
        LENGHT = lengt;
        WIDTH = width;
    }
    void setLenght(float lenght) {LENGHT = lenght;}
    void setWidth (float  width) {WIDTH = width;}

    float getLenght() {return LENGHT;}
    float getWidth () {return WIDTH;}
};

class parkingSlot
{
private:
    bool ISOCCUPIED;
    vehicleType VEHICLETYPE;
    int SLOTNUMBER;
    dimension SIZE;
public:
    parkingSlot( vehicleType vehicletype, float  lenght, float  width): SIZE(lenght,width)
    {
        static int index = 1;
        SLOTNUMBER = index++;

        ISOCCUPIED = false;
        VEHICLETYPE = vehicletype;
    }

    void setIsOccupied(bool status) {ISOCCUPIED = status;}
    void setVehicleType(vehicleType type) {VEHICLETYPE = type;}
    void setDimension(float  lenght, float  width) {
    SIZE.setWidth(width);
    SIZE.setLenght(lenght);
    }

    bool getIsOccupied () {return ISOCCUPIED;}
    vehicleType getVehicleType() {return VEHICLETYPE;}
    int getSlotNumber() {return SLOTNUMBER;}
    dimension getSize() {return SIZE;}
};

class parkingLot
{
private:
    list<parkingSlot> SLOT;
public:
    parkingLot(int numberOfSlot){
        for(int i = 1; i <= numberOfSlot; i++){
            parkingSlot pS( CAR, 4,4);
            SLOT.push_back(pS);
        }
    }

    int getAvailableSlots () {
        int availableCount = 0;
        list<parkingSlot> :: iterator itAvailable = SLOT.begin();
        for(itAvailable = SLOT.begin(); itAvailable != SLOT.end(); itAvailable++){
            if(itAvailable->getIsOccupied() == false) availableCount++;
        }
        return availableCount;
    }

    int getTotalSlots () const{
        return SLOT.size();
    }

    list<parkingSlot>& getSlotParkingdata() {
        return SLOT;    
    }

    bool checkSlotStatus(int slotNumber){
        if(SLOT.size() < slotNumber){
            return 0;
        }else{
            list<parkingSlot> :: iterator itUpdate;
            for(itUpdate = SLOT.begin(); itUpdate != SLOT.end(); itUpdate++){
                if(itUpdate->getSlotNumber() == slotNumber && itUpdate->getIsOccupied() == true){
                    return 1;
                }else if(itUpdate->getSlotNumber() == slotNumber && itUpdate->getIsOccupied() == false){
                    return 0;
                }
            }
        }
        
    }

    void parking (int slotNumber){
        list<parkingSlot> :: iterator itParking;
        for(itParking = SLOT.begin(); itParking != SLOT.end(); itParking++ ){
            if(itParking->getSlotNumber() == slotNumber ){
                itParking->setIsOccupied(true);
            }
        }
    }
};

class vehicle
{
private:
    string LICENSEPLATE;
    string SLOTADRESS;
    dimension SIZE;
    vehicleType VEHICLETYPE;
public:
    vehicle(string licensePlate, vehicleType vehicletype, float  lenght, float  width): SIZE(lenght, width)
    {
        LICENSEPLATE = licensePlate;
        SLOTADRESS = "";
        VEHICLETYPE = vehicletype;
    }

    // return the slot in list
    int findParkingSpot(parkingLot findSlot){
        list<parkingSlot> :: iterator itFindSlot;
        for(itFindSlot = findSlot.getSlotParkingdata().begin(); itFindSlot != findSlot.getSlotParkingdata().end(); itFindSlot++){
                if(itFindSlot->getIsOccupied() == false){
                    dimension size = itFindSlot->getSize();
                    if(SIZE.getLenght() <= size.getLenght() && SIZE.getWidth() <= size.getWidth()){
                        return itFindSlot->getSlotNumber();
                        // break;
                    }
                }
            }
            return 0;
        }
    string getLicenseTemplate() {return LICENSEPLATE;}
    dimension getSize (){return SIZE;}
};

void display(parkingLot myParking);








