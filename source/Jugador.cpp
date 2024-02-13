#include "../headers/jugador.h"
#include <iostream>

Jugador::Jugador() {
  this->posicion = Pos_Portero;
  this->goles = 0;
  this->experiencia = 0;
  this->lesionado = false;
}

void Jugador::inicializar(string equipo, string nombre, string apellido,
                          Posicion posicion, int experiencia) {
  this->equipo = equipo;
  this->nombre = nombre;
  this->apellido = apellido;
  this->posicion = posicion;
  this->experiencia = experiencia;
}

void Jugador::print() {
  cout << "Jugador: " << endl;
  cout << "\tequipo: " << this->equipo << endl;
  cout << "\tnombre: " << this->nombre << endl;
  cout << "\tapellido: " << this->apellido << endl;
  cout << "\tposicion: ";
  switch (posicion) {
  case Pos_Portero:
    cout << "Portero";
    break;
  case Pos_Delantero:
    cout << "Delantero";
    break;
  case Pos_Defenza:
    cout << "Defenza";
    break;
  case Pos_Mediocampista:
    cout << "Mediocampista";
    break;
  }
  cout << endl;
  cout << "\texperiencia: " << this->experiencia << endl << endl;
}

string Jugador::getEquipo() { return this->equipo; }

string Jugador::getNombreCompleto() {
  return this->nombre + " " + this->apellido;
}

Posicion Jugador::getPosicion() { return this->posicion; }

string Jugador::getPosicionStr() {
  switch (posicion) {
  case Pos_Portero:
    return "Portero";
    break;
  case Pos_Delantero:
    return "Delantero";
    break;
  case Pos_Defenza:
    return "Defenza";
    break;
  case Pos_Mediocampista:
    return "Mediocampista";
    break;
  }
  return "";
}

int Jugador::getExperiencia() { return this->experiencia; }

int Jugador::incrementarExperiencia(int incremento) {
  this->experiencia += incremento;
  return this->experiencia;
}
