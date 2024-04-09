/*El programa debe contener como mínimo:
✅Comprar cartón automático
✅Comprar carton seleccionando los 8 números
✅Jugar, creación de los 20 números del partido
✅Verificar cartón, saber si has ganado y cuánto has ganado
✅Imprimir el cartón, marcando de alguna forma los números que salieron, también guardarlo en un archivo.
Generar un bucle que te diga cuantas veces tenes que jugar con el mismo cartón para llegar a ganar con 8 aciertos
*/
#include <stdio.h>
#include <stdlib.h>
#include "jugador.h"
#include <stdbool.h>
#include "carton.h"
#include <time.h>

CartonPtr ComprarCartonAutomatico(JugadorPtr jugador);
CartonPtr ComprarCartonSeleccionando(JugadorPtr jugador);
JugadorPtr RegistrarJugador(jugador);
void RealizarSorteo(int numerosSorteo[]);
void generarNumerosAleatorios(int vector[], int tamanio);
void VerificarCarton(int numerosSorteo[20],CartonPtr carton);
int calcularJugadasParaGanar8Aciertos(CartonPtr carton);
char *obtenerFechaHoraActual();

char *obtenerFechaHoraActual()
{
    time_t tiempoActual = time(NULL);
    struct tm *fechaHora = localtime(&tiempoActual);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaHora);

    return strdup(buffer);
}

