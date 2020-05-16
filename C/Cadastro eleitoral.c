// TEMA 3: SISTEMA ELEITORAL USANDO STRUCTS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define TAM 100 //tamanho do vetor inicial
#define MIN 100 //delimitar a quantidade de caracteres que a pessoa digita
#define MAX 999 //delimitar a quantidade de caracteres que a pessoa digita
#define minTel 10000000 //delimitar o tamanho do numero de telefone
#define maxTel 99999999

struct Pessoa{
	char nome[50];
	char email[50];
	int telefone;
};

struct Candidato{
	struct Pessoa cand;
	int codigo;	
	float votos;
};

//chamar menu
int menu(){
	int op;
	printf("\n\t1 - Inserir candidato\n\t2 - Pesquisar candidato\n\t3 - Alterar\n\t4 - Mais votado\n\t5 - Excluir\n\t6 - Listar\n\t0 - Sair\n\tDigite sua opçao: ");
    scanf("%d", &op);
    return op;
}

void printarCandidato(struct Candidato *cand, int var){
	if(var == -1) printf("Codigo de candidato inexistente\n");
  	else printf("Candidato %s \ncodigo %d \nTelefone: %d \nE-mail: %s\nVotos: %.2f%%\n",cand[var].cand.nome, cand[var].codigo, cand[var].cand.telefone, cand[var].cand.email,cand[var].votos);
}


//verificar se o codigo ja existe----------------------------------------
int verifCodigo(struct Candidato *cand, int cod, int tam){
	int i;
	for(i = 0; i<tam; i++){
		if(cand[i].codigo == cod) return i;
	}
	return -1;
}

int verifEmail(struct Candidato *cand, char *email, int tam){
	int i;
	for(i = 0; i<tam; i++){
		if(strcmp(cand[i].cand.email, email) == 0)return i;
	}
	return -1;
}

int verifNome(struct Candidato *cand, char *nome, int tam){
	int i;
	for(i = 0; i<tam; i++){
		if(strcmp(cand[i].cand.nome, nome) == 0) return i;
	}
	return -1;
}

int verifTelefone(struct Candidato *cand, int tel, int tam){
	int i;
	for(i = 0; i<tam; i++){
		if(cand[i].cand.telefone == tel) return i;
	}
	return -1;
}
//-------------------------------------------------------------------------
//pedir um dado e verificar
int pedirCodigo(){ //eu nÃ£o posso validar se o codigo jÃ¡ existe, pois essa funÃ§Ã£o serÃ¡ usada na pesquisar
	int codigo;
	do{
		printf("Digite o numero do candidato (100-999): ");
		scanf("%d", &codigo);
	}while(codigo <MIN || codigo >MAX);
  	return codigo;
}

void pedirNome(char *nome){
	printf("Nome: ");
	scanf(" %50[^\n]s", &*nome);
}

char pedirEmail(char *email){
	printf("E-mail: ");
	scanf(" %50[^\n]s", &*email);
}

int pedirTelefone(){
	int num;
	do{
		printf("Telefone: ");
		scanf("%d", &num);
		if(num < 8) printf("Numero deve conter 8 digitos\n");
	}while(num < minTel || num > maxTel);
	return num;
}

//inserir candidato
void inserirCand(struct Candidato *cand, int tam){
	int var, cod;
	do{
		cod = pedirCodigo();
		var = verifCodigo(cand, cod, tam);
		if(var != -1) printf("Codigo existente, insira outro\n");
	}while(var != -1);
	cand[tam].codigo = cod;
}

void inserirNome(struct Candidato *cand, int tam){
	char nome[50];
	int var;
	do{
		pedirNome(nome);
		var = verifNome(cand, nome, tam);
		if(var != -1) printf("Nome ja existente, insira outro\n");
	}while(var != -1);
	strcpy(cand[tam].cand.nome, nome);
}

void inserirEmail(struct Candidato *cand, int tam){
	char email[50];
	int var;
	do{	
		pedirEmail(email);
		var = verifEmail(cand, email, tam);
		if(var != -1) printf("E-mail existente, insira outro\n");
	}while(var != -1);
	strcpy(cand[tam].cand.email, email);
}

void inserirTelefone(struct Candidato *cand, int tam){
	int telefone, var;
	do{
		telefone = pedirTelefone();
		var = verifTelefone(cand, telefone, tam);
		if(var != -1) printf("Telefone existente, insira outro\n");
	}while(var != -1);
	cand[tam].cand.telefone = telefone;
}

//--------------------------------------------------------------------------------PORCENTAGEM TOTAL DE VOTOS
float totalVotos(struct Candidato *cand, int tam){ //retorna o valor que falta para dar 100%
	int i;
	float soma = 0;
	for(i = 0; i<tam; i++){
		soma += cand[i].votos;
	}
	return soma;
}

void inserirPercentual(struct Candidato *cand, int tam){
	//primeiro eu preciso saber qual a porcentagem total contabilizada para nï¿½o inserir mais que 100%
	float total, sobra;
	total = totalVotos(cand, tam);
	sobra = 100 - total;
    printf("Digite o percentual: ");
    scanf("%f", &cand[tam].votos);
    
  	while(cand[tam].codigo <0 || cand[tam].votos>sobra){
  		printf("Esse valor nao e permitido pois excede os 100%%\n");
  		printf("Digite outro percentual: ");
  		scanf("%f",&cand[tam].votos);
  	}
	
}


