// GRR20190633 Andrews Pinheiro Roman de Araujo
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include "funcoes.h"
#define SIZE 200
#define DATA 10

/* gera o endereço dos arquivos */
char *gera_endereco(char a[],char b[]){
	char str[]="/";
	char *aux;
	aux = strcat(a,str);
	aux = strcat(aux,b);
    return aux;
}

/* carrega os arquivos */
/* e preenche o vetor com os dados encontrados*/
void le_diretorio(dados_arquivos_t vetor[],char c[], int tam){
	
	printf("*********** LENDO ARQUIVOS ***********\n");
	int i = 0;
	DIR *dirstream;
	FILE *arq;
	char *aux;
	char str[SIZE+1];
	copia_string(str,c);

	struct dirent *direntry;
	dirstream = opendir(c);
	if(!dirstream){
		perror("erro ao abrir diretorio");
		exit(1);
	}
	while((direntry = readdir(dirstream))!=NULL){
		if(direntry->d_type==DT_REG){
			copia_string(c,str);
			aux = gera_endereco(c,direntry->d_name);
			arq=fopen(aux, "r");	
			if ( ! arq ){	//se o arquivo n existir
				perror ("Erro ao abrir arquivo") ;
				exit (1) ;
		  	}
			//rewind(arq) serve para o ponteiro de leitura ir para o inicio do arquivo
			nome(arq,vetor,i);//determina o nome da bicicleta
		  	rewind(arq);
		  		
			cadencia_media(arq,vetor,i);//determina a cadencia
		  	rewind(arq);
		  	
		  	distancia(arq,vetor,i);//determina a distancia percorrida
			rewind(arq);
			
		  	velocidade_maxima(arq,vetor,i);//determina a maior velocidade
		  	rewind(arq);	
		  	
		  	velocidade_media(arq,vetor,i);//determina a velocidade media
		  	rewind(arq);
		  	
		  	heart_rate_maximo(arq,vetor,i);//determina o maior heart rate 
		  	rewind(arq);

		  	heart_rate_medio(arq,vetor,i);//determina o heart rate medio
		  	rewind(arq);
		  	
		  	data(arq,vetor,i);//determina a data
		  	rewind(arq);
		  	
		  	subida_acumulada(arq, vetor,i);//determina a subida acumulada
		  	rewind(arq);
		  	
		  	strcpy(vetor[i].log,direntry->d_name);
			i++;		
			fclose(arq);
		}	/* fim if */
	}/* fim while */
	
	ordena_nomes(vetor,tam);//ordena o vetor pelo nome das bicicletas
		
	printf("******* CARREGAMENTO CONCLUIDO *******\n");
	//fclose(arq);
	closedir(dirstream);
	return;
}
/* retorna quantidade de arquivos no diretorio selecionado */
int le_qtd_arquivos(char c[]){
	//printf("INICIANDO contador arq\n");
	int cont = 0;
	DIR *dirstream;
	struct dirent *direntry;
	dirstream = opendir(c);
	if(!dirstream){
		perror("erro ao abrir diretorio");
		exit(1);
	}
	while((direntry = readdir(dirstream))!=NULL){
		if(direntry->d_type==DT_REG){
			cont++;		
		}
	}
	closedir(dirstream);
	return cont;
}
