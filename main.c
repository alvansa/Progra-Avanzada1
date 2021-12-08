// Nombres: Alvaro Soto Albornoz - Benjamín Melis Guerra
// Nombre Profesora: Nicolas Théériault
// IDE: Visual Studio Code 1.62.3
// SO: Windows 10
// Fecha: 1 de Diciembre - 2021
// Este progroma se dejó de hinchar las weas (nadie sabe ni tampoco se pregunta el porque(caja negra XD))el dia 1 de diciembre y se digno a resolver sistemas lineales con eliminacion gaussiona

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define P (long long)3781996138433268199
#define Pa (long long)1761129190
#define Pb (long long)892783079
#define bAJO (long long)2147483647

long long **asignar_matriz(int n, int m);                                              // Reservar la memoria y crear una matriz nula
void llenar_matriz(long long **matriz, int filas, int columnas);                       // Llenar la matriz nula con valores al azar utilizando la funcion rand()
void imprimir_matriz(long long **array, int filas, int columnas);                      // Funcion que imprime la matriz
void Triangular_SUP(long long **matriz_vellda, int filas, int columnas);               // Matriz Triangular superior
void Triangular_INF(long long **matriz, int filas, int columnas);                      // Matriz Triangular inferior
void Eliminacion_Gaussiana(long long **matriz, int filas, int columnas);               // Eliminacion Gaussiana completa
void Matriz_inversa(long long **matriz, int filas, int columnas);                      // Matriz inversa
void eye(long long **matriz, int fila, int columnas);                                  // Matriz identidad
void menu();                                                                           // Menu para desplazarse entre las funciones del programa
void cambiar_linea(long long **matriz, int dim, int linea, long long valor);           // Toma un fila de la matriz y la amplifica por un valor dado
void resta_lineas(long long **matriz, int dim, int minu, int sustra, long long valor); // Resta dos filas

// ###########Funciones PROFE#######//
long long MultP(long long a, long long b);
long long RestaP(long long a, long long b);
long long SumaP(long long a, long long b);
long long InvP(long long A);

int main()
{
    srand(time(0)); // metodo para generar numeros aleatorios
    menu();

    return 0;
}

void menu()
{
    int opcion, filas, columnas;
    long long **matriz;
    clock_t tiempo1, tiempo2;

    // generar matriz

    printf("\nEscoga la cantidad de filas de la matriz: ");
    scanf("%i", &filas);
    printf("\nEscoga la cantidad de columnas de la matriz: ");
    scanf("%i", &columnas);

    matriz = asignar_matriz(filas, columnas);
    llenar_matriz(matriz, filas, columnas);
    do
    {

        printf("\n\nOperaciones matriciales. Por favor seleccione una opcion");
        printf("\n1) Eliminacion Gaussiana ");
        printf("\n2) Triangular Superior. ");
        printf("\n3) Triangular Inferior ");
        printf("\n4) Matriz Inversa. ");
        printf("\n5) Llenar matriz con valores. ");
        printf("\n Opcion: (Presione 0 para salir) ");
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            tiempo1 = clock();
            Eliminacion_Gaussiana(matriz, filas, columnas);
            printf("\nAca esta wea ya termino pero le cuesta calcular el tiempo........");
            for (int i = 0; i < columnas; i++)
            {
                free(matriz[i]);
            }
            free(matriz);
            tiempo2 = clock();
            printf("\nPrograma terminado, la ejecucion duro : %f", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));

            break;
        case 2:
            tiempo1 = clock();
            Triangular_SUP(matriz, filas, columnas);
            tiempo2 = clock();
            printf("Programa terminado, la ejecucion duro : %f", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
            // free(matriz);
            break;
        case 3:
            tiempo1 = clock();
            Triangular_INF(matriz, filas, columnas);
            tiempo2 = clock();
            printf("Programa terminado, la ejecucion duro : %f", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
            // free(matriz);
            break;
        case 4:
            tiempo1 = clock();
            Matriz_inversa(matriz, filas, columnas);
            tiempo2 = clock();
            printf("Programa terminado, la ejecucion duro : %f", ((double)tiempo2 - (double)tiempo1) / ((double)CLOCKS_PER_SEC));
            break;
        case 0:
            break;
        default:
            printf("Seleccione una opcion valida");
            break;
        }
    } while (opcion);
    free(matriz);
}

