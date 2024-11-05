#ifndef HOUGH_H
#define HOUGH_H
#include "nodo.h"
#include "lectura.h"

Nodo* votacion_paralela(Pixel* pixeles_borde, long ancho, long largo_img, int largo,int hebras_1, int hebras_2, double min_alpha, double porcentaje, int betas);

#endif /* HOUGH_H */
