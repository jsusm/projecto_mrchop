#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <string>

const int max_jugadores = 11;

class Equipo {
  std::string nombre;
  int jugadoresIdx[max_jugadores];
  int n_jugadores;
public:
  Equipo();
  Equipo(std::string nombre);

  void inicializar(std::string nombre);
  void sumarJugador(int idx);
  std::string getNombre();
  void imprimirJugadores(Jugador *jugadores, int n_jugadores);
};

#endif // EQUIPO_H