long long **asignar_matriz(int n, int m)
{
    int i, j;
    long long **array;
    array = (long long **)malloc(n * sizeof(long long *)); // se reserva memoria  para la matriz de x filas que contiene direcciones de memoria a las segundas dimensiones.
    for (i = 0; i < n; i++)
    {
        array[i] = (long long *)malloc(m * sizeof(long long)); // se reserva memoria para las segundas dimensiones , x columnas
    }
    // en memoria ya tenemos reservado espacio para una matriz de x por x --> array[x][x]
    return &*array; // retorno de un puntero doble
}

void llenar_matriz(long long **matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            matriz[i][j] = ((long long)(rand() % P)); // Se asignan valores aleatorios a cada coordenadas de la matriz
        }
    }
}

void imprimir_matriz(long long **array, int filas, int columnas)
{
    int i, j;
    printf("\nIMPRIMIENDO MATRIZ\n");
    printf("\n==================\n");

    for (i = 0; i < filas; i++)
    {
        printf("\n");
        for (j = 0; j < columnas; j++)
        {
            printf("%lld ", array[i][j]);
        }
    }
}

void cambiar_linea(long long **matriz, int dim, int linea, long long valor)
{
    for (int i = 0; i < dim; i++)
    {
        matriz[linea][i] = MultP(matriz[linea][i], valor); // se aplifica la linea por la variable valor
    }
}

void resta_lineas(long long **matriz, int dim, int minu, int sustra, long long valor)
{
    long long aux; // variable auxiliar que guarda la linea que se va a restar

    for (int i = 0; i < dim; i++)
    {
        aux = MultP(matriz[sustra][i], valor);
        matriz[minu][i] = RestaP(matriz[minu][i], aux);
    }
}

void Triangular_SUP(long long **matriz, int filas, int columnas)
{
    long long inv;
    if (matriz == NULL)  // Revision si la matriz fue creada satisfactoriamente
    {
        printf("\nMemoria alocada incorrectamnete......");
        exit(0);
    }
    else
    {
        for (int i = 0; i < columnas; i++)   //Ciclo que revisa columnas 
        {                                  
            
            for (int j = i; j < filas - 1; j++) //Ciclo que revisa filas
            {                                                               
                inv = InvP(matriz[i][i]);                                   
                cambiar_linea(matriz, columnas, i, inv);                    
                resta_lineas(matriz, columnas, j + 1, i, matriz[j + 1][i]); 
            }
        }
        inv = InvP(matriz[filas - 1][filas - 1]);
        cambiar_linea(matriz, columnas, filas - 1, inv);
    }
}

void Triangular_INF(long long **matriz, int filas, int columnas)
{

    long long aux, inv; 
    int cont = 0;       
    if (matriz == NULL)
    {
        printf("\nMemoria alocada incorrectamnete......");
        exit(0);
    }
    else
    {
        for (int i = filas - 1; i > 0; i--) 
        {
            printf("  Ciclo %i", i);
            for (int j = i; j > 0; j--) 
            {
                inv = InvP(matriz[i][i]);                                   
                cambiar_linea(matriz, columnas, i, inv);                    
                resta_lineas(matriz, columnas, j - 1, i, matriz[j - 1][i]); 
            }
        }
        inv = InvP(matriz[0][0]); 
        cambiar_linea(matriz, columnas, 0, inv);
    }
}

void Eliminacion_Gaussiana(long long **matriz, int filas, int columnas)
{

    long long aux = 0, inv = 0; 
    if (matriz == NULL)
    {
        printf("\nMemoria alocada incorrectamnete......");
        exit(0);
    }
    else
    {
        for (int i = 0; i < columnas; i++) 
        {                                  
            printf("  Ciclo %i", i);
            for (int j = i; j < filas - 1; j++)
            {                                                              
                inv = InvP(matriz[i][i]);                                  
                cambiar_linea(matriz, columnas, i, inv);                   
                resta_lineas(matriz, columnas, j + 1, i, matriz[j + 1][i]);
            }
        }
        
        for (int i = filas - 1; i > 0; i--) 
        {
            for (int j = i; j > 0; j--) 
            {
                inv = InvP(matriz[i][i]);                                   
                cambiar_linea(matriz, columnas, i, inv);                    
                resta_lineas(matriz, columnas, j - 1, i, matriz[j - 1][i]); 
            }
        }
    }

    printf("\nAca tambien la wea ya termino......");
    
}

