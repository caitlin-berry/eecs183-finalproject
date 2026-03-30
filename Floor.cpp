/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Julia Sochava, Caitlin Berry, Maddie Miller, Liad Gross
 * jsochava, cnberry, liadgr, millemad
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    int exploded = 0;
    int index[MAX_PEOPLE_PER_FLOOR];
    int num = 0;
    for (int i = 0; i < numPeople; i++) {
        if (people[i].tick(currentTime)) {
            index[num] = i;
            num++;
            exploded++;
        }
    }
    removePeople(index, num);
    return exploded;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        numPeople++;
        if (request > 0) {
            hasUpRequest = true;
        } else {
            hasDownRequest = true;
        }
    }
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    int newNumPeople = 0;
    for (int i = 0; i < numPeople; i++) {
        // Indicating whether to keep the person
        bool keepPerson = true;
            // going through people array to keep only the people that should not be removed
            for (int j = 0; j < numPeopleToRemove; j++) {
                if (indicesToRemove[j] == i) {
                    keepPerson = false;
                }
            }
            if (keepPerson) {
                if (newNumPeople != i) {
                    // Moving person to a new index if the indecies don't match(meaning they shouldn't be removed)
                    people[newNumPeople] = people[i];
                }
                newNumPeople++;
            }
        }
    numPeople = newNumPeople;
    resetRequests();
}

void Floor::resetRequests() {
    hasDownRequest = false;
    hasUpRequest = false;
    for (int i = 0; i < numPeople; i++) {
        if (people[i].getCurrentFloor() > people[i].getTargetFloor()) {
            hasDownRequest = true;
        } else if(people[i].getCurrentFloor() < people[i].getTargetFloor()) {
            hasUpRequest = true;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
