#include <iostream>
#include "ReservationSystem.hpp"

ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;
    this->room_capacities = new int[room_count];
    for (int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    }

    this->week[0] = "segunda";
    this->week[1] = "terca";
    this->week[2] = "quarta";
    this->week[3] = "quinta";
    this->week[4] = "sexta";

    this->week_size = 5;
}

ReservationSystem::~ReservationSystem(){
    delete[] this->room_capacities;
}

bool ReservationSystem::reserve(ReservationRequest request){
    return false;
}
