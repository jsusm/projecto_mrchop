#ifndef DIRECTOR_H
#define DIRECTOR_H
#include <string>

class Director {
  std::string nombre;
  std::string apellido;
  int experiencia;
public:
  void inicializar(std::string nombre, std::string apellido, int experiencia);
  void print();
};


#endif // DIRECTOR_H
