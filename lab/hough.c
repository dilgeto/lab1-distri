#include <stdlib.h>
#include <omp.h>
#include "parametrizacion.h"
#include "nodo.h"

// TODO: Decidir si se guardará en un arreglo o una lista
int votacion(int** puntos, int largo) {
  Nodo* new_elipses = inicializar_lista();

  // TODO: Verificar si cambiar el orden afecta la elipse (creo que sí)
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
      oX = o_x(puntos[t][0], puntos[u][0]);
      oY = o_y(puntos[t][1], puntos[u][1]);
      alpha = alpha(puntos[t][o], puntos[t][1], puntos[u][0], puntos[u][1]);
      theta = alpha(puntos[t][o], puntos[t][1], puntos[u][0], puntos[u][1]);

      // Para cada k
      for (int k = 0 ; k < largo ; k++) {
        if (k == t || k == u) {
          continue;
        }
        // Se calcula Delta y Gamma
        double delta = delta(puntos[k][0], puntos[k][1], oX, oY);
        double gamma = gammaCal(theta, puntos[k][0], puntos[k][1], oX, oY);

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
// TODO: Incluir cantidad de hebras para ambos niveles como parámetros
Nodo* votacion_paralela(int** puntos, int largo) {
  int t, u, k;
  Nodo* new_elipses = inicializar_lista();
  omp_set_nested(1);
  for (t = 0 ; t < largo ; t++) {
    #pragma omp parallel num_threads(2) private(u)
    {
      #pragma omp for
        for (u = 0 ; u < largo ; u++) {
          if (u == t) {
            continue;
          }
          int* voto = (int*) calloc(0, sizeof(int));
          
          int oX, oY; double alpha, theta;
          
          // Calculas los parámetros
          oX = o_x(puntos[t][0], puntos[u][0]);
          oY = o_y(puntos[t][1], puntos[u][1]);
          alpha = alpha(puntos[t][o], puntos[t][1], puntos[u][0], puntos[u][1]);
          theta = alpha(puntos[t][o], puntos[t][1], puntos[u][0], puntos[u][1]);

          #pragma omp parallel num_threads(2) private(k)
          {
            #pragma omp for
              for(k = 0 ; k < largo ; k++) {
                if (k == t || k == u) {
                  continue;
                }
                
                // Se calcula Delta y Gamma
                double delta = delta(puntos[k][0], puntos[k][1], oX, oY);
                double gamma = gammaCal(theta, puntos[k][0], puntos[k][1], oX, oY);
                
                // Se calcula beta y discretiza
                double beta = beta(alpha, delta, gamma);
                double beta_discreto = discretizacion();
              }
          }
        }
    }
  }
}
