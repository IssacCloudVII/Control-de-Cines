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
struct struct_funcion
{
    char nombre_pelicula[N];
    idioma idioma_funcion;
};
typedef struct struct_funcion funcion;
// *       *     *    *     *
struct struct_sala
{
    int numero;
    char tamano[N];
    char tipo[N];
    int n_funciones;
    funcion Funciones[10];
    idioma idioma_sala;
};
typedef struct struct_sala sala;

struct struct_pelicula //genero accion fantasia ciencia ficcion historia romance //
{
    char nombre[N];
    char genero[2][N];
    int dia;
    int mes;
    int ano;
    int duracion;
    char clasificacion[N];
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

void llena_pelicula(pelicula A[20], char G[5][N], int *dir);//da de alta una pelicula
void imprimir_pelicula(pelicula A);//imprime una pelicula
int buscar_pelicula_nombre(pelicula A[20], int dir);//busca una pelicula por su nombre y regresa su posicion
void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char horarios[15][38], int colores[15][38]);//llena una sala con funciones de una pelicula
void imprimir_horario(char horarios[15][38], int colores[15][38]);//imprime el horario general del dia

int main()
{
    time_t actual;
    time(&actual);
    printf("Bienvenido al sistema de control de cines.\nHoy estamos a: %s",ctime(&actual));
    struct tm *local = localtime(&actual);
    int horas, minutos, segundos, dia, mes, ano;
    horas=local->tm_hour;
    minutos=local->tm_min;
    segundos=local->tm_sec;
    dia=local->tm_mday;
    mes=local->tm_mon+1;
    ano=local->tm_year+1900;
    printf("%d %d %d %d %d %d\n",horas,minutos,segundos,dia,mes,ano);

    char generos[5][N]={"Accion","Fantasia","Ciencia Ficcion","Historia,Romance"};
    char idiomas[3][N]={"Espanol","Ingles","Japones"};
    char horarios[SALAS][38]={'\0'};
    int colores[SALAS][38]={0};
    int dir = 0;
    int salas_ocupadas = 0;
    sala Salas[SALAS]={NULL};
    pelicula Peliculas[20];
    int opcion;
    do
    {
        printf("Introduce una opcion:\n1.Dar de alta una pelicula\n2.Imprime el horario de las peliculas del dia de hoy\n"
               "3.Llenar una sala para una pelicula.\n0.Salir\n");
        scanf("%d",&opcion);
        system("cls");
        int pos_aux;
        switch(opcion)
        {
            case 1:
                llena_pelicula(Peliculas, generos, &dir);
            break;
            case 2:
                imprimir_horario(horarios, colores);
            break;
            case 3:
                pos_aux=buscar_pelicula_nombre(Peliculas, dir);
                if(pos_aux!=-1)
                    llena_sala(Peliculas[pos_aux], Salas, idiomas, horarios, colores);
                else
                    puts("No se encontro esa pelicula, y no se pudo llenar la sala");
            break;
        }
        printf("Presiona cualquier tecla para salir. \n");
        fflush(stdin);
        getch();
        system("cls");
    }while(opcion!=0);
    return 0;
}

void llena_pelicula(pelicula A[20], char G[5][N], int *dir)
{
    printf("Introduce el nombre de la pelicula: ");
    fflush(stdin);
    gets(A[*dir].nombre);
    printf("Introduce los generos de la pelicula:\n1.Para Accion\n2.Para Fantasia\n"
           "3.Ciencia Ficcion\n4.Historia\n5.Romance\nSi no esta uno, presiona 6 ");
    for(int i=0;i<2;++i)
    {
        int genero;
        scanf("%d",&genero);
        if(genero<=5)
            strcpy(A[*dir].genero[i],G[genero-1]);
        else
        {
            printf("Introduce el genero: ");
            fflush(stdin);
            gets(A[*dir].genero[i]);
        }
    }
    printf("Introduce la fecha en la que se estreno (dia mes y a%co con numero): ",164);
    scanf("%d %d %d", &A[*dir].dia, &A[*dir].mes, &A[*dir].ano);
    printf("Introduce la clasificacion: ");
    fflush(stdin);
    gets(A[*dir].clasificacion);
    printf("Introduce la duracion de la pelicula en minutos: ");
    scanf("%d",&A[*dir].duracion);
    printf("Que caracter quieres asignar a esta pelicula: ");
    fflush(stdin);
    scanf("%c",&A[*dir].caracter);
    printf("Introduce de que colores quieres ese caracter:\n1.Gris Oscuro\n"
           "2.Azul Claro\n3.Verde Claro\n4.Cyan Claro\n5.Rojo Claro\n6.Magenta Claro\n"
           "7.Amarillo\n8.Blanco");
    scanf("%d",&A[*dir].color);
    A[*dir].color+=7;
    ++(*dir);
}

void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char horarios[15][38], int colores[15][38])
{
    int sala;
    printf("A que sala le quieres asignar la funcion: ");
    scanf("%d",&sala);
    int funciones_max=19*60/(A.duracion+30)-B[sala].n_funciones;
    int funciones;
    do
    {
        printf("Para la sala %d cuantas funciones quieres asignar para %s. Tienes como maximo %d funciones."
               "La sala lleva %d funciones ocupadas. ", sala, A.nombre, funciones_max, B[sala].n_funciones);
        scanf("%d",&funciones);
        if(funciones>funciones_max)
            printf("Superas el limite de funciones maximas\n");
    }while(funciones>funciones_max);

    for(int i=B[sala].n_funciones;i<B[sala].n_funciones+funciones;++i)//llena una sala con una funcion
    {
        strcpy(B[sala].Funciones[i].nombre_pelicula, A.nombre);
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
        printf("Introduce el doblaje de la pelicula y el subtitulado: 1.Espa%col\n2.Ingles\n3.Japones\nSi no esta, deja un 4. ",164);
        scanf("%d %d", &horas, &minutos);
        fflush(stdin);
        if(horas<4)
            strcpy(B[sala].idioma_sala.doblaje,idiomas[horas-1]);
        else
        {
            printf("Introduce tu idioma: ");
            gets(B[sala].idioma_sala.doblaje);
        }
        fflush(stdin);
        if(minutos<4)
            strcpy(B[sala].idioma_sala.subtitulado,idiomas[minutos-1]);
        else
        {
            printf("Introduce tu idioma: ");
            gets(B[sala].idioma_sala.subtitulado);
        }
    }
    B[sala].n_funciones+=funciones;
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

}
int buscar_pelicula_nombre(pelicula A[20], int dir)
{
    char nombre[N];
    printf("Introduce el nombre de la pelicula que quieres buscar: ");
    fflush(stdin);
    gets(nombre);
    for(int i=0;i<dir;++i)
    {
        if(strcmp(A[i].nombre, nombre)==0)
            return i;
    }
    return -1;
}