void Matriz_inversa(long long **matriz, int filas, int columnas)
{
    
    long long aux, inv, **identidad;
    identidad = asignar_matriz(filas, columnas);
    eye(identidad, filas, columnas);
    if (matriz == NULL || identidad == NULL)
    {
        printf("\nMemoria alocada incorrectamnete......");
        exit(0);
    }
    else
    {
        for (int i = 0; i < columnas; i++) 
        {                                  

            for (int j = i; j < filas - 1; j++)
            { 

                inv = InvP(matriz[i][i]);                
                cambiar_linea(matriz, columnas, i, inv); 
                cambiar_linea(identidad, columnas, i, inv);
                resta_lineas(identidad, columnas, j + 1, i, matriz[j + 1][i]);
                resta_lineas(matriz, columnas, j + 1, i, matriz[j + 1][i]); 
            }
        }
       
        for (int i = columnas - 1; i > 0; i--) 
        {
            for (int j = i; j > 0; j--) 
            {

                inv = InvP(matriz[i][i]);
                cambiar_linea(matriz, columnas, i, inv);
                cambiar_linea(identidad, columnas, i, inv);
                resta_lineas(identidad, columnas, j - 1, i, matriz[j - 1][i]);
                resta_lineas(matriz, columnas, j - 1, i, matriz[j - 1][i]);
                
            }
        }
        //printf("\n\nLa matriz inversa es: \n");
        
        free(identidad);
    }
}

void eye(long long **matriz, int fila, int columnas)
{
    for (int i = 0; i < fila; i++)
    {
        matriz[i][i] = 1;
    }
}

long long InvP(long long A)
{
    long long a, b, s1, s2, r, u;
    a = A;
    b = P;
    s1 = 1;
    s2 = 0;
    if (A == 0)
    {
        printf("Error, division entre 0\n");
        return (0);
    }
    while ((a % 2) == 0)
    {
        a >>= 1;
        if ((s1 % 2) == 0)
        {
            s1 >>= 1;
        }
        else
        {
            s1 = (s1 + P) >> 1;
        }
    }
    if (b > a)
    {
        r = b;
        b = a;
        a = r;
        u = s2;
        s2 = s1;
        s1 = u;
    }
    while ((b != 0) && (b != a))
    {
        r = a - b;
        u = RestaP(s1, s2);
        while ((r % 2) == 0)
        {
            r >>= 1;
            if ((u % 2) == 0)
            {
                u >>= 1;
            }
            else
            {
                u = (u + P) >> 1;
            }
        }
        if (r < b)
        {
            a = b;
            b = r;
            s1 = s2;
            s2 = u;
        }
        else
        {
            a = r;
            s1 = u;
        }
    }
    return (s1);
}

long long SumaP(long long a, long long b)
{
    long long c;
    c = a + b;
    if (c < P)
    {
        return (c);
    }
    else
    {
        return (c - P);
    }
}

long long MultP(long long a, long long b) //???
{
    long long a0, a1, b0, b1, d0, d1, d2, d3;
    long long c;

    a0 = a & bAJO;
    a1 = a >> 31;
    b0 = b & bAJO;
    b1 = b >> 31;
    d0 = a0 * b0;
    d3 = a1 * b1;
    a1 += a0;
    b1 += b0;
    d2 = d0 + d3;
    d1 = a1 * b1;
    d1 -= d2;
    d3 += (d1 >> 31);
    d2 = d1 & bAJO;
    d2 += d0 >> 31;
    d1 = d0 & bAJO;
    a1 = d3 / Pa;
    b1 = ((d3 % Pa) << 31) + d2 - (a1 * Pb);
    while (b1 < 0)
    {
        b1 += P;
    }
    while (b1 >= P)
    {
        b1 -= P;
    }
    a0 = b1 / Pa;
    b0 = ((b1 % Pa) << 31) + d1 - (a0 * Pb);
    while (b0 < 0)
    {
        b0 += P;
    }
    while (b0 >= P)
    {
        b0 -= P;
    }
    return (b0);
}

long long RestaP(long long a, long long b)
{
    if (a < b)
    {
        return ((P + a) - b);
    }
    else
    {
        return (a - b);
    }
}
