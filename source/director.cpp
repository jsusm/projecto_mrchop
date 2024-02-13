#include "../headers/director.h"
#include <iostream>

void Director::inicializar(std::string nombre, std::string apellido, int experiencia) {
  this->nombre = nombre;
  this->apellido = apellido;
  this->experiencia = experiencia;
}

void Director::print(){
  std::cout << "Director: " << std::endl;
  std::cout << "\tnombre: " << this->nombre << std::endl; 
  std::cout << "\tapellido: " << this->apellido << std::endl; 
  std::cout << "\texperiencia: " << this->experiencia << std::endl << std::endl;
}
