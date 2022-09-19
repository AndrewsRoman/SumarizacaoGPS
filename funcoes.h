// GRR20190633 Andrews Pinheiro Roman de Araujo
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "loadFiles.h"
/**/

/* aloca espaço para vetor do tipo dados_arquivos_t */
/* retorna endereço do espaço alocado para o vetor */
dados_arquivos_t *cria_vetor(int tam);

/* libera o espaço alocado para o vetor*/
dados_arquivos_t *destroi_vetor(dados_arquivos_t vetor[]);

/* determina o nome da bicicleta e o coloca no vetor de dados*/
void nome(FILE *arq, dados_arquivos_t vetor[], int n);

/* copia a string a na string b*/
void copia_string(char b[], char a[]);

/* separa a string e converte para float*/
float string_to_float(char str[]);

/* imprime o cabeçalho da tabela resultante*/
void imprime_cabecalho();
/* imprime tracejado do final do cabeçalho */
void imprime_fim_cabecalho();

/* imprime os dados presentes no vetor */
void imprime_dados(dados_arquivos_t vetor[], int i);

/* realiza a troca entre variavais do tipo dados_arquivos_t */
void troca(dados_arquivos_t vetor[], int i, int j);

/* ordena vetor de string pelo nome da bicicleta */
void ordena_nomes(dados_arquivos_t vetor[], int n);

/* Lista todas atividades agrupadas por bicicleta e ordenadas pela data */
void ordena_datas(dados_arquivos_t vetor[], int tam);

/*Lista todas atividades agrupadas por bicicleta e ordenadas pela distância*/
void ordena_distancia(dados_arquivos_t vetor[], int tam);

/* ordena vetor de string pela subida acumulada */
void ordena_subida(dados_arquivos_t vetor[], int inicio, int fim);

/* imprime as atividades da bicicleta selecionada */
void lista_atividade_bicicleta(dados_arquivos_t vetor[], int tam);

/*imprime todas as bicicletas sem repetição */
void lista_bicicletas(dados_arquivos_t vetor[],int tam);

/* histograma da distancia da bicicleta escolhida */
void histograma(dados_arquivos_t vetor[], int tam);

/* preenche a distancia percorrida no vetor de dados em km */
void distancia(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina a subida acumulada */
void subida_acumulada(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina a velocidade maxima em km/h */
void velocidade_maxima(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina a velocidade media em km/h */
void velocidade_media(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina o heart rate maximo em bpm */
void heart_rate_maximo(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina o heart rate medio em bpm */
void heart_rate_medio(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina a cadencia media */
void cadencia_media(FILE *arq, dados_arquivos_t vetor[], int n);

/* determina data do arquivo */
void data(FILE *arq, dados_arquivos_t vetor[],int n);
