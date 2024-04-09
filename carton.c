#include "carton.h"
#include <string.h>
#include <stdio.h>

CartonPtr CrearCarton(int n[], JugadorPtr j,char *d,char *f, int p)
{
    Carton* carton = (Carton*)malloc(sizeof(Carton));
    for (int i = 0; i < 8; i++)
    {
        carton->numeros[i] = n[i];
    }
    carton->jugador = j;

    //char *fechaJuego;
    //calcularFechaJuego( *f,  *fechaJuego);

    strcpy(carton->direccion_agencia,d);
    strcpy(carton->fecha_de_emision, f);
    //strcpy(carton->fecha_juego, fechaJuego);
    carton->precio = p;

    return carton;
}


// Getter
int GetNumero(CartonPtr carton, int indice)
{
    return carton->numeros[indice];
}

char* GetFechaEmision(CartonPtr carton)
{
    return carton->fecha_de_emision;
}

/*char* GetFechaJuego(CartonPtr carton)
{
    return carton->fecha_juego;
}*/
char* GetDireccionAgencia(CartonPtr carton)
{
    return carton->direccion_agencia;
}

int GetPrecio(CartonPtr carton)
{
    return carton->precio;
}

JugadorPtr GetJugador(CartonPtr carton)
{
    return carton->jugador;
}
/*int calcularFechaJuego(char *fechaEmision, char *fechaJuego)
{
    // Convertir la fecha de emisi�n a una estructura tm
    struct tm fechaEmisionTm;
    strptime(fechaEmision, "%Y-%m-%d", &fechaEmisionTm);

    // Obtener el d�a de la semana de la fecha de emisi�n
    int diaSemana = fechaEmisionTm.tm_wday;

    // Calcular el n�mero de d�as hasta el pr�ximo domingo
    int diasHastaDomingo = 7 - diaSemana;

    // Sumar los d�as hasta el domingo a la fecha de emisi�n
    fechaEmisionTm.tm_mday += diasHastaDomingo;

    // Convertir la estructura tm a una cadena de caracteres
    strftime(fechaJuego, sizeof(fechaJuego), "%Y-%m-%d", &fechaEmisionTm);

    return 0;
}
*/
void leerCarton(const Carton *carton)
{
    // Imprimir encabezado
    printf("\n**Cart�n de Quiniela**\n");

    // Imprimir n�meros del cart�n
    printf("N�meros: ");
    for (int i = 0; i < 8; i++)
    {
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
