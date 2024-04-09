#ifndef JUGADOR_H
#define JUGADOR_H

typedef struct {
  char nombre[50];
  int dni;
} Jugador;

typedef Jugador* JugadorPtr;

JugadorPtr crearJugador(char n[], int d);
void destruirJugador(JugadorPtr j);

char* GetNombre(JugadorPtr jugador);
int GetDni(JugadorPtr jugador);

void SetNombre(JugadorPtr jugador, char n[]);
void SetDni(JugadorPtr jugador, int d);
#endif // JUGADOR_H
