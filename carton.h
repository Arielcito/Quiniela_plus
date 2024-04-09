#ifndef CARTON_H
#define CARTON_H

#include "jugador.h"

typedef struct{
    char fecha_de_emision[30];
    int numeros[8];
    char direccion_agencia[100];
    int precio;
    JugadorPtr jugador;
} Carton;

typedef Carton* CartonPtr;

CartonPtr CrearCarton(int n[], JugadorPtr j,char *d,char *f, int p);
void destruirCarton(char d,int p);

int GetNumero(CartonPtr carton, int indice);
char* GetFechaEmision(CartonPtr carton);
char* GetDireccionAgencia(CartonPtr carton);
int GetPrecio(CartonPtr carton);
JugadorPtr GetJugador(CartonPtr carton);
#endif // CARTON_H
