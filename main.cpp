#include <iostream>
#include <string>
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

int main(){
    int room_count = 3;
    int capacities[3] = {30, 50, 80};

    ReservationSystem sistema(room_count, capacities);
    ReservationRequest r1("Cálculo I", "segunda", 7, 9, 25);
    ReservationRequest r2("Álgebra Linear Numérica", "terca", 8, 10, 56);
    ReservationRequest r3("Estruturas de Dados e Algoritmos", "quarta", 12, 14, 34);
    ReservationRequest r4("Cálculo II", "segunda", 7, 9, 50);
    ReservationRequest r5("Linguagens de Programação", "segunda", 7, 9, 80);
    ReservationRequest r6("Cálculo III", "segunda", 7, 9, 23);

    sistema.reserve(r1);
    sistema.reserve(r2);
    sistema.reserve(r3);
    sistema.reserve(r4);
    sistema.reserve(r5);
    sistema.reserve(r6);
    sistema.printSchedule();

    sistema.cancel("Cálculo I");
    sistema.cancel("Estruturas de Dados e Algoritmos");

    sistema.printSchedule();

    ReservationRequest r7("Estruturas de Dados e Algoritmos", "quinta", 11, 13, 34);
    ReservationRequest r8("Matemática Discreta", "segunda", 9, 11, 50);

    sistema.reserve(r7);
    sistema.reserve(r8);

    sistema.printSchedule();
    
    sistema.~ReservationSystem();


    
    return 0;
}