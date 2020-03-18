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
    int h_i;
    int h_f;
    int min_in;
    int min_fin; //sala 1
                    //LOL Español Japones 12 00 15 00
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

struct struct_pelicula //genero accion fantasia ciencia ficcion historia romance // Montse estuvo aqui
{
    char nombre[N];
    char genero[N];
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

void llena_pelicula(pelicula A[20], char G[5][N], char C[6][5], int *dir);//da de alta una pelicula
void imprimir_pelicula(pelicula A);//imprime una pelicula
int buscar_pelicula_nombre(pelicula A[20], int dir);//busca una pelicula por su nombre y regresa su posicion
void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char horarios[15][38], int colores[15][38]);//llena una sala con funciones de una pelicula
void imprimir_horario(char horarios[15][38], int colores[15][38]);//imprime el horario general del dia
int comprueba_horario(char horarios[38], int a, int b);//comprueba si una pelicula cabe en un intervalo
int convierte_hora(int horas, int minutos);//convierte una hora a una posicion de la matriz hola
void borra_pelicula(pelicula A[20], char horarios[15][38], int colores[15][38], int *dir);//borra una pelicula del sistema
void borra_horario(char horarios[15][38], int colores[15][38], char caracter, int color);//borra los caracteres de una pelicula que ya eliminaste, del horario
void modifica_pelicula(pelicula A);

int main()
{
    float precio_adulto;
    float precio_nino;
    float precio_viejo;
    printf("Introduce la zona en la que estas: ");
    char zona[N];
    gets(zona);
    printf("Introduce los precios adecuados para tu zona para los boletos: ");
    scanf("%f %f %f",&precio_adulto, &precio_nino, &precio_viejo);
    time_t actual;
    time(&actual);
    struct tm *local = localtime(&actual);
//    int horas, minutos, segundos, dia, mes, ano;
//    horas=local->tm_hour;
//    minutos=local->tm_min;
//    segundos=local->tm_sec;
//    dia=local->tm_mday;
//    mes=local->tm_mon+1;
//    ano=local->tm_year+1900;
    system("cls");
    char generos[5][N]={"Accion","Fantasia","Ciencia Ficcion","Historia,Romance"};
    char clasificaciones[6][5]={"AA","A","B","B15","C","D"};
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
        printf("Bienvenido al sistema de control de cines. Estas en la zona: %s\nHoy estamos a: %s",zona, ctime(&actual));
        printf("Introduce una opcion:\n1.Opciones de trabajador.\n2.Opciones de cliente\n0.Salir ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                system("cls");
                printf("Introduce una opcion:\n1.Dar de alta una pelicula\n2.Imprime el horario de las peliculas del dia de hoy\n"
               "3.Llenar una sala para una pelicula.\n4.Imprimir peliculas\n5.Borrar pelicula\n");
                scanf("%d",&opcion);
                int pos_aux;
                system("cls");
                switch(opcion)
                {
                    case 1:
                        llena_pelicula(Peliculas, generos, clasificaciones, &dir);
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
                    case 4:
                        if(dir==0)
                            puts("No tienes peliculas");
                        for(int i=0;i<dir;++i)
                        {
                            imprimir_pelicula(Peliculas[i]);
                        }
                    break;
                    case 5:
                        borra_pelicula(Peliculas, horarios, colores, &dir);
                    break;
                    default:
                        puts("Opcion incorrecta");
                    break;
                }
                printf("Presiona cualquier tecla para continuar. \n");
                fflush(stdin);
                getch();
                system("cls");
            case 2:
            break;
            case 0:
                puts("¡Gracias por usar!");
            break;
        }
    }while(opcion!=0);
    return 0;
}

void llena_pelicula(pelicula A[20], char G[5][N], char C[6][5], int *dir)
{
    if(dir==20)
    {
        puts("Ya no caben mas peliculas, lo sentimos");
        return;
    }
    printf("Introduce el nombre de la pelicula: ");
    fflush(stdin);
    gets(A[*dir].nombre);
    printf("Introduce el genero de la pelicula:\n1.Para Accion\n2.Para Fantasia\n"
           "3.Ciencia Ficcion\n4.Historia\n5.Romance\nSi no esta uno, presiona 6\n");
    int genero;
    scanf("%d",&genero);
    if(genero<=5)
        strcpy(A[*dir].genero,G[genero-1]);
    else
    {
        printf("Introduce el genero: ");
        fflush(stdin);
        gets(A[*dir].genero);
    }
    printf("Introduce la fecha en la que se estreno (dia mes y a%co con numero): ", 164);
    scanf("%d %d %d", &A[*dir].dia, &A[*dir].mes, &A[*dir].ano);
    printf("Introduce la clasificacion:\n1. AA: Peliculas para todo publico, generalmente para menores de 7 a%cos.\n"
            "2. A: Peliculas para todo publico\n3. B: Peliculas para adolescentes de 12 a%cos en adelante\n"
            "4. B15: Pelicula para menores de 15 a%cos\n5. C: Peliculas para mayores de 18 a%cos\n"
            "6. D: Peliculas exclusivas para adultos.\n", 164, 164, 164, 164);
    scanf("%d",&genero);
    strcpy(A[*dir].clasificacion, C[genero-1]);
    printf("Introduce la duracion de la pelicula en minutos: ");
    scanf("%d",&A[*dir].duracion);
    printf("Que caracter quieres asignar a esta pelicula: ");
    fflush(stdin);
    scanf("%c",&A[*dir].caracter);
    printf("Introduce de que colores quieres ese caracter:\n1.Negro\n"
           "2.Azul\n3.Verde\n4.Cyan\n5.Rojo\n6.Magenta\n"
           "7.Marron\n8.Gris Claro\n");
    scanf("%d",&A[*dir].color);
    ++(*dir);
}

