#include "HeaderFiles/Room.h"

Room::Room() 
{
    roomNo = "";
    capacity = 0;
    isLab = false;
}

Room::Room(string roomNo, int capacity, bool isLab) 
{
    this->roomNo = roomNo;
    this->capacity = capacity;
    this->isLab = isLab;
}

string Room::getRoomNo() 
{
    return roomNo;
}

int Room::getCapacity() 
{
    return capacity;
}

bool Room::getIsLab() 
{
    return isLab;
}

void Room::display() 
{
    cout << "Room: " << roomNo << ", Capacity: " << capacity 
         << ", Lab: " << (isLab ? "Yes" : "No") << endl;
}