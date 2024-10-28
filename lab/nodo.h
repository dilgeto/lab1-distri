typedef struct {
  Elipse* elipse;
  Nodo* next;
}Nodo;

typedef struct {
  double beta;
  int total_votos;
  Voto* next;
}Voto;

Nodo* inicializar_lista();
Nodo* crear_nodo(Elipse* elipse);
Nodo* agregar_cabeza(Nodo* lista, Elipse* new_elipse);