void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char horarios[15][38], int colores[15][38])
{
    int sala;
    printf("A que sala le quieres asignar la funcion: ");
    scanf("%d",&sala);
    int funciones_max=19*60/(A.duracion+30)-B[sala].n_funciones;
    int funciones;
    int minutos;
    int horas;
    if(funciones_max==0)
    {
        puts("No quedan funciones disponibles para esta sala");
        return;
    }
    printf("Introduce el doblaje de la pelicula y el subtitulado:\n1.Espa%col\n2.Ingles\n3.Japones\nSi no esta, deja un 4. ",164);
    scanf("%d %d", &horas, &minutos);
    fflush(stdin);
    if(horas<4)
        strcpy(B[sala].idioma_sala.doblaje,idiomas[horas-1]);
    else
    {
        printf("Introduce tu idioma para doblaje: ");
        gets(B[sala].idioma_sala.doblaje);
    }
    fflush(stdin);
    if(minutos<4)
        strcpy(B[sala].idioma_sala.subtitulado,idiomas[minutos-1]);
    else
    {
        printf("Introduce tu idioma para subtitulos: ");
        gets(B[sala].idioma_sala.subtitulado);
    }
    do
    {
        printf("Para la sala %d cuantas funciones quieres asignar para %s.\nTienes como maximo %d funciones para esta misma pelicula.\n"
               "La sala lleva %d funcion(es) ocupadas. ", sala, A.nombre, funciones_max, B[sala].n_funciones);
        scanf("%d",&funciones);
        if(funciones>funciones_max)
            printf("Superas el limite de funciones maximas\n");
    }while(funciones>funciones_max);

    for(int i=B[sala].n_funciones;i<B[sala].n_funciones+funciones;++i)//llena una sala con una funcion
    {
        strcpy(B[sala].Funciones[i].nombre_pelicula, A.nombre);
        int n_intervalos, a;
        int se_puede;
        do
        {
            printf("A que hora comienza la pelicula? (introduce hora y minutos en formato 24 hrs, en intervalos de 30."
                   " Se empieza a las 8:00 am y se termina a las 3:00 am): ");
            scanf("%d %d", &horas, &minutos);
            n_intervalos=(A.duracion+30)/30;
            a=convierte_hora(horas, minutos);
            se_puede=comprueba_horario(horarios[sala-1], a, a+n_intervalos);
            if(se_puede)
                puts("Ya hay una funcion en ese intervalo de tiempo");
        }while(se_puede);
//        B[sala].Funciones[i].h_i=horas;
//        B[sala].Funciones[i].min_in_i=minutos;
//        B[sala].Funciones[i].h_i=;
        for(int j=a;j<a+n_intervalos;++j)//llena la matriz de horarios
        {
            horarios[sala-1][j]=A.caracter;
            colores[sala-1][j]=A.color;
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colores[i][j]-1);
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

int convierte_hora(int horas, int minutos)
{
    int pos;
    if(horas>=8)
        pos=(horas-8)*2;
    else
        pos=horas+33;
    if(minutos==30)
        ++pos;
    return pos;
}

int comprueba_horario(char horarios[38], int a, int b)
{
    for(int i=a;i<=b;++i)
    {
        if(horarios[i]!='\0')
            return 1;
    }
    return 0;
}

void imprimir_pelicula(pelicula A)
{
    printf("Nombre: %s\n",A.nombre);
}

void borra_pelicula(pelicula A[20], char horarios[15][38], int colores[15][38], int *dir)
{
    char nombre[N];
    int pos;
    pos=buscar_pelicula_nombre(A, *dir);//pos 2
    if(pos==-1)
    {
        puts("No se encontro esa pelicula");
        return;
    }
    borra_horario(horarios, colores, A[pos].caracter, A[pos].color);
    puts("Se borro satisfactoriamente la pelicula");
    A[pos]=A[(*dir)-1];
    --(*dir);
}

void borra_horario(char horarios[15][38], int colores[15][38], char caracter, int color)
{
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<38;++j)
        {
            if(horarios[i][j]==caracter&&colores[i][j]==color)
            {
                horarios[i][j]='\0';
            }
        }
    }
}

void modifica_pelicula(pelicula A)
{
    int opcion;
    printf("Que quieres modificar de esta pelicula?\n1.nombre\n2.genero3.Fecha de estreno\n"
           "4.duracion\n5.clasificacion\n6.caracter\n7.\ncolor");

}
