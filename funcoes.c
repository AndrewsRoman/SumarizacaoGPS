// GRR20190633 Andrews Pinheiro Roman de Araujo
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include "loadFiles.h"
#define SIZE 200 
#define DATA 10
/* aloca memoria para o vetor e retorna o endereço*/
dados_arquivos_t *cria_vetor(int tam){
	dados_arquivos_t *vetor;
	vetor =(dados_arquivos_t *)(malloc(tam * sizeof(dados_arquivos_t)) );
	if(vetor == NULL)
		return NULL;
	return vetor;
}
/* desaloca a memoria do vetor*/
dados_arquivos_t  *destroi_vetor(dados_arquivos_t vetor[]){
	free(vetor);	
	return NULL;
}

void nome(FILE *arq, dados_arquivos_t vetor[], int n){
	/* le a primeira linha do arquivo */
	fscanf(arq,"%[^\n]s", vetor[n].nome_bike);
	int i=0;
	/* determina o nome da bicicleta caracter a caracter*/
	for(; vetor[n].nome_bike[i+6]!='\0';i++){
		vetor[n].nome_bike[i]=vetor[n].nome_bike[i+6];
	}	
	vetor[n].nome_bike[i]='\0';
	return;
}
/* copia string a para a string b*/
void copia_string(char b[], char a[]){
	int i=0;
    while(a[i]!='\0'){
        b[i]=a[i];
        i++;
    }
    b[i]='\0';
}
/* quebra a string passada a cada espaço, adiciona essa string para uma
string auxiliar e converte os dados da string auxiliar para float */
float string_to_float(char str[]){
	char *aux;
	aux = strtok(str,"  ");
	aux = strtok(NULL,"  ");
	return atof(aux);
}
/* cabeçalho */
void imprime_cabecalho(){
	printf("----------------------------------------------------------------------");
	printf("-----------------------------------------------------------\n");
	printf("               Distância    Velocidade Média    Velocidade Máxima    HR Médio    HR Máximo    Cadência Média    Subida Acumulada \n");
	printf("Data           (km)         (km/h)              (km/h)               (bpm)        (bpm)       (rpm)             (m)\n");
}

void imprime_fim_cabecalho(){
	printf("----------------------------------------------------------------------");
	printf("-----------------------------------------------------------\n");
}

