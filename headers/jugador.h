#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>

using namespace std;

enum Posicion {
  Pos_Portero,
  Pos_Defenza,
  Pos_Mediocampista,
  Pos_Delantero,
};

class Jugador {
  string equipo;
  string nombre;
  string apellido;
  Posicion posicion;
  int experiencia;
  int goles;
  bool lesionado;

public:
  Jugador();
  void inicializar(string equipo, string nombre, string apellido,
                   Posicion posicion, int experiencia);
  void print();
  string getEquipo();
  string getNombreCompleto();
  Posicion getPosicion();
  string getPosicionStr();
  int getExperiencia();
  int incrementarExperiencia(int incremento);
};

#endif // JUGADOR_H
