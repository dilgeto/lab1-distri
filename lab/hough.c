#include <stdlib.h>
#include <omp.h>
#include "parametrizacion.h"
#include "nodo.h"

// TODO: Decidir si se guardará en un arreglo o una lista
int votacion(int** elipse, int largo) {
  Nodo* new_elipses = inicializar_lista();

  // TODO: Verificar si cambiar el orden afecta la elipse (creo que sí)
  // Para cada t
  for (int t = 0 ; t < largo ; i++) {
    // Para cada u
    for (int u = 0 ; u < largo ; j++) {
      int* voto = (int*) calloc(largo, sizeof(int));

      // Se calculan los parámetros
      double oX, oY, alpha, theta;
      oX = o_x(elipse[t][0], elipse[u][0]);
      oY = o_y(elipse[t][1], elipse[u][1]);
      alpha = alpha(elipse[t][o], elipse[t][1], elipse[u][0], elipse[u][1]);
      theta = alpha(elipse[t][o], elipse[t][1], elipse[u][0], elipse[u][1]);

      // Para cada k
      for (int k = 0 ; k < largo ; k++) {
        if (k == t || k == u) {
          continue;
        }
        // Se calcula Delta y Gamma
        double delta = delta(elipse[k][0], elipse[k][1], oX, oY);
        double gamma = gammaCal(theta, elipse[k][0], elipse[k][1], oX, oY);

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

// TODO: Implementar paralelismo
Elipse** votacion_paralela(int** elipse, int largo) {
  int t, u, k;
  omp_set_nested(1);
  #pragma omp parallel num_threads(4)
  {
    #pragma omp for
    {
      for (t = 0 ; t < largo ; t++) {
      }
    }
  }
}
