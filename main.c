#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#define N 40
#define SALAS 15
struct struct_idioma //idiomas Español Ingles Japones doblaje //
{
   char doblaje[N];
   char subtitulado[N];
};
typedef struct struct_idioma idioma;  //duracion = minutos/30 12:30 0 1 179/30
//12 00 12 30 13 00 13 30 14:00 14:30 15:00 15:30
// *       *     *    *     *
struct struct_sala
{
    int numero;
    char tamano[N];
    char tipo[N];
    char salas[5][7][10];
    int funciones;
    idioma idioma_pelicula[5];
};
typedef struct struct_sala sala;

struct struct_pelicula //genero accion fantasia ciencia ficcion historia romance // * rojo lol
{
    char nombre[N];
    char genero[2][N];
    int dia;
    int mes;
    int ano;
    int duracion;
    char clasificacion[N];
    int n_salas;
    sala sala_peliculas[5];
    char caracter;
    int color;
};
typedef struct struct_pelicula pelicula;

struct struct_boleto
{
    char nombre[N];
    char hora[N];
    char sala;
    int edad;
    char etapa[N];
    float precio;
    int refill;
};
typedef struct struct_boleto boleto;

struct struct_botana
{
    char nombre[N];
    char tipo[N];
    char tamano[N];
    float precio;
};

void llena_pelicula(pelicula A[20], char G[5][N], char I[3][N], char H[15][38], int C[15][38], int *dir);//da de alta una pelicula
void llena_sala(pelicula A, int num_sala, char horarios[15][38], int colores[15][38]);//llena una sala con funciones de una pelicula
void imprimir_horario(char horarios[15][38], int colores[15][38]);//imprime el horario general del dia
int obtener_n_funciones(int duracion);//obtiene el numero maximo de funciones que se puede poner de una pelicula en una salas

int main()
{
    char generos[5][N]={"Accion","Fantasia","Ciencia Ficcion","Historia,Romance"};
    char idiomas[3][N]={"Espanol","Ingles","Japones"};
    time_t actual;
    time(&actual);
    printf("Bienvenido al sistema de control de cines. Hoy estamos a: %s",ctime(&actual));
    char horarios[15][38]={'\0'};
    int colores[15][38]={0};
    int dir = 0;
    int salas_ocupadas = 0;
    pelicula Peliculas[15];
    int opcion;
    do
    {
        printf("Introduce una opcion:\n1.Dar de alta una pelicula\n2.Imprime el horario de las peliculas del dia de hoy\n0.Salir\n");
        scanf("%d",&opcion);
        system("cls");
        switch(opcion)
        {
            case 1:
                llena_pelicula(Peliculas, generos, idiomas, horarios, colores, &dir);
            break;
            case 2:
                imprimir_horario(horarios, colores);
            break;
        }
        system("cls");
    }while(opcion!=0);
    return 0;
}

