#ifndef BARAJA_H
#define BARAJA_H

#define DECK_SIZE 52
#define RANKS 13
#define SUITS 4
#define MAX_HAND 12

struct Carta {
    char rank[3];   
    char suit[12];  
    int value;      
};

void inicializarBaraja();
void mezclarBaraja();
struct Carta repartirCarta();
int cartasRestantes();

#endif
