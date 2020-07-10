#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogadas_computador.h"
#include "structs.h"
#define PAUS 1
#define ESPADA 2
#define OURO 3
#define COPAS 4



int retornarBooleano(struct Baralho *auxiliar, char *carta){
	int i;
	for(i = 0; i< 10; i++){
		if((strcmp((auxiliar[i].carta), carta)) == 0){
			return i;
		}
	}
	return -1;
}


int encontrarNipe(struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, char *carta){

	if(retornarBooleano(paus, carta) != -1){
		return PAUS;
	}
	else if(retornarBooleano(espada, carta) != -1){
		return ESPADA;
	}
	else if(retornarBooleano(ouro, carta) != -1){
		return OURO;
	}
	else if(retornarBooleano(copas, carta) != -1){
		return COPAS;
	}
	else{
		printf("\nAconteceu algo de errado na função que encontra o nipe");
	}
}


//essa função de maior carta terá que retornar 1 ou 0, então se retornar 1 é porque a primeira carta que o infeliz chamar na função é maior que a segunda que ele chamar
int maiorCarta(char *carta1, char *carta2, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, int nipe_corte){

	int var1 = encontrarNipe(paus, espada, ouro, copas, carta1);
	int var2 = encontrarNipe(paus, espada, ouro, copas, carta2);



	int aux = var1;
	if(var1 == var2){ //são do mesmo nipe

		if(aux == 1){
			var1 = retornarBooleano(paus, carta1);
			var2 = retornarBooleano(paus, carta2);
		}
		else if(aux == 2){
			var1 = retornarBooleano(espada, carta1);
			var2 = retornarBooleano(espada, carta2);
		}
		else if(aux == 3){
			var1 = retornarBooleano(ouro, carta1);
			var2 = retornarBooleano(ouro, carta2);
		}
		else if(aux == 4){
			var1 = retornarBooleano(copas, carta1);
			var2 = retornarBooleano(copas, carta2);
		}

		//até ai ta ok, ele ja achou o nipe e agora tenho o indice da carta, agora só retornar o maior indice
		if(var1 > var2) return 1;
		else return 0;
		//traduzindo, se o var1 for maior que o 2, retorna 1 pois a char carta1 será maior, senão retorna 0 pois será menor a carta1 do que  acarta2
	}


	else{ //não são do mesmo nipe
		if(var1 == nipe_corte){
			return 1;
		}
		else if(var2 == nipe_corte){
			return 0;
		}
		else{ //depois de tudo, se nenhuma carta é maior que a outra, logo a maior será a primeira carta jogada na mesa
			return 1;
		}
	}

}


int somarCarta(char *carta, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas){
	int nipe, aux;
	nipe = encontrarNipe(paus, espada, ouro, copas, carta);

	if(nipe == 1) aux = retornarBooleano(paus, carta);
	else if(nipe == 2) aux = retornarBooleano(espada, carta);
	else if(nipe == 3) aux = retornarBooleano(ouro, carta);
	else aux = retornarBooleano(copas, carta);

	int vetor[10] = {0,0,0,0,0,2,3,4,10,11};
	return vetor[aux];

}

// -- farei essa função mais tarde para escolher a carta mais inutil do computador e jogar ela
//essa retorna o indice da carta com menor valor, ou mais inutil da mao da pessoa
int maisInutil(struct Baralho *mao, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, int nipe_corte){
	//bom, para decidir qual carta é mais inútil, eu preciso avaliar algumas condições:
	//Se é corte ou não, se vale ponto, se é bisca
	//se for corte e bisca ao mesmo tempo, melhor não descartar
	//sair somente com o sete de copas de fundo para evitar o réli... coisa que devo acrescentar mais pra frente
	int vetor_aux[3] = {0,0,0};
	int i;
	for(i = 0; i < 3; i++){
		int nipe, valor, soma;
		if((strcmp((mao[i].carta), "")) != 0){

			nipe = encontrarNipe(paus, espada, ouro, copas, mao[i].carta);
			valor = somarCarta(mao[i].carta, paus, espada, ouro, copas);
			if(nipe != nipe_corte){
				valor = valor/2;
				vetor_aux[i] = valor;
			}
			else{
				if(nipe == 1) soma = retornarBooleano(paus, mao[i].carta);
				else if(nipe == 2) soma = retornarBooleano(espada, mao[i].carta);
				else if(nipe == 3) soma = retornarBooleano(ouro, mao[i].carta);
				else soma = retornarBooleano(copas, mao[i].carta);
				soma += 2; //adicionei 2 para igualar o indice à carta... isso acaba aumentando as biscas
				valor = valor + soma;
				vetor_aux[i] = valor;
			}
		}
		else{
			vetor_aux[i] = 999;
		}
	}

	//ok, aqui ele ja deu as minhas cartas alguns valores, que irei avaliar:

	int menor = 99;
	int indice_menor;
	for(i = 0; i< 3; i++){
		if(vetor_aux[i] < menor){
			menor = vetor_aux[i];
			indice_menor = i;
		}
	}

	return indice_menor;
}

void encarteComputer(struct Baralho *mao, char *carta, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, struct Baralho *buffer, int nipe_corte){
	int i, j;
	int aux;

	for(i = 0; i < 3; i++){
		aux = maiorCarta(carta, mao[i].carta, paus, espada, ouro, copas, nipe_corte);
		if (aux == 0){ //carta do pc é maior	

			strcpy(buffer[1].carta, mao[i].carta);
			strcpy(mao[i].carta, "");
			return; //vamo testar esse trambique
		}
	}

	aux = maisInutil(mao, paus, espada, ouro, copas, nipe_corte);
	strcpy(buffer[1].carta, mao[aux].carta);
	strcpy(mao[aux].carta, "");
}


//função que apenas joga aleatorio  uma carta
void jogadaComputer(struct Baralho *mao, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, struct Baralho *buffer, int nipe_corte){
	int aux;

	aux = maisInutil(mao, paus, espada, ouro, copas, nipe_corte);
	strcpy(buffer[0].carta, mao[aux].carta);
	strcpy(mao[aux].carta, "");
	
}