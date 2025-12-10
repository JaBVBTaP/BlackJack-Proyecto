#include <stdio.h>
#include <string.h>
#include "blackjack.h"
#include "baraja.h"
#include "monedas.h"

static void mostrarCarta(const struct Carta *c) {
    printf("%s de %s", c->rank, c->suit);
}

static void mostrarMano(const struct Carta mano[], int count, int ocultarPrimera) {
    for (int i = 0; i < count; i++) {
        if (i == 0 && ocultarPrimera) {
            printf("Carta Oculta, ");
        } else {
            mostrarCarta(&mano[i]);
            if (i < count - 1) printf(", ");
        }
    }
    printf("\n");
}

static int valorMano(const struct Carta mano[], int count) {
    int total = 0;
    int aces = 0;
    for (int i = 0; i < count; i++) {
        total += mano[i].value;
        if (strcmp(mano[i].rank, "A") == 0) aces++;
    }
    while (total > 21 && aces > 0) {
        total -= 10; 
        aces--;
    }
    return total;
}

static int esBlackjack(const struct Carta mano[], int count) {
    if (count != 2) return 0;
    return (valorMano(mano, count) == 21);
}

static void limpiarBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void jugarBlackjack(int *monedas) {
    if (*monedas <= 0) {
        printf("No tienes monedas para jugar. Volvé a intentar si quieres.\n");
        return;
    }

    int apuesta = 0;
    printf("Tienes %d Rupias. Ingresá tu apuesta: ", *monedas);
    if (scanf("%d", &apuesta) != 1) {
        limpiarBufferEntrada();
        printf("Apuesta invalida.\n");
        return;
    }
    limpiarBufferEntrada();

    if (!validarApuesta(*monedas, apuesta)) {
        printf("Apuesta invalida (tiene que ser un número mayor a 0 y menor que tus monedas).\n");
        return;
    }

    if (cartasRestantes() < 20) {
        inicializarBaraja();
        mezclarBaraja();
    }

    struct Carta manoJugador[MAX_HAND];
    struct Carta manoDealer[MAX_HAND];
    int countJ = 0, countD = 0;


    manoJugador[countJ++] = repartirCarta();
    manoDealer[countD++] = repartirCarta();
    manoJugador[countJ++] = repartirCarta();
    manoDealer[countD++] = repartirCarta();

    printf("\nReparto Inicial\n");
    printf("Tu mano: ");
    mostrarMano(manoJugador, countJ, 0);
    printf("Valor tu mano: %d\n", valorMano(manoJugador, countJ));
    printf("Mano del Gran Duende Croupier: ");
    mostrarMano(manoDealer, countD, 1);

  
    int jugadorBlackjack = esBlackjack(manoJugador, countJ);
    int dealerBlackjack = esBlackjack(manoDealer, countD);

    if (jugadorBlackjack || dealerBlackjack) {
    
        printf("\nMano del Croupier: ");
        mostrarMano(manoDealer, countD, 0);
        printf("Valor croupier: %d\n", valorMano(manoDealer, countD));

        if (jugadorBlackjack && !dealerBlackjack) {
            printf("¡Blackjack! Ganaste (paga 3:2).\n");
            actualizarMonedasBlackjack(monedas, apuesta);
        } else if (!jugadorBlackjack && dealerBlackjack) {
            printf("El croupier tiene Blackjack. Perdiste.\n");
            actualizarMonedasPerdedor(monedas, apuesta);
        } else {
            printf("Ambos tienen Blackjack. Empate.\n");
            actualizarMonedasEmpate(monedas, apuesta);
        }
        return;
    }

    int dobleDisponible = 1; 
    int plantado = 0;
    while (!plantado) {
        int valor = valorMano(manoJugador, countJ);
        if (valor > 21) {
            printf("Te pasaste con %d. Perdiste.\n", valor);
            actualizarMonedasPerdedor(monedas, apuesta);
            return;
        }


        printf("\nTu mano: ");
        mostrarMano(manoJugador, countJ, 0);
        printf("Valor: %d\n", valor);
        printf("Mano del Croupier (una oculta): ");
        mostrarMano(manoDealer, countD, 1);

        printf("Elige accion: (1) Hit  (2) Stand");
        if (dobleDisponible && (*monedas >= apuesta * 2)) printf("  (3) Double");
        printf("\nOpcion: ");

        int opcion = 0;
        if (scanf("%d", &opcion) != 1) {
            limpiarBufferEntrada();
            printf("Entrada invalida. Se toma como Stand.\n");
            opcion = 2;
        }
        limpiarBufferEntrada();

        if (opcion == 1) { 
            manoJugador[countJ++] = repartirCarta();
            dobleDisponible = 0;
            continue;
        } else if (opcion == 2) { 
            plantado = 1;
            break;
        } else if (opcion == 3 && dobleDisponible && (*monedas >= apuesta * 2)) {
            
            apuesta *= 2;
            manoJugador[countJ++] = repartirCarta();
            printf("Doblas y recibes una carta extra.\n");
            int v = valorMano(manoJugador, countJ);
            printf("Tu mano ahora: ");
            mostrarMano(manoJugador, countJ, 0);
            printf("Valor: %d\n", v);
            if (v > 21) {
                printf("Te pasaste tras el doble (valor %d). Perdiste.\n", v);
                actualizarMonedasPerdedor(monedas, apuesta);
                return;
            }
            plantado = 1;
            break;
        } else {
            printf("Opcion invalida o no disponible.\n");
            
            dobleDisponible = 0;
        }
    }

    printf("\n Turno del Dealer Mr chicho\n");
    printf("Mano del croupier: ");
    mostrarMano(manoDealer, countD, 0);
    int valorD = valorMano(manoDealer, countD);
    printf("Valor croupier: %d\n", valorD);

    while (valorMano(manoDealer, countD) < 17) {
        manoDealer[countD++] = repartirCarta();
        printf("El croupier toma una carta. Mano ahora: ");
        mostrarMano(manoDealer, countD, 0);
        valorD = valorMano(manoDealer, countD);
        printf("Valor croupier: %d\n", valorD);
    }

    int valorJ = valorMano(manoJugador, countJ);
    valorD = valorMano(manoDealer, countD);


    if (valorD > 21) {
        printf("El croupier se pasó con %d. Ganaste.\n", valorD);
        actualizarMonedasGanador(monedas, apuesta);
    } else if (valorJ > valorD) {
        printf("Tu %d es mayor que %d del croupier. Ganaste.\n", valorJ, valorD);
        actualizarMonedasGanador(monedas, apuesta);
    } else if (valorJ < valorD) {
        printf("Tu %d es menor que %d del croupier. Perdiste.\n", valorJ, valorD);
        actualizarMonedasPerdedor(monedas, apuesta);
    } else {
        printf("Empate con %d. No se mueven las monedas.\n", valorJ);
        actualizarMonedasEmpate(monedas, apuesta);
    }


    printf("Monedas restantes: %d\n", *monedas);
    if (objetivoAlcanzado(*monedas)) {
        printf("\n Felicidades, alcanzaste %d monedas: objetivo cumplido! \n", *monedas);
    }
}
