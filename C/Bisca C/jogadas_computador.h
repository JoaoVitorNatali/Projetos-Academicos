#ifndef JOGADAS_COMPUTADOR_H
#define JOGADAS_COMPUTADOR_H

#include "structs.h"
#include "jogadas_computador.c"

int retornarBooleano(struct Baralho *auxiliar, char *carta);

int encontrarNipe(struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, char *carta);

int maiorCarta(char *carta1, char *carta2, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, int nipe_corte);

int somarCarta(char *carta, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas);

int maisInutil(struct Baralho *mao, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, int nipe_corte);

void encarteComputer(struct Baralho *mao, char *carta, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, struct Baralho *buffer, int nipe_corte);

void jogadaComputer(struct Baralho *mao, struct Baralho *paus, struct Baralho *espada, struct Baralho *ouro, struct Baralho *copas, struct Baralho *buffer, int nipe_corte);

#endif // jogadas_computador_INCLUDED