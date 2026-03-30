/*
 * Copyright 2023 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Caitlin Berry, Julia Sochava, Liad Gross, Madison Miller
 * cnberry, jsochava, liadgr, millemad
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <iostream>
#include <string>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

string getAIMoveString(const BuildingState& buildingState) {
    
    string move = "";
    int maxAngerFloor = -1;
    int angerLevelPerFloor = 0;
    int currentAngerLevel = 0;
    int floorToGoTo = -1;
    int elevatorZeroLocation = buildingState.elevators[0].currentFloor;
    int elevatorOneLocation = buildingState.elevators[1].currentFloor;
    int elevatorTwoLocation = buildingState.elevators[2].currentFloor;
    int minDistance = 11;
    int elevator = -1;
    bool peopleThere = false;

    if (buildingState.elevators[0].isServicing) {
        if (buildingState.elevators[1].isServicing) {
            if (buildingState.elevators[2].isServicing) {
                return move;
            }
        }
    }
    
    for (int i = 0; i < NUM_FLOORS; i++) {
        if(buildingState.floors[i].numPeople > 0) {
            peopleThere = true;
        }
    }
    if(peopleThere == false) {
        return move;
    }
    
    if (!buildingState.elevators[0].isServicing) {
        elevator = 0;
    }

    
    for (int i = 0; i < NUM_FLOORS; i++) {
        angerLevelPerFloor = 0;
        if (buildingState.floors[i].numPeople > 0 ) {
            for (int j = 0; j < buildingState.floors[i].numPeople; j++) {
                currentAngerLevel = buildingState.floors[i].people[j].angerLevel;
                angerLevelPerFloor += currentAngerLevel;
            }
            if (maxAngerFloor <= angerLevelPerFloor) {
                maxAngerFloor = angerLevelPerFloor;
                floorToGoTo = i;
            }
        }
    }
    
    // BACKUP FLOOR CODE
    
    int backUpFloor = 0;
    maxAngerFloor = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        angerLevelPerFloor = 0;
        if (buildingState.floors[i].numPeople > 0 ) {
            for (int j = 0; j < buildingState.floors[i].numPeople; j++) {
                currentAngerLevel = buildingState.floors[i].people[j].angerLevel;
                angerLevelPerFloor += currentAngerLevel;
            }
            if (maxAngerFloor <= angerLevelPerFloor && i != floorToGoTo) {
                maxAngerFloor = angerLevelPerFloor;
                backUpFloor = i;
            }
        }
    }
    
    // BACKUP FLOOR CODE
    
    
    int changeInLocationZero = abs(floorToGoTo - elevatorZeroLocation);
    int changeInLocationOne = abs(floorToGoTo - elevatorOneLocation);
    int changeInLocationTwo = abs(floorToGoTo - elevatorTwoLocation);
    
    
    if (!buildingState.elevators[0].isServicing && changeInLocationZero < minDistance) {
        minDistance = changeInLocationZero;
        elevator = 0;
    }
    if (!buildingState.elevators[1].isServicing && changeInLocationOne < minDistance) {
        minDistance = changeInLocationOne;
        elevator = 1;
    }
    if (!buildingState.elevators[2].isServicing && changeInLocationTwo < minDistance) {
        minDistance = changeInLocationTwo;
        elevator = 2;
    }
    
    int target0 = buildingState.elevators[0].targetFloor;
    int target1 = buildingState.elevators[1].targetFloor;
    int target2 = buildingState.elevators[2].targetFloor;
    
    
    if (!buildingState.elevators[elevator].isServicing && buildingState.floors[buildingState.elevators[elevator].currentFloor].numPeople > 0){
        move += "e" + to_string(elevator) + "p";
        return move;
    }
    if (buildingState.elevators[elevator].isServicing) {
        move = "";
        return move;
    } else {
        if (floorToGoTo  == target0 || floorToGoTo  == target1 || floorToGoTo  == target2){
            
            
        // BACKUP FLOOR CODE
            bool peopleOnAFloor = 0;
            for (int i = 0; i < NUM_FLOORS; i++){
                if (i != floorToGoTo){
                    if (buildingState.floors[i].numPeople > 0){
                        peopleOnAFloor = 1;
                    }
                }
            }

            if (peopleOnAFloor){
                move += "e" + to_string(elevator) + "f" + to_string(backUpFloor);
                return move;
            } else {
                move = "";
                return move;
            }
            
        // BACKUP FLOOR CODE
            
        } else {
            move += "e" + to_string(elevator) + "f" + to_string(floorToGoTo);
            return move;
        }
    }
    
    
    
    return move;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
                       const Floor& floorToPickup) {
    
    string moveIndicies = "";
    int angerLevelUp = 0;
    int angerLevelDown = 0;
    bool direction = false;
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
            if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
                angerLevelUp += floorToPickup.getPersonByIndex(i).getAngerLevel();
            } else {
                angerLevelDown += floorToPickup.getPersonByIndex(i).getAngerLevel();
            }
        }
        
    int requestUp = 0;
    int requestDown = 0;
    
        if (angerLevelUp > angerLevelDown) {
            direction = 1;
        } else if (angerLevelUp < angerLevelDown) {
            direction = 0;
        }
        else {
            for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
                if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
                    angerLevelUp += floorToPickup.getPersonByIndex(i).getAngerLevel();
                    requestUp++;
                } else {
                    angerLevelDown += floorToPickup.getPersonByIndex(i).getAngerLevel();
                    requestDown++;
                }
            }
            if (requestUp >= requestDown){
                direction = 1;
            } else {
                direction = 0;
            }
        }
        
        if (direction){
            for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
                if (floorToPickup.getPersonByIndex(i).getTargetFloor() > floorToPickup.getPersonByIndex(i).getCurrentFloor()) {
                    moveIndicies += to_string(i);
                }
            }
        } else {
            for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
                int targetFloor = floorToPickup.getPersonByIndex(i).getTargetFloor();
                int currentFloor = floorToPickup.getPersonByIndex(i).getCurrentFloor();
                if (targetFloor < currentFloor) {
                    moveIndicies += to_string(i);
                }
            }
        }
    
    return moveIndicies;
}
