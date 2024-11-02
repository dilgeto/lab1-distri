#include <stdlib.h>
#include <omp.h>
#include "parametrizacion.h"
#include "nodo.h"

Nodo* votacion(Pixel* pixeles_borde, long ancho, long largo, int largo) {
  Nodo* new_elipses = inicializar_lista();
  // Para cada t
  for (int t = 0 ; t < largo ; i++) {
    // Para cada u
    for (int u = 0 ; u < largo ; j++) {
      if (u == t) {
        continue;
      }
      int* voto = (int*) calloc(largo, sizeof(int));

      // Se calculan los parámetros
      double oX, oY, alpha, theta;
      oX = o_x(pixeles_borde[t]->x, pixeles_borde[u]->x);
      oY = o_y(pixeles_borde[t]->y, pixeles_borde[u]->y);
      alpha = alpha(pixeles_borde[t]->x, pixeles_borde[t]->y, pixeles_borde[u]->x, pixeles_borde[u]->y);
      theta = alpha(pixeles_borde[t]->x, pixeles_borde[t]->y, pixeles_borde[u]->x, pixeles_borde[u]->y);

      // Para cada k
      for (int k = 0 ; k < largo ; k++) {
        if (k == t || k == u) {
          continue;
        }
        // Se calcula Delta y Gamma
        double delta = delta(pixeles_borde[k]->x, pixeles_borde[k]->y, oX, oY);
        double gamma = gammaCal(theta, pixeles_borde[k]->x, pixeles_borde[k]->y, oX, oY);

        // Se calcula beta y discretiza
        double beta = beta(alpha, delta, gamma);
        double beta_discreto = discretizacion();

        // Se realiza la votación
        voto[beta_discreto]++;

        // Procedimiento


      }


    }
  }
}

// Implementación del algoritmo de Hough con paralelismo
Nodo* votacion_paralela(Pixel* pixeles_borde, long ancho, long largo, int largo,int hebras_1, int hebras_2) {
  int t, u, k;
  Nodo* new_elipses = inicializar_lista();
  omp_set_nested(1);
  for (t = 0 ; t < largo ; t++) {
    #pragma omp parallel num_threads(hebras_1) private(u)
    {
      #pragma omp for
        for (int u = 0 ; u < largo ; j++) {
          if (u == t) {
            continue;
          }
          int* voto = (int*) calloc(largo, sizeof(int));

          // Se calculan los parámetros
          double oX, oY, alpha, theta;
          oX = o_x(pixeles_borde[t]->x, pixeles_borde[u]->x);
          oY = o_y(pixeles_borde[t]->y, pixeles_borde[u]->y);
          alpha = alpha(pixeles_borde[t]->x, pixeles_borde[t]->y, pixeles_borde[u]->x, pixeles_borde[u]->y);
          theta = alpha(pixeles_borde[t]->x, pixeles_borde[t]->y, pixeles_borde[u]->x, pixeles_borde[u]->y);

          #pragma omp parallel num_threads(hebras_2) private(k)
          {
            #pragma omp for
              for (int k = 0 ; k < largo ; k++) {
                if (k == t || k == u) {
                   continue;
                }
                // Se calcula Delta y Gamma
                double delta = delta(pixeles_borde[k]->x, pixeles_borde[k]->y, oX, oY);
                double gamma = gammaCal(theta, pixeles_borde[k]->x, pixeles_borde[k]->y, oX, oY);

                // Se calcula beta y discretiza
                double beta = beta(alpha, delta, gamma);
                double beta_discreto = discretizacion();
              }
          }
        }
    }
  }
}
