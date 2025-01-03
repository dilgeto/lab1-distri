#ifndef PARAMETRIZACION_H
#define PARAMETRIZACION_H

double o_x(double t_x, double u_x);
double o_y(double t_y, double u_y);
double calcular_alpha(double t_x, double t_y, double u_x, double u_y);
double calcular_theta(double t_x, double t_y, double u_x, double u_y);
double calcular_beta(double alpha, double delta, double gamma); 
double calcular_delta(double k_x, double k_y, double o_x, double o_y);
double calcular_gamma(double theta, double k_x, double k_y, double o_x, double o_y);
double* calcular_w(double o_x, double o_y, double alpha, double beta, double theta);
double* calcular_v(double o_x, double o_y, double alpha, double beta, double theta);
int comprobacion_elipse(double o_x, double o_y, double theta, double alpha, double beta, int k_x, int k_y);
double calcular_delta_beta(int N, int B);
int discretizacion(double delta_beta, double beta);

#endif /* PARAMETRIZACION_H */
