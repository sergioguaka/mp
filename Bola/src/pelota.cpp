#include "pelota.h"
#include "definiciones.h"
#include "miniwin.h"
using namespace miniwin;

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>

float Pelota::aleatorio(float tope) {
  return (rand() % (int)(tope) + 1);
}

Pelota::Pelota() {
  x = aleatorio(MIN_X);
  y = aleatorio(MIN_Y);
  dx = aleatorio(100);
  dy = aleatorio(100);
  radio = UMBRAL/2;
  c = PColor::ROJO;
}

Pelota::Pelota(float x, float y) {
  this->x = x;
  this->y = y;
  dx = 1.0;
  dy = 1.0;
  radio = 10.0;
  c = PColor::ROJO;
}

Pelota::Pelota(float x, float y, float dx, float dy, float radio, PColor c) {
  this->x = x;
  this->y = y;
  this->dx = dx;
  this->dy = dy;
  this->radio = radio;
  this->c = c;
}

float Pelota::distancia(const Pelota& otra)const {
  float deltaX = getX() - otra.getX();
  float deltaY = getY() - otra.getY();

  return (sqrt(deltaX*deltaX + deltaY*deltaY));
}

bool Pelota::colisionado(const Pelota& otra)const {
  return (distancia(otra) < UMBRAL);
}

void Pelota::mover() {
  const float FACTOR = 0.97;
  x += dx;
  y += dy;
  if (x > vancho() - radio) {
    dx = -dx * FACTOR;
    x = vancho() - radio;
  } else if (x < radio) {
    dx = -dx * FACTOR;
    x = radio;
  } else if (y > valto() - radio) {
    dy = -dy * FACTOR;
    y = valto() - radio;
  } else if (y < radio) {
    dy = -dy * FACTOR;
    y = radio;
  }
  dy += 10;
  dx *= 0.97;
}

void Pelota::pintar() {
  color((int) c);
  circulo_lleno(x, y, radio);
}


// Clase pelotas

#include "pelota.h"
#include "pelotas.h"

Pelotas::Pelotas() {
  v = new Pelota[10];
  capacidad = 10;
  util = 10;
}

Pelotas::Pelotas(Pelota *v, int util) {
  this->util = util;
  capacidad = util + 5;
  this->v = reservar(capacidad);
  for (int i = 0; i < util; i++) {
    this->v[i] = v[i];
  }
}

Pelotas::~Pelotas() {
  liberar(v);
}

Pelota* Pelotas::reservar(int n) {
  Pelota* array = nullptr;
  array = new Pelota[n];
  return array;
}

void Pelotas::liberar(Pelota*& array) {
  if (array != nullptr) {
    delete[] array;
  }
}

void Pelotas::borrar(int indice) {
  if (0 <= indice && indice < util) {
    for (int i = indice; i < util-1; i++) {
      v[i] = v[i+1];
    }
  }
}

void Pelotas::aniadir(const Pelota& pelota) {
  if (util < capacidad) {
    v[util] = pelota;
    util++;
  } else {
    Pelota* nuevoV = nullptr;
    nuevoV = reservar(capacidad + 5);
    for (int i = 0; i < util; i++) {
      nuevoV[i] = v[i];
    }
    nuevoV[util] = pelota;
    util++;
    capacidad += 5;
    liberar(v);
    v = nuevoV;
  }
}