int alterarCand(struct Candidato *cand, int tam){ //para alterar precisa pesquisar pelo candidato
	int var, op;
	var = pesquisar(cand, tam);
	if(var == -1) return 0;
	printarCandidato(cand, var);
	printf("1 - Alterar Codigo\n2 - Alterar porcentagem\n3 - Alterar Nome\n4 - Alterar telefone\n5 - Alterar E-mail\n");
	scanf("%d", &op);
	if (op == 1) {
		cand[var].codigo = 0;
		inserirCand(cand, var);
	}
	else if(op == 2){
		cand[var].votos = 0;
		inserirPercentual(cand, var);	
	}
	else if(op == 3){
		strcpy(cand[var].cand.nome, "");
		inserirNome(cand, var);
	}
	else if(op == 4){
		cand[var].cand.telefone = 0;
		inserirTelefone(cand, var);
	}
	else if (op == 5){
		strcpy(cand[var].cand.email, "");
		inserirEmail(cand, var);
	}
}

int maisVotado(struct Candidato *cand, int tam){
  	int i, varMa = 0;
  	float maior = cand[0].votos;
  	for(i=0; i< tam; i++){
    	if(cand[i].votos > maior){
      		maior = cand[i].votos;
      		varMa = i;
    	}
	}
	return varMa; //retorna o indice do vetor do mais votado
}

void excluir(struct Candidato *cand, int *tam){
	int i;
	int cod = pedirCodigo();
	int var = verifCodigo(cand, cod, *tam);
	if(var == -1) printf("Candidato Inexistente\n");
	else{
		for(i = var; i < *tam; i++){	
			cand[i].votos = cand[i+1].votos;
			cand[i].codigo = cand[i+1].codigo; 
			strcpy(cand[i].cand.nome,cand[i+1].cand.nome);
			strcpy(cand[i].cand.email, cand[i+1].cand.email);
			cand[i].cand.telefone = cand[i+1].cand.telefone;
		}
	}
	(*tam)--;
}

void listar(struct Candidato *cand, int tam){
	int i;
	char nome[50];
	char email[50];
	for(i = 0; i < tam; i++){
		printf("----------------------------------------------------------------------------------------\n");
		printf("Nome: %s\nE-mail: %s\nTelefone: %d\n", cand[i].cand.nome, cand[i].cand.email, cand[i].cand.telefone);
		printf("Código: %d\nVotos: %.2f%%\n", cand[i].codigo, cand[i].votos);
	}
	float resto = 100 - totalVotos(cand, tam);
	printf("----------------------------------------------------------------------------------------\n");
	printf("Votos brancos, nulos ou indecisos: %.1f%%\n",resto);
}








//-------------------------------------------------------------------------------------CHAMAR AS FUNÇOES

void funcao1(struct Candidato *cand, int *tam){ // chamar as funçoes de inserir
	inserirCand(cand, *tam);
	inserirNome(cand, *tam);
	inserirEmail(cand, *tam);
	inserirTelefone(cand, *tam);
	inserirPercentual(cand, *tam);
	*tam += 1;
}

int pesquisar(struct Candidato *cand, int tam){ // pesquisar
	int op, cod, var;
	char nom[50];
	do{
		printf("1 - Pesquisar por codigo\n2 - Pesquisar por Nome\nOpçao: ");
		scanf("%d", &op);
	}while(op != 1 && op != 2);

	if(op == 1){
		cod = pedirCodigo();
		return verifCodigo(cand, cod, tam);
	}
	else{
		pedirNome(nom);
		return verifNome(cand, nom, tam);
	}
}



//funçao para chamar o switch
void chamarSwitch(struct Candidato *candidatos){
	int op, var, tam = 0;
	do{
		op = menu();
	    switch(op){
	    	 case 0:system("CLS");
		  			printf("Good Bye"); 
					break;
//-------------------------------------------------------------------------------- inserir
	    	case 1: funcao1(candidatos, &tam);
        			break;
//-------------------------------------------------------------------------------- pesquisar			
	    	case 2:	var = pesquisar(candidatos, tam);
	    			printarCandidato(candidatos, var);
	    			break;
////-------------------------------------------------------------------------------- alterar	      	
	    	case 3: var = alterarCand(candidatos, tam);
	    			if(var == 0) printf("Candidato nao cadastrado");
        			break;
////-------------------------------------------------------------------------------- mais votado	
	    	case 4: var = maisVotado(candidatos, tam);
	    			printarCandidato(candidatos, var);
	    			break;
//-------------------------------------------------------------------------------- excluir	      
	    	case 5: excluir(candidatos, &tam);
	    			break;
////-------------------------------------------------------------------------------- listar
	    	case 6: listar(candidatos, tam);
					break;
//--------------------------------------------------------------------------------defalult
	    	default:break;
	    }
	  }while(op!=0);
	
}

int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
	
	struct Candidato candidatos[TAM];
	
	
	
	
	chamarSwitch(candidatos);
	
  	return 0;
}
