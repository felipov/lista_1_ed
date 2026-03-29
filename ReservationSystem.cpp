#include <iostream>
#include "ReservationSystem.hpp"


// Funções da classe Rooms

Rooms::Rooms() = default;

Rooms::Rooms(Reserves* reserve, std::string* name, int list_capacity, int* room_capacity){
    this->reserve = new Reserves[list_capacity];
    this->name = new std::string[list_capacity];
    this->room_capacity = new int[list_capacity];
    
    for (int i = 0; i < list_capacity; i++) {
        this->reserve[i] = reserve[i];
        this->name[i] = name[i];
        this->room_capacity[i] = room_capacity[i];
    }

    this->size = 0;
    this->list_capacity = list_capacity;
}

Rooms::~Rooms(){
    delete[] this->reserve;
    delete[] this->name;
    delete[] this->room_capacity;
}

void Rooms::append(std::string name, int room_capacity){
    if (this->size == this->list_capacity) {
        Rooms::resize(2 * this->list_capacity);
    }
    this->reserve[this->size] = Reserves();
    this->name[this->size] = name;
    this->room_capacity[this->size] = room_capacity;
    this->size++;
}

void Rooms::resize(int nova_capacidade) {
    Reserves* new_reserve = new Reserves[nova_capacidade];
    std::string* new_name = new std::string[nova_capacidade];
    int* new_room_capacity = new int[nova_capacidade];

    for (int i = 0; i < this->list_capacity; i++) {
       new_reserve[i] = this->reserve[i];
       new_name[i] = this->name[i];
       new_room_capacity[i] = this->room_capacity[i];
    }

    delete[] this->reserve;
    delete[] this->name;
    delete[] this->room_capacity;

    this->reserve = new_reserve;
    this->name = new_name;
    this->room_capacity = new_room_capacity;
    this->list_capacity = nova_capacidade;
}

void Rooms::display(){
    std::cout << "Número de salas: " << this->size << std::endl;
    std::cout << "Capacidade atual de salas: " << this->list_capacity << std::endl;
    for (int i = 0; i < this->size; i++){
        std::cout << "Nome: " << this->name[i] << std::endl;
        std::cout << "Capacidade da sala: " << this->room_capacity[i] << std::endl;
    }
    std::cout << std::endl;
}

int Rooms::getSize(){
    return this->size;
}

int Rooms::getRoomCapacity(int index){
    return this->room_capacity[index];
}

Reserves& Rooms::getReserves(int index){
    return this->reserve[index];
}
 
std::string Rooms::getName(int index){
    return this->name[index];
}


// Funções da classe Reserves

Reserves::Reserves() = default;

Reserves::Reserves(ReservationRequest* request, int capacity){
    this->request = new ReservationRequest[capacity];
    for (int i = 0; i < capacity; i++){
        this->request[i] = request[i];
    }
    this->size = 0;
    this->capacity = capacity;
}

Reserves::~Reserves(){
    delete[] this->request;
}

void Reserves::append(ReservationRequest request){
    if (this->size == this->capacity) {
        Reserves::resize(2 * this->capacity);
    }
    this->request[this->size] = request;
    this->size++;
}

void Reserves::remove(ReservationRequest request){
    if (this->size <= this->capacity / 2) {
        Reserves::resize(this->capacity / 2);
    }

    ReservationRequest* new_request = new ReservationRequest[this->capacity];
    int critical_value = 0;

    for (int i = 0; i < this->size; i++) {
        if (this->request[i].getCourseName() != request.getCourseName()) {
            new_request[i] = this->request[i];
        } else {
            critical_value = i;
            break;
        }
    }

    for (int i = critical_value + 1; i < this->size; i++) {
        new_request[i-1] = this->request[i];
    }
    delete[] this->request;
    this->request = new_request;
    this->size--;
}

void Reserves::resize(int new_capacity){
    ReservationRequest* new_reserves = new ReservationRequest[new_capacity];

    for (int i = 0; i < this->size; i++) {
        new_reserves[i] = this->request[i];
    }

    delete[] this->request;
    this->request = new_reserves;
    this->capacity = new_capacity;
}

void Reserves::display() {
    std::cout << "Número de reservas feitas: " << this->size << std::endl;
    std::cout << "Capacidade atual de reservas: " << this->capacity << std::endl;
    for (int i = 0; i < this->size; i++){
        std::cout << "Reserva:" << std::endl;
        std::cout << "Nome do curso: " << this->request[i].getCourseName() << std::endl;
        std::cout << "Dia da semana: " << this->request[i].getWeekday() << std::endl;
        std::cout << "Horário inicial: " << this->request[i].getStartHour() << "h" << std::endl;
        std::cout << "Horário final: " << this->request[i].getEndHour() << "h" << std::endl;
        std::cout << "Quantidade de estudantes: " << this->request[i].getStudentCount() << "h" << std::endl;
    }
    std::cout << std::endl;
}

int Reserves::getSize(){
    return this->size;
}
 
ReservationRequest Reserves::getRequest(int index){
    return this->request[index];
}


// Funções da classe ReservationSystem

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
    this->list_rooms = new Rooms;
    this->list_reserves = new Reserves;

}

ReservationSystem::~ReservationSystem(){
    delete[] this->room_capacities;
    delete this->list_rooms;
    delete this->list_reserves;
}


bool ReservationSystem::reserve(ReservationRequest request){
    int start = request.getStartHour();
    int end = request.getEndHour();
    int students = request.getStudentCount();
    std::string dia = request.getWeekday();
 
    for (int i = 0; i < this->list_rooms->getSize(); i++) {

        if (this->list_rooms->getRoomCapacity(i) < students) continue;
 
        Reserves& reservas = this->list_rooms->getReserves(i);
        bool conflito = false;
 
        for (int j = 0; j < reservas.getSize(); j++) {
            ReservationRequest existing = reservas.getRequest(j);
            if (existing.getWeekday() == dia) {
                if (end > existing.getStartHour() && existing.getEndHour() > start) {
                    conflito = true;
                    break;
                }
            }
        }
 
        if (conflito) continue;
 
        reservas.append(request);
        this->list_reserves->append(request);

        return true;
    }
    return false;
}

bool ReservationSystem::cancel(std::string course_name){
    for (int i = 0; i < this->list_rooms->getSize(); i++) {
        Reserves& reservas = this->list_rooms->getReserves(i);

        for (int j = 0; j < reservas.getSize(); j++) {
            if (reservas.getRequest(j).getCourseName() == course_name) {
                ReservationRequest req = reservas.getRequest(j);
                reservas.remove(req);
                this->list_reserves->remove(req);

                return true;
            }
        }
    }
    return false;
}