/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Julia Sochava, Caitlin Berry, Maddie Miller, Liad Gross
 * jsochava, cnberry, liadgr, millemad
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"
#include "Floor.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if (commandString == "") {
        isPass = true;
    } else if (commandString == "S") {
        isSave = true;
    } else if (commandString == "Q") {
        isQuit = true;
    } else {
        stringstream s;
        s << commandString;
        char junk;
        s >> junk >> elevatorId;
        char moveType;
        s >> moveType;
        if(moveType == 'f') {
            s >> targetFloor;
        } else if(moveType == 'p') {
            isPickup = true;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass || isQuit || isSave) {
        return true;
    } else if (elevatorId < 0 || elevatorId >= NUM_ELEVATORS){
        return false;
    } else if (elevators[elevatorId].isServicing()){
        return false;
    } else if (!isPickup){
        if (elevators[elevatorId].getCurrentFloor() == targetFloor){
            return false;
    }
        if (targetFloor < 0 || targetFloor >= NUM_FLOORS){
            return false;
        }
    }
    return true;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int anger1;
    int maxDistance = 0;
    for(int i = 0; i< pickupList.size(); i++) {
        peopleToPickup[i] = pickupList.at(i) - '0';
        numPeopleToPickup++;
        anger1 = pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        totalSatisfaction += (MAX_ANGER - anger1);
        if(abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor) > maxDistance) {
            maxDistance = abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor);
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
