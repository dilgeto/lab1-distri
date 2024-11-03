#ifndef ELIPSE_H
#define ELIPSE_H
typedef struct elipse {
  int o_x;
  int o_y;
  double alpha;
  double theta;
  int beta_i;
}Elipse;

Elipse* crear_elipse(int o_x, int o_y, double alpha, double theta, int beta_i);

#endif /* ELIPSE_H */
