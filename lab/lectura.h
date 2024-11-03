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
Data* leer_fits_paralelo(char* imagen);
Pixel crear_pixel(int x, int y);
