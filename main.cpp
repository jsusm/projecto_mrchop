#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*#####################
      Constantes
#####################*/
const int nmax = 100;
const bool mostrar_menus = true;

const int n_frasesPositivas = 9;
const string frasesPositiva[n_frasesPositivas] = {
    "Tiro al arco",  "Entrada eficaz", "Saludo al publico",
    "Gol",           "Pase",           "Atajada",
    "Centro eficaz", "Regate",         "Reincorporacion",
};

const int n_frasesNegativas = 9;
const string frasesNegativas[n_frasesNegativas] = {
    "Tiro a las gradas",
    "Entrada a destiempo",
    "Insulto al arbitro",
    "Falta",
    "Tarjeta",
    "Mal despeje",
    "Mano al balon",
    "Cansancio",
    "Lesion",
};

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
enum Frase {
  Frase_positiva,
  Frase_gol,
  Frase_negativa,
  Frase_lesion,
  Frase_reincorporacion,
  Frase_desconocida,
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
  void prettyPrint() {
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
    cout << "\texperiencia: " << this->experiencia << endl;
    cout << "\tgoles: " << this->goles << endl;
    cout << "\tlecionado: " << boolalpha << this->lesionado << endl;
    cout << endl;
  }

  void print() {
    cout << this->getNombreCompleto() << this->getPosicionStr()
         << this->getExperiencia() << endl;
  }

  string getEquipo() { return this->equipo; }

  string getNombreCompleto() { return this->nombre + " " + this->apellido; }
  string getNombre() { return this->nombre; }
  string getApellido() { return this->apellido; }

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

  int adicionarExperiencia(int incremento) {
    this->experiencia += incremento;
    return this->experiencia;
  }
  int adicionarGoles(int incremento) {
    this->goles += incremento;
    return this->goles;
  }
  bool getLesion() { return this->lesionado; }
  void setLecionado(bool valor) { this->lesionado = valor; }

  void setNombre(string nombre) { this->nombre = nombre; }
  void setApellido(string apellido) { this->apellido = apellido; }
  void setExperiencia(int experiencia) { this->experiencia = experiencia; }
  void setPosicion(Posicion posicion) { this->posicion = posicion; }
};

// Equipo
const int max_jugadores = 11;

class Equipo {
  string nombre;
  int jugadoresIdx[max_jugadores];
  int n_jugadores;
  int mejoresJugadores[max_jugadores];

public:
  // Inicializa a valores po defecto
  Equipo() { this->n_jugadores = 0; }

  Equipo(string nombre) { this->nombre = nombre; }

  void inicializarOrdenamientos() {
    for (int i = 0; i < n_jugadores; i++) {
      mejoresJugadores[i] = i;
    }
  }

  // Asignar valores a la instancia
  void inicializar(string nombre) {
    this->nombre = nombre;
    this->inicializarOrdenamientos();
  }

  // Ordenamiento
  // el arreglo de mejores jugadores tiene que estar en sus valores por defecto
  // [0,1,2,3,4,5,...]
  void ordenarMejoresJugadores(Jugador *jugadores) {
    for (int i = 0; i < n_jugadores; i++) {
      for (int j = i; j < n_jugadores; j++) {
        if (jugadores[jugadoresIdx[mejoresJugadores[i]]].getExperiencia() <
            jugadores[jugadoresIdx[mejoresJugadores[j]]].getExperiencia()) {
          int aux = mejoresJugadores[i];
          mejoresJugadores[i] = mejoresJugadores[j];
          mejoresJugadores[j] = aux;
        }
      }
    }
  }

  void sumarJugador(int idx, Jugador *jugadores) {
    // TODO: Añadir validacion: no puede sobrepasar la cantidad de jugadores
    // permitido
    this->jugadoresIdx[this->n_jugadores] = idx;
    n_jugadores++;

    this->inicializarOrdenamientos();
    ordenarMejoresJugadores(jugadores);
  };

  string getNombre() { return this->nombre; }

  // Imprime los jugadores que pertenecen al equipo
  void imprimirJugadores(Jugador *jugadores, bool numerado) {
    for (int i = 0; i < this->n_jugadores; i++) {
      if (numerado) {
        cout << i + 1 << ") ";
      }
      jugadores[jugadoresIdx[i]].print();
    }
  }
  // Imprime los jugadores que pertenecen al equipo
  void imprimirMejoresJugadores(Jugador *jugadores) {
    for (int i = 0; i < this->n_jugadores; i++) {
      jugadores[jugadoresIdx[mejoresJugadores[i]]].print();
    }
  }
  // Imprime los mejores jugadores en sentido contrario
  void imprimirJugadoresNuevos(Jugador *jugadores) {
    for (int i = 1; i <= this->n_jugadores; i++) {
      jugadores[jugadoresIdx[mejoresJugadores[n_jugadores - i]]].print();
    }
  }
  void imprimirJugadoresLesionados(Jugador *jugadores) {
    for (int i = 0; i < this->n_jugadores; i++) {
      if (jugadores[jugadoresIdx[i]].getLesion()) {
        jugadores[jugadoresIdx[i]].print();
      }
    }
  }
  void print() { cout << this->getNombre() << endl; }

