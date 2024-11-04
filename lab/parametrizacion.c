#include <math.h>
#include <stdlib.h>
#include "parametrizacion.h"

double o_x(double t_x, double u_x) {
  return (t_x + u_x) / 2.0;
}

double o_y(double t_y, double u_y) {
  return (t_y + u_y) / 2.0;
}

double calcular_alpha(double t_x, double t_y, double u_x, double u_y) {
  double x = (u_x - t_x) * (u_x - t_x);
  double y = (u_y - t_y) * (u_y - t_y);
  return sqrt(x + y) / 2.0;
}

double calcular_theta(double t_x, double t_y, double u_x, double u_y) {
  double y = u_y - t_y;
  double x = u_x - t_x;
  return atan2(y, x);
}

double calcular_beta(double alpha, double delta, double gamma) {
  double num1, num2, den1, den2, fraccion;
  num1 = (alpha * alpha) * (delta * delta);
  num2 = (alpha * alpha) * (gamma * gamma);
  den1 = alpha * alpha;
  den2 = gamma * gamma;
  fraccion = (num1 - num2) / (den1 - den2);
  return sqrt(fraccion);
}

double calcular_delta(double k_x, double k_y, double o_x, double o_y) {
  double resta_1 = (k_y - o_y) * (k_y - o_y);
  double resta_2 = (k_x - o_x) * (k_x - o_x);
  return sqrt(resta_1 + resta_2);
}

double calcular_gamma(double theta, double k_x, double k_y, double o_x, double o_y) {
  double coef_1 = sin(theta) * (k_y - o_y);
  double coef_2 = cos(theta) * (k_x - o_x);
  return (coef_1 + coef_2);
}

double* calcular_w(double o_x, double o_y, double alpha, double beta, double theta) {
  double w_x = o_x - (cos(abs(theta)) * sqrt(((alpha)*(alpha)) - ((beta)*(beta))));
  double w_y = o_y - (sin(abs(theta)) * sqrt(((alpha)*(alpha)) - ((beta)*(beta))));
  double* resultados = (double*) malloc(sizeof(double) * 2);
  resultados[0] = w_x;
  resultados[1] = w_y;
  return resultados;
}

double* calcular_v(double o_x, double o_y, double alpha, double beta, double theta) {
  double v_x = o_x + (cos(abs(theta)) * sqrt(((alpha)*(alpha)) - ((beta)*(beta))));
  double v_y = o_y + (sin(abs(theta)) * sqrt(((alpha)*(alpha)) - ((beta)*(beta))));
  double* resultados = (double*) malloc(sizeof(double) * 2);
  resultados[0] = v_x;
  resultados[1] = v_y;
  return resultados;
}

int comprobacion_elipse(double o_x, double o_y, double theta, double alpha, double beta, int k_x, int k_y) {
  double* w = calcular_w(o_x, o_y, alpha, beta, theta);
  double* v = calcular_v(o_x, o_y, alpha, beta, theta);
  double largo_w = sqrt((k_y-w[1])*(k_y-w[1])+(k_x-w[0])*(k_x-w[0]));
  double largo_v = sqrt((k_y-v[1])*(k_y-v[1])+(k_x-v[0])*(k_x-v[0]));
  double largo_segmento = largo_w + largo_v;
  if(largo_segmento == 2*alpha){
    return 1;
  }else{
    return 0;
  }
}

double calcular_delta_beta(int N, int B) {
  return (N / (2 * B));
}


int discretizacion(double delta_beta, double beta) {
  int i = floor(beta / delta_beta);
  return i;
}