/* realiza a impressão dos dados de acordo com o exemplo dado*/
void imprime_dados(dados_arquivos_t vetor[], int i){
	
	printf("%s%10.2f%13.2f%20.2f%19.0f%13.0f%11.0f%23.2f\n",vetor[i].data, vetor[i].distancia, vetor[i].vmedia,vetor[i].vmax,vetor[i].hrmedio, vetor[i].hrmax, vetor[i].cad_media,vetor[i].subida);
	/*a seguinte parte comentada serve para comparar com a saida quando descomentada
	para usar comente o printf acima e descomente a sequencia abaixo*/
	/*
	printf("nome: %s | ", vetor[i].nome_bike);
	printf("%s | ", vetor[i].log);
	printf("cad: %0.0f | ", vetor[i].cad_media);
	printf("hr: %0.0f | ",vetor[i].hrmedio);
	printf("hr_m: %0.0f | ",vetor[i].hrmax);
	printf("s: %0.2f | ",vetor[i].vmedia);
	printf("s_m: %0.2f | ",vetor[i].vmax);
	printf("dist: %0.2f | ",vetor[i].distancia);
	printf("elev: %0.2f | ",vetor[i].subida);
	printf("data: %s\n", vetor[i].data);
	*/
	
	return; 
}
/* realiza a troca de dados entre posições do vetor 
do tipo dados_arquivos_t*/
void troca(dados_arquivos_t vetor[], int i, int j){
	dados_arquivos_t aux;
	/*coloca os dados do vetor na posição i na variavel aux*/
	strcpy(aux.nome_bike,vetor[i].nome_bike);
	strcpy(aux.data,vetor[i].data);
	strcpy(aux.log,vetor[i].log);
	aux.distancia=vetor[i].distancia;
	aux.vmedia=vetor[i].vmedia;
	aux.vmax=vetor[i].vmax;
	aux.hrmedio=vetor[i].hrmedio;
	aux.hrmax=vetor[i].hrmax;
	aux.cad_media=vetor[i].cad_media;
	aux.subida=vetor[i].subida;			
		/* fim da aux*/
	/* coloca os dados do vetor na posição j na posição i do vetor*/
	strcpy(vetor[i].nome_bike,vetor[j].nome_bike);
	strcpy(vetor[i].data,vetor[j].data);
	strcpy(vetor[i].log,vetor[j].log);
	vetor[i].distancia=vetor[j].distancia;
	vetor[i].vmedia=vetor[j].vmedia;
	vetor[i].vmax=vetor[j].vmax;
	vetor[i].hrmedio=vetor[j].hrmedio;
	vetor[i].hrmax=vetor[j].hrmax;
	vetor[i].cad_media=vetor[j].cad_media;
	vetor[i].subida=vetor[j].subida;
		/* fim de i */
	/*coloca os dados da variavel aux na posição j do vetor */
	strcpy(vetor[j].nome_bike,aux.nome_bike);
	strcpy(vetor[j].data,aux.data);
	strcpy(vetor[j].log,aux.log);
	vetor[j].distancia=aux.distancia;
	vetor[j].vmedia=aux.vmedia;
	vetor[j].vmax=aux.vmax;
	vetor[j].hrmedio=aux.hrmedio;
	vetor[j].hrmax=aux.hrmax;
	vetor[j].cad_media=aux.cad_media;
	vetor[j].subida=aux.subida;
	return;
}
/* ordena o vetor alfabeticamente pelo nome das bicicletas*/
void ordena_nomes(dados_arquivos_t vetor[], int tam){
	int i,j,comp;

	for(i=0; i < tam; i++){
		for(j=i+1; j < tam; j++){
			comp = strcmp(vetor[i].nome_bike, vetor[j].nome_bike);
			// se strcmp retornar um valor maior que zero
			// significa que a posição i deve trocar com a posição j
			if(comp > 0)
				troca(vetor,i,j);
		}/* fim for  j*/
	}/* fim for i*/
	return;
}
/* ordena as bicicletas, agrupadas pelo nome, pela data */
void ordena_datas(dados_arquivos_t vetor[], int tam){
	int i,j,comp;
	comp=0;
	for (i=0;i<tam;i++){ 
		j=i+1;
		/* compara o nome das bicicletas, se forem iguais entra no while*/
		while(!(strcmp(vetor[i].nome_bike,vetor[j].nome_bike)) ){
			comp=strcmp(vetor[i].data,vetor[j].data);
			// se strcmp retornar um valor maior que zero
			// significa que a posição i deve trocar com a posição j
			if(comp > 0) 
				troca(vetor,i,j);
			j++;
		}		
	}
	imprime_cabecalho();
	for(i=0;i<tam;i++){
		imprime_dados(vetor, i);	
	}
	imprime_fim_cabecalho();
	return;
}
/* com para os numeros a e b se a for maior retorna 1, 
se b for maior retorna -1, se forem iguais retorna 0*/
int compara_numeros(float a, float b){
	float resultado = a - b;
	if(resultado > 0)
		return 1;
	if(resultado < 0)
		return -1;
	return 0;
}

/* ordena as bicicletas, agrupadas pelo nome, pela distancia */
void ordena_distancia(dados_arquivos_t vetor[], int tam){
	int i,j,comp;
	comp=0;
	for (i=0;i<tam;i++){
		j=i+1;
		/* compara o nome das bicicletas, se forem iguais entra no while*/
		while(!(strcmp(vetor[i].nome_bike,vetor[j].nome_bike)) ){
			// se strcmp retornar um valor maior que zero
			// significa que a posição i deve trocar com a posição j
			comp=compara_numeros(vetor[i].distancia,vetor[j].distancia);
			if(comp > 0)
				troca(vetor,i,j);
			j++;
		}
	}
	imprime_cabecalho();	
	for(i=0;i<tam;i++){
		imprime_dados(vetor, i);	
	}
	imprime_fim_cabecalho();
	return;
}

int particiona(dados_arquivos_t vetor[], int a, int b) {	  
	int i, j;
	i=a;
	j=b;
	while(i<j){	
		while(vetor[i].subida <= vetor[a].subida)		
			i++;
		while(vetor[j].subida > vetor[a].subida)
			j--;
		if (i < j)
			troca(vetor,i,j);
	}
	troca(vetor,j,a);
	return j;
	
} 
/*ordena o vetor pela subida usando quicksort*/
void ordena_subida(dados_arquivos_t vetor[], int inicio, int fim){
	if (inicio < fim){
		int m = particiona(vetor,inicio,fim);
		ordena_subida(vetor,inicio,m-1);
		ordena_subida(vetor,m+1,fim);
		return;
	}
	return;	
}


/* lista todas as bicicletas */
void lista_bicicletas(dados_arquivos_t vetor[],int tam){
	int i,j;
	char aux[SIZE+1];
	strcpy(aux,vetor[0].nome_bike);//aux = nome da primeira bike do vetor
	j=1;
	printf("%s\n",vetor[0].nome_bike);
	for(i=0;i<tam;i++){
		/*compara aux com o nome da bicicleta se forem diferentes 
		atribui um novo nome para aux e imprime*/
		if((strcmp(aux,vetor[i].nome_bike))	){
			strcpy(aux,vetor[i].nome_bike);
			j++;
			printf("%s\n",vetor[i].nome_bike);
		}
	}/*fim for*/
}

