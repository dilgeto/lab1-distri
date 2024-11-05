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
  struct timespec inicio_monohebra, inicio_hough_monohebra, inicio_paralelo, inicio_hough_paralelo, fin_hough_paralelo;
  double tiempo_hough_monohebra, tiempo_hough_paralelo, tiempo_proceso_monohebra, tiempo_proceso_paralelo;

  // 1 SOLA HEBRA

  clock_gettime(CLOCK_MONOTONIC, &inicio_monohebra);

  // Llamar a leer_fits
  Data* info_img = leer_fits_paralelo(imagen, 1);
  Pixel* pixeles_borde = info_img->pixeles_borde;
  long ancho = info_img->ancho;
  long largo = info_img->largo;
  int largo_arreglo = info_img->largo_arreglo;

  clock_gettime(CLOCK_MONOTONIC, &inicio_hough_monohebra);

  // Algoritmo de Hough con 1 hebra
  Nodo* lista_elipses = votacion_paralela(pixeles_borde, ancho, largo, largo_arreglo, 1, 1, a, r, b);
  free(lista_elipses);

  // PARALELISMO
  
  clock_gettime(CLOCK_MONOTONIC, &inicio_paralelo);
  
  // Llamar a leer_fits
  Data* info_img_p = leer_fits_paralelo(imagen, u);
  Pixel* pixeles_borde_p = info_img->pixeles_borde;
  long ancho_p = info_img_p->ancho;
  long largo_p = info_img_p->largo;
  int largo_arreglo_p = info_img_p->largo_arreglo;

  clock_gettime(CLOCK_MONOTONIC, &inicio_hough_paralelo);

  // Algoritmo de Hough con paralelismo
  Nodo* lista_elipses_p = votacion_paralela(pixeles_borde_p, ancho_p, largo_p, largo_arreglo_p, u, d, a, r, b);
  
  clock_gettime(CLOCK_MONOTONIC, &fin_hough_paralelo);

  while (lista_elipses_p->next != NULL) {
    printf("%f %f %f %f %f\n", lista_elipses_p->elipse->o_x,lista_elipses_p->elipse->o_y,lista_elipses_p->elipse->alpha,(double)lista_elipses_p->elipse->beta_i,lista_elipses_p->elipse->theta);
    lista_elipses_p = lista_elipses_p->next;
  }

  // Calculo de los tiempos
  tiempo_hough_monohebra = (inicio_paralelo.tv_sec - inicio_hough_monohebra.tv_sec) + (inicio_paralelo.tv_nsec - inicio_hough_monohebra.tv_nsec) / 1e9;
  tiempo_hough_paralelo = (fin_hough_paralelo.tv_sec - inicio_hough_paralelo.tv_sec) + (fin_hough_paralelo.tv_nsec - inicio_hough_paralelo.tv_nsec) / 1e9;
  tiempo_proceso_monohebra = (inicio_paralelo.tv_sec - inicio_monohebra.tv_sec) + (inicio_paralelo.tv_nsec - inicio_monohebra.tv_nsec) / 1e9;
  tiempo_proceso_paralelo = (fin_hough_paralelo.tv_sec - inicio_paralelo.tv_sec) + (fin_hough_paralelo.tv_nsec - inicio_paralelo.tv_nsec) / 1e9;

  printf("%f\n", tiempo_proceso_monohebra);
  printf("%f\n", tiempo_proceso_paralelo);
  //printf("%f\%\n", porcion_serial);
  //printf("%f\n", speedup_proceso);
  printf("%f\n", tiempo_hough_monohebra);
  printf("%f\n", tiempo_hough_paralelo);
  //printf("%f\n", speedup_hough);

  return 0;
}
