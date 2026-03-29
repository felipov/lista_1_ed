#include "ReservationRequest.hpp"

#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

class Reserves{
private:
    ReservationRequest* request;
    int size;
    int capacity;

public:
    Reserves();
    Reserves(ReservationRequest* request, int capacity);
    Reserves(const Reserves& other);
    Reserves& operator = (const Reserves& other);
    ~Reserves();
    void append(ReservationRequest request);
    void remove(ReservationRequest request);
    void resize(int nova_capacidade);
    void display();
    int getSize();
    ReservationRequest getRequest(int index);
};


class Rooms{

private:
    Reserves* reserve;
    std::string* name;
    int* room_capacity;
    int size;
    int list_capacity;

public:
    Rooms();
    Rooms(Reserves* reserve, std::string* name, int list_capacity,
            int* room_capacity);
    Rooms(const Rooms& other);
    Rooms& operator = (const Rooms& other);
    ~Rooms();
    void append(std::string name, int room_capacity);
    void resize(int nova_capacidade);
    void display();
    int getSize();
    int getRoomCapacity(int index);
    Reserves& getReserves(int index);
    std::string getName(int index);
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...
    std::string week[5];

public:
    Reserves* list_reserves;
    Rooms* list_rooms;

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif