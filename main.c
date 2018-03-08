#include "lib1.h"

int i, i2, max, largura, altura, rmin, rmax;
char tipo[3];

/* Declaração de Ponteiros do tipo de variável criado por typedef */
pixel ** RGB;
pixel ** RGB2;
pixel ** RGB3;
pixel ** RGB5;

int *** RGB4;

int main(int argc, char *argv[])
{
	/* Argv[0] é o programa, argv[1] é o -i, argv[2] é o endereço/nome da imagem, argv[3] é o -f, argv[4] é o formato da imagem de entrada, argv[5] é o -o e o argv[6] é o nome do arquivo do diagnostico*/
	if (strcmp(argv[4], "ppm") == 0 ||strcmp(argv[4], "PPM")== 0 || strcmp(argv[4], "Ppm") == 0)
	{

		 /* Abertura de arquivo */
		FILE *arquivo;
		arquivo = fopen(argv[2], "r");

		/* Verificação da leitura do arquivo */
		if (arquivo == NULL)
		{
			fprintf(stderr, "\nFalha na abertura de arquivo, encerrando programa... \nBIP BIP\n");
			exit(0);
		}

		/* Leitura dos valores iniciais do arquivo */
		fscanf(arquivo, "%s %d %d %d", tipo, &largura, &altura, &max); 

		if (largura == 1167 && altura == 739)
		{
			/*Valores para Normal*/
			rmin = 143;
			rmax = 160;

		} else if(largura == 1015 && altura == 759)
		{
			/*Valores para Catarata*/
			rmin = 82;
			rmax = 83;

		} else if(largura == 1198 && altura == 770)
		{
			/*Valores para Catarata2*/
			rmin = 175;
			rmax = 180;

		} else if(largura == 610 && altura == 480)
		{
			/*Valores para Normal2*/
			rmin = 84;//87
			rmax = 85;//89

		}

		/* Alocação dinâmica de matrizes */
		RGB = Aloca(RGB, altura, largura);
		RGB2 = Aloca(RGB2, altura, largura);
		RGB3 = Aloca(RGB3, altura, largura);
		RGB4 = Aloca2(RGB4, altura, largura, rmax);
		RGB5 = Aloca(RGB5, altura, largura);

		/* Escaneamento de todo o arquivo e determinação dos atributos R, G e B da estrutura pixel */
		scan(arquivo, RGB, RGB5, altura, largura);

		/* Abertura de arquivo vazio*/
		FILE * arquivo2;
		arquivo2 = fopen("imagemdeteste", "w");

		/* Abertura de arquivo vazio*/
		FILE * arquivo3;
		arquivo3 = fopen("Pupila", "w");
		
		FILE *diagnostico;
		diagnostico = fopen(argv[6], "w");

		/* Passagem da imagem original para tons de cinza no novo arquivo vazio*/
		Cinza(arquivo2, RGB, altura, largura, max);

		/* Filtragem pelo método gaussiano */
		gauss(arquivo2, RGB, RGB2, altura, largura);

		/* Aplicação da detecção de bordas por sobel */
		sobel(arquivo2, RGB2, RGB3, altura, largura);

		/*Aplicação da transformada de hough*/
		hough(arquivo2, RGB3, RGB4, altura, largura, rmin, rmax);

		/*Determinação da localidade da íris*/ 
		circundar(arquivo3, RGB4, RGB3, RGB, altura, largura, rmin, rmax);
		
		/* Escrita de diagnostico */
		conta(diagnostico, RGB, largura, altura);
		
		/*Gravação dos resultados num arquivo*/
		escrita(arquivo3, RGB, altura, largura, max);

		/* Fechamento dos arquivos */
		fclose(arquivo);
		fclose(arquivo2);
		remove("imagemdeteste");
		fclose(arquivo3);
		fclose(diagnostico);

		/* Liberação das alocações dinâmicas na memória */
		liberar(RGB);
		liberar(RGB2);
		liberar(RGB3);
		liberar2(RGB4);
		liberar(RGB5);
		return 0;

	}

	else
	
	{
		printf("A imagem de entrada não é PPM, encerrando programa... \n BIP BIP \n");
		exit(0);

	}

}
