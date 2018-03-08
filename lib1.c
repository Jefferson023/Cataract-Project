#include "lib1.h"

/* Função de alocação dinâmica de espaço da memória */
pixel ** Aloca(pixel ** RGB, int alt, int larg)
{
  printf("Alocando matriz do tipo 1... \n");

  RGB = calloc(alt, sizeof(unsigned char*));

  for (int i = 0; i < alt; i++)
  {
    RGB[i] = calloc(larg*3, sizeof(unsigned char));
  }
  /* Fim da alocação */

  /* Verificação da alocação */
  if (RGB == NULL)
  {
    fprintf(stderr, "Falha na Alocação de memória, encerrando o programa... \nBIP BIP\n");
    exit(0);
  }

  return RGB;

}

int *** Aloca2(int *** RGB4, int alt, int larg, int prof)
{
  printf("Alocando matriz do tipo 2... \n");

  RGB4 = calloc(alt, sizeof(unsigned int **));;
  
  for (int i = 0; i < alt; i++)
  {
    RGB4[i] = calloc(larg, sizeof(unsigned int *));
    for (int i2 = 0; i2 < larg; i2++)
    {
        RGB4[i][i2] = calloc(prof, sizeof(unsigned int));

        for (int i3 = 0; i3 < prof; i3++)
        {
          RGB4[i][i2][i3] = 0;         
        }
    }
  }

  if(RGB4 == NULL)
  {
    fprintf(stderr, "Falha na Alocação de memória, encerrando o programa... \nBIP BIP\n");
    exit(0); 
  }

  return RGB4;

}

/* Função de escaneamento dos valores da imagem */
void scan(FILE * arquivo, pixel ** RGB, pixel **RGB5, int alt, int larg)
{
  printf("Escaneando o arquivo... \n");
  for (int i = 0; i < alt; i++)
    {
      for (int i2 = 0; i2 < larg; i2++)
      {
        fscanf(arquivo, "%c%c%c", &RGB[i][i2].Red, &RGB[i][i2].Green, &RGB[i][i2].Blue);
        RGB5[i][i2].Green = RGB[i][i2].Green;
        RGB5[i][i2].Blue = RGB[i][i2].Blue;
        RGB5[i][i2].Red = RGB[i][i2].Red;
      }

    }

}

/*Função de escrita dos valores de uma matriz num arquivo*/
void escrita(FILE * arquivo, pixel ** RGB, int alt, int larg, int max)
{
  printf("Escrevendo no arquivo... \n");
  fprintf(arquivo, "P6\n %d %d\n %d\n", larg, alt, max);

  for (int i = 0; i < alt; i++)
    {
      for (int i2 = 0; i2 < larg; i2++)
      {
        fprintf(arquivo, "%c%c%c", RGB[i][i2].Green, RGB[i][i2].Blue, RGB[i][i2].Red);
      }

    }
}

/* Função de passagem para tons de cinza */
void Cinza(FILE * arquivo, pixel ** RGB, int alt, int larg, int max)
{

  printf("Criando a imagem em tons de cinza... \n");

  fprintf(arquivo, "P6\n %d %d\n %d\n", larg, alt, max);

  for (int i = 0; i < alt; i++)
  {
    for (int i2 = 0; i2 < larg; i2++)
    {
      RGB[i][i2].Green =  RGB[i][i2].Blue*0.11 + RGB[i][i2].Red*0.3 + RGB[i][i2].Green*0.59;
      RGB[i][i2].Blue = RGB[i][i2].Green;
      RGB[i][i2].Red = RGB[i][i2].Green;
    }
  }

}

/* Função de filtragem com gauss */
void gauss(FILE * arquivo, pixel ** RGB, pixel ** RGB2, int alt, int larg)
{

  printf("Aplicando o filtro Gaussiano... \n");

  int filtrogau[5][5] = {{2, 4, 5, 4, 2 }, { 4, 9, 12, 9, 4 }, {5, 12, 15, 12, 5}, {4, 9, 12, 9, 4}, {2, 4, 5, 4, 2}};

  int i, i2, i3 = 0, i4 = 0, k, k1, soma = 0;

  for (i = 0; i < alt; i++)
    {
      for (i2 = 0; i2 < larg; i2++)
      {
        i3 = i-2;
        i4 = i2-2;
        if (i > 1 && i2 > 1 && i2 < larg-3 && i < alt-3)
        {
          for (k = 0; k < 5; k++)
          {
            for (k1 = 0; k1 < 5; k1++)
            {
              soma = soma + filtrogau[k][k1]*RGB[i3][i4].Green;
              i4++; 
            }
            i3++;
            i4 = i2-2;
          }
          RGB2[i][i2].Green = (soma/159);
        } 
        
        RGB2[i][i2].Blue = RGB2[i][i2].Green;
        RGB2[i][i2].Red = RGB2[i][i2].Green;
        i3 = 0;
        i4 = 0;
        soma = 0;
      }
    
    
    }

}

