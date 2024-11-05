#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include "parametrizacion.h"
#include "lectura.h"
#include "nodo.h"
#include "hough.h"

int main(int argc, char *argv[]) {
  int opt;
  char *imagen = NULL;
  double a = 0.0;
  double r = 0.0;
  int b = 0;
  int u = 0;
  int d = 0;

  while ((opt = getopt(argc, argv, "i:a:r:b:u:d:")) != -1) {
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

  // Inicio del timer
  clock_t inicio, fin_lectura, fin_procesado, fin;
  double tiempo_lectura, tiempo_procesado, tiempo_total;

  inicio = clock();

  // TODO: Llamar a leer_fits(Faltan detalles dentro de leer_fits)
  Data* info_img = leer_fits(imagen);
  Pixel* pixeles_borde = info_img->pixeles_borde;
  long ancho = info_img->ancho;
  long largo = info_img->largo;
  int largo_arreglo = info_img->largo_arreglo;

  fin_lectura = clock();
  
  // TODO: Algoritmo de Hough 
  printf("prefuncado\n");
  Nodo* lista_elipses = votacion_paralela(pixeles_borde, ancho, largo, largo_arreglo, u, d, a, r, b);
  printf("funcando\n");
  
  fin_procesado = clock();

  while(lista_elipses->next != NULL){
    printf("%f %f %f %d %f\n", lista_elipses->elipse->o_x,lista_elipses->elipse->o_y,lista_elipses->elipse->alpha,lista_elipses->elipse->beta_i,lista_elipses->elipse->theta);
    lista_elipses = lista_elipses->next;
  }

  fin = clock();

  tiempo_lectura = ((double)(fin_lectura - inicio)) / CLOCKS_PER_SEC;
  tiempo_procesado = ((double)(fin_procesado - fin_lectura)) / CLOCKS_PER_SEC;
  tiempo_total = ((double)(fin - inicio)) / CLOCKS_PER_SEC;

  printf("Tiempo lectura:   %f segundos\n", tiempo_lectura);
  printf("Tiempo procesado: %f segundos\n", tiempo_procesado);
  printf("Tiempo total:     %f segundos\n", tiempo_total);

  return 0;
}
