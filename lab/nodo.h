#ifndef NODO_H
#define NODO_H
#include "elipse.h"

typedef struct nodo {
  Elipse* elipse;
  struct nodo* next;
}Nodo;

typedef struct voto {
  double beta;
  int total_votos;
  struct voto* next;
}Voto;

Nodo* inicializar_lista();
Nodo* crear_nodo(Elipse* elipse);
Nodo* agregar_cabeza(Nodo* lista, Elipse* new_elipse);
#endif /* NODO_H */