void llena_pelicula(pelicula A[20], char G[5][N], char I[3][N], char H[15][38], int C[15][38], int *dir)
{
    printf("Introduce el nombre de la pelicula: ");
    fflush(stdin);
    gets(A[*dir].nombre);
    printf("Introduce los generos de la pelicula:\n1.Para Accion\n2.Para Fantasia\n"
           "3.Ciencia Ficcion\n4.Historia\n5.Romance\nSi no esta uno, presiona 6 ");
    for(int i=0;i<5;++i)
    {
        A[*dir].sala_peliculas[i].funciones=0;
    }
    for(int i=0;i<2;++i)
    {
        int genero;
        scanf("%d",&genero);
        char genero_aux[N];
        if(genero<=5)
            strcpy(A[*dir].genero[i],G[genero-1]);
        else
        {
            printf("Introduce el genero: ");
            fflush(stdin);
            gets(genero_aux);
            strcpy(A[*dir].genero[i],genero_aux);
        }
    }
    printf("Introduce la fecha en la que se estreno (dia mes y a%co con numero): ",164);
    scanf("%d %d %d", &A[*dir].dia, &A[*dir].mes, &A[*dir].ano);
    printf("Introduce la clasificacion: ");
    fflush(stdin);
    gets(A[*dir].clasificacion);
    printf("Introduce la duracion de la pelicula en minutos: ");
    scanf("%d",&A[*dir].duracion);
    do
    {
        printf("En cuantas salas quieres que este la pelicula: ");
        scanf("%d",&A[*dir].n_salas);
        if(A[*dir].n_salas>5)
            puts("No puedes asignar mas de 5 salas para una pelicula");
        else if(A[*dir].n_salas<=0)
            puts("Pusiste un numero menor a 0");
    }while(A[*dir].n_salas>5||A[*dir].n_salas<=0);
    printf("Que caracter quieres asignar a esta pelicula: ");
    fflush(stdin);
    scanf("%c",&A[*dir].caracter);
    printf("Introduce de que colores quieres ese caracter:\n1.Gris Oscuro\n"
           "2.Azul Claro\n3.Verde Claro\n4.Cyan Claro\n5.Rojo Claro\n6.Magenta Claro\n"
           "7.Amarillo\n8.Blanco");
    scanf("%d",&A[*dir].color);
    A[*dir].color+=7;
    for(int i=0;i<A[*dir].n_salas;++i)
    {
        llena_sala(A[*dir], i, H, C);
    }
    ++(*dir);
}

void llena_sala(pelicula A, int num_sala, char horarios[15][38], int colores[15][38])
{
    int funciones;
    int sala;
    printf("A que sala le quieres asignar la funcion: ");
    scanf("%d",&sala);
    do
    {
        printf("Para la pelicula %s, cuantas funciones quieres en esta sala: ",A.nombre);
        scanf("%d",&funciones);
        if(A.sala_peliculas[num_sala].funciones+funciones>5)
            printf("No puedes asignar mas de 5 funciones para una sala, llevas %d funciones.", A.sala_peliculas[sala].funciones);
        else if(funciones<=0)
            puts("Pusiste un numero 0 o menor");
    }while(A.sala_peliculas[num_sala].funciones+funciones>5);
    A.sala_peliculas[num_sala].funciones+=funciones;

    for(int i=0;i<funciones;++i)
    {
        int minutos;
        int horas;
        printf("A que hora comienza la pelicula? (introduce hora y minutos en formato 24 hrs, en intervalos de 30."
               "Se empieza a las 8:00 am y se termina a las 3:00 am): ");
        scanf("%d %d", &horas, &minutos);
        if(horas>=8)
            horas-=8;
        else
            horas+=32;
        if(minutos==30)
            ++horas;
        int n_intervalos=(A.duracion+30)/30;
        for(int j=horas*2;j<n_intervalos+(horas*2);++j)//llena la matriz de horarios
        {
            horarios[sala-1][j]=A.caracter;
            colores[sala-1][j]=A.color;
        }
    }
}

void imprimir_horario(char horarios[15][38], int colores[15][38])
{
    printf("%9c",' ');
    for(int i=0, horas=7 ;i<38; ++i)
    {
        int minutos=3;
        if(i%2==0)
        {
            ++horas;
            minutos=0;
        }
        if(i==32)
            horas=0;
        printf("%d:%d0 ",horas,minutos);
    }
    puts("");
    for(int i=0;i<15;++i)
    {
        printf("Sala: %2d ",i+1);
        for(int j=0;j<38;++j)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colores[i][j]+1);
            if(j==0)
                printf("%2c", horarios[i][j]);
            else if((j>0&&j<4)||j>=32)
                printf("%5c", horarios[i][j]);
            else if(j>=4&&j<32)
                printf("%6c", horarios[i][j]);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        puts("");
    }
    printf("Presiona cualquier tecla para salir. \n");
    fflush(stdin);
    getch();
}
