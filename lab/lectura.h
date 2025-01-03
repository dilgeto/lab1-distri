#ifndef LECTURA_H
#define LECTURA_H
typedef struct pixel {
  int x;
  int y;
}Pixel;

typedef struct data {
  long ancho;
  long largo;
  int largo_arreglo;
  Pixel* pixeles_borde;
}Data;

Data* leer_fits(char* imagen);
Data* leer_fits_paralelo(char* imagen, int hebras_1);
Pixel crear_pixel(int x, int y);

#endif /* LECTURA_H */ 
