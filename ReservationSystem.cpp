#include <iostream>
#include <string>
#include "ReservationSystem.hpp"


// Funções da classe Reserves
Reserves::Reserves(){
    this->size = 0;
    this->capacity = 10;
    this->request = new ReservationRequest[capacity];
}

Reserves::Reserves(ReservationRequest* request, int capacity){
    this->request = new ReservationRequest[capacity];
    this->size = 0;
    this->capacity = capacity;
}

Reserves::Reserves(const Reserves& other){
    this->size = other.size;
    this->capacity = other.capacity;
    this->request = new ReservationRequest[this->capacity];

    for (int i = 0; i < this->size; i++) {
        this->request[i] = other.request[i];
    }
}

Reserves& Reserves::operator = (const Reserves& other){
    if (this != &other){

        ReservationRequest* new_request = new ReservationRequest[other.capacity];
        for (int i = 0; i < other.size; i++) {
            new_request[i] = other.request[i];
        }

        delete[] this->request;

        this->size = other.size;
        this->capacity = other.capacity;
        this->request = new_request;

        for (int i = 0; i < this->size; i++) {
            this->request[i] = other.request[i];
        }
    }
    return *this;
}

Reserves::~Reserves(){
    if (this->request != nullptr) {
        delete[] this->request;
        this->request = nullptr;
    }
}

void Reserves::append(ReservationRequest request){
    if (this->size == this->capacity) {
        Reserves::resize(2 * this->capacity);
    }
    this->request[this->size] = request;
    this->size++;
}

void Reserves::remove(ReservationRequest request){

    int index = -1;

    for (int i = 0; i < this->size; i++) {
        if (this->request[i].getCourseName() == request.getCourseName()) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < this->size - 1; i++) {
            this->request[i] = this->request[i + 1];
        }

        this->size--;
    }

    if (this->capacity > 4 && this->size <= this->capacity / 4) {
        Reserves::resize(this->capacity / 2);
    }
}

void Reserves::resize(int new_capacity){
    ReservationRequest* new_reserves = new ReservationRequest[new_capacity];

    for (int i = 0; i < this->size; i++) {
        new_reserves[i] = this->request[i];
    }

    if (this->request != nullptr) {
        delete[] this->request;
        this->request = nullptr;
    }
    this->request = new_reserves;
    this->capacity = new_capacity;
}

void Reserves::display() {
    std::cout << "Número de reservas feitas: " << this->size << std::endl;
    std::cout << "Capacidade atual de reservas: " << this->capacity << std::endl;
    std::cout << std::endl;
    std::cout << "Reservas:" << std::endl;
    for (int i = 0; i < this->size; i++){
        std::cout << "Nome do curso: " << this->request[i].getCourseName() << std::endl;
        std::cout << "Dia da semana: " << this->request[i].getWeekday() << std::endl;
        std::cout << "Horário inicial: " << this->request[i].getStartHour() << "h" << std::endl;
        std::cout << "Horário final: " << this->request[i].getEndHour() << "h" << std::endl;
        std::cout << "Quantidade de estudantes: " << this->request[i].getStudentCount() << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Reserves::getSize(){
    return this->size;
}
 
ReservationRequest Reserves::getRequest(int index){
    return this->request[index];
}


// Funções da classe Rooms

Rooms::Rooms(){
    this->size = 0;
    this->list_capacity = 10;
    this->reserve = new Reserves[list_capacity];
    this->name = new std::string[list_capacity];
    this->room_capacity = new int[list_capacity];

}

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

Rooms::Rooms(const Rooms& other){
    this->size = other.size;
    this->list_capacity = other.list_capacity;
    this->reserve = new Reserves[this->list_capacity];
    this->name = new std::string[this->list_capacity];
    this->room_capacity = new int[this->list_capacity];

    for (int i = 0; i < this->size; i++) {
        this->reserve[i] = other.reserve[i];
        this->name[i] = other.name[i];
        this->room_capacity[i] = other.room_capacity[i];
    }
}

Rooms& Rooms::operator = (const Rooms& other){
    if (this != &other) {

        if (this->reserve != nullptr && this->name != nullptr && this->room_capacity != nullptr) {
            delete[] this->reserve;
            delete[] this->name;
            delete[] this->room_capacity;
            this->reserve = nullptr;
            this->name = nullptr;
            this->room_capacity = nullptr;
        }

        this->size = other.size;
        this->list_capacity = other.list_capacity;

        this->reserve = new Reserves[list_capacity];
        this->name = new std::string[list_capacity];
        this->room_capacity = new int[list_capacity];

        for (int i = 0; i < this->size; i++) {
            this->reserve[i] = other.reserve[i];
            this->name[i] = other.name[i];
            this->room_capacity[i] = other.room_capacity[i];
        }
    }

    return *this;
}

Rooms::~Rooms(){
    if (this->reserve != nullptr) {
        delete[] this->reserve;
        this->reserve = nullptr;
    }

    if (this->name != nullptr) {
        delete[] this->name;
        this->name = nullptr;
    }

    if (this->room_capacity != nullptr) {
        delete[] this->room_capacity;
        this->room_capacity = nullptr;
    }
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

    for (int i = 0; i < this->size; i++) {
       new_reserve[i] = this->reserve[i];
       new_name[i] = this->name[i];
       new_room_capacity[i] = this->room_capacity[i];
    }

    if (this->reserve != nullptr){
        delete[] this->reserve;
        this->reserve = nullptr;
    }

    if (this->name != nullptr) {
        delete[] this->name;
        this->reserve = nullptr;
    }

    if (this->room_capacity != nullptr) {
        delete[] this->room_capacity;
        this->room_capacity = nullptr;
    }

    this->reserve = new_reserve;
    this->name = new_name;
    this->room_capacity = new_room_capacity;
    this->list_capacity = nova_capacidade;
}

void Rooms::display(){
    // std::cout << "Número de salas: " << this->size << std::endl;
    // std::cout << "Capacidade atual de salas: " << this->list_capacity << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < this->size; i++){
        std::cout << "Nome: " << this->name[i] << std::endl;
        std::cout << "Capacidade da sala: " << this->room_capacity[i] << std::endl;
        this->getReserves(i).display();
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

void Reserves::display(){
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

    this->list_rooms = new Rooms();

    for (int i = 0; i < room_count; i++) {
        std::string name = "Sala " + std::to_string(i + 1);
        this->list_rooms->append(name, room_capacities[i]);
    }

}

ReservationSystem::~ReservationSystem(){
    if (this->room_capacities != nullptr) {
        delete[] this->room_capacities;
        this->room_capacities = nullptr;
    }
    if (this->list_rooms != nullptr) {
        delete this->list_rooms;
        this->list_rooms = nullptr;
    }
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

                return true;
            }
        }
    }
    return false;
}

void ReservationSystem::printSchedule(){
    std::cout << "\n=== Grade de Reservas ===" << "\n";

    for (int i = 0; i < this->list_rooms->getSize(); i++) {
        Reserves& reservas = this->list_rooms->getReserves(i);

        std::cout << this->list_rooms->getName(i) << "\n";
        
        for (int d = 0; d < 5; d++) {
            bool imprimiu_dia = false;

            for (int j = 0; j < reservas.getSize(); j++) {
                ReservationRequest req = reservas.getRequest(j);

                if (!imprimiu_dia) {
                    std::cout << this->week[d] << ":" << std::endl;
                    imprimiu_dia = true;
                }
            }
        }
    }
}