int main()
{
    int numerosSorteo[20];
    JugadorPtr jugador = RegistrarJugador();
    CartonPtr carton;
    bool sorteoRealizado = false;
    bool cartonComprado = false;
    while (true)
    {
        int opcion;

        printf("\n**Bienvenido a la Quiniela Plus**\n\n");
        printf("%s , %d\n",jugador->nombre,jugador->dni);
        printf("**Opciones:**\n");
        printf("1. Jugar\n");
        printf("2. Salir\n\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);

        // Opción para jugar
        if (opcion == 1)
        {
            // Submenú de juego
            while (true)
            {
                int opcionJuego;

                // Mostrar opciones
                printf("\n**Opciones:**\n");
                printf("1. Comprar cartón automatico\n");
                printf("2. Comprar carton seleccionando numeros\n");
                if (cartonComprado)
                {
                    printf("3. Realizar sorteo\n");
                }
                if  (sorteoRealizado)
                {
                    printf("4. Verificar cartón\n");
                }

                printf("5. Salir\n\n");
                printf("Elige una opción: ");
                scanf("%d", &opcionJuego);

                // Opciones del submenú
                switch (opcionJuego)
                {
                case 1:
                    cartonComprado = true;
                    carton = ComprarCartonAutomatico(jugador);
                    break;
                case 2:
                    cartonComprado = true;
                    carton = ComprarCartonSeleccionando(jugador);
                    break;
                case 3:
                     sorteoRealizado = true;
                    RealizarSorteo(numerosSorteo);
                    break;
                case 4:
                    VerificarCarton(numerosSorteo, carton);
                    break;
                case 5:
                    // Salir del submenú
                    break;
                default:
                    printf("Opción inválida.\n");
                    break;
                }

                // Salir del submenú si se elige la opción 5
                if (opcionJuego == 5)
                {
                    break;
                }
            }
        }

        // Opción para salir del programa
        if (opcion == 2)
        {
            break;
        }
    }

    return 0;
}

JugadorPtr RegistrarJugador()
{
    char nombre[50];
    char dniStr[20];
    int dni = 0;
    int esNumerico = 1;


    printf("1. Ingrese su nombre\n");
    scanf("%49s", nombre);


    do
    {
        printf("Ingrese su DNI (solo numeros):\n");
        scanf("%19s", dniStr);
        esNumerico = 1;
        for (int i = 0; i < strlen(dniStr); i++)
        {
            if (!isdigit(dniStr[i]))
            {
                esNumerico = 0;
                printf("Error: El DNI debe contener solo numeros.\n");
                break;
            }
        }

        if (esNumerico)
        {
            dni = atoi(dniStr);
        }

    }
    while (!esNumerico);


    JugadorPtr jugador = crearJugador(nombre,dni);

    return jugador;
}

CartonPtr ComprarCartonAutomatico(JugadorPtr jugador)
{
    int numeros[8] = {0};

    char *fechaHoraActual  = obtenerFechaHoraActual();

    generarNumerosAleatorios(numeros, 8);

    printf("Tus numeros son:");
    for (int i = 0; i < 8; i++)
    {
        printf(" %d ", numeros[i]);
    }
    printf("\n");

    CartonPtr carton = CrearCarton(numeros,jugador,"Siempreviva 123", fechaHoraActual, 70);
    printf("Fecha de emision: %s", GetFechaEmision(carton));
    return carton;
}

CartonPtr ComprarCartonSeleccionando(JugadorPtr jugador)
{
    int numeros[8] = {0};

    printf("Ingrese los números para su cartón, deben ser únicos y estar entre 0 y 99:\n");

    for (int i = 0; i < 8; )
    {
        int numero;
        bool numeroRepetido = false;

        printf("Número %d: ", i + 1);
        scanf("%d", &numero);

        if (numero < 0 || numero > 99)
        {
            printf("El número debe ser entre 0 y 99. Intente nuevamente:\n");
            continue;
        }

        for (int j = 0; j < i; j++)
        {
            if (numeros[j] == numero)
            {
                printf("Número repetido, ingrese un número diferente.\n");
                numeroRepetido = true;
                break;
            }
        }

        if (!numeroRepetido)
        {
            numeros[i] = numero;
            i++;
        }
    }

    printf("\n");

    printf("Tus números son:");
    for (int i = 0; i < 8; i++)
    {
        printf(" %d ", numeros[i]);
    }
    printf("\n");

    char *fechaHoraActual  = obtenerFechaHoraActual();
    CartonPtr carton = CrearCarton(numeros, jugador, "Calle Mayor 123", fechaHoraActual, 70);
    printf("Fecha de emision: %s", GetFechaEmision(carton));
    return carton;
}

void generarNumerosAleatorios(int vector[], int tamanio)
{
    for (int i = 0; i < tamanio; i++)
    {
        vector[i] = -1;
    }
    int contador = 0;
    while(contador < tamanio)
    {
        bool repetido = false;
        int numeroAleatorio = rand() % 100;

        for (int j=0; j < contador; j++)
        {
            if(vector[j] == numeroAleatorio)
            {
                repetido = true;
                break;
            }
        }

        if(!repetido)
        {
            vector[contador] = numeroAleatorio;
            contador++;
        }
    }

}

void RealizarSorteo(int numerosSorteo[])
{
    generarNumerosAleatorios(numerosSorteo, 20);
}

void VerificarCarton(int numerosSorteo[20],CartonPtr carton)
{
    int posicionAciertos[8];
    ordenarBurbuja(numerosSorteo, 20);
    int aciertos = busquedaBinaria(carton->numeros, numerosSorteo,posicionAciertos);
    printf("\n**Resultado del sorteo**\n");
    printf("Los numeros del sorteo son:");
    for (int i = 0; i < 20; i++)
    {
        printf(" %d ", numerosSorteo[i]);
    }
    printf("\n");
    printf("Aciertos: %d\n", aciertos);

    printf("Carton con aciertos: ");

    for (int i = 0; i < 8; i++)
    {
        bool encontrado = false;
        for(int j=0; j<aciertos; j++)
        {

            if(carton->numeros[i] == posicionAciertos[j])
            {
                printf("[%d] ", carton->numeros[i]);
                encontrado = true;
                break;
            }
        }
        if(!encontrado)
        {
            printf("%d ", carton->numeros[i]);
        }
    }

    printf("\n");
    int premio = determinarPremio(aciertos);
    if (premio > 0)
    {
        printf("¡Felicidades! Usted ha ganado $%d\n", premio);
    }
    else
    {
        printf("Lo sentimos, no ha ganado ningún premio en este sorteo.\n");
    }

    if(aciertos < 8)
    {
        int eleccion;
        printf("Queres saber cuantas veces tenes que jugar con el mismo cartón para llegar a ganar con 8 aciertos?\n");
        printf("1- SI\n");
        printf("2- NO\n");
        scanf("%d",&eleccion);
        if(eleccion == 1)
        {
            int intentos = calcularJugadasParaGanar8Aciertos(carton);
            printf("Para ganar el mayor premio con este carton necesitaria %d intentos para lograrlo",intentos);
        }
        else
        {
            return;
        }
    }
}
int calcularJugadasParaGanar8Aciertos(CartonPtr carton)
{
    int intentos = 0;
    int numerosSorteo[20];
    int aciertos = 0;
    int posicionAciertos[8];
    do
    {
        intentos++;
        RealizarSorteo(numerosSorteo);
        aciertos = busquedaBinaria(carton->numeros, numerosSorteo,posicionAciertos);
        printf("%d",intentos);
    }
    while(aciertos != 8);
    return intentos;
}

void guardarCartonGanador(CartonPtr carton, char *nombreArchivo)
{
    // Abrir el archivo en modo escritura
    FILE *archivo = fopen(nombreArchivo, "w");

    // Guardar la información del cartón
    fprintf(archivo, "**Cartón ganador de Quiniela Plus**\n");
    fprintf(archivo, "Jugador: %s - DNI: %d\n", GetNombre(GetJugador(carton)), GetDni(GetJugador(carton)));
    fprintf(archivo, "Fecha de emisión: %d\n", GetFechaEmision(carton));
    fprintf(archivo, "Precio: $%d\n", GetPrecio(carton));
    fprintf(archivo, "Dirección de la agencia: %s\n", GetDireccionAgencia(carton));

    // Guardar los números del cartón
    fprintf(archivo, "Números: ");
    for (int i = 0; i < 8; i++)
    {
        fprintf(archivo, "%d ", carton->numeros[i]);
    }

    // Cerrar el archivo
    fclose(archivo);
}

int determinarPremio(int aciertos)
{
    switch (aciertos)
    {
    case 8:
        return 11000000;
    case 7:
        return 20000;
    case 6:
        return 500;
    case 5:
        return 50;
    default:
        return 0;
    }
}

int busquedaBinaria(int carton[], int numerosSorteo[], int posicionAciertos[])
{
    int aciertos = 0;

    // Recorrer los números del sorteo
    for (int i = 0; i < 8; i++)
    {
        int numeroCarton = carton[i];

        // Búsqueda binaria del número sorteado en el cartón
        int inicio = 0;
        int fin = 19;
        while (inicio <= fin)
        {
            int mitad = (inicio + fin) / 2;

            if (numerosSorteo[mitad] == numeroCarton)
            {
                posicionAciertos[aciertos] = numeroCarton;
                aciertos++;
                break;
            }
            else if (numeroCarton > numerosSorteo[mitad])
            {
                inicio = mitad + 1;
            }
            else
            {
                fin = mitad - 1;
            }
        }
    }

    return aciertos;
}

void ordenarBurbuja(int array[], int longitud)
{

    int calcularFechaDeJuego(CartonPtr carton)
    {

    }

    char *obtenerFechaHoraActual()
    {
        time_t tiempoActual = time(NULL);
        struct tm *fechaHora = localtime(&tiempoActual);

        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fechaHora);

        return strdup(buffer);
    }
    for (int i = 0; i < longitud - 1; i++)
    {
        for (int j = 0; j < longitud - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
}
