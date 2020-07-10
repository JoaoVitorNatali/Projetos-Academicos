#ifndef structs_INCLUDED
#define structs_INCLUDED


struct Baralho{
    char carta[15];
};


struct Baralho copas[10] = {"dois-copas", "tres-copas", "quatro-copas","cinco-copas","seis-copas","dama-copas","valete-copas","reis-copas","sete-copas","As-copas"};
struct Baralho ouro[10] = {"dois-ouro", "tres-ouro", "quatro-ouro","cinco-ouro","seis-ouro","dama-ouro","valete-ouro","reis-ouro","sete-ouro","As-ouro"};
struct Baralho espada[10] = {"dois-espada", "tres-espada", "quatro-espada","cinco-espada","seis-espada","dama-espada","valete-espada","reis-espada","sete-espada","As-espada"};
struct Baralho paus[10] = {"dois-paus", "tres-paus", "quatro-paus","cinco-paus","seis-paus","dama-paus","valete-paus","reis-paus","sete-paus","As-paus"};
struct Baralho baralho[40] = {"dois-copas", "tres-copas", "quatro-copas","cinco-copas","seis-copas","sete-copas","dama-copas","valete-copas","reis-copas","As-copas", "dois-ouro", "tres-ouro", "quatro-ouro","cinco-ouro","seis-ouro","sete-ouro","dama-ouro","valete-ouro","reis-ouro","As-ouro", "dois-espada", "tres-espada", "quatro-espada","cinco-espada","seis-espada","sete-espada","dama-espada","valete-espada","reis-espada","As-espada", "dois-paus", "tres-paus", "quatro-paus","cinco-paus","seis-paus","sete-paus","dama-paus","valete-paus","reis-paus","As-paus"};



#endif // structs_INCLUDED