/* lista todas as atividades da bicicleta escolhida*/
void lista_atividade_bicicleta(dados_arquivos_t vetor[], int tam){	
	char str[SIZE+1];
	int i,cont;
	cont=0;
	/*mostra as opções de bicicletas*/
	lista_bicicletas(vetor,tam);
	
	printf("Escolha uma das bicicletas acima:\n");	
	fgets(str, SIZE+1, stdin);
	str[strcspn(str,"\n")]='\0'; /*troca o \n por \0 na string*/
	
	/*verifica se o nome selecionado existe no vetor de bicicletas
		se existir sai do for*/
	for(i=0;i<tam;i++){
		if(!(strcmp(str,vetor[i].nome_bike))){
			cont++;
			break;
		}
	}
	if(!cont){
		printf("bicicleta não encontrada\n");
		return;
	}
	imprime_cabecalho();
	
	for(i=0;i<tam;i++){
		/*se a bicicleta escolhida for a mesma do vetor, imprime sua atividade*/
		if(!(strcmp(str,vetor[i].nome_bike))){
			imprime_dados(vetor, i);
			cont++;
		}
	}
	imprime_fim_cabecalho();
	return ;	
}

int particiona_float(float vetor[], int a, int b) {	  
	int i, j;
	float aux;
	i=a;
	j=b;
	while(i<j){	
		while(vetor[i] <= vetor[a])		
			i++;
		while(vetor[j] > vetor[a])
			j--;
		if (i < j){
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j]=aux;
		}
	}
	aux = vetor[j];
	vetor[j] = vetor[a];
	vetor[a]=aux;
	return j;
	
} 
/*ordena o vetor usando quicksort*/
void quicksort(float vetor[], int inicio, int fim){
	if (inicio < fim){
		int m = particiona_float(vetor,inicio,fim);
		quicksort(vetor,inicio,m-1);
		quicksort(vetor,m+1,fim);
		return;
	}
	return;	
}

void histograma(dados_arquivos_t vetor[], int tam){
	char str[SIZE+1];
	int i,j;
	float distancias[SIZE+1];
	float menor, maior, dezena;
	
	lista_bicicletas(vetor,tam);
	printf("insira uma bicicleta:\n");	
	fgets(str, SIZE+1, stdin);
	str[strcspn(str,"\n")]='\0';
	j=0;
	/*atribui todas as distancias do vetor, para o vetor de distancias*/
	for(i=0;i<tam;i++){
		if(!(strcmp(str,vetor[i].nome_bike))){
			distancias[j]=vetor[i].distancia;
			j++;
		}	
	}
	/* se j for 0 significa que não encontrou nenhuma bicicleta com aquele nome*/
	if(!j){
		printf("bicicleta não encontrada\n");
		return;
	}
	/* ordena vetor de distancias*/
	quicksort(distancias,0,j-1);
	menor=distancias[0];
	maior=distancias[j-1];
	/* determina a menor dezena mais proxima da menor distancia*/
	i=0;
	while(menor > i){
		if(i+10>menor)
			break;
		i+=10;
	}
	dezena=menor-i;
	dezena=menor - dezena;
	/* imprime o histograma na tela */
	
	i=0;
	while(dezena<=maior){
		printf("%3.0f-%3.0f	  | ", dezena, dezena+10);
		while (distancias[i] < dezena+10){
			printf("*");
			i++;

			if( (distancias[i]>=dezena+10)||(i==j))
				break;
		}
		if(i==j){
			printf("\n");
			break;
		}
		dezena=dezena+10;
		printf("\n");
	}
	printf("            0123456789#123456789#123456789#\n");
	printf("Distancia |          Quantidade\n");
	return;
}
/* determina a distancia percorrida da bicicleta*/
void distancia(FILE *arq, dados_arquivos_t vetor[],int n){

	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	float distance;
	verificador = fgets(c,SIZE, arq);
	/*enquanto não acabar o arquivo*/
	while(verificador != NULL){
		/* se os primeiros 7 caracteres da linha forem iguais a distance */
		if(!(strncmp(c,"distance",7))){	
			copia_string(str,c);
		}
		verificador = fgets(c,SIZE, arq);
	}
	/* separa a string e retorna o valor float encontrado*/
	distance = string_to_float(str);
	vetor[n].distancia=distance/1000;//converte para km
	return;
}

