#include "../headers/equipo.h"
#include <iostream>
#include <string>

void Equipo::inicializar(std::string nombre){
  this->nombre = nombre;
}

void Equipo::sumarJugador(int idx) {
  // Añadir validacion: no puede sobrepasar la cantidad de jugadores permitido (11)
  this->jugadoresIdx[this->n_jugadores] = idx;
  n_jugadores++;
}

Equipo::Equipo(std::string nombre){
  this->inicializar(nombre);
}
Equipo::Equipo(){
  this->nombre = "";
  this->n_jugadores = 0;
}

std::string Equipo::getNombre() {
  return this->nombre;

}

void Equipo::imprimirJugadores(Jugador *jugadores, int n_jugadores){
  cout << "Jugadores en el equipo: " << nombre << endl;
  for(int i = 0; i < this->n_jugadores; i++){
    jugadores[jugadoresIdx[i]].print();
  }
}
