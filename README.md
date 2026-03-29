# Room Reservation System

Sistema para gerenciamento de reservas de salas de aula para disciplinas durante uma semana.
Ao reservar uma sala, o sistema verifica automaticamente a disponibilidade e a capacidade, 
atribuindo a primeira sala disponível que comporte a turma.

Funcionalidades:
- Reservar salas de aula;
- Cancelar uma reserva existente;
- Exibir a grade de reservas por sala.

## Compilação
```g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system```

## Execução
```./reservation_system```

## Organização dos dados

O sistema funciona com três classes principais:

**ReservationRequest**: Guarda os dados de uma solicitação de reserva (nome da disciplina,
dia da semana, horário de início, horário de término e número de alunos).

**Reserves**: Array dinâmico de `ReservationRequest`. Quando o array enche, dobra de tamanho
automaticamente.

**Rooms**: Array dinâmico de salas, que também dobra de tamanho quando necessário. Cada sala 
possui um nome, uma capacidade máxima e uma lista de reservas (Reserves) associada a ela.

**ReservationSystem**: Controlador do sistema. Guarda a lista de salas e uma lista de reservas
para cada sala. Para reservar, percorre as salas em ordem procurando a primeira que tenha 
capacidade suficiente e sem conflito de horário no dia solicitado.
