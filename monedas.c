#include "monedas.h"

int inicializarMonedas(int dificultad) {
    if (dificultad == FACIL) return 1000;
    if (dificultad == MEDIO) return 500;
    return 200; // DIFICIL
}

int validarApuesta(int monedas, int apuesta) {
    if (apuesta <= 0) return 0;
    if (apuesta > monedas) return 0;
    return 1;
}

void actualizarMonedasGanador(int *monedas, int apuesta) {
    *monedas += apuesta;
}

void actualizarMonedasPerdedor(int *monedas, int apuesta) {
    *monedas -= apuesta;
    if (*monedas < 0) *monedas = 0;
}

void actualizarMonedasEmpate(int *monedas, int apuesta) {
 
    (void) monedas; (void) apuesta;
}

void actualizarMonedasBlackjack(int *monedas, int apuesta) {
    int premio = (apuesta * 3) / 2; 
    *monedas += premio;
}

int objetivoAlcanzado(int monedas) {
    return (monedas >= 3500);
}
