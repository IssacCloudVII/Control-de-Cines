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
    char asientos[10][8];// 5*6
    int asientos_ocupados;
    int h_i;
    int min_in;  //sala 1 //LOL Español Japones 12 00 15 00
    char tipo[N];
};
typedef struct struct_funcion funcion;
// *       *     *    *     *
struct struct_sala
{
    char tamano[N];
    int n_funciones[7];
    funcion Funciones[7][10];
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
    char clasificacion[5];
    char caracter;
    int color;
    unsigned int ventas;
};
typedef struct struct_pelicula pelicula;//Hola soy Montse

struct struct_boleto
{
    char nombre_pelicula[N];
    int num_sala;
    float precio;
    char fila;
    int columna;
    int h_i, min_i;
    int codigo_boleto;
    char tipo_funcion[N];
};
typedef struct struct_boleto boleto;

struct struct_botana
{
    char nombre[N];
    char tipo[N];
    char tamano[N];
    float precio;
};
typedef struct struct_botana botana;

void llena_pelicula(pelicula A[20], char G[5][N], char C[6][5], int *dir);//da de alta una pelicula
void imprimir_pelicula(pelicula A);//imprime una pelicula
int buscar_pelicula_nombre(pelicula A[20], int dir);//busca una pelicula por su nombre y regresa su posicion
void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char dias[7][N], char tipo[4][N], char horarios[7][15][38], int colores[7][15][38]);//llena una sala con funciones de una pelicula
void imprimir_horario(char horarios[7][15][38], int colores[7][15][38], char dias[7][N], int dia);//imprime el horario general del dia
int comprueba_horario(char horarios[38], int a, int b);//comprueba si una pelicula cabe en un intervalo
int convierte_hora(int horas, int minutos);//convierte una hora a una posicion de la matriz
void borra_pelicula(pelicula A[20], char horarios[7][15][38], int colores[7][15][38], int *dir);//borra una pelicula del sistema
void borra_horario(char horarios[7][15][38], int colores[7][15][38], char caracter, int color);//borra los caracteres de una pelicula que ya eliminaste, del horario
void modifica_pelicula(pelicula *A, sala B[SALAS], char G[5][N], char C[6][5], char horarios[7][15][38], int colores[7][15][38], char caracter, int color);
int imprimir_funciones(pelicula A[20], int dir, sala B[15], char dias[7][N], char tipo[N]);
void imprimir_leyenda(pelicula A[20], int dir);
void borra_funcion_pelicula(sala B[15], char nombre[N]);
void imprimir_cartelera(sala B[15], char dias[7][N]);
void imprimir_sala(sala B, char dias[7][N]);
void comprar_boleto(pelicula *A, sala B[15], boleto C[1000], char tipos[N], int *dir_boletos, int n_clasificaciones[6], char clasifaciones[6][5]);
funcion * buscar_funcion(sala B[15], int h_i, int m_i, char nombre_pelicula[N], int dia, char tipo[N], int *sala);
void imprimir_asientos(char M[10][8], int c, int r);
int comprobar_boleto_no_repite(int n, boleto C[1000], int dir);
void imprimir_boleto(boleto C);
int comprueba_clasificacion(char clasificacion[5], char clasificaciones[6][5]);
pelicula * ordenar_por_ventas(pelicula A[15], int dir);//imprime cuanto dinero han generado las peliculas y devuelve un puntero a la pelicula mas vendida

int main()
{
    srand(time(NULL));
    printf("Introduce la zona en la que estas: ");
    char zona[N];
    gets(zona);
    time_t actual;
    time(&actual);
    struct tm *local = localtime(&actual);
    int horas, minutos, segundos, dia, mes, ano;
    horas=local->tm_hour;
    minutos=local->tm_min;
    segundos=local->tm_sec;
    dia=local->tm_mday;
    mes=local->tm_mon+1;
    ano=local->tm_year+1900;
    system("cls");
    char generos[5][N]={"Accion", "Fantasia", "Ciencia Ficcion", "Historia, Romance"};
    char clasificaciones[6][5]={"AA", "A", "B", "B15", "C", "D"};
    char idiomas[3][N]={"Espa\xA4ol","Ingles","Japones"};
    char dias_semana[7][N]={"Lunes","Martes","Miercoles","Jueves","Viernes","Sabado","Domingo"};
    char tipos_funcion[4][N]={"Tradicional", "Premium", "3D", "IMAX"};
    char horarios[7][SALAS][38]={'\0'};
    int colores[7][SALAS][38]={0};
    int dir_boletos=0;
    boleto Boletos[1000];
    botana Botanas[40];
    int dir = 0;
    sala Salas[SALAS]={NULL};
    int ventas_clasificaciones[6]={0};
    for(int i=0;i<15;++i)//inicia todas las matrices de asientos con 'o'
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                memset(Salas[i].Funciones[j][k].asientos, 'o', sizeof(Salas[i].Funciones[j][k].asientos));
            }
        }
    }
    pelicula Peliculas[20];
    pelicula *pelicula_aux;
    int opcion;
    int sala;
    int tipo_funcion;
    if(minutos>=10)
        minutos=minutos/10;
    do
    {
        int pos_aux;
        printf("Bienvenido al sistema de control de cines. Estas en la zona: %s\n", zona);
        printf("Hoy estamos a: %d/%d/%d\n", dia, mes, ano);
        if(minutos>=10)
            printf("Ultima hora registrada: %d:%d0\n", horas, minutos);
        else
           printf("Ultima hora registrada: %d:0%d\n", horas, minutos);
        printf("Introduce una opcion:\n1.Opciones de trabajador.\n2.Opciones de cliente\n0.Salir ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                do
                {
                    system("cls");
                    printf("Introduce una opcion:\n1.Dar de alta una pelicula\n2.Imprime el horario de las peliculas del dia de hoy\n"
                   "3.Llenar una sala para una pelicula.\n4.Imprimir peliculas\n5.Borrar pelicula\n6.Modificar algo de una pelicula\n7.Imprimir toda la cartelera\n"
                   "8.Imprimir una sala en particular.\n9.Imprimir reporte por clasificacion.\n10.Imprimir reporte de ventas por pelicula.");
                    scanf("%d",&opcion);
                    system("cls");
                    switch(opcion)
                    {
                        case 1:
                            printf("Caracteres ya ocupados: \n");
                            if(dir==0)
                                puts("No hay peliculas registradas aun");
                            else
                                imprimir_leyenda(Peliculas, dir);
                            llena_pelicula(Peliculas, generos, clasificaciones, &dir);
                        break;
                        case 2:
                            printf("Introduce que dia quieres imprimir:\n1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo ");
                            scanf("%d",&opcion);
                            system("cls");
                            imprimir_horario(horarios, colores, dias_semana, --opcion);
                            printf("Caracteres ya ocupados: \n");
                            imprimir_leyenda(Peliculas, dir);
                        break;
                        case 3:
                            for(int i=0;i<dir;++i)
                            {
                                printf("Pelicula: %d\n", i+1);
                                imprimir_pelicula(Peliculas[i]);
                            }
                            pos_aux=buscar_pelicula_nombre(Peliculas, dir);
                            if(pos_aux!=-1)
                                llena_sala(Peliculas[pos_aux], Salas, idiomas, dias_semana, tipos_funcion, horarios, colores);
                            else
                                puts("No se encontro esa pelicula, y no se pudo llenar la sala");
                        break;
                        case 4:
                            if(dir==0)
                                puts("No tienes peliculas");
                            for(int i=0;i<dir;++i)
                            {
                                printf("Pelicula: %d\n", i+1);
                                imprimir_pelicula(Peliculas[i]);
                            }
                        break;
                        case 5:
                            borra_pelicula(Peliculas, horarios, colores, &dir);
                        break;
                        case 6:
                            pos_aux=buscar_pelicula_nombre(Peliculas, dir);
                            if(pos_aux!=-1)
                                modifica_pelicula(&Peliculas[pos_aux], Salas, generos, clasificaciones, horarios,
                                colores, Peliculas[pos_aux].caracter, Peliculas[pos_aux].caracter);
                            else
                                puts("No se encontro esa pelicula.");
                        break;
                        case 7:
                            imprimir_cartelera(Salas, dias_semana);
                        break;
                        case 8:
                            printf("Introduce el numero de sala que quieres imprimir: ");
                            scanf("%d", &sala);
                            imprimir_sala(Salas[--sala], dias_semana);
                        break;
                        case 9:
                            for(int i=0;i<6;++i)
                            {
                                printf("La clasificacion %s ha vendido %d peliculas\n", clasificaciones[i], ventas_clasificaciones[i]);
                            }
                        break;
                        case 10:
                            pelicula_aux=ordenar_por_ventas(Peliculas, dir);
                            printf("La pelicula mas vendida es %s, ha generado $%u\n", pelicula_aux->nombre, pelicula_aux->ventas);
                        break;
                        default:
                            puts("Opcion incorrecta");
                        break;
                    }
                    printf("Presiona cualquier tecla para continuar. \n");
                    fflush(stdin);
                    getch();
                    system("cls");
                }while(opcion!=10);
            break;
            case 2:
                do
                {
                    system("cls");
                    printf("Introduce una opcion:\n1.Imprimir todas las funciones de una pelicula\n2.Comprar boletos para una pelicula.\n"
                           "3.Imprimir boleto por su codigo\n10.Salir\n");
                    scanf("%d",&opcion);
                    switch(opcion)
                    {
                        case 1:
                            printf("Que tipo de funcion quieres quieres buscar?\n1.Para tradicional.\n2.Para premium.\n3.Para 3D.\n4.Para IMAX ");
                            scanf("%d", &tipo_funcion);
                            imprimir_funciones(Peliculas, dir, Salas, dias_semana, tipos_funcion[--tipo_funcion]);
                        break;
                        case 2:
                            printf("Que tipo de funcion quieres quieres buscar?\n1.Para tradicional.\n2.Para premium.\n3.Para 3D.\n4.Para IMAX ");
                            scanf("%d", &tipo_funcion);
                            pos_aux=imprimir_funciones(Peliculas, dir, Salas, dias_semana, tipos_funcion[--tipo_funcion]);
                            if(pos_aux!=-1)
                            {
                                comprar_boleto(&Peliculas[pos_aux], Salas, Boletos, tipos_funcion[tipo_funcion], &dir_boletos, ventas_clasificaciones, clasificaciones);
                            }
                        break;
                        case 10:
                        break;
                        default:
                            puts("Opcion incorrecta");
                        break;
                    }
                    printf("Presiona cualquier tecla para continuar. \n");
                    fflush(stdin);
                    getch();
                    system("cls");
                }while(opcion!=10);
            break;
            default:
                puts("Opcion incorrecta");
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

void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char dias[7][N], char tipo[3][N], char horarios[7][15][38], int colores[7][15][38])
{
    int sala;
    printf("A que sala le quieres asignar la funcion: ");
    scanf("%d",&sala);
    --sala;
    int dia;
    printf("Introduce que dia quieres llenar:\n1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo ");
    scanf("%d",&dia);
    --dia;
    int funciones_max=19*60/(A.duracion+30)-B[sala].n_funciones[dia];
    int funciones;
    int minutos;
    int horas;
    if(funciones_max==0)
    {
        puts("No quedan funciones disponibles para esta sala");
        return;
    }
    do
    {
        printf("Para la sala %d cuantas funciones quieres asignar para el %s.\nTienes como maximo %d funciones para la pelicula %s.\n"
               "La sala lleva %d funcion(es) ocupadas. ", sala+1, dias[dia], funciones_max, A.nombre, B[sala].n_funciones[dia]);
        scanf("%d",&funciones);
        if(funciones>funciones_max)
            printf("Superas el limite de funciones maximas\n");
    }while(funciones>funciones_max);
    for(int i=B[sala].n_funciones[dia];i<B[sala].n_funciones[dia]+funciones;++i)//llena una sala con una funcion
    {
        strcpy(B[sala].Funciones[dia][i].nombre_pelicula, A.nombre);
        int n_intervalos, a;
        int se_puede;
        do
        {
            printf("A que hora comienza la pelicula? (introduce hora y minutos en formato 24 hrs, en intervalos de 30, no uses \":\""
                   " Se abre a las 8:00 am, se cierra a las 1 am, a menos que sea estreno, entonces se cierra a las 3 am): ");
            scanf("%d %d", &horas, &minutos);
            n_intervalos=(A.duracion+30)/30+1;
            a=convierte_hora(horas, minutos);
            se_puede=comprueba_horario(horarios[dia][sala], a, a+n_intervalos);
            if(se_puede)
                puts("Ya hay una funcion en ese intervalo de tiempo");
        }while(se_puede);
        B[sala].Funciones[dia][i].h_i=horas;
        if(minutos==30)
            B[sala].Funciones[dia][i].min_in=(minutos-27);
        printf("Introduce el doblaje de la pelicula y el subtitulado:\n1.Espa%col\n2.Ingles\n3.Japones\nSi no esta, deja un 4. ", 164);
        scanf("%d %d", &horas, &minutos);
        fflush(stdin);
        if(horas<4)
            strcpy(B[sala].Funciones[dia][i].idioma_funcion.doblaje, idiomas[horas-1]);
        else
        {
            printf("Introduce tu idioma para doblaje: ");
            gets(B[sala].Funciones[dia][i].idioma_funcion.doblaje);
        }
        fflush(stdin);
        if(minutos<4)
            strcpy(B[sala].Funciones[dia][i].idioma_funcion.subtitulado, idiomas[minutos-1]);
        else
        {
            printf("Introduce tu idioma para subtitulos: ");
            gets(B[sala].Funciones[dia][i].idioma_funcion.subtitulado);
        }
        if(sala<=9)
            strcpy(B[sala].Funciones[dia][i].tipo, tipo[0]);
        else if(sala>=10&&sala<=12)
            strcpy(B[sala].Funciones[dia][i].tipo, tipo[1]);
        else if(sala==13)
            strcpy(B[sala].Funciones[dia][i].tipo, tipo[2]);
        else
            strcpy(B[sala].Funciones[dia][i].tipo, tipo[3]);
        for(int j=a;j<a+n_intervalos;++j)//llena la matriz de horarios
        {
            horarios[dia][sala][j]=A.caracter;
            colores[dia][sala][j]=A.color;
        }
    }
    B[sala].n_funciones[dia]+=funciones;
}

void imprimir_horario(char horarios[7][15][38], int colores[7][15][38], char dias[7][N], int dia)
{
    puts(dias[dia]);
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colores[dia][i][j]-1);
            if(j==0)
                printf("%2c", horarios[dia][i][j]);
            else if((j>0&&j<4)||j>=32)
                printf("%5c", horarios[dia][i][j]);
            else if(j>=4&&j<32)
                printf("%6c", horarios[dia][i][j]);
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
    printf("Nombre: %s\n", A.nombre);
    printf("Genero: %s\n", A.genero);
    printf("Fecha de estreno: %d/%d/%d\n", A.dia, A.mes, A.ano);
    printf("Duracion: %d minutos\n", A.duracion);
    printf("Clasificacion: %s\n", A.clasificacion);
    printf("Caracter asignado: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), A.color-1);
    printf("%c\n", A.caracter);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("Dinero generado: $%u\n", A.ventas);
}

void borra_pelicula(pelicula A[20], char horarios[7][15][38], int colores[7][15][38], int *dir)
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

void borra_horario(char horarios[7][15][38], int colores[7][15][38], char caracter, int color)
{
    for(int k=0;k<7;++k)
    {
        for(int i=0;i<15;++i)
        {
            for(int j=0;j<38;++j)
            {
                if(horarios[k][i][j]==caracter&&colores[k][i][j]==color)
                {
                    horarios[k][i][j]='\0';
                }
            }
        }
    }
}

void borra_funcion_pelicula(sala B[15], char nombre[N])
{
    char nombre_aux[N]={'\0'};
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                if(strcmp(nombre, B[i].Funciones[j][k].nombre_pelicula)==0)
                {
                    --B[i].n_funciones[j];
                    strcpy(B[i].Funciones[j][k].nombre_pelicula, nombre_aux);
                    strcpy(B[i].Funciones[j][k].idioma_funcion.doblaje, nombre_aux);
                    strcpy(B[i].Funciones[j][k].idioma_funcion.subtitulado, nombre_aux);
                    memset(B[i].Funciones[j][k].asientos, '\0', sizeof(B[i].Funciones[j][k].asientos));
                    B[i].Funciones[j][k].asientos_ocupados=0;
                    B[i].Funciones[j][k].h_i=0;
                    B[i].Funciones[j][k].min_in=0;
                }
            }
        }
    }
}


