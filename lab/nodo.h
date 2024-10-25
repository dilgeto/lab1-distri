typedef struct {
  Elipse* elipse;
  Nodo* next;
}Nodo;

Nodo* inicializar_lista();
Nodo* crear_nodo(Elipse* elipse);
Nodo* agregar_cabeza(Nodo* lista, Elipse* new_elipse);
