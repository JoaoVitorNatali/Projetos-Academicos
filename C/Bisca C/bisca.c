#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jogadas_computador.h"
#include "structs.h"


void reorganizar(struct Baralho *baralho, int posi, int *tam){
	int i;
	struct Baralho aux;
	for(i = posi; i < *tam; i++){
		baralho[i] = baralho[i+1];
	}
	(*tam)--;
}

void cortar(struct Baralho *baralho, int *tam, char *corte){
	int aux;
	aux = rand()%(*tam);
	strcpy(corte, baralho[aux].carta);
	reorganizar(baralho, aux, *&tam);
}

void distribuir(struct Baralho *baralho, struct Baralho *mao, int *tam, char *corte){
    int var;
    char carta[15];
    if((*tam)== 0){ //se acabar as cartas, da o corte pra pessoa
    	strcpy(carta, corte);
    	strcpy(corte, "");
    }
    else{
    	var = (rand()%(*tam));
    	strcpy(carta, baralho[var].carta);
    	reorganizar(baralho, var, &*tam);
    }
    
    //colocar a carta no meio da mao da pessoa
    int i;
    for(i = 0; i< 3; i++){
        if((strcmp(mao[i].carta, "")) == 0){
            strcpy(mao[i].carta, carta);
            break;
        }
    }
}

void printarMao(struct Baralho *mao){
    int i;
    printf("\nSuas cartas: \n");
    for(i = 0; i< 3; i++){
        printf("\n\t%d- %s", (i+1), mao[i].carta);
    }
    printf("\n");
}

void printarBuffer(struct Baralho *buffer){
	int i;
	printf("\n###############################");
	printf("\n\tCARTAS NA MESA: ");
	for(i = 0; i<2; i++){
		printf("\n\t- %s", buffer[i].carta);
	}
	printf("\n###############################\n");
}

int verifCarta(struct Baralho *mao, char *carta){
	int i;
	for(i = 0; i< 3; i++){
		if( (strcmp(mao[i].carta, carta)) == 0 ){
			return i;
		}
	}
	return -1;
}

void jogadaPlayer(struct Baralho *mao, struct Baralho *buffer){
	int i, validar;
	char carta[15];

	printarMao(mao);
	do{
		printf("\nDigite qual carta jogar: ");
		scanf(" %15[^\n]s", &*carta);
		validar = verifCarta(mao, carta);
		if(validar == -1) printf("\nEssa carta não está na sua mão, digite novamente: ");
	}while(validar == -1);

	//tirar aquela carta da mão
	strcpy(mao[validar].carta, "");

	for(i = 0; i< 2; i++){
		if(strcmp(buffer[i].carta, "") == 0){
			strcpy(buffer[i].carta, carta);
			break;
		}
	}

}