void modifica_pelicula(pelicula *A, sala B[SALAS], char G[5][N], char C[6][5], char horarios[7][15][38], int colores[7][15][38], char caracter, int color)
{
    int opcion;
    printf("Estas modificando la pelicula: %s.\nQue quieres modificar de esta pelicula?\n1.Nombre\n2.Genero\n3.Fecha de estreno\n"
           "4.Duracion\n5.Clasificacion\n6.Caracter\n7.Color ", A->nombre);
    scanf("%d",&opcion);
    char nombre_aux[N];
    char caracter_aux;
    int color_aux;
    switch(opcion)
    {
        case 1:
            printf("Introduce el nombre por el que quieres sustituir la pelicula: ");
            fflush(stdin);
            gets(nombre_aux);
            for(int i=0;i<15;++i)
            {
                for(int j=0;j<7;++j)
                {
                    for(int k=0;k<10;++k)
                    {
                        if(strcmp(A->nombre, B[i].Funciones[j][k].nombre_pelicula)==0)
                        {
                            strcpy(B[i].Funciones[j][k].nombre_pelicula, nombre_aux);
                        }
                    }
                }
            }
            strcpy(A->nombre, nombre_aux);
        break;
        case 2:
            printf("Introduce el genero de la pelicula:\n1.Para Accion\n2.Para Fantasia\n"
                   "3.Ciencia Ficcion\n4.Historia\n5.Romance\nSi no esta uno, presiona 6\n");
            int genero;
            scanf("%d",&genero);
            if(genero<=5)
                strcpy(A->genero, G[genero-1]);
            else
            {
                printf("Introduce el genero: ");
                fflush(stdin);
                gets(A->genero);
            }
        break;
        case 3:
            printf("Introduce la nueva fecha de estreno: ");
            scanf("%d %d %d", &A->dia, &A->mes, &A->ano);
        break;
        case 4:
            printf("ADVERTENCIA: MODIFICAR LA DURACION DE UNA PELICULA ELIMINARA TODAS LAS FUNCIONES YA ESTABLECIDAS DE LA MISMA");
            printf("\nIntroduce la nueva duracion en minutos: ");
            scanf("%d", &A->duracion);
            borra_horario(horarios, colores, A->caracter, A->color);
            borra_funcion_pelicula(B, A->nombre);
        break;
        case 5:
            printf("Introduce la nueva clasificacion:\n1. AA: Peliculas para todo publico, generalmente para menores de 7 a%cos.\n"
            "2. A: Peliculas para todo publico\n3. B: Peliculas para adolescentes de 12 a%cos en adelante\n"
            "4. B15: Pelicula para menores de 15 a%cos\n5. C: Peliculas para mayores de 18 a%cos\n"
            "6. D: Peliculas exclusivas para adultos.\n", 164, 164, 164, 164);
            scanf("%d", &genero);
            strcpy(A->clasificacion, C[genero-1]);
        break;
        case 6:
            printf("Introduce el nuevo caracter de la pelicula: ");
            fflush(stdin);
            scanf("%c", &caracter_aux);
            for(int k=0;k<7;++k)
            {
                for(int i=0;i<15;++i)
                {
                    for(int j=0;j<38;++j)
                    {
                        if(horarios[k][i][j]==A->caracter)
                        {
                            horarios[k][i][j]=caracter_aux;
                        }
                    }
                }
            }
            A->caracter=caracter_aux;
        break;
        case 7:
            printf("Introduce el nuevo color:\n1.Negro\n"
           "2.Azul\n3.Verde\n4.Cyan\n5.Rojo\n6.Magenta\n"
           "7.Marron\n8.Gris Claro\n");
            scanf("%d", &color_aux);
            for(int k=0;k<7;++k)
            {
                for(int i=0;i<15;++i)
                {
                    for(int j=0;j<38;++j)
                    {
                        if(colores[k][i][j]==A->color)
                        {
                            colores[k][i][j]=color_aux;
                        }
                    }
                }
            }
            A->color=color_aux;
        break;
        default:
            puts("Opcion incorrecta");
        break;
    }
}

int imprimir_funciones(pelicula A[20], int dir, sala B[15], char dias[7][N], char tipo[N])
{
    char nombre[N];
    int pos=buscar_pelicula_nombre(A, dir);
    if(pos==-1)
    {
        puts("No se encontro la pelicula");
        return -1;
    }
    else
    {
        strcpy(nombre, A[pos].nombre);
    }
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                if(strcmp(nombre, B[i].Funciones[j][k].nombre_pelicula)==0&&strcmp(tipo, B[i].Funciones[j][k].tipo)==0)
                {
                    printf("%s disponible en la sala %d. %s a las: %d:%d0.\nTipo de funcion: %s\n", B[i].Funciones[j][k].nombre_pelicula, i+1, dias[j],
                    B[i].Funciones[j][k].h_i, B[i].Funciones[j][k].min_in, B[i].Funciones[j][k].tipo);
                    printf("Doblaje: %s Subtitulos: %s\n", B[i].Funciones[j][k].idioma_funcion.doblaje, B[i].Funciones[j][k].idioma_funcion.subtitulado);
                }
            }
        }
    }
    return pos;
}

void imprimir_leyenda(pelicula A[N], int dir)
{
    for(int i=0;i<dir;++i)
    {
        printf("Pelicula: %s\n", A[i].nombre);
        printf("Caracter: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), A[i].color-1);
        printf("%c", A[i].caracter);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        puts("");
    }
}

void imprimir_cartelera(sala B[15], char dias[7][N])
{
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                if(B[i].Funciones[j][k].nombre_pelicula[0]!='\0')
                {
                    printf("%s disponible en la sala %d. %s a las: %d:%d0.\nTipo de funcion: %s\n", B[i].Funciones[j][k].nombre_pelicula,
                           i+1, dias[j],
                    B[i].Funciones[j][k].h_i, B[i].Funciones[j][k].min_in, B[i].Funciones[j][k].tipo);
                    printf("Doblaje: %s Subtitulos: %s\n", B[i].Funciones[j][k].idioma_funcion.doblaje,
                           B[i].Funciones[j][k].idioma_funcion.subtitulado);
                }
            }
        }
    }
}