/*determina a soma das subidas da bicicleta*/
void subida_acumulada(FILE *arq, dados_arquivos_t vetor[], int n){
	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	double antes, depois,total;
	int cont =0;
	antes = 0;
	depois = 0;
	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		if(!(strncmp(c,"altitude",8))){
			/* se for a primeira ocorrencia de altitude*/
			if(!cont){
				copia_string(str,c);
				antes = string_to_float(str);
				cont++;
			}
			else{
				copia_string(str,c);
				depois = string_to_float(str);
				if(depois > antes)
					total = total + (depois - antes);			
				antes = depois;
			}	
		}
		verificador=fgets(c,SIZE,arq);
	}
	vetor[n].subida=total;
	
	return;
}
void velocidade_maxima(FILE *arq, dados_arquivos_t vetor[], int n){
	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	float depois;
	float velocidade=0;
	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		if(!(strncmp(c,"speed",5))){
			copia_string(str,c);
			depois = string_to_float(str);

			if(depois > velocidade)
				velocidade = depois;
		}
		verificador=fgets(c,SIZE,arq);
	}
	/* velocidade em m/s *3.6 = velocidade em km/hr*/
	vetor[n].vmax=velocidade*3.6;
	return;
}

void velocidade_media(FILE *arq, dados_arquivos_t vetor[], int n){
	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	float velocidade;
	float total=0;
	int cont=0;

	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		if( !(strncmp(c,"speed",5)) ){
			copia_string(str,c);
			velocidade = string_to_float(str);
			/*se a velocidade não for 0
			somo um no contador de segundos*/	
			if(velocidade){
				total=velocidade+total;
				cont++;
			}
		}
		verificador=fgets(c,SIZE,arq);
	}	
	/* o resultado deve ser em km/hr, por isso esta *3.6*/
	vetor[n].vmedia=(total/cont)*3.6;
	return;
}
void heart_rate_maximo(FILE *arq, dados_arquivos_t vetor[], int n){
	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	float depois;
	float batimentos=0;
	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		if(!(strncmp(c,"heart_rate",10))){
			copia_string(str,c);
			depois = string_to_float(str);
			/*compara o batimento anterior com o proximo
				se o proximo for maior, guarda em batimentos*/
			if(depois > batimentos)
				batimentos = depois;
		}
		verificador=fgets(c,SIZE,arq);
	}
	vetor[n].hrmax=batimentos;

	return; 
}

void heart_rate_medio(FILE *arq, dados_arquivos_t vetor[], int n){
	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	float total=0;
	float aux;
	int cont=0;
	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		aux=0;
		if(!(strncmp(c,"heart_rate",10))){
			copia_string(str,c);
			aux = string_to_float(str);
			
			if(aux > 0){
				total = total + aux;
				cont++;
			}
		}
		verificador=fgets(c,SIZE,arq);
	}
	if(!cont){
		vetor[n].hrmedio=0;
		return;
	}

	vetor[n].hrmedio=total/cont;
	return; 
}

void cadencia_media(FILE *arq, dados_arquivos_t vetor[], int n){
	char c[SIZE+1], str[SIZE+1];
	char *verificador;
	float total=0;
	float aux;
	int cont=0;

	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		aux=0;
		if(!(strncmp(c,"cadence",7))){
			copia_string(str,c);
			aux = string_to_float(str);
		
			if(aux > 0){
				total = total + aux;
				cont++;
			}
		}/*fim if */
		verificador=fgets(c,SIZE,arq);
	}/* fim while */
	
	if(cont==0){
		vetor[n].cad_media=0; 
		return;
	}
	/*calcula a media e adiciona na posição n do vetor*/
	vetor[n].cad_media=total/cont;
	return; 
}

void data(FILE *arq, dados_arquivos_t vetor[],int n){
	char c[SIZE+1], str[SIZE+1], aux[DATA+1];
	char *verificador;
	char *ptr;

	verificador=fgets(c,SIZE,arq);
	while(verificador != NULL){
		if(!(strncmp(c,"timestamp",9))){
			copia_string(str,c);
			//printf("str: %s",str);
			/* gera a data yyyy-mm-dd*/
			ptr = strtok(str,"  ");
			ptr = strtok(NULL,"  ");
			
			/* pega somente o ano */
			ptr= strtok(ptr,"-");
			strcpy(aux,ptr);
			strcat(aux,"/");
			/* pega somente o mes*/	
			ptr= strtok(NULL,"-");
			strcat(aux,ptr);
			strcat(aux,"/");
			/*pega somente o dia */
			ptr= strtok(NULL,"-");
			strcat(aux,ptr);
			//printf("aux: %s\n",aux);
			/* break pois o primeiro timestamp ja nos da a data*/
			break;
		}
		verificador=fgets(c,SIZE,arq);
	}
	copia_string(vetor[n].data,aux);
	
	return ;
}