int main()
{
    srand(time(NULL));
    
    int tam = 40; //tamanho do baralho, talkey
    
    //inicializar a mao da galera---//
    struct Baralho computador[3] = {"", "", ""};
    struct Baralho player1[3] = {"", "", ""};
    
    struct Baralho cartasPlayer[40]; //deixei caso futuramente eu use para visualizar as cartas conquistadas
    int tam_player = 0; //variavel para saber o tamanho do vetor do meu baralho
    int total_player = 0; //variavel para contar a pontuação

    struct Baralho cartasComputer[40]; //deixei caso futuramente eu use para visualizar as cartas conquistadas
    int tam_computer = 0;
    int total_computer = 0;
    
    struct Baralho cartasBuffer[2] = {"", ""}; //isso é para saber as cartas que estão na mesa, talkey

    //função para definir o corte
    char corte[15]; //guarda a carta do corte
    int nipe_corte; //guarda o numero correspondente ao nipe
    cortar(baralho, &tam, corte);
    nipe_corte = encontrarNipe(paus, espada, ouro, copas, corte);

    //distribuir aleatoriamente as 3 primeiras cartas
    int i;
    for(i = 0; i < 3; i++){
        distribuir(baralho, computador, &tam, corte);
        distribuir(baralho, player1, &tam, corte);
    }
           
    //sortear quem começa
    int sequencia;
    sequencia = rand()%2;

    //função para as jogadas  (definir quem matou a carta, quem começa, somar os pontos, etc)

    int pc_ganhou = 0; //essas duas é para saber quem foi o ultimo a matar a carta
    int player_ganhou = 0;
    int jogadas_totais = 20; //isso é para rodar o laço 20 vezes, que é o número máximo de jogadas
    char aux_corte[15];
    strcpy(aux_corte, corte);
    do{

    	
    	player_ganhou = 0;
    	pc_ganhou = 0;

    	printf("\nO corte é %s\n\n", aux_corte);
    	int aux;
    	if(sequencia == 1){
    		jogadaPlayer(player1, cartasBuffer);
    		encarteComputer(computador, cartasBuffer[0].carta, paus, espada, ouro, copas, cartasBuffer, nipe_corte);
    		printarBuffer(cartasBuffer);
    		aux = maiorCarta(cartasBuffer[0].carta, cartasBuffer[1].carta, paus, espada, ouro, copas, nipe_corte);
    		if(aux == 1){ //carta do player ganhou
    			player_ganhou = 1;
    		}
    		else{ //carta do pc ganhou
    			pc_ganhou = 1;
    		}
    	}

    	else{
    		jogadaComputer(computador, paus, espada, ouro, copas, cartasBuffer,  nipe_corte); //lembrar de atualizar a função
    		printarBuffer(cartasBuffer);
    		jogadaPlayer(player1, cartasBuffer);
    		aux = maiorCarta(cartasBuffer[0].carta, cartasBuffer[1].carta, paus, espada, ouro, copas, nipe_corte);
    		if(aux == 1){ //carta do pc ganhou
    			pc_ganhou = 1;    			
    		}
    		else{ //carta do player ganhou
    			player_ganhou = 1;
    		}  		
    	}
    	if(pc_ganhou == 1){
    		sequencia = 0;
    		//guardar as cartas no vetor do pc:
    		cartasComputer[tam_computer] = cartasBuffer[0];
    		tam_computer ++;
    		cartasComputer[tam_computer] = cartasBuffer[1];
    		tam_computer ++;
    		//somar os pontos do pc:
    		total_computer += somarCarta(cartasBuffer[0].carta,paus, espada, ouro, copas);
    		total_computer += somarCarta(cartasBuffer[1].carta,paus, espada, ouro, copas);
    		distribuir(baralho, computador, &tam, corte);
    		distribuir(baralho, player1, &tam, corte);
     	}
     	else{
     		sequencia = 1;
     		//guardar cartas no vetor do player:
    		cartasPlayer[tam_player] = cartasBuffer[0];
    		tam_player ++;
    		cartasPlayer[tam_player] = cartasBuffer[1];
    		tam_player ++;
    		//somar os pontos do player:
    		total_player += somarCarta(cartasBuffer[0].carta,paus, espada, ouro, copas);
    		total_player += somarCarta(cartasBuffer[1].carta,paus, espada, ouro, copas);
        	distribuir(baralho, player1, &tam, corte);
    		distribuir(baralho, computador, &tam, corte);
     	}
     	
     	strcpy(cartasBuffer[0].carta, "");
     	strcpy(cartasBuffer[1].carta, "");
     	
     	printf("\n\n###########");
     	if(pc_ganhou == 1) printf(" COMPUTADOR GANHOU A ULTIMA MÃO ");
    	else if(player_ganhou == 1) printf(" VOCÊ GANHOU A ULTIMA MÃO ");
    	printf("###########\n");
    	jogadas_totais --;
    }while(jogadas_totais > 0);

    printf("\nSua pontuação: %d", total_player);
    printf("\nPontuação do pc: %d", total_computer);
    
    
    
    return 0; //final do programa
}
