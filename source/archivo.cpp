#include "../headers/archivo.h"
#include <iostream>

void extraerEquipo(Equipo *equipos, int &n_equipos, string line) {
  equipos[n_equipos].inicializar(line);
  n_equipos++;
}

void extraerJugador(Jugador *jugadores, int &n_jugadores, string line) {
  int cursor = 0;
  string equipo1 = line.substr(cursor, line.find(" "));
  cursor = line.find(" ", cursor) + 1;
  string equipo2 = line.substr(cursor, line.find(" ", cursor) - cursor);
  cursor = line.find(" ", cursor) + 1;
  string nombre = line.substr(cursor, line.find(" ", cursor) - cursor);
  cursor = line.find(" ", cursor) + 1;
  string apellido = line.substr(cursor, line.find(" ", cursor) - cursor);
  cursor = line.find(" ", cursor) + 1;
  string posicion = line.substr(cursor, line.find(" ", cursor) - cursor);
  cursor = line.find(" ", cursor) + 1;
  string exp = line.substr(cursor, cursor - line.length());

  Posicion pos;
  if (posicion.compare("Portero") == 0) {
    pos = Pos_Portero;
  } else if (posicion.compare("Defensa") == 0) {
    pos = Pos_Defenza;
  } else if (posicion.compare("Delantero") == 0) {
    pos = Pos_Delantero;
  } else if (posicion.compare("Mediocampista") == 0) {
    pos = Pos_Mediocampista;
  }

  int experiencia = stoi(exp);

  jugadores[n_jugadores].inicializar(equipo1 + " " + equipo2, nombre, apellido, pos,
                                     experiencia);
  n_jugadores++;
}

void extraerDirector(Director *directores, int &n_directores, string line) {
  int cursor = 0;
  string nombre = line.substr(cursor, line.find(" ", cursor) - cursor);
  cursor = line.find(" ", cursor) + 1;
  string apellido = line.substr(cursor, line.find(" ", cursor) - cursor);
  cursor = line.find(" ", cursor) + 1;
  string exp = line.substr(cursor, cursor - line.length());
  int experiencia = stoi(exp);
  directores[n_directores].inicializar(nombre, apellido, experiencia);
  n_directores++;
}

void leerArchivo(Equipo *equipos, int &n_equipos, Jugador *jugadores,
                 int &n_jugadores, Director *directores, int &n_directores) {
  std::fstream archivo;
  archivo.open("mock/entrada.in");
  if (!archivo.is_open()) {
    return;
  }

  int bandera = 0;

  while (!archivo.eof()) {
    string line;
    getline(archivo, line);
    if (line.empty()) {
      continue;
    }

    // Entra en la seccion de [E]quipos
    if (line.compare("E") == 0) {
      bandera = 1;
      continue;
    }
    // Entra en la seccion de [J]ugadores
    if (line.compare("J") == 0) {
      bandera = 2;
      continue;
    }
    // Entra en la seccion de [D]irectores
    if (line.compare("D") == 0) {
      bandera = 3;
      continue;
    }

    switch (bandera) {
    case 1:
      extraerEquipo(equipos, n_equipos, line);
      break;
    case 2:
      extraerJugador(jugadores, n_jugadores, line);
      break;
    case 3:
      extraerDirector(directores, n_directores, line);
      break;
    }
  }
  // añadimos los jugadores al los equipos
  for(int j = 0; j < n_jugadores; j++){
    string nombreEquipo = jugadores[j].getEquipo();
    jugadores[j].print();
    for(int e = 0; e < n_equipos; e++) {
      cout << nombreEquipo << "," << equipos[e].getNombre() << endl;
      if(equipos[e].getNombre().compare(nombreEquipo) == 0){
        jugadores[j].print();
        equipos[e].sumarJugador(j);
      }
    }
  }
  for(int i = 0; i < n_equipos; i++) {
    equipos[i].imprimirJugadores(jugadores, n_jugadores);
  }
  archivo.close();
}

