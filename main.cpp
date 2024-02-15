#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*#####################
      Constantes
#####################*/
const int nmax = 100;
const bool mostrar_menus = true;


/*#####################
        Enums
#####################*/

// Posicion de los jugadores
enum Posicion {
  Pos_Portero,
  Pos_Defenza,
  Pos_Mediocampista,
  Pos_Delantero,
};

/*#####################
        Clases
#####################*/

// Director
class Director {
  string nombre;
  string apellido;
  int experiencia;

public:
  // Asignar valores a la instancia de la clase
  void inicializar(string nombre, string apellido, int experiencia) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->experiencia = experiencia;
  }
  // Inprimir los atributos de la instancia
  void print() {
    cout << "Director: " << endl;
    cout << "\tnombre: " << this->nombre << endl;
    cout << "\tapellido: " << this->apellido << endl;
    cout << "\texperiencia: " << this->experiencia << endl << endl;
  }
};

// Jugador
class Jugador {
  string equipo;
  string nombre;
  string apellido;
  Posicion posicion;
  int experiencia;
  int goles;
  bool lesionado;

public:
  // Inicializar a valores por defecto
  Jugador() {
    this->posicion = Pos_Portero;
    this->goles = 0;
    this->experiencia = 0;
    this->lesionado = false;
  }

  // Asignar valores a la instancia
  void inicializar(string equipo, string nombre, string apellido,
                   Posicion posicion, int experiencia) {
    this->equipo = equipo;
    this->nombre = nombre;
    this->apellido = apellido;
    this->posicion = posicion;
    this->experiencia = experiencia;
  }

  // Inprimir los atributos de la instancia
  void print() {
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

  string getEquipo() { return this->equipo; }

  string getNombreCompleto() { return this->nombre + " " + this->apellido; }

  Posicion getPosicion() { return this->posicion; }

  // Retorna el nombre de la posicion de la instancia
  string getPosicionStr() {
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

  int getExperiencia() { return this->experiencia; }

  int incrementarExperiencia(int incremento) {
    this->experiencia += incremento;
    return this->experiencia;
  }
};

// Equipo
const int max_jugadores = 11;

class Equipo {
  string nombre;
  int jugadoresIdx[max_jugadores];
  int n_jugadores;

public:
  // Inicializa a valores po defecto
  Equipo() { this->n_jugadores = 0; }

  Equipo(string nombre) { this->nombre = nombre; }

  // Asignar valores a la instancia
  void inicializar(string nombre) { this->nombre = nombre; }

  void sumarJugador(int idx) {
    // TODO: Añadir validacion: no puede sobrepasar la cantidad de jugadores
    // permitido
    this->jugadoresIdx[this->n_jugadores] = idx;
    n_jugadores++;
  };

  string getNombre() { return this->nombre; }

  // Imprime los jugadores que pertenecen al equipo
  void imprimirJugadores(Jugador *jugadores, int n_jugadores) {
    cout << "Jugadores en el equipo: " << nombre << endl;
    for (int i = 0; i < this->n_jugadores; i++) {
      jugadores[jugadoresIdx[i]].print();
    }
  }
};

/*#####################
      Entrada.in
#####################*/
// Añade un equipo al arreglo de la informacion contenida en la linea
void extraerEquipo(Equipo *equipos, int &n_equipos, string line) {
  equipos[n_equipos].inicializar(line);
  n_equipos++;
}

// Añade un jugador al arreglo de la informacion contenida en la linea
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

  jugadores[n_jugadores].inicializar(equipo1 + " " + equipo2, nombre, apellido,
                                     pos, experiencia);
  n_jugadores++;
}

// Añade un jugador al arreglo de la informacion contenida en la linea
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

// Lee el archivo y guarda los datos serializados en memoria
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
  for (int j = 0; j < n_jugadores; j++) {
    string nombreEquipo = jugadores[j].getEquipo();
    jugadores[j].print();
    for (int e = 0; e < n_equipos; e++) {
      cout << nombreEquipo << "," << equipos[e].getNombre() << endl;
      if (equipos[e].getNombre().compare(nombreEquipo) == 0) {
        jugadores[j].print();
        equipos[e].sumarJugador(j);
      }
    }
  }
  archivo.close();
}

/*#####################
        Main
#####################*/
int main() {
  Equipo equipos[nmax];
  int n_equipos = 0;

  Jugador jugadores[nmax];
  int n_jugadores = 0;

  Director directores[nmax];
  int n_directores = 0;

  leerArchivo(equipos, n_equipos, jugadores, n_jugadores, directores,
              n_directores);

  for (int i = 0; i < n_equipos; i++) {
    equipos[i].imprimirJugadores(jugadores, n_jugadores);
  }

  return 0;
}
