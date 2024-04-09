/*El programa debe contener como m�nimo:
Comprar cart�n autom�tico
Comprar carton seleccionando los 8 n�meros
Jugar, creaci�n de los 20 n�meros del partido
Verificar cart�n, saber si has ganado y cu�nto has ganado
Imprimir el cart�n, marcando de alguna forma los n�meros que salieron, tambi�n guardarlo en un archivo.
Generar un bucle que te diga cuantas veces tenes que jugar con el mismo cart�n para llegar a ganar con 8 aciertos
*/
#include <stdio.h>
#include <stdlib.h>
#include "jugador.h"
#include <stdbool.h>
#include "carton.h"

CartonPtr ComprarCartonAutomatico(JugadorPtr jugador);
CartonPtr ComprarCartonSeleccionando(JugadorPtr jugador);
JugadorPtr RegistrarJugador(jugador);
void RealizarSorteo(int numerosSorteo[]);
void generarNumerosAleatorios(int vector[], int tamanio);
void VerificarCarton(int numerosSorteo[20],CartonPtr carton);

int main()
{

  int numerosSorteo[20];
  JugadorPtr jugador = RegistrarJugador();
    CartonPtr carton;
  while (true) {
    int opcion;

    printf("\n**Bienvenido a la Quiniela Plus**\n\n");
    printf("%s , %d\n",jugador->nombre,jugador->dni);
    printf("**Opciones:**\n");
    printf("1. Jugar\n");
    printf("2. Salir\n\n");
    printf("Elige una opci�n: ");
    scanf("%d", &opcion);

    // Opci�n para jugar
    if (opcion == 1) {
      // Submen� de juego
      while (true) {
        int opcionJuego;

        // Mostrar opciones
        printf("\n**Opciones:**\n");
        printf("1. Comprar cart�n automatico\n");
        printf("2. Comprar carton seleccionando numeros\n");
        printf("3. Realizar sorteo\n");
        printf("4. Verificar carton\n");
        printf("5. Salir\n\n");
        printf("Elige una opci�n: ");
        scanf("%d", &opcionJuego);

        // Opciones del submen�
        switch (opcionJuego) {
          case 1:
            carton = ComprarCartonAutomatico(jugador);
            break;
          case 2:
            carton = ComprarCartonSeleccionando(jugador);
            break;
          case 3:
            RealizarSorteo(numerosSorteo);
            break;
          case 4:
            VerificarCarton(numerosSorteo, carton);
            break;
          case 5:
            // Salir del submen�
            break;
          default:
            printf("Opci�n inv�lida.\n");
            break;
        }

        // Salir del submen� si se elige la opci�n 5
        if (opcionJuego == 5) {
          break;
        }
      }
    }

    // Opci�n para salir del programa
    if (opcion == 2) {
      break;
    }
  }

  return 0;
}

JugadorPtr RegistrarJugador(){
    char nombre[50];
    int dni;

    printf("1. Ingrese su nombre\n");
    scanf("%s",nombre);

    printf("2. Ingrese su DNI\n");
    scanf("%d",&dni);

    JugadorPtr jugador = crearJugador(nombre,dni);

    return jugador;
}

CartonPtr ComprarCartonAutomatico(JugadorPtr jugador){
    int numeros[8] = {0};

    generarNumerosAleatorios(numeros, 8);

    printf("Tus numeros son:");
    for (int i = 0; i < 8; i++) {
        printf(" %d ", numeros[i]);
    }
      printf("\n");

    CartonPtr carton = CrearCarton(numeros,jugador,"Calle Mayor 123", "9/4/2024", 70);

    return carton;
}

CartonPtr ComprarCartonSeleccionando(JugadorPtr jugador){
    int numeros[8] = {0};

    printf("Ingrese los numeros para su carton:\n");
    for (int i = 0; i < 8; i++) {
        int numero;
        scanf("%d",&numero);

        numeros[i] = numero;
    }
      printf("\n");

    printf("Tus numeros son:");
    for (int i = 0; i < 8; i++) {
    printf(" %d ", numeros[i]);
      }
      printf("\n");
    CartonPtr carton = CrearCarton(numeros,jugador,"Calle Mayor 123", "9/4/2024", 70);

    return carton;
}

void generarNumerosAleatorios(int vector[], int tamanio) {
  // Inicializar la semilla del generador aleatorio
  srand(time(NULL));

  // Generar 8 n�meros aleatorios y cargarlos en el vector
  for (int i = 0; i < tamanio; i++) {
    vector[i] = rand() % 100;
  }
}

void RealizarSorteo(int numerosSorteo[]){

    generarNumerosAleatorios(numerosSorteo, 20);

    printf("Los numeros del sorteo son:");
    for (int i = 0; i < 20; i++) {
        printf(" %d ", numerosSorteo[i]);
    }
    printf("\n");

}

void VerificarCarton(int numerosSorteo[20],CartonPtr carton){
    int aciertos = busquedaBinaria(carton->numeros, numerosSorteo);
    printf("La cantidad de aciertos es de: %d", aciertos);
}

int busquedaBinaria(int carton[], int numerosSorteo[]) {
  int aciertos = 0;
    ordenarBurbuja(numerosSorteo, 20);

  // Recorrer los n�meros del sorteo
  for (int i = 0; i < 8; i++) {
    int numeroCarton = carton[i];

    // B�squeda binaria del n�mero sorteado en el cart�n
    int inicio = 0;
    int fin = 19;
    while (inicio <= fin) {
      int mitad = (inicio + fin) / 2;
        printf("[%d]:%d\n",numeroCarton,numerosSorteo[mitad]);
      if (numerosSorteo[mitad] == numeroCarton) {

        aciertos++;
        break;
      } else if (numeroCarton > numerosSorteo[mitad]) {
        inicio = mitad + 1;
      } else {
        fin = mitad - 1;
      }
    }
  }

  return aciertos;
}

void ordenarBurbuja(int array[], int longitud) {
  for (int i = 0; i < longitud - 1; i++) {
    for (int j = 0; j < longitud - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
      }
    }
  }
}
