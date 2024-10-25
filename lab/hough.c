#include <stdlib.h>
#include "parametrizacion.h"

// TODO: Implementar paralelismo
int votacion(int** elipse, int largo) {
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
        double gamma = gammaCal(theta, elipse[][], elipse[][], elipse[][], elipse[][]);
        // Se calcula beta y discretiza
        // TODO: Incluir el cálculo de Delta
        double beta = beta(alpha, delta, gamma);
        double beta_discreto = discretizacion();
      }
    }
  }
}
