#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "parametrizacion.h"
#include "nodo.h"
#include "lectura.h"
#include "elipse.h"

/*
Nodo* votacion(Pixel* pixeles_borde, long ancho, long largo_img, int largo, double min_alpha, double porcentaje, int betas) {
  Nodo* new_elipses = inicializar_lista();
  // Para cada t
  for (int t = 0 ; t < largo ; t++) {
    // Para cada u
    for (int u = 0 ; u < largo ; u++) {
      if (u == t) {
        continue;
      }
      int* voto = (int*) calloc(betas, sizeof(int));

      // Se calculan los parámetros
      double oX, oY, alpha, theta;
      oX = o_x(pixeles_borde[t].x, pixeles_borde[u].x);
      oY = o_y(pixeles_borde[t].y, pixeles_borde[u].y);
      alpha = calcular_alpha(pixeles_borde[t].x, pixeles_borde[t].y, pixeles_borde[u].x, pixeles_borde[u].y);
      if(alpha < min_alpha){
        continue;
      }
      theta = calcular_theta(pixeles_borde[t].x, pixeles_borde[t].y, pixeles_borde[u].x, pixeles_borde[u].y);

      // Para cada k
      for (int k = 0 ; k < largo ; k++) {
        if (k == t || k == u) {
          continue;
        }
        // Se calcula Delta y Gamma
        double delta = calcular_delta(pixeles_borde[k].x, pixeles_borde[k].y, oX, oY);
        if(delta > alpha){
          continue;
        }
        double gamma = calcular_gamma(theta, pixeles_borde[k].x, pixeles_borde[k].y, oX, oY);

        // Se calcula beta y discretiza
        double beta = calcular_beta(alpha, delta, gamma);
        double delta_beta = calcular_delta_beta(largo_img, betas);
        int beta_discreto = discretizacion(delta_beta, beta);

        // Se realiza la votación
        voto[beta_discreto]++;

        // Procedimiento


      }
      double delta_beta_1 = calcular_delta_beta(largo_img, betas);
      for(int i = 0 ; i < betas; i++){
        if(voto[i] < porcentaje*largo || voto[i] <= 0){
          continue;
        }
        double beta_i = i * delta_beta_1;
        Elipse* elipse = crear_elipse(oX, oY, alpha, theta, beta_i);
        new_elipses = agregar_cabeza(new_elipses, elipse);
      }

    }
  }
}
*/

// Implementación del algoritmo de Hough con paralelismo
Nodo* votacion_paralela(Pixel* pixeles_borde, long ancho, long largo_img, int largo,int hebras_1, int hebras_2, double min_alpha, double porcentaje, int betas) {
  int t, u, k;
  Nodo* new_elipses = inicializar_lista();
  omp_set_nested(1);
  for (t = 0 ; t < largo ; t++) {
    #pragma omp parallel num_threads(hebras_1) private(u)
    {
      #pragma omp for
        for (u = 0 ; u < largo ; u++) {
          printf("uwu\n");
          if (u == t) {
            continue;
          }
          int* voto = (int*) calloc(betas, sizeof(int));

          // Se calculan los parámetros
          double oX, oY, alpha, theta;
          oX = o_x(pixeles_borde[t].x, pixeles_borde[u].x);
          oY = o_y(pixeles_borde[t].y, pixeles_borde[u].y);
          alpha = calcular_alpha(pixeles_borde[t].x, pixeles_borde[t].y, pixeles_borde[u].x, pixeles_borde[u].y);
          if(alpha < min_alpha){
            continue;
          }
          theta = calcular_theta(pixeles_borde[t].x, pixeles_borde[t].y, pixeles_borde[u].x, pixeles_borde[u].y);

          #pragma omp parallel num_threads(hebras_2) private(k)
          {
            #pragma omp for
              for (k = 0 ; k < largo ; k++) {
                printf("owo\n");
                if (k == t || k == u) {
                   continue;
                }
                // Se calcula Delta y Gamma
                double delta = calcular_delta(pixeles_borde[k].x, pixeles_borde[k].y, oX, oY);
                if(delta > alpha){
                  continue;
                }
                double gamma = calcular_gamma(theta, pixeles_borde[k].x, pixeles_borde[k].y, oX, oY);

                // Se calcula beta y discretiza
                double beta = calcular_beta(alpha, delta, gamma);
                double delta_beta = calcular_delta_beta(largo_img, betas);
                int beta_discreto = discretizacion(delta_beta, beta);
                // Se realiza la votación
                printf("iwi\n");
                //printf("beta_discreto: %d\n", beta_discreto);
                //printf("delta_beta: %f\n", delta_beta);
                printf("theta: %f\n", theta);
                printf("ox: %f, oy: %f\n", oX, oY);
                printf("gamma: %f\n", gamma);
                printf("beta: %f\n", beta);
                voto[beta_discreto]++;
                printf("ewe\n");
              }
            double delta_beta_1 = calcular_delta_beta(largo_img, betas);
            for(int i = 0 ; i < betas ; i++){
              if(voto[i] < porcentaje*largo || voto[i] <= 0){
                continue;
              }
              double beta_i = (i + 1) * delta_beta_1;
              Elipse* elipse = crear_elipse(oX, oY, alpha, theta, beta_i);
              printf("o_x: %f, o_y: %f, alpha: %f, theta: %f, beta_i: %f\n", oX, oY, alpha, theta, beta_i);
              new_elipses = agregar_cabeza(new_elipses, elipse);
            }
          }
        }
    }
  }
  return new_elipses;
}
