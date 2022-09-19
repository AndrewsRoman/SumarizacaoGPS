// GRR20190633 Andrews Pinheiro Roman de Araujo
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define SIZE 200
#define DATA 10
struct dados_arquivos{
	char nome_bike[SIZE+1];	/* nome da bicicleta    */ 
	char data[DATA+1];		/* data do arquivo      */ 
	char log[SIZE+1];		/* log do arquivo       */
	float distancia;		/* distancia percorrida */ 
	float vmedia;			/* velocidade media     */ 
	float vmax;				/* velocidade maxima    */ 
	float hrmedio;			/* heart rate medio     */ 
	float hrmax;			/* heart rate maximo    */ 
	float cad_media;		/* cadencia media       */
	float subida;			/* subida acumulada     */ 
};
typedef struct dados_arquivos dados_arquivos_t;

/* gera o endereço do arquivo b juntando as string a e b*/
/* retorn um ponteiro para a string endereço gerada */
char *gera_endereco(char a[],char b[]);

/* le o conteudo do diretorio*/
void le_diretorio(dados_arquivos_t vetor[], char c[], int tam);

/* conta quantos arquivos há no diretorio*/
int le_qtd_arquivos(char c[]);
