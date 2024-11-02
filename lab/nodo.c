#include <stdlib.h>
#include "nodo.h"

Nodo* inicializar_lista() {
  Nodo* lista = (Nodo*) malloc(sizeof(Nodo));
  lista->elipse = NULL;
  lista->next = NULL;
  
  return lista;
}

Nodo* crear_nodo(Elipse* elipse) {
  Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
  nodo->elipse = elipse;
  nodo->next = NULL;

  return nodo;
}

Nodo* agregar_cabeza(Nodo* lista, Elipse* new_elipse) {
  Nodo* new_lista = crear_nodo(new_elipse);
  new_lista->next = lista;

  return new_lista;
}