  // Retorna el indice del jugador en el arreglo original
  // desde el arreglo de jugadores propios del equipo
  int getJugadorIdx(int idx) { return jugadoresIdx[idx]; }

  int getNJugadores() { return this->n_jugadores; }
};

/*#####################
      Entrada.in
#####################*/
// Añade un equipo al arreglo de la informacion contenida en la linea
void extraerEquipo(Equipo *equipos, int &n_equipos, string line) {
  equipos[n_equipos].inicializar(line);
  n_equipos++;
}

Posicion evaluarPosicion(string palabra) {
  Posicion pos;
  if (palabra.compare("Portero") == 0) {
    pos = Pos_Portero;
  } else if (palabra.compare("Defensa") == 0) {
    pos = Pos_Defenza;
  } else if (palabra.compare("Delantero") == 0) {
    pos = Pos_Delantero;
  } else if (palabra.compare("Mediocampista") == 0) {
    pos = Pos_Mediocampista;
  }
  return pos;
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

  Posicion pos = evaluarPosicion(posicion);

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
void leerEntrada(Equipo *equipos, int &n_equipos, Jugador *jugadores,
                 int &n_jugadores, Director *directores, int &n_directores) {
  std::fstream archivo;
  archivo.open("entrada.in");
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
    for (int e = 0; e < n_equipos; e++) {
      if (equipos[e].getNombre().compare(nombreEquipo) == 0) {
        equipos[e].sumarJugador(j, jugadores);
      }
    }
  }
  archivo.close();
}

/*#####################
      jornada#.in
#####################*/

// Categoriza la cadena en el enum Frase
Frase leerFrase(string word) {
  if (word.compare("Gol") == 0) {
    return Frase_gol;
  }
  if (word.compare("Reincorporacion") == 0) {
    return Frase_reincorporacion;
  }
  if (word.compare("Lesion") == 0) {
    return Frase_lesion;
  }
  for (int i = 0; i < n_frasesPositivas; i++) {
    if (word.compare(frasesPositiva[i]) == 0) {
      return Frase_positiva;
    }
  }
  for (int i = 0; i < n_frasesNegativas; i++) {
    if (word.compare(frasesNegativas[i]) == 0) {
      return Frase_negativa;
    }
  }
  return Frase_desconocida;
}

// Suma o resta experiencia segun la frase
// añade goles y actualiza las leciones
void evaluarFrase(Jugador &jugador, Frase frase) {
  switch (frase) {
  case Frase_desconocida:
    break;
  case Frase_gol:
    jugador.adicionarGoles(1);
    jugador.adicionarExperiencia(1);
    break;
  case Frase_reincorporacion:
    jugador.setLecionado(false);
    jugador.adicionarExperiencia(1);
    break;
  case Frase_positiva:
    jugador.adicionarExperiencia(1);
    break;
  case Frase_lesion:
    jugador.setLecionado(true);
  case Frase_negativa:
    jugador.adicionarExperiencia(-1);
    break;
  }
}

// extrae datos de la linea que representa las acciones de un jugador
// durante el partido
void extraerEntradaJornada(Jugador *jugadores, int &n_jugadores, string line) {
  int start = 0;
  int end = line.find(" ");
  // Extraer el nombre del equipo
  string equipo1 = line.substr(start, end - start);
  start = end + 1;
  end = line.find(" ", start);
  string equipo2 = line.substr(start, end - start);
  start = end + 1;
  // Extraer el nombre y apellido del jugador
  end = line.find(" ", start);
  string nombre = line.substr(start, end - start);
  start = end + 1;
  end = line.find(" ", start);
  string apellido = line.substr(start, end - start);

  // buscar el jugador
  string equipo = equipo1 + " " + equipo2;
  cout << "Leyendo linea -> " << line << endl;
  int jugadorActualIdx = -1;
  for (int j = 0; j < n_jugadores; j++) {
    if (jugadores[j].getEquipo().compare(equipo) == 0 &&
        jugadores[j].getNombre().compare(nombre) == 0 &&
        jugadores[j].getApellido().compare(apellido) == 0) {
      jugadorActualIdx = j;
    }
  }
  if (jugadorActualIdx == -1) {
    return;
  }
  // Extraer la actuacion del jugador
  string palabraActual = "";
  do {
    start = end + 1;
    end = line.find(" ", start);
    string palabra = line.substr(start, end - start);
    if (isupper(palabra.at(0))) {
      Frase frase = leerFrase(palabraActual);
      evaluarFrase(jugadores[jugadorActualIdx], frase);
      // Inicia una nueva frase
      palabraActual = palabra;
    } else {
      // Añade palabras a la frase actual
      palabraActual.append(" ");
      palabraActual.append(palabra);
    }
  } while (line.find(" ", start) != string::npos);
  // Repetir para la ultima palabra restante
  Frase frase = leerFrase(palabraActual);
  evaluarFrase(jugadores[jugadorActualIdx], frase);
}

