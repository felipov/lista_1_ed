#include "ReservationRequest.hpp"

#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

class Rooms{

private:
    ReservationRequest* request;
    std::string name;
    int size;
    int list_capacity;
    int room_capacity;

public:
    Rooms(ReservationRequest* request, std::string name, int size, int list_capacity,
            int room_capacity);
    ~Rooms();
    bool append(Rooms* room_list, std::string name, int room_capacity);
    bool remove(Rooms* room_list, std::string name);
};

class Reserves{
private:
    ReservationRequest* request;
    int size;
    int capacity;

public:
    Reserves(ReservationRequest* request, int size, int capacity);
    ~Reserves();
    bool append(ReservationRequest request);
    bool remove(ReservationRequest request);
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...
    std::string week[5];
    int week_size;

    // Aqui inicializar um Rooms e um Reserves.

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif