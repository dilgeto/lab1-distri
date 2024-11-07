#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string.h>
#include "parametrizacion.h"
#include "nodo.h"
#include "lectura.h"
#include "elipse.h"

/*
 * Descripcion: Implementacion de algoritmo Hough con paralelismo de dos niveles
 * Entradas: Arreglo de structs con pixeles borde, ancho y largo imagen, largo arreglo de pixeles, cantidad hebras nivel 1 y 2, alpha minimo, porcentaje minimo de circurferencia
 * y cantidad de intervalos de betas.
 * Salidas: Lista enlazada de elipses selectos.
 */
Nodo* votacion_paralela(Pixel* pixeles_borde, long ancho, long largo_img, int largo, int hebras_1, int hebras_2, double min_alpha, double porcentaje, int betas) {
  int t, u, k;
  Nodo* new_elipses = inicializar_lista();
  omp_set_nested(1);  // Activamos el paralelismo anidado

  #pragma omp parallel num_threads(hebras_1) private(u, k)
  {
    int* voto = (int*) calloc(betas * 2, sizeof(int));  // Asignación de memoria por hebra para evitar conflictos

    #pragma omp for
    for (t = 0; t < largo; t++) {
      for (u = 0; u < largo; u++) {
        if (u == t) continue;

        // Se calculan los parámetros
        double oX = o_x(pixeles_borde[t].x, pixeles_borde[u].x);
        double oY = o_y(pixeles_borde[t].y, pixeles_borde[u].y);
        double alpha = calcular_alpha(pixeles_borde[t].x, pixeles_borde[t].y, pixeles_borde[u].x, pixeles_borde[u].y);
        if (alpha < min_alpha) continue;

        double theta = calcular_theta(pixeles_borde[t].x, pixeles_borde[t].y, pixeles_borde[u].x, pixeles_borde[u].y);

        // Limpiamos el arreglo de votos
        memset(voto, 0, betas * 2 * sizeof(int));

        #pragma omp parallel for num_threads(hebras_2) private(k) shared(voto)
        for (k = 0; k < largo; k++) {
          if (k == t || k == u) continue;

          // Se calcula Delta y Gamma
          double delta = calcular_delta(pixeles_borde[k].x, pixeles_borde[k].y, oX, oY);
          if (delta > alpha) continue;

          double gamma = calcular_gamma(theta, pixeles_borde[k].x, pixeles_borde[k].y, oX, oY);
          double beta = calcular_beta(alpha, delta, gamma);

          if (isnan(beta)) continue;

          // Discretización de beta
          double delta_beta = calcular_delta_beta(largo_img, betas);
          int beta_discreto = discretizacion(delta_beta, beta);

          // Incremento de votos usando `omp atomic`
          #pragma omp atomic
          voto[beta_discreto]++;
        }

        // Comprobación de porcentaje y creación de elipses seleccionados
        double delta_beta_1 = calcular_delta_beta(largo_img, betas);
        for (int i = 1; i < betas; i++) {
          double beta_i = i * delta_beta_1;
          if (voto[i] > porcentaje * (beta_i + alpha) * 3.14) {
            Elipse* elipse = crear_elipse(oX, oY, alpha, theta * (180.0 / 3.1415), beta_i);
            
            #pragma omp critical
            {
              new_elipses = agregar_cabeza(new_elipses, elipse);
            }
          }
        }
      }
    }

    free(voto);  // Liberación de memoria después de cada hebra del primer nivel
  }

  return new_elipses;
}
