#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 4

typedef char string[50]; //na boa, isso é gambiarra

typedef struct registro{
    int amigos[TAMANHO][TAMANHO];
    string vertices[TAMANHO];
    
}registro;

void zeraVet(int *vet, int tam){
    int i;
    for(i = 0; i< tam; i++){
        vet[i] = 0;
    }
}

void inicializa(registro *d){
    
    //DEFINIÇÃO DOS USUARIOS
    strcpy(d->vertices[0], "JOSIVALDO");
    strcpy(d->vertices[1], "LUCICREIDE");
    strcpy(d->vertices[2], "RODOSVALDO");
    strcpy(d->vertices[3], "KLEBINHO");
    
    //DEIXAR A MATRIZ ZERADA
    int i, j;

    for(i = 0; i < TAMANHO; i++){
        for(j = 0; j<TAMANHO; j++){
            d->amigos[i][j] = 0;
        }
    }
    
    
    //DEFINIÇÃO DE QUEM É AMIGO DE QUEM
    d->amigos[0][1] = 1; //josivaldo amigo de lucicreide...
    d->amigos[0][2] = 1;
    d->amigos[1][0] = 1; //lucicreide..
    d->amigos[1][2] = 1;
    d->amigos[1][3] = 1;
    d->amigos[2][0] = 1;
    d->amigos[2][1] = 1;
    d->amigos[2][3] = 1;
    d->amigos[3][1] = 1;
    d->amigos[3][2] = 1;
    
    
}

int TruAmigo(int pessoa, int pos, registro d){
    return d.amigos[pessoa][pos];
}

void AdoAmigo(int col, registro d, int *vet){
    int lin;
    for(lin = 0; lin<TAMANHO; lin++){
        if(TruAmigo(col, lin, d) == 1){
            // printf("\n%s", d.vertices[lin]);  //codigo para printar o amigo do meu amigo
            vet[lin] += 1; //contabiliza os amigos em comum
        }
    }
}

void amigosComum(int *vet, registro d, int you){
    int i;
    for(i = 0; i< TAMANHO; i++){
        if(vet[i] > 0 && i != you){
            if(TruAmigo(you, i, d) == 0){ //significa que essa pessoa não é minha amiga, então sugere como amiga!
                printf("\n%s possui %d amigos em comum com você!", d.vertices[i], vet[i]);
            }
        }
    }
    
}

void sugerirAmigos(int you, registro *d){
    int col;
    int auxVet[TAMANHO];
    zeraVet(auxVet, TAMANHO);
    for(col = 0; col< TAMANHO; col++){
        if(TruAmigo(you, col, *d) == 1){
            // printf("\nSeu amigo %s tem como amigos: ", d->vertices[col]); //esse é para printar meus amigos, caso queira
            AdoAmigo(col, *d, &auxVet); 
        }
    }
    
    amigosComum(auxVet, *d, you);
}




int main(){
    
    registro usuarios; //registro de usuarios da rede social
    
    inicializa(&usuarios);
    int zero = 0;
    sugerirAmigos(0, &usuarios);
}






//isso ai abaixo representa a matriz de quem é amigo de quem.
//as ligações são bidirecionais 

// [ 
    //                  josivaldo    lucicreide     rodosvaldo   klebinho 
    //     josivaldo      0             1               1           0
        
    //     lucicreide    1              0               1           1
        
    //     rodosvaldo    1              1               0           1 
    
    //     klebinho      0              1               1           0
        
    // ]