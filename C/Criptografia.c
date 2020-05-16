#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAM 1000

//fun��o para digitar texto
void chamarTexto(char *vet){
	printf("Sua mensagem: \n");
	scanf(" %1000[^\n]s", &*vet);
}
//------------------------------------------------------------------------------------
//fun��o para trocar as letras a @ o 0
void trocarLetra(char *frase){
	int i;
	for(i = 0; frase[i] != '\0'; i++){
		if(frase[i] == '\0') frase[i] = '\0';
    else if(frase[i] == 'o'|| frase[i] == 'O') frase[i] = '0'; 
		else if(frase[i] == '0') frase[i] = 'o';
		else if(frase[i] == 'a' || frase[i] == 'A') frase[i] = '@';
		else if(frase[i] == '@') frase[i] = 'a';
	}
}
//------------------------------------------------------------------------------------

//fun��o para pegar os char em posi��o impar e colocar em outro vetor
void trocarImpar(char *vetInteiro, char *vetImpar){
	int i, a = 0;
	for(i = 0; i < TAM; i++){
		if(i % 2 == 0){	
			vetImpar[a] = vetInteiro[i];
			a++;
		}
	}
}
//------------------------------------------------------------------------------------
//Pegar o vetor na posi��o par, por�m de traz pra frente, e colocar na string pares 
void trocarPar(char *vetInteiro, char *vetPar){
	//primeiro pegar a ultima posi�a
	int tamanho = strlen(vetInteiro) -1;
//	fazer a troca
	int i, a=0, b = 1;
	for(i = tamanho; i>=0; i--){
    if(b%2 == 0){
			vetPar[a] = vetInteiro[i];
			a++;
		}
    b++;
	}
}
//------------------------------------------------------------------------------------
//fun��o para juntar os vetores
void juntarVet(char *impar, char *par, char *novo){
  int i;
  for(i = 0; i<TAM; i++){
    novo[i] = impar[i];
    novo[i+1] = par[i];
  }
}






int main(){
	setlocale(LC_ALL, "Portuguese");
	
	char frase[TAM] = "Problemas Hiper-Interessantes com 0 (zero) e @.";
  printf("frase: %s\n", frase);
	char impares[TAM];
	char pares[TAM];
  char criptografado[TAM];
	
//	chamarTexto(frase);
	trocarLetra(frase);
	trocarImpar(frase, impares);
	trocarPar(frase, pares);
	juntarVet(impares, pares, criptografado);
	
	
	
	printf("1� %s\n", frase);
	printf("2� %s\n", impares);
	printf("3� %s\n", pares);
	printf("Final: %s", criptografado);

	
	
	return 0;
}