void imprimir_sala(sala B, char dias[7][N])
{
    for(int i=0;i<7;++i)
    {
        printf("%s: Hay %d funciones este dia\n", dias[i], B.n_funciones[i]);
        for(int j=0;j<10;++j)
        {
            if(B.Funciones[i][j].nombre_pelicula[0]!='\0')
            {
                printf("%s disponible en la sala %d. %s a las: %d:%d0 \n", B.Funciones[i][j].nombre_pelicula, j+1, dias[i],
                       B.Funciones[i][j].h_i, B.Funciones[i][j].min_in);
                printf("Doblaje: %s Subtitulos: %s\n", B.Funciones[i][j].idioma_funcion.doblaje,
                        B.Funciones[i][j].idioma_funcion.subtitulado);
            }
        }
    }
}

funcion * buscar_funcion(sala B[15], int h_i, int m_i, char nombre_pelicula[N], int dia, char tipo[N], int *sala)
{
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                if(strcmp(B[i].Funciones[j][k].nombre_pelicula, nombre_pelicula)==0
                &&h_i==B[i].Funciones[j][k].h_i
                &&m_i==B[i].Funciones[j][k].min_in&&dia==j
                &&strcmp(B[i].Funciones[j][k].tipo, tipo)==0)
                {
                    *sala=i;
                    return &B[i].Funciones[j][k];
                }
            }
        }
    }
    return  NULL;
}