// Lee el contenido de la jornada y aplica los cambios a los jugadores
void leerJornada(string nombreArchivo, Equipo *equipos, int &n_equipos,
                 Jugador *jugadores, int &n_jugadores, Director *directores,
                 int &n_directores) {
  fstream archivo;
  archivo.open(nombreArchivo);

  if (!archivo.is_open()) {
    return;
  }

  while (!archivo.eof()) {
    string line;
    getline(archivo, line);
    string primeraPalabra = line.substr(0, line.find(" "));
    // Ignora la cabecera de los partidos
    // No hay que registrar informacion acerca de qué partidos se jugaron
    if (line.empty()) {
      continue;
    }
    if (primeraPalabra.compare("Partido") == 0) {
      getline(archivo, line);
      continue;
    } else {
      extraerEntradaJornada(jugadores, n_jugadores, line);
    }
  }

  archivo.close();
}

/*#########################
Operaciones sobre arreglos
#########################*/

/*#####################
        Menu
#####################*/
class Menu {
private:
  Equipo equipos[nmax];
  int n_equipos = 0;

  Jugador jugadores[nmax];
  int n_jugadores = 0;

  Director directores[nmax];
  int n_directores = 0;

  void imprimirTitulo(string titulo, bool menu) {
    cout << endl;
    if (mostrar_menus) {
      cout << "----------";
      if (menu) {
        cout << "Menu ";
      }
      cout << titulo;
      cout << "----------" << endl;
    }
  }

public:
  Menu() {
    leerEntrada(equipos, n_equipos, jugadores, n_jugadores, directores,
                n_directores);
  }

  void AgregarEquipo() {
    cin.ignore();
    string nombre;
    getline(cin, nombre);
    equipos[n_equipos].inicializar(nombre);
    n_equipos++;
  }

  void ImprimirEquipos(bool enumerados) {
    for (int i = 0; i < n_equipos; i++) {
      if (enumerados)
        cout << i + 1 << ") ";
      equipos[i].print();
    }
  }

  void ModificarEquipo() {
    imprimirTitulo("Modificar Equipo", false);
    ImprimirEquipos(true);
    int opt = 0;
    cin >> opt;
    if (opt - 1 >= n_equipos || opt - 1 < 0) {
      cout << "Respuesta invalida." << endl;
      return;
    }
    int idx = opt - 1;
    cout << "1) Nombre: " << this->equipos[idx].getNombre() << endl;
    cout << "2) Volver" << endl;

    cin >> opt;
    if (opt == 1) {
      cin.ignore();
      string nombre;
      getline(cin, nombre);
      this->equipos[idx].inicializar(nombre);
    }
    this->equipos[idx].print();
  }

  void EleminarEquipo() {
    ImprimirEquipos(true);
    int idx = 0;
    cin >> idx;
    idx = idx - 1;
    if (idx < 0 || idx >= n_equipos) {
      return;
    }
    for (int i = idx; i < n_equipos - 1; i++) {
      Equipo aux = equipos[i];
      equipos[i] = equipos[i + 1];
      equipos[i + 1] = aux;
    }
    n_equipos -= 1;
  }

  void AgregarJugadorAEquipo(int equipoIdx) {
    string nombre;
    string apellido;
    string pos;
    int experiencia;
    cin >> nombre;
    cin >> apellido;
    cin >> pos;
    cin >> experiencia;
    Posicion posicion = evaluarPosicion(pos);

    jugadores[n_jugadores].inicializar(equipos[equipoIdx].getNombre(), nombre,
                                       apellido, posicion, experiencia);
    equipos[equipoIdx].sumarJugador(n_jugadores, jugadores);
    n_jugadores++;
  }

