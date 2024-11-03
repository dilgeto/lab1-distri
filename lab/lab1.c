#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "parametrizacion.h"
#include "lectura.h"
#include "nodo.h"

int main(int argc, char *argv[]) {
  int opt;
  char *imagen = NULL;
  double a = 0.0;
  double r = 0.0;
  int b = 0;
  int u = 0;
  int d = 0;

  while ((opt = getopt(argc, argv, "i:a:r:b:u:d")) != 1) {
    switch (opt) {
      case 'i':
        imagen = optarg;
        break;
      case 'a':
        a = strtod(optarg, NULL);
        break;
      case 'r':
        r = strtod(optarg, NULL);
        break;
      case 'b':
        b = atoi(optarg);
        break;
      case 'u':
        u = atoi(optarg);
        break;
      case 'd':
        d = atoi(optarg);
        break;
    }
  }

  // Casos de fallo
  if (imagen == NULL) {
    printf("Debe incluir una entrada por medio de -i\n");
    return 0;

  } else if (a == 0.0) {
    printf("Incluya la bandera -a y debe ser mayor que 0.0\n");
    return 0;

  } else if (r == 0.0) {
    printf("Incluya la bandera -r y debe ser mayor que 0.0\n");
    return 0;

  } else if (b == 0) {
    printf("Incluya la bandera -b y debe ser mayor que 0\n");
    return 0;

  } else if (u == 0) {
    printf("Incluya la bandera -u y debe ser mayor que 0\n");
    return 0;

  } else if (d == 0) {
    printf("Incluya la bandera -d y debe ser mayor que 0\n");
    return 0;
  }
  // TODO: Llamar a leer_fits(Faltan detalles dentro de leer_fits)
  Data* info_img = leer_fits(imagen);
  Pixel* pixeles_borde = info_img->pixeles_borde;
  long ancho = info_img->ancho;
  long largo = info_img->largo;
  int largo_arreglo = info_img->largo_arreglo;
  
  // TODO: Algoritmo de Hough 
  Nodo* lista_elipses = votacion_paralela(pixeles_borde, ancho, largo, largo_arreglo, u, d, a, r, b);
  while(lista_elipses->next != NULL){
    printf("o_x: %d, o_y: %d, alpha: %f, theta: %f, beta_i: %d", lista_elipses->elipse->o_x,lista_elipses->elipse->o_y,lista_elipses->elipse->alpha,lista_elipses->elipse->theta,lista_elipses->elipse->beta_i);
  }

  return 0;
}
