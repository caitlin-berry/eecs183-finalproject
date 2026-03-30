# Final Project - Elevators Simulation Game

A C++ simulation game where the player controls multiple elevators in a building to transport passengers efficiently while minimizing wait times and penalties. The project models a real-world system using object-oriented design and interactive gameplay.

## Overview
This project simulates an elevator system in a 10-floor building with 3 elevators. The goal is to manage elevator movements to pick up and deliver passengers while minimizing their wait time (measured by increasing "anger levels").

The program:
- Processes time-based events from an input file
- Simulates passengers appearing and requesting elevators
- Tracks elevator movement and passenger state
- Updates the system each turn (tick-based simulation)
- Ends when all events are processed or too many passengers "explode"

The system is built using multiple interacting classes, each responsible for a different component of the simulation.

## How to Run
Compile the program:
```bash
g++ Person.cpp Elevator.cpp Floor.cpp Move.cpp Building.cpp Game.cpp main.cpp -o elevators
```

Run the program:
```bash
./elevators
```

Follow the on-screen prompts to control the elevators and progress through the simulation.

## Concepts Used
- Object-oriented programming (classes and encapsulation)
- Simulation and state management
- File input/output (reading event data)
- Modular program design across multiple classes
- Game loop and time-step ("tick") updates
- Conditional logic and decision-making systems

## Program Structure
- `Person.cpp`: Represents passengers and tracks their destination and anger level
- `Elevator.cpp`: Handles elevator movement and passenger transport
- `Floor.cpp`: Manages passengers waiting on each floor
- `Move.cpp`: Represents user actions and elevator commands
- `Building.cpp`: Coordinates floors and elevators
- `Game.cpp`: Controls overall game flow and state updates
- `AI.cpp` (optional/Reach): Implements an automated strategy for playing the game

## Contributions
This project was completed with a team of four students. Work was split evenly across all members, with each person contributing to the implementation and integration of the system components.

## Example Features
- Real-time simulation using discrete time steps ("ticks")
- Dynamic passenger generation from input files
- Elevator scheduling and movement logic
- Passenger state tracking (including increasing wait times)
- Scoring system based on efficiency and performance
- Option to save and reload game state

## Example Gameplay
- Players control 3 elevators across 10 floors
- Passengers appear over time and request to go up or down
- Each turn, the player chooses how elevators should move
- Delayed service increases passenger anger, affecting score
