#include "jugador.h"
#include <string.h>

JugadorPtr crearJugador(char n[], int d) {
  Jugador* jugador = (Jugador*)malloc(sizeof(Jugador));

  strcpy(jugador->nombre,n);
  jugador->dni = d;
  return jugador;
}

// Getter
char* GetNombre(JugadorPtr jugador) {
  return jugador->nombre;
}

int GetDni(JugadorPtr jugador) {
  return jugador->dni;
}
