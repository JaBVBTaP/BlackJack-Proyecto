#ifndef MONEDAS_H
#define MONEDAS_H

enum Dificultad { FACIL=1, MEDIO=2, DIFICIL=3 };

int inicializarMonedas(int dificultad);
int validarApuesta(int monedas, int apuesta);
void actualizarMonedasGanador(int *monedas, int apuesta);
void actualizarMonedasPerdedor(int *monedas, int apuesta);
void actualizarMonedasEmpate(int *monedas, int apuesta);
void actualizarMonedasBlackjack(int *monedas, int apuesta);
int objetivoAlcanzado(int monedas);

#endif
