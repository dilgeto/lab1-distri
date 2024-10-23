#include <math.h>

double o_x(t_x, u_x) {
  return (t_x + u_x) / 2;
}

double o_y(t_y, u_y) {
  return (t_y + u_y) / 2;
}

double alpha(t_x, t_y, u_x, u_y) {
  double x = pow(u_x - t_x, 2);
  double y = pow(u_y - t_y, 2);
  return sqrt(x + y) / 2;
}

double theta(t_x, t_y, u_x, u_y) {
  double y = u_y - t_y;
  double x = u_x - t_x;
  return atan(y / x);
}
