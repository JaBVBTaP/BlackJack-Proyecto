#include <stdio.h>
#include <stdlib.h>
#include "baraja.h"
#include "blackjack.h"
#include "monedas.h"

static void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    inicializarBaraja();
    mezclarBaraja();

    int monedas = 0;
    int dificultad = 0;
    int opcion = -1;

    printf("  Bienvenido al Casino Beltrán\n");
    printf("Objetivo: Alcanzar 3500 Rupias\n");

    while (dificultad < 1 || dificultad > 3) {
        printf("Elegí la dificultad: (1) Fácil (1000 monedas)  (2) Medio (500)  (3) Difícil (200): ");
        if (scanf("%d", &dificultad) != 1) {
            limpiarBuffer();
            dificultad = 0;
            continue;
        }
        limpiarBuffer();
    }
    monedas = inicializarMonedas(dificultad);
    printf("Comenzás con %d Rupias. ¡Suerte\n", monedas);

    do {
        printf("\n Menú del Casino de Duendes\n");
        printf("1. Jugar Blackjack\n");
        printf("2. Cambiar dificultad (reinicia monedas)\n");
        printf("3. Ver monedas actuales\n");
        printf("0. Salir\n");
        printf("Opción: ");
        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer();
            opcion = -1;
        }
        limpiarBuffer();

        switch (opcion) {
            case 1:
                jugarBlackjack(&monedas);
                break;
            case 2: {
                int nueva;
                printf("Elegí nueva dificultad: (1) Fácil  (2) Medio  (3) Difícil: ");
                if (scanf("%d", &nueva) != 1) {
                    limpiarBuffer();
                    printf("Entrada invalida.\n");
                } else {
                    limpiarBuffer();
                    dificultad = nueva;
                    monedas = inicializarMonedas(dificultad);
                    printf("Dificultad cambiada. Rupias reiniciadas a %d.\n", monedas);
                }
                break;
            }
            case 3:
                printf("Rupias actuales: %d\n", monedas);
                break;
            case 0:
                printf("Gracias por visitar el Casino Beltrán. Gracias por jugar.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

        if (objetivoAlcanzado(monedas)) {
            printf("\nHas alcanzado 3500 o más monedas. ¡Has ganado el juego del Casino.\n");
            break;
        }
        if (monedas <= 0) {
            printf("\nTe quedaste sin monedas. Perdiste.\n");
            break;
        }

    } while (opcion != 0);

    return 0;
}
