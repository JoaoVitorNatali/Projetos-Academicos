#include <stdlib.h>
#include <stdio.h>
#define TAM 200

void zeraVetor(int *vet, int tam){
	int i = 0;
	for(i = 0; i < tam; i++){
		vet[i] = 0;
	}
}

void insere(int *vet, int posicao){
	vet[posicao] = 1;
}

void remover(int *vet, int posicao){
	vet[posicao] = 0;
}

int pertence(int *vet, int posicao){
	return vet[posicao];
}

//A está contido em B? 
int estaContido(int *vetA, int *vetB){
	int i;
	for(i = 0; i<TAM; i++){
		if( pertence(vetA, i) && !pertence(vetB, i) ) return 0;
	}
	return 1;
}

int contem(int *vetA, int *vetB){
	return estaContido(vetB, vetA);
}

int contidoPropriamente(int *vetA, int *vetB){	
	return ( estaContido(vetA, vetB) && !contem(vetA, vetB) );
}

int contemPropriamente(int *vetA, int *vetB){
	return contidoPropriamente(vetB, vetA);
}

void uniao(int *vetA, int *vetB, int *vetC){
	int i;
	for(i = 0; i<TAM; i++){
		vetC[i] = (pertence(vetA, i) || pertence(vetB, i));
	}
}

void intercecao(int *vetA, int *vetB, int *vetC){
	int i;
	for(i = 0; i< TAM; i++){
		vetC[i] = (pertence(vetA, i) && pertence(vetB, i));
	}
}

void diferenca(int *vetA, int *vetB, int *vetC){
	int i;
	for(i = 0; i < TAM; i++){
		vetC[i] = ( pertence(vetA, i) && !pertence(vetB, i) );
	}
}

void complemento(int *vetA, int *vetC){
	int i;
	for(i = 0; i< TAM; i++){
		vetC[i] = !pertence(vetA, i);
	}
}


int main(){

	int conjuntoA[TAM];
	int conjuntoB[TAM];
	int conjuntoC[TAM];
	zeraVetor(conjuntoA, TAM);
	zeraVetor(conjuntoB, TAM);
	zeraVetor(conjuntoC, TAM);

	

	return 0;
}