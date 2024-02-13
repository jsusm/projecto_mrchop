#include "../headers/director.h"
#include "../headers/equipo.h"
#include "../headers/jugador.h"
#include "../headers/archivo.h"

const int nmax = 100;

using namespace std;

const bool mostrar_menus = true;

int main() {
  Equipo equipos[nmax];
  int n_equipos = 0;

  Jugador jugadores[nmax];
  int n_jugadores = 0;

  Director directores[nmax];
  int n_directores = 0;

  leerArchivo(equipos, n_equipos, jugadores, n_jugadores, directores,
              n_directores);

  return 0;
}
