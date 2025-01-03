#include <stdio.h>
#include <stdlib.h>
#include <fitsio.h>
#include <omp.h>
#include "lectura.h"

/*
 * Descripcion: Funcion encargada de abrir archivo fits, trasladar su informacion a una variable, extraer los pixeles bordes, introducirlos en un struct
 * y devolver el arreglo de pixeles, con cierto numero de hebras para paralelismo.
 * Entradas: Chars del nombre del archivo con la imagen y un entero que representa la cantidad de hebras a usar.
 * Salidas: Struct Data, el cual almacena internamente: Ancho y largo de la imagen, arreglo de pixeles borde y largo del arreglo de pixeles borde.
 */
Data* leer_fits_paralelo(char* imagen, int hebras_1) {
  fitsfile *fptr, *gptr; /* pointer to the FITS file; defined in fitsio.h */
  int status;
  long fpixel=1, naxis = 2, nelements, exposure;
  long naxes[2];

  status = 0; /* Inicializar estado*/
  fits_open_file(&fptr, imagen, READONLY, &status);

  /*Lectura de imagen*/
  fits_get_img_size(fptr, 2, naxes, &status);
  double *myimage = (double *) malloc(naxes[0]*naxes[1]*sizeof(double));

  fits_read_img(fptr, TDOUBLE, fpixel, naxes[0]*naxes[1], NULL, myimage, NULL, &status);

  int i;
  int count = 0;

  /* Se obtiene cantidad de pixeles borde para largo array*/
  for (i = 0 ; i < naxes[0]*naxes[1] ; i++) {
    if (myimage[i] == 255.0) {
      count++;
    }
  }

  Pixel* pixeles_borde = (Pixel*) malloc(sizeof(Pixel) * count);
  int count_1 = 0;
  /*Ciclo for especializado para obtención de coordenadas y almacenamiento de estas en Struct*/
  #pragma omp parallel for num_threads(hebras_1) shared(count_1)
  for (int i = 0; i < naxes[1]; i++) {
    for (int j = 0; j < naxes[0]; j++) {
      if (myimage[j * naxes[0] + i] == 255.0) {
        #pragma omp critical
        {
          pixeles_borde[count_1] = crear_pixel(i, j);
          count_1++;
        }
      }
    }
  }
  

  /* Se crea y llena de información el struct para retornar todo lo necesario*/
  Data* info = (Data*) malloc(sizeof(Data));
  info->ancho = naxes[1];
  info->largo = naxes[0];
  info->pixeles_borde = pixeles_borde;
  info->largo_arreglo = count;
  fits_close_file(fptr, &status);
  return info;
}
/* Contructor de pixel*/
Pixel crear_pixel(int x, int y){
    Pixel pix;
    pix.x = x;
    pix.y = y;
    return pix;
}
