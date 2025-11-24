#pragma once
#include "Constants.h"

class Room 
{
private:
    string roomNo;
    int capacity;
    bool isLab;
    
public:
    Room();
    Room(string roomNo, int capacity, bool isLab);
    
    string getRoomNo();
    int getCapacity();
    bool getIsLab();
    
    void display();
};