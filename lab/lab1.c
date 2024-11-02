#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "parametrizacion.h"
#include "lectura.h"

int main(int argc, char *argv[]) {
  int opt;
  char *imagen = NULL;
  double alpha = 0.0;
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
        a = strtod(optarg);
        break;
      case 'r':
        r = strod(optarg);
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

  } else if (alpha == 0.0) {
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

  // TODO: Discretización espacio parámetros (algo)
  
  // TODO: Algoritmo de Hough 
  Nodo* votacion_paralela(info_img->pixeles_borde, info_img->ancho, info_img->largo, info_img->largo_arreglo, u, d)
  return 0;
}
