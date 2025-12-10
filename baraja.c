#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "baraja.h"

static struct Carta deck[DECK_SIZE];
static int top = 0;

static const char *suits[SUITS] = {"Corazones", "Diamantes", "Treboles", "Espadas"};
static const char *ranks[RANKS] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

void inicializarBaraja() {
    int i = 0;
    for (int s = 0; s < SUITS; s++) {
        for (int r = 0; r < RANKS; r++) {
        
            strcpy(deck[i].rank, ranks[r]);
            
            strcpy(deck[i].suit, suits[s]);
        
            if (r >= 10) deck[i].value = 10;
            else if (r == 0) deck[i].value = 11;
            else deck[i].value = r + 1;
            i++;
        }
    }
    top = 0;
   
    srand((unsigned) time(NULL));
}

void mezclarBaraja() {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Carta tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
    top = 0;
}

struct Carta repartirCarta() {
    if (top >= DECK_SIZE) {
       
        inicializarBaraja();
        mezclarBaraja();
    }
    return deck[top++];
}

int cartasRestantes() {
    return DECK_SIZE - top;
}
