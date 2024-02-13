#include "../headers/director.h"
#include "../headers/equipo.h"
#include "../headers/jugador.h"
#include <fstream>
#include <string>
using std::string;

void extraerEquipo(Equipo *equipos, int &n_equipos, string line);
void extraerJugador(Jugador *jugadores, int &n_jugadores, string line);
void extraerDirector(Director *directores, int &n_directores, string line);
void leerArchivo(Equipo *equipos, int &n_equipos, Jugador *jugadores,
                 int &n_jugadores, Director *directores, int &n_directores);
