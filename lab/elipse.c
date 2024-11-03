#include <stdlib.h>
#include "elipse.h"

Elipse* crear_elipse(double o_x, double o_y, double alpha, double theta, int beta_i) {
  Elipse* elipse = (Elipse*) malloc(sizeof(Elipse));
  elipse->o_x = o_x;
  elipse->o_y = o_y;
  elipse->alpha = alpha;
  elipse->theta = theta;
  elipse->beta_i = beta_i;

  return elipse;
}