/* Função para aplicação do sobel */
void sobel(FILE * arquivo, pixel ** RGB2, pixel ** RGB3, int alt, int larg)
{

  printf("Aplicando o filtro de Sobel... \n");

  int i, i2, i3, i4, k, k1, soma2 = 0, soma3 = 0;

  int sobelx[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
    
  int sobely[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};


  for (i = 0; i < alt; i++)
    {
      for (i2 = 0; i2 < larg; i2++)
      {
        if (i > 0 && i2 > 0 && i2 < larg-2 && i < alt-2)
        {
          for (k = 0; k < 3; k++)
          {
            i3 = i-1;
                  
            i4 = i2-1;
            for (k1 = 0; k1 <3; k1++)
            {
              soma2 = soma2 + sobelx[k][k1]*RGB2[i3][i4].Green;
              soma3 = soma3 + sobely[k][k1]*RGB2[i3][i4].Green;
              i4++; 
            }
            i3++;
            i4 = i2-1;
          }
          RGB3[i][i2].Green = sqrt((soma2*soma2)+(soma3*soma3));
          
        }else
        {
          RGB3[i][i2].Green = 0;      
        }
        if (RGB3[i][i2].Green < 14)
        {
          RGB3[i][i2].Green = 0;
        }else
        {
          RGB3[i][i2].Green = 255;
        }
        
        RGB3[i][i2].Blue = RGB3[i][i2].Green;
        RGB3[i][i2].Red = RGB3[i][i2].Green;
        soma3 = 0;
        soma2 = 0;
        i3 = 0;
        i4 = 0;

      }
    }

}

/* Função para aplicação da transformada de Hough*/
void hough(FILE * arquivo, pixel ** RGB3, int *** RGB4, int alt, int larg, int rmin, int rmax)
{

  printf("Aplicando a transformada de Hough... \n");

  int a, b, i, i2, r;
  double theta;

  for(i = rmin; i < alt-rmin; i++)
  {
    for(i2 = rmin; i2 < larg-rmin; i2++)
    {
      if(RGB3[i][i2].Green == 255)
      {
        for(r = rmin; r < rmax; r++)
        {
          for(theta = 0; theta <= 360; theta++)
          {
            a = i2 - r * cos((theta * pi)/180);
            b = i - r * sin((theta * pi)/180);
            
            if (a < larg && a > 0 && b < alt && b > 0)
            {
                
              RGB4[b][a][r] += 1;

            }
          }
        }
      }      
    }
  }

}

/*Função para determinar a área da pupila*/
void circundar(FILE * arquivo, int *** RGB4, pixel ** RGB3, pixel ** RGB5, int alt, int larg, int rmin, int rmax)
{

  printf("Circundando a área da Pupila... \n");

  int a, b, i, i2, var1, var2, r, v_a = 0, v_b = 0, v_r = 0, valor = 0;
  double theta;

  RGB4[v_b][v_a][v_r] = 0;

  for(b = 0; b < alt; b++)
  {
    for(a = 0; a < larg; a++)
    {
      if (a < larg && a > 0 && b < alt && b > 0)
      {
        for(r = rmin; r < rmax; r++)
        {
          if(RGB4[b][a][r] > RGB4[v_b][v_a][v_r])
          {
            v_a = a;
            v_b = b;
            v_r = r;
            valor = RGB4[b][a][r];
          }  
        }
      }
    }
  }
  

  for(i = 0; i < alt; i++)
  {
    for (i2 = 0; i2 < larg; i2++)
    {
      for(r = rmin; r < rmax; r++)
      {
        var1 = (i2 - v_a);
        var2 = (i - v_b);
    
        if(r * r >= (var1*var1) + (var2*var2))
        {
            RGB5[i][i2].Green = RGB5[i][i2].Green;
            RGB5[i][i2].Red = RGB5[i][i2].Red;
            RGB5[i][i2].Blue = RGB5[i][i2].Blue;
        } else {
            RGB5[i][i2].Green = 0;
            RGB5[i][i2].Red = 0;
            RGB5[i][i2].Blue = 0;
        }
      }
    }
  }     
}

/* FUnção para contagem de pixels comprometidos */

void conta(FILE *diagnostico, pixel **RGB, int largura, int altura)
{
	printf("Contando pixels de catarata... \n");
	int total = 0, comprometido = 0, porcentagem = 0;
	for (int i = 0; i < altura; i++)
	{
		for (int i2 = 0; i2 < largura; i2++)
		{
			if (RGB[i][i2].Green != 0)
			{
				if(RGB[i][i2].Green > 70)
				{
					comprometido = comprometido + 1;
				}
				total = total + 1;
			}
		
		}
	
	
	}
	
	porcentagem = (100*comprometido)/total;
	if (porcentagem > 60)
	{
		fprintf(diagnostico, "O paciente se encontra com %d%% de sua pupila comprometida por catarata.", porcentagem);
	}else
	{
		fprintf(diagnostico, "O paciente possui catarata leve ou não possui, com %d%% da pupila comprometida", porcentagem);
	}
	

}

/* Função para liberação da alocação dinâmica do espaço de memória de uma matriz do tipo pixel*/
void liberar(pixel ** RGB)
{
  printf("Liberando a memória de uma matriz do tipo 1... \n");
  free(RGB);
  RGB = NULL;

}

/* Função para liberação da alocação dinâmica do espaço de memória de uma matriz do tipo int*/
void liberar2(int *** RGB)
{
  printf("Liberando a memória de uma matriz do tipo 2... \n");
  free(RGB);
  RGB = NULL;

}
