#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define pi 3.14

/* Declaração da estrutura dos pixels */
typedef struct
{
  unsigned char Red;
  unsigned char Green;
  unsigned char Blue;

}pixel;

pixel ** Aloca(pixel ** RGB, int alt, int larg);

int *** Aloca2(int *** RGB4, int alt, int larg, int prof);

void scan(FILE * arquivo, pixel ** RGB, pixel **RGB5, int alt, int larg);

void escrita(FILE * arquivo, pixel ** RGB, int alt, int larg, int max);

void Cinza(FILE *arquivo,pixel ** RGB, int alt, int larg, int max);

void gauss(FILE * arquivo, pixel ** RGB, pixel ** RGB2, int alt, int larg);

void sobel(FILE * arquivo, pixel ** RGB2, pixel ** RGB3, int alt, int larg);

void hough(FILE * arquivo, pixel ** RGB3, int *** RGB4, int alt, int larg, int rmin, int rmax);

void circundar(FILE * arquivo, int *** RGB4, pixel ** RGB3, pixel ** RGB5, int alt, int larg, int rmin, int rmax);

void liberar(pixel ** RGB);

void liberar2(int *** RGB);

void conta(FILE *diagnostico, pixel **RGB, int largura, int altura);
