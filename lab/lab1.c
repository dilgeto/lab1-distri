#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fitsio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
  /* TODO: Agregar getopt con los parámetros:
   *   - i: imagen fits
   *   - a: valor minimo de alpha
   *   - r: porcentaje aplicado a la circunferencia
   *   - b: el número de betas
   *   - u: el número de hebras para el nivel 1
   *   - d: el número de hebras para el nivel 2
   */
  int opt;
  char *imagen = NULL;
  double alpha = 0.0;
  double r = 0.0;
  int b = 0;
  int u = 0;
  int d = 0;

  while ((opt = getopt(argc, argv, "i:a:r:b:u:d")) != 1) {
    switch (opt) {
      case 'i':
        imagen = optarg;
        break;
      case 'a':
        a = strtod(optarg);
        break;
      case 'r':
        r = strod(optarg);
        break;
      case 'b':
        b = atoi(optarg);
        break;
      case 'u':
        u = atoi(optarg);
        break;
      case 'd':
        d = atoi(optarg);
        break;
    }
  }

  // Casos de excepción
  // TODO: Añadir el caso en que el archivo no exista.
  if (imagen == NULL) {
    printf("Debe incluir una entrada por medio de -i\n");
    return 0;

    //TODO: Verificar si el valor de alpha puede ser 0.
  } else if (alpha == 0.0) {
    printf("Incluya la bandera -a y debe ser mayor que 0.0\n");
    return 0;

    // TODO: Verificar si el porcentaje puede ser 0.
  } else if (r == 0.0) {
    printf("Incluya la bandera -r y debe ser mayor que 0.0\n");
    return 0;

    // TODO: Verificar si beta puede ser 0.
  } else if (b == 0) {
    printf("Incluya la bandera -b y debe ser mayor que 0\n");
    return 0;

  } else if (u == 0) {
    printf("Incluya la bandera -u y debe ser mayor que 0\n");
    return 0;

  } else if (d == 0) {
    printf("Incluya la bandera -d y debe ser mayor que 0\n");
    return 0;
  }
  // TODO: Adaptar a paralelismo en el for
  // TODO: Cambiar ciclo for por discriminacion entre pixeles borde (255) y pixeles no borde(0)
  fitsfile *fptr, *gptr; /* pointer to the FITS file; defined in fitsio.h */
  int status;
  long fpixel=1, naxis = 2, nelements, exposure;
  long naxes[2];
 
  status = 0; /* initialize status before calling fitsio routines */
 
  fits_open_file(&fptr, argv[1], READONLY, &status);
  
  fits_get_img_size(fptr, 2, naxes, &status);
  printf("naxes[0] = %ld\n", naxes[0]);
  double *myimage = (double *) malloc(naxes[0]*naxes[1]*sizeof(double));
 
  printf("size = (%ld, %ld)\n", naxes[1], naxes[0]);

  fits_read_img(fptr, TDOUBLE, fpixel, naxes[0]*naxes[1], NULL, myimage, NULL, &status);
  printf("%.10e \n", myimage[1024*512+128]);
  
  int i, j;
  double max = -1.0e-6;
  for (i=0; i < naxes[0]*naxes[1]; i++)
    if (myimage[i] > max)
      max = myimage[i];
      
  printf("max = %f\n", max);

  // TODO: Creación de lista de puntos bordes (recorrer la imagen para obtener los puntos 255)

  // TODO: Discretización espacio parámetros (algo)
  return 0;
}
