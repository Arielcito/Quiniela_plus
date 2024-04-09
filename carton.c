#include "carton.h"
#include <string.h>
#include <stdio.h>

CartonPtr CrearCarton(int n[], JugadorPtr j,char *d,char *f, int p) {
  Carton* carton = (Carton*)malloc(sizeof(Carton));
    for (int i = 0; i < 8; i++) {
    carton->numeros[i] = n[i];
  }
  carton->jugador = j;

  strcpy(carton->direccion_agencia,d);
  strcpy(carton->fecha_de_emision, f);

  carton->precio = p;

  return carton;
}


// Getter
int GetNumero(CartonPtr carton, int indice) {
  return carton->numeros[indice];
}

char* GetFechaEmision(CartonPtr carton) {
  return carton->fecha_de_emision;
}


char* GetDireccionAgencia(CartonPtr carton) {
  return carton->direccion_agencia;
}

int GetPrecio(CartonPtr carton) {
  return carton->precio;
}

void leerCarton(const Carton *carton) {
  // Imprimir encabezado
  printf("\n**Cart�n de Quiniela**\n");

  // Imprimir n�meros del cart�n
  printf("N�meros: ");
  for (int i = 0; i < 8; i++) {
    printf("%d ", carton->numeros[i]);
  }
  printf("\n");

  // Imprimir fecha de emisi�n
  printf("Fecha de emisi�n: %d\n", carton->fecha_de_emision);

  // Imprimir fecha de juego
  printf("direccion agencia: %d\n", carton->direccion_agencia);

  // Imprimir precio
  printf("Precio: %d\n", carton->precio);
}
