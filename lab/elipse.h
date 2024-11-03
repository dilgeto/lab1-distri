#ifndef ELIPSE_H
#define ELIPSE_H
typedef struct elipse {
  double o_x;
  double o_y;
  double alpha;
  double theta;
  int beta_i;
}Elipse;

Elipse* crear_elipse(double o_x, double o_y, double alpha, double theta, int beta_i);

#endif /* ELIPSE_H */
