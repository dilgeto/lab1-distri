#include <stdio.h>
#include <stdlib.h>
#include <fitsio.h>
#include "lectura.h"

Data* leer_fits(char* imagen) {
  fitsfile *fptr, *gptr; /* pointer to the FITS file; defined in fitsio.h */
  int status;
  long fpixel=1, naxis = 2, nelements, exposure;
  long naxes[2];

  status = 0; /* initialize status before calling fitsio routines */
  fits_open_file(&fptr, imagen, READONLY, &status);
  
  fits_get_img_size(fptr, 2, naxes, &status);
  printf("naxes[0] = %ld\n", naxes[0]);
  double *myimage = (double *) malloc(naxes[0]*naxes[1]*sizeof(double));

  printf("size = (%ld, %ld)\n", naxes[1], naxes[0]);

  fits_read_img(fptr, TDOUBLE, fpixel, naxes[0]*naxes[1], NULL, myimage, NULL, &status);
  printf("%.10e \n", myimage[1024*512+128]);
  
  int i,j;
  int count = 0;

  for (i = 0 ; i < naxes[0]*naxes[1] ; i++) {
    if (myimage[i] == 255.0)
      count++;
  }
  
  //  Pixel* pixeles_borde[count];
  Pixel* pixeles_borde = (Pixel*) malloc(sizeof(Pixel) * count);

  int count_1 = 0;

  for (i = 0 ; i < naxes[1] ; i++) {
    for (j = 0 ; j < naxes[0] ; j++) {
      if (myimage[j * naxes[0] + i] == 255.0) {
        pixeles_borde[count_1] = crear_pixel(i,j);
        count_1++;
      }
    }
  }
  Data* info = (Data*) malloc(sizeof(Data));
  info->ancho = naxes[1];
  info->largo = naxes[0];
  info->pixeles_borde = pixeles_borde;
  info->largo_arreglo = count;

  return info;
}
// TODO: Adaptar a paralelismo en el for
Data* leer_fits_paralelo(char* imagen) {
  fitsfile *fptr, *gptr; /* pointer to the FITS file; defined in fitsio.h */
  int status;
  long fpixel=1, naxis = 2, nelements, exposure;
  long naxes[2];

  status = 0; /* initialize status before calling fitsio routines */
  fits_open_file(&fptr, imagen, READONLY, &status);

  fits_get_img_size(fptr, 2, naxes, &status);
  printf("naxes[0] = %ld\n", naxes[0]);
  double *myimage = (double *) malloc(naxes[0]*naxes[1]*sizeof(double));

  printf("size = (%ld, %ld)\n", naxes[1], naxes[0]);

  fits_read_img(fptr, TDOUBLE, fpixel, naxes[0]*naxes[1], NULL, myimage, NULL, &status);
  printf("%.10e \n", myimage[1024*512+128]);

  int i,j;
  int count = 0;

  for (i = 0 ; i < naxes[0]*naxes[1] ; i++) {
    if (myimage[i] == 255.0) {
      count++;
    }
  }
  //Pixel* pixeles_borde[count];
  Pixel* pixeles_borde = (Pixel*) malloc(sizeof(Pixel) * count);
  int count_1 = 0;

  for (i = 0 ; i < naxes[1] ; i++) {
    for (j = 0 ; j < naxes[0] ; j++) {
      if(myimage[j * naxes[0] + i] == 255.0) {
        pixeles_borde[count_1] = crear_pixel(i,j);
        count_1++;
      }
    }
  }
  Data* info = (Data*) malloc(sizeof(Data));
  info->ancho = naxes[1];
  info->largo = naxes[0];
  info->pixeles_borde = pixeles_borde;
  info->largo_arreglo = count;

  return info;
}

Pixel crear_pixel(int x, int y){
    Pixel pix;
    pix.x = x;
    pix.y = y;
    return pix;
}
