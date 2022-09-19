// GRR20190633 Andrews Pinheiro Roman de Araujo
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include "funcoes.h"
#define SIZE 200
#define DATA 10
/* lista o menu de opções e verifica se a opção selecionada esta correta,
retorna a opção selecionada em caso verdadeiro ou 0 caso contrario */
int menu();
/* switch case para a opção selecionada no menu */
void selecao(int opcao, dados_arquivos_t vetor[], int tam);

int main(int argc, char **argv){
	dados_arquivos_t *vetor;
	char *str=argv[2];
	int tam = le_qtd_arquivos(str);
	/* aloca espaço para vetor de dados_arquivos_t*/
	vetor=cria_vetor(tam);
	/* le o diretorio indicado no argv*/
	le_diretorio(vetor,str,tam);
	int opcao=1;
	while(opcao){
		opcao=menu();
		if(!opcao){
			printf("você escolheu sair do programa\n");
			vetor = destroi_vetor(vetor);
			return 0;
		}
		selecao(opcao,vetor,tam);
		if(opcao!=0)
			ordena_nomes(vetor,tam);
	}
	vetor = destroi_vetor(vetor);
	return 0;
}

int menu(){
	int n;
	printf("*** Insira o numero da opção desejada            ***\n");
	printf("*** 1 - Bicicletas Encontradas                   ***\n");
	printf("*** 2 - Listar atividade de bicicleta especifica ***\n");
	printf("*** 3 - Listar atividades por data               ***\n");
	printf("*** 4 - Listar atividades por distância          ***\n");
	printf("*** 5 - Listar atividades por subida acumulada   ***\n");
	printf("*** 6 - Histograma                               ***\n");
	printf("*** 0 - Encerrar programa                        ***\n");

	scanf("%d", &n);
	getchar();

	// enquanto não for uma das opções acima
	while( (n < 0) || (n > 6) ){
		printf("opção inválida, tente novamente\n");
		printf("*** Insira o numero da opção desejada            ***\n");
		printf("*** 1 - Bicicletas Encontradas                   ***\n");
		printf("*** 2 - Listar atividade de bicicleta especifica ***\n");
		printf("*** 3 - Listar atividades por data               ***\n");
		printf("*** 4 - Listar atividades por distância          ***\n");
		printf("*** 5 - Listar atividades por subida acumulada   ***\n");
		printf("*** 6 - Histograma                               ***\n");
		printf("*** 0 - Encerrar programa                        ***\n");
		scanf("%d", &n);
		getchar();
	}		
	return n;
}

void selecao(int opcao, dados_arquivos_t vetor[], int tam){
	int i=0;
	switch(opcao){
		case 1: 
			lista_bicicletas(vetor,tam);
			printf("\n");
		break;
		
		case 2:
			lista_atividade_bicicleta(vetor,tam);
			printf("\n");		
		break;
		
		case 3:
			ordena_datas(vetor,tam);
			printf("\n");
		break;
		
		case 4:
			ordena_distancia(vetor,tam);
			printf("\n");
		break;
		
		case 5:
			ordena_subida(vetor,0,tam-1);
			imprime_cabecalho();
	
			for(i=0;i<tam;i++){
				imprime_dados(vetor, i);	
			}
			imprime_fim_cabecalho();
			printf("\n");
		break;
		
		case 6:
			histograma(vetor,tam);
			printf("\n");
		break;
	}
}
