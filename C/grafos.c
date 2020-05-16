#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>


void pedirDados(int *vert, int *direct, int *pond){
    printf("Número de vértices: ");
	scanf("%d", &*vert);
	
	printf("Direcionado? Sim(1), Não(0): ");
	scanf("%d", &*direct);
	
	printf("Ponderado? Sim(1), Não(0): ");
	scanf("%d", &*pond);
}


void zerarMatriz(int tam, int matriz[][tam]){
	int i, j;
	for(i = 0; i< tam; i++){
		for(j = 0; j< tam; j++){
			matriz[i][j] = -1;
		}
	}
}


void gravar(FILE *arquivo, int tam, int matriz[][tam]){
	int i, j;
	for(i = 0; i < tam; i++){
		for(j = 0; j<tam; j++){
			// fprintf(arquivo, "%d\t", (matriz[i][j]));
			printf("%d\t", (matriz[i][j]));
		}
		// fprintf(arquivo,"\n");
		printf("\n");
	}
}


void gerarMatriz(int vert, int direct, int pond, int matriz[][vert]){
    int x = 0, y = 0, z;
	z = 1; //coloquei o z como 1, para o caso de nao ser ponderado ele receber esse valor fixo para dizer que tem elemento
	do{
		do{
			scanf("%d", &x);
			if(x != -1)
			{
			scanf("%d", &y);
			if(pond == 1) scanf("%d", &z); //se for ponderado pede o peso
			
			if((x > (vert-1))|| (y > (vert-1)) ){
				printf("Valor inválido, digite novamente: \n");
			}
			}
			
			
		}while((x > (vert-1))|| (y > (vert-1)) );
		
		if(x!=-1){
			matriz[x][y] = z;
			if(direct == 0){ //se for direcionado ele tera 1, então nem entra nesse trecho do código, que é o que diferencia
		        matriz[y][x] = z;
		    }
		}

	}while (x != -1);
}


void gerarDot(int tam, int matriz[][tam], int direct, FILE *arq, int pond){
    int i, j,x = 0;
    char s;
    if(direct == 1){
        s = '>'; //isso é pra decidir se é direcionado
        fprintf(arq, "di");
    }
    else{
    	s = '-';
	} 
    
    fprintf(arq, "graph {\n");
    
    for(i = 0; i< tam; i++){ //declarando variaveis
        fprintf(arq, "\tA%d; \n", i);
    }

    for(i = 0; i< tam; i++){
    	
        for(j = x; j<tam; j++){

            if((matriz[i][j])!= -1 ){
            	fprintf(arq, "\n\tA%d -%c A%d", i,s,j);
            	if(pond == 1) fprintf(arq, "[label = %d]", (matriz[i][j])); //se for ponderado ele coloca o label
            	fprintf(arq, ";");
			}
        }
        if(direct == 0) x++; //se não for direcionado,o x vai incrementar para printar somente a diagonal principal pra cima
    }
    
    fprintf(arq, "\n}");
}


void zerarVetor(int *vetor, int tam){
	int i;
	for(i = 0; i < tam; i++){
		vetor[i] = 0;
	}
}


int regular(int tam, int matriz[][tam]){
	int i, j;
	int auxVet[tam];
	zerarVetor(auxVet, tam);


	for(i = 0; i< tam; i++){
		for(j = 0; j<tam; j++){
			if(matriz[i][j] != -1){
				auxVet[i] += 1;
			}
		}
	}

	int aux = auxVet[0];
	for(i = 1; i< tam; i++){
		if(auxVet[i] != aux) return -1;
	}


	return 1;
}



int conexo(int tam, int matriz[][tam], int direct){
	int i, j, k;
	int auxVet[tam];
	zerarVetor(auxVet, tam);
	int novaVisita;
	int amplitude;
	if(direct == 0) amplitude = 1;
	else amplitude = tam;
	
	for(k = 0; k< amplitude; k++){
	    zerarVetor(auxVet, tam);
	    do{
		    novaVisita = 0;
		    auxVet[k] = 1; //isso pra poder rodar o codigo com pelo menos 1 elemento visitado
		    for(i = 0; i< tam; i++){
			    for(j = 0; j< tam; j++){
			        if(auxVet[i] ==1){ //se foi visitado então eu posso chegar nele, logo eu continuo por ele
			            if((matriz[i][j] != -1)&&( auxVet[j])!= 1 ){ //se na posição da matriz tiver ligação, e não foi visitada ainda, segue o baile
					        auxVet[j] = 1;
					        novaVisita = 1;
				        }
			        }
			    }
		    }
	    }while(novaVisita == 1);
	}
	
    for(i = 0; i< tam; i++){
        if(auxVet[i] == 0){
            return 0;
        }
    }
    
    return 1;
}

int aleatorio(int tam){
	return ((rand()%tam) +1);
}


void remove_adiciona(int tam,int direct, int matriz[][tam], int executar){
	int aresta, i;

	do{
		printf("\nDigite quantas arestas ");
		if(executar == 1)printf("remover: ");
		else printf("adicionar: ");
		scanf("%d", &aresta); 
	}while(aresta >= (tam*tam)); //brow, se não me engano a quantidade máxima de arestas é a quantidade de elementos da matriz, que é tamanho ao quadrado

	//se for pra remover
	if(executar == 1){
		for(i = 0; i< aresta; i++){
			int p1 = aleatorio(tam);
			int p2 = aleatorio(tam);
			if(matriz[p1][p2]!= -1){
				matriz[p1][p2]= -1;
				if(direct != 1){
					matriz[p2][p1] = -1;
				}
			}
			else{
				i--;
			}
		}
	}
	//se for pra adicionar
	int aux = aleatorio(tam);
	if(executar != 1){
		for(i = 0; i< aresta; i++){
			int p1 = aleatorio(tam);
			int p2 = aleatorio(tam);
			if(matriz[p1][p2]== -1){
				matriz[p1][p2]= aux;
				if(direct != 1){
					matriz[p2][p1] = aux;
				}
			}
			else{
				i--;
			}
		}
	}
}


void analise(int tam, int matriz[][tam], int direct){
    if(regular(tam, matriz) == 1){
		printf("\nGráfico regular");
	}	
	else{
		printf("\nGráfico não regular");
	}
	
	if(conexo(tam, matriz, direct) == 1){
	    printf("\nGrafo Conexo");
	}
	else{
	    printf("\nGrafo não conexo");    
	}
}

int main(){
	setlocale(LC_ALL, "");
	srand(time(NULL));

	FILE *arquivo;
    arquivo = fopen("Grafos.dot", "w"); //lembrar de trocar a extensão de saída
	if(arquivo == NULL){
		printf("Tem algo errado");
		exit(1);
	}

	
	int vert, direct, pond;
	pedirDados(&vert, &direct, &pond);
	
	int matriz[vert][vert];
	zerarMatriz(vert, matriz);
	
	gerarMatriz(vert, direct, pond, matriz); //pede os dados da matriz
	analise(vert, matriz, direct); //fala se é conexa e regular
	remove_adiciona(vert, direct, matriz, 1); //remove
	remove_adiciona(vert, direct, matriz, 2); //adiciona
    analise(vert, matriz, direct); //analisa denovo se é ou não conexa e regular



    gerarDot(vert, matriz, direct, arquivo, pond);

	fclose(arquivo);
	return 0;
}