  void ModificarJugador(int equipoIdx) {
    equipos[equipoIdx].imprimirJugadores(this->jugadores, true);
    int jugador = 0;
    cin >> jugador;
    if (jugador - 1 < 0 || jugador - 1 > equipos[equipoIdx].getNJugadores()) {
      return;
    }
    int jugadorIdx = equipos[equipoIdx].getJugadorIdx(jugador);
    int opt = 0;
    cout << "1) Nombre: " << jugadores[jugadorIdx].getNombre() << endl;
    cout << "2) Apellido: " << jugadores[jugadorIdx].getApellido() << endl;
    cout << "3) Posicion: " << jugadores[jugadorIdx].getPosicionStr() << endl;
    cout << "4) Experiencia: " << jugadores[jugadorIdx].getExperiencia()
         << endl;
    cout << "5) Volver: " << jugadores[jugadorIdx].getExperiencia() << endl;

    cin >> opt;
    if(opt == 1){
      string nombre;
      cin >> nombre;
      jugadores[jugadorIdx].setNombre(nombre);
    } else if(opt == 2){
      string apellido;
      cin >> apellido;
      jugadores[jugadorIdx].setApellido(apellido);
    } else if(opt == 3){
      string pos ;
      cin >> pos;
      Posicion posicion = evaluarPosicion(pos);
      jugadores[jugadorIdx].setExperiencia(posicion);
    } else if(opt == 3){
      int experiencia ;
      cin >> experiencia;
      jugadores[jugadorIdx].setExperiencia(experiencia);
    }

  }

  void MenuJugadoresEquipo(int equipoIdx) {
    int opt = 0;
    do {
      if (mostrar_menus) {
        cout << "1. Todos" << endl;
        cout << "2. Agregar" << endl;
        cout << "3. Modificar" << endl;
        cout << "4. Eliminar" << endl;
        cout << "5. Volver" << endl;
      }
      cin >> opt;
      switch (opt) {
      case 1:
        equipos[equipoIdx].imprimirJugadores(this->jugadores, false);
        break;
      case 2:
        AgregarJugadorAEquipo(equipoIdx);
        break;
      case 3:
        ModificarJugador(equipoIdx);
        break;
      case 4:
        break;
      case 5:
        break;
      default:
        cout << "[Error]: Opcion Invalida." << endl;
        break;
      }
    } while (opt != 5);
  }

  void MenuEquipoJugadores() {
    imprimirTitulo("Equipos-Jugadores", true);
    ImprimirEquipos(true);
    int opt = 0;
    cin >> opt;
    if (opt - 1 >= n_equipos || opt - 1 < 0) {
      cout << "Respuesta invalida." << endl;
      return;
    }
    int idx = opt - 1;

    do {
      if (mostrar_menus) {
        cout << "1. Jugadores" << endl;
        cout << "2. Mejores Jugadores" << endl;
        cout << "3. Lesionados" << endl;
        cout << "4. Los nuevos" << endl;
        cout << "5. Volver" << endl;
      }
      cin >> opt;
      switch (opt) {
      case 1:
        MenuJugadoresEquipo(idx);
        break;
      case 2:
        equipos[idx].imprimirMejoresJugadores(this->jugadores);
        break;
      case 3:
        equipos[idx].imprimirJugadoresLesionados(this->jugadores);
        break;
      case 4:
        equipos[idx].imprimirJugadoresNuevos(this->jugadores);
        break;
      case 5:
        break;
      default:
        cout << "[Error]: Opcion Invalida." << endl;
        break;
      }
    } while (opt != 5);
  }

  void MenuEquipos() {
    int opt = 0;
    do {
      if (mostrar_menus) {
        imprimirTitulo("Equipos", true);
        cout << "1. Agregar" << endl;
        cout << "2. Modificar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Listar Todos" << endl;
        cout << "5. Volver" << endl;
      }
      cin >> opt;
      switch (opt) {
      case 1:
        imprimirTitulo("Agregar Equipo", false);
        AgregarEquipo();
        break;
      case 2:
        ModificarEquipo();
        break;
      case 3:
        imprimirTitulo("Eliminar Equipo", false);
        EleminarEquipo();
        break;
      case 4:
        MenuEquipoJugadores();
        break;
      case 5:
        break;
      default:
        cout << "[Error]: Opcion Invalida." << endl;
        break;
      }
    } while (opt != 5);
  }

  void Principal() {
    int opt = 0;
    do {
      if (mostrar_menus) {
        cout << "----------Menu Principal----------" << endl;
        cout << "1. Equipos" << endl;
        cout << "2. Jugadores" << endl;
        cout << "3. Directores Tecnicos" << endl;
        cout << "4. Partidos" << endl;
        cout << "5. Salir" << endl;
      }
      cin >> opt;
      switch (opt) {
      case 1:
        this->MenuEquipos();
        break;
      case 2:
        //
        break;
      case 3:
        //
        break;
      case 4:
        //
        break;
      case 5:
        cout << "Programa finalizado" << endl;
        break;
      default:
        cout << "[Error]: Opcion Invalida." << endl;
        break;
      }
    } while (opt != 5);
  }
};

/*#####################
        Main
#####################*/
int main() {
  Menu menu;
  menu.Principal();
  return 0;
}