void imprimir_asientos(char M[10][8], int c, int r)//grande: 10x8 chica: 4x6
{
    puts("\t\t\tPANTALLA\n");
    for(int i=0;i<r;++i)
    {
        printf("   %c\t\t", 65+i);
        for(int j=0;j<c;++j)
        {
            if(j==4)
                printf("\t");
            printf("%c ", M[i][j]);
        }
        puts("");
    }
    if(c==4)
        puts("\n\t\t1 2 3 4\n");
    else
        puts("\n\t\t1 2 3 4\t\t5 6 7 8\n");
}

void comprar_boleto(pelicula *A, sala B[15], boleto C[1000], char tipos[N], int *dir_boletos, int n_clasificaciones[6], char clasifaciones[6][5])
{
    if(*dir_boletos==1000)
    {
        puts("Ya no se pueden vender mas boletos");
        return;
    }
    else
    {
        int h_i;
        int m_i;
        int dia_semana;
        int boletos_comprar;
        int n_sala;
        int opcion;
        funcion *funcion_aux;
        printf("Introduce el dia de tu funcion:\n1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo ");
        scanf("%d", &dia_semana);
        printf("A que hora comienza la pelicula? (introduce hora y minutos en formato 24 hrs, en intervalos de 30, no uses \":\""
               "Se abre a las 8:00 am, se cierra a las 1 am, a menos que sea estreno, entonces se cierra a las 3 am): ");
        scanf("%d %d", &h_i, &m_i);
        funcion_aux=buscar_funcion(B, h_i, m_i, A->nombre, --dia_semana, tipos, &n_sala);
        if(funcion_aux!=NULL)
        {
            printf("Introduce cuantos boletos vas a comprar: ");
            scanf("%d", &boletos_comprar);
            printf("Cuentas con alguna tarjeta?\n1.Si\n0.No ");
            scanf("%d", &opcion);
            float descuento=1.00;
            if(opcion)
            {
                printf("Con cual tarjeta cuentas?\n1.Estandar\n2.Premium\n3.VIP ");
                scanf("%d", &opcion);
                if(opcion==1)
                    descuento=0.95;
                else if(opcion==2)
                    descuento=0.90;
                else
                    descuento=0.85;
            }
            for(int i=*dir_boletos; i<*dir_boletos+boletos_comprar; ++i)
            {
                if(n_sala<=9)
                    imprimir_asientos(funcion_aux->asientos, 8, 10);
                else
                    imprimir_asientos(funcion_aux->asientos, 4, 6);
                printf("Introduce el precio inicial del boleto: ");
                scanf("%f", &C[*dir_boletos].precio);
                C[*dir_boletos].precio*=descuento;
                fflush(stdin);
                printf("Introduce la fila: ");
                scanf("%c", &C[*dir_boletos].fila);
                printf("Introduce la columna: ");
                scanf("%d", &C[*dir_boletos].columna);
                C[*dir_boletos].fila=toupper(C[*dir_boletos].fila);
                funcion_aux->asientos[C[*dir_boletos].fila-65][--C[*dir_boletos].columna]='x';
                do
                {
                    C[*dir_boletos].codigo_boleto=1+rand()%1000;
                }while(comprobar_boleto_no_repite(C[*dir_boletos].codigo_boleto, C, *dir_boletos));
                C[*dir_boletos].h_i=funcion_aux->h_i;
                C[*dir_boletos].min_i=funcion_aux->min_in;
                C[*dir_boletos].num_sala=n_sala;
                strcpy(C[*dir_boletos].nombre_pelicula, funcion_aux->nombre_pelicula);
                strcpy(C[*dir_boletos].tipo_funcion, funcion_aux->tipo);
                imprimir_boleto(C[*dir_boletos]);
                A->ventas+=C[*dir_boletos].precio;
                ++n_clasificaciones[comprueba_clasificacion(A->clasificacion, clasifaciones)];
                printf("Introduce cualquier tecla para continuar ");
                getch();
                system("cls");
            }
            (*dir_boletos)+=boletos_comprar;
        }
        else
        {
            puts("No has registrado esa funcion");
            return;
        }
    }
}
void imprimir_boleto(boleto C)
{
    printf("Codigo del boleto: %d\n", C.codigo_boleto);
    printf("Hora de la pelicula: %d:%d0 \n", C.h_i, C.min_i);
    printf("Numero de sala: %d\n", C.num_sala+1);
    printf("Fila y columna del asiento: %c%d\n", C.fila, C.columna+1);
    printf("Nombre de la pelicula: %s\n", C.nombre_pelicula);
    printf("Tipo de funcion: %s\n", C.tipo_funcion);
    printf("Precio final: %g\n", C.precio);
}

int comprobar_boleto_no_repite(int n, boleto C[1000], int dir)
{
    for(int i=0;i<dir;++i)
    {
        if(C[i].codigo_boleto==n)
            return 1;
    }
    return 0;
}

int comprueba_clasificacion(char clasificacion[5], char clasificaciones[6][5])
{
    for(int i=0;i<6;++i)
    {
        if(strcmp(clasificacion, clasificaciones[i])==0)
        {
            return i;
        }
    }
}

pelicula * ordenar_por_ventas(pelicula A[15], int dir)
{
    pelicula aux;
    for(int i=0;i<dir-1;++i)
    {
        for(int j=0;j<dir-1;++j)
        {
            if(A[j].ventas<A[j].ventas)
            {
                aux=A[j];
                A[j]=A[j+1];
                A[j+1]=aux;
            }
        }
    }
    for(int i=0;i<dir;++i)
    {
        printf("Pelicula: %s. Ventas: $%u\n", A[i].nombre, A[i].ventas);
    }
    int mayor=A[0].ventas;
    int n=0;
    for(int i=0;i<dir;++i)
    {
        if(A[i].ventas>mayor)
        {
            mayor=A[i].ventas;
            n=i;
        }
    }
    return &A[n];
}
