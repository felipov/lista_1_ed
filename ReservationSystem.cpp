#include <iostream>
#include "ReservationSystem.hpp"

ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    this->room_capacities = new int[room_count];
    for (int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    }
}

ReservationSystem::~ReservationSystem(){
    delete[] this->room_capacities;
}