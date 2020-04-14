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
    int boletos_ocupados;
    int h_i;
    int min_in;  //sala 1 //LOL Español Japones 12 00 15 00
};
typedef struct struct_funcion funcion;
// *       *     *    *     *
struct struct_sala
{
    char tamano[N];
    char tipo[N];
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
    char clasificacion[N];
    char caracter;
    int color;
    unsigned int boletos_vendidos;
};
typedef struct struct_pelicula pelicula;//Hola soy Montse

struct struct_boleto
{
    char nombre_pelicula[N];
    char tipo_sala[N];
    int num_sala;
    float precio;
    char fila;
    int columna;
    int h_i, min_i;
    int codigo_boleto;
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void llena_pelicula(pelicula A[20], char G[5][N], char C[6][5], int *dir);//da de alta una pelicula
void imprimir_pelicula(pelicula A);//imprime una pelicula
int buscar_pelicula_nombre(pelicula A[20], int dir);//busca una pelicula por su nombre y regresa su posicion
void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char dias[7][N], char horarios[7][15][38], int colores[7][15][38]);//llena una sala con funciones de una pelicula
void imprimir_horario(char horarios[7][15][38], int colores[7][15][38], char dias[7][N], int dia);//imprime el horario general del dia
int comprueba_horario(char horarios[38], int a, int b);//comprueba si una pelicula cabe en un intervalo
int convierte_hora(int horas, int minutos);//convierte una hora a una posicion de la matriz
void borra_pelicula(pelicula A[20], char horarios[7][15][38], int colores[7][15][38], int *dir);//borra una pelicula del sistema
void borra_horario(char horarios[7][15][38], int colores[7][15][38], char caracter, int color);//borra los caracteres de una pelicula que ya eliminaste, del horario
void modifica_pelicula(pelicula *A, sala B[SALAS], char G[5][N], char C[6][5], char horarios[7][15][38], int colores[7][15][38], char caracter, int color);
int imprimir_funciones(pelicula A[20], int dir, sala B[15], char dias[7][N]);
void imprimir_leyenda(pelicula A[20], int dir);
void borra_funcion_pelicula(sala B[15], char nombre[N]);
void imprimir_cartelera(sala B[15], char dias[7][N]);
void imprimir_sala(sala B, char dias[7][N]);
void comprar_boleto(pelicula A, sala B[15], boleto C[1000], int *dir_boletos);
funcion * buscar_funcion(sala B[15], int h_i, int m_i, char nombre_pelicula[N], int dia, int *sala);
void imprimir_asientos(char M[10][8]);
void imprimir_botanas (botana C[100],char [7][N], char [3][N]);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    int ventas_clasificaciones[6]={0};
    char idiomas[3][N]={"Espa\xA4ol","Ingles","Japones"};
    char dias_semana[7][N]={"Lunes","Martes","Miercoles","Jueves","Viernes","Sabado","Domingo"};
    char productos [7][N]={"Palomitas","Refrescos","Nachos","Hot Dog","Chocolate","Helado","Crepas"};
    char tamanos_palomitas_refresco [3][N] ={"Grande","Mediano","Pequeno"};
    char horarios[7][SALAS][38]={'\0'};
    int colores[7][SALAS][38]={0};
    int dir_boletos=0;
    pelicula pelicula_venta;
    boleto Boletos[1000];
    botana C[100];
    int dir = 0;
    sala Salas[SALAS]={NULL};
    for(int i=0;i<15;++i)//inicia todas las matrices de asientos con 'o'
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                memset(Salas[i].Funciones[j][k].asientos, 'O', sizeof(Salas[i].Funciones[j][k].asientos));
            }
        }
    }
    pelicula Peliculas[20];
    int opcion,opcionh,ver;
    int sala;
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
                    printf("\t>>MENU<<\nIntroduce una opcion:\nSelecciona CERO para salir\n1.Dar de alta una pelicula\n2.Imprime el horario de las peliculas del dia de hoy\n"
                   "3.Llenar una sala para una pelicula.\n4.Imprimir peliculas\n5.Borrar pelicula\n6.Modificar algo de una pelicula\n7.Imprimir toda la cartelera\n"
                   "8.Imprimir una sala en particular.\n9.Realizar una venta de boletos\n10. Compra de botanas\nOpcion seleccionada: ");
                    scanf("%d",&opcion);
                    system("cls");
                    switch(opcion)
                    {
                        case 0:
                            printf ("Gracias por usar el programa");
                        break;
                        case 1://Da de alta una pelicula
                            printf("Caracteres ya ocupados: \n");
                            if(dir==0)
                                puts("No hay peliculas registradas aun");
                            else
                                imprimir_leyenda(Peliculas, dir);
                            llena_pelicula(Peliculas, generos, clasificaciones, &dir);
                        break;
                        case 2://Imprime los horarios
                            printf("Selecciona el dia que quieras ver su horario :\n1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo ");
                            scanf("%d",&opcionh);
                            system("cls");
                            imprimir_horario(horarios, colores, dias_semana, --opcionh);
                            printf("Caracteres ya ocupados: \n");
                            imprimir_leyenda(Peliculas, dir);
                        break;
                        case 3://Llena una sala para una pélicula
                            for(int i=0;i<dir;++i)
                            {
                                printf("Pelicula: %d\n", i+1);
                                imprimir_pelicula(Peliculas[i]);
                            }
                            pos_aux=buscar_pelicula_nombre(Peliculas, dir);
                            if(pos_aux!=-1)
                                llena_sala(Peliculas[pos_aux], Salas, idiomas, dias_semana, horarios, colores);
                            else
                                puts("No se encontro esa pelicula, por lo tanto no se pudo llenar la sala");
                        break;
                        case 4://Imprime peliculas disponibles
                            if(dir==0)
                                puts("No tienes peliculas");
                            for(int i=0;i<dir;++i)
                            {
                                printf ("\n------------------------------------\n");
                                printf("Pelicula: %d\n", i+1);
                                imprimir_pelicula(Peliculas[i]);
                                 printf ("\n------------------------------------\n");
                            }
                        break;
                        case 5://borra pelicula
                            borra_pelicula(Peliculas, horarios, colores, &dir);
                        break;
                        case 6://modifica pelicula
                            pos_aux=buscar_pelicula_nombre(Peliculas, dir);
                            if(pos_aux!=-1)
                                modifica_pelicula(&Peliculas[pos_aux], Salas, generos, clasificaciones, horarios,
                                colores, Peliculas[pos_aux].caracter, Peliculas[pos_aux].caracter);
                            else
                                puts("No se encontro esa pelicula.");
                        break;
                        case 7://imprime cartelera
                            printf ("----------- >> C A R T E L E R A << ----------");
                            imprimir_cartelera(Salas, dias_semana);
                        break;
                        case 8://Imprime sala
                            printf("Introduce el numero de sala que quieres imprimir: ");
                            scanf("%d", &sala);
                            imprimir_sala(Salas[--sala], dias_semana);
                            printf ("Deseas vizualizar el tamaño de la sala y el tipo?\n-Presiona 1 para SI\n-Presiona cualquier otro numero para NO\nOpcion seleccionda: ");
                            scanf("%d",&ver);
                            if (ver==1)
                            {
                                printf ("\nLas salas 1 a 10 son salas normales\nLas salas 11 y 12 son salas IMAX\nLas salas 13 a 15 son salas VIP\n");
                                imprimir_asientos(Salas[0].Funciones[0][0].asientos);
                            }
                        break;
                        case 9://compra de boletos
                            pos_aux=buscar_pelicula_nombre(Peliculas,dir);
                            if (pos_aux!=-1)
                            {
                                printf ("-------- >>Cartelera auxiliar<< ------");
                                imprimir_cartelera(Salas, dias_semana);
                                strcpy(pelicula_venta.nombre,Peliculas[pos_aux].nombre);
                                comprar_boleto(pelicula_venta,Salas,Boletos,&dir_boletos);
                                //imprimir_asientos(Salas[0].Funciones[0][0].asientos);
                            }
                            else
                            {
                                printf ("\nPor el momento no se encuentra esa pelicula\n");
                            }

                        break;
                        case 10:
                            imprimir_botanas(C,productos,tamanos_palomitas_refresco);
                            break;
                        default:
                            puts("Opcion incorrecta");
                        break;
                    }
                    printf("Presiona cualquier tecla para continuar. \n");
                    fflush(stdin);
                    getch();
                    system("cls");
                }while(opcion!=0);
            break;
            case 2:
                do
                {
                    system("cls");
                    printf("Introduce una opcion:\n1.Imprimir todas las funciones de una pelicula\n2.Comprar boletos para una pelicula.\n10.Salir\n");
                    scanf("%d",&opcion);
                    switch(opcion)
                    {
                        case 1:
                            imprimir_funciones(Peliculas, dir, Salas, dias_semana);
                        break;
                        case 2:
                            pos_aux=imprimir_funciones(Peliculas, dir, Salas, dias_semana);
                            if(pos_aux!=-1)
                            {
                                comprar_boleto(Peliculas[pos_aux], Salas, Boletos, &dir_boletos);
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void llena_pelicula(pelicula A[20], char G[5][N], char C[6][5], int *dir)
{
    int genero,clasifica;
    if(dir==20)
    {
        puts("Ya no caben mas peliculas, lo sentimos");
        return;
    }
    printf("Introduce el nombre de la pelicula: ");
    fflush(stdin);
    gets(A[*dir].nombre);
    do{printf("Introduce el genero de la pelicula:\n1.Para Accion\n2.Para Fantasia\n"
           "3.Ciencia Ficcion\n4.Historia\n5.Romance\nSi no esta uno, presiona 6\n");
    scanf("%d",&genero);
    if (genero>=7)
    {printf ("Esa opcion no esta disponible\n");}} while (genero>=7);
    if(genero<=5)
        strcpy(A[*dir].genero,G[genero-1]);
    else
    {
        printf("Introduce el genero: ");
        fflush(stdin);
        gets(A[*dir].genero);
    }
    printf("Introduce la fecha en la que se estreno (dia mes y a%co con numero separado por espacios): ", 164);
    scanf("%d %d %d", &A[*dir].dia, &A[*dir].mes, &A[*dir].ano);
    do{printf("Introduce la clasificacion:\n1. AA: Peliculas para todo publico, generalmente para menores de 7 a%cos.\n"
            "2. A: Peliculas para todo publico\n3. B: Peliculas para adolescentes de 12 a%cos en adelante\n"
            "4. B15: Pelicula para menores de 15 a%cos\n5. C: Peliculas para mayores de 18 a%cos\n"
            "6. D: Peliculas exclusivas para adultos.\n", 164, 164, 164, 164);
    scanf("%d",&clasifica);
    if (clasifica>=7)
    {printf ("Esa opcion no esta disponible\n");}} while (clasifica>=7);
    strcpy(A[*dir].clasificacion, C[genero-1]);
    printf("Introduce la duracion de la pelicula en minutos: ");
    scanf("%d",&A[*dir].duracion);
    printf("Que caracter quieres asignar a esta pelicula: ");
    fflush(stdin);
    scanf("%c",&A[*dir].caracter);
    do{printf("Introduce de que colores quieres ese caracter:\n1.Negro\n"
           "2.Azul\n3.Verde\n4.Cyan\n5.Rojo\n6.Magenta\n"
           "7.Marron\n8.Gris Claro\n");
    scanf("%d",&A[*dir].color);
    if (A[*dir].color>=8)
    {printf ("Esa opcion no esta disponible\n");}} while (A[*dir].color>=8);
    ++(*dir);
}

void llena_sala(pelicula A, sala B[15], char idiomas[3][N], char dias[7][N], char horarios[7][15][38], int colores[7][15][38])
{
    int sala;
    do{printf("A que sala le quieres asignar la funcion: ");
    scanf("%d",&sala);
    if (sala>15)
    {
        printf ("Solo se cuenta con 15 salas\n");
        printf ("Intente de nuevo\n");
    }} while (sala>15);
    --sala;
    int dia;
    do{printf("Introduce que dia quieres llenar:\n1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo\nOpcion seleccionada: ");
    scanf("%d",&dia);
    if (dia>7)
    {
        printf ("Solo se cuenta con 7 dias de la semana\n");
        printf ("Intente de nuevo\n");
    }} while (dia>7);
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
                    B[i].Funciones[j][k].boletos_ocupados=0;
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

int imprimir_funciones(pelicula A[20], int dir, sala B[15], char dias[7][N])
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
                if(strcmp(nombre, B[i].Funciones[j][k].nombre_pelicula)==0)
                {
                    printf("%s disponible en la sala %d. %s a las: %d:%d0 \n", B[i].Funciones[j][k].nombre_pelicula, i+1, dias[j],
                    B[i].Funciones[j][k].h_i, B[i].Funciones[j][k].min_in);
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
                    printf ("\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ \n");
                    printf("%s disponible en la sala %d. %s a las: %d:%d0 \n", B[i].Funciones[j][k].nombre_pelicula, i+1, dias[j],
                    B[i].Funciones[j][k].h_i, B[i].Funciones[j][k].min_in);
                    printf("Doblaje: %s Subtitulos: %s\n", B[i].Funciones[j][k].idioma_funcion.doblaje, B[i].Funciones[j][k].idioma_funcion.subtitulado);
                    printf ("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
                }
            }
        }
    }
}

void imprimir_sala(sala B, char dias[7][N])
{
    printf("Tamaño: \n", B.tamano);
    printf("Tipo: \n", B.tipo);
    for(int i=0;i<7;++i)
    {
        printf("%s: Hay %d funciones este dia\n", dias[i], B.n_funciones[i]);
        for(int j=0;j<10;++j)
        {
            if(B.Funciones[i][j].nombre_pelicula[0]!='\0')
            {
                printf("%s disponible en la sala %d. %s a las: %d:%d0 \n", B.Funciones[i][j].nombre_pelicula, i+1, dias[i],
                B.Funciones[i][j].h_i, B.Funciones[i][j].min_in);
                printf("Doblaje: %s Subtitulos: %s\n", B.Funciones[i][j].idioma_funcion.doblaje, B.Funciones[i][j].idioma_funcion.subtitulado);
            }
        }
    }
}

funcion * buscar_funcion(sala B[15], int h_i, int m_i, char nombre_pelicula[N], int dia, int *sala)
{
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<7;++j)
        {
            for(int k=0;k<10;++k)
            {
                if(strcmp(B[i].Funciones[j][k].nombre_pelicula, nombre_pelicula)==0
                &&h_i==B[i].Funciones[j][k].h_i&&m_i==B[i].Funciones[j][k].min_in&&dia==j)
                {
                    return &B[i].Funciones[j][k];
                    *sala=i;
                }
            }
        }
    }
    return  NULL;
}

void imprimir_asientos(char M[10][8])
{
    int sala,i=0,j=0,letra=65,numero=1;
    printf ("Que sala desea ver? ");
    scanf ("%d",&sala);
    if (sala<11)
    {
        printf ("\t---<<P A N T A L L A>>---\n");
        for (i=0;i<7;i++)
        {
            if (i==6)
            {
                printf ("\n");
                for (int k=0;k<14;k++)
                {
                    if (k==6||k==7)
                    {printf("  ");}
                    else
                    {printf ("%3d",numero);
                    numero++;}
                }
            }
            else{
            printf ("\n");
            for (j=0;j<15;j++)
            {
                if (j==7||j==8)
                {
                   printf ("  ");
                }else if (j==0)
                {
                    printf ("%c",letra);
                    letra++;
                }
                else
                {
                   printf (" %c ",M[i][j]);
                }
            }
        }
        }
        printf ("\n\t\t\t\t\tTama%co: 6x12 ",164);
    }else if (sala>10)
    {
        printf ("  --<<P A N T A L L A>>--");
       for (int i=0;i<5;i++)
        {
            if (i==4)
            {
                printf ("\n");
                for (int k=0;k<10;k++)
                {
                    if (k==4||k==5)
                    {printf("  ");}
                    else
                    {printf ("%3d",numero);
                    numero++;}
                }
            }
            else{printf ("\n");
            for (int j=0;j<11;j++)
            {
                if(j==5||j==6)
                {
                    printf ("  ");
                }else if (j==0)
                {
                    printf ("%c",letra);
                    letra++;
                }
                else
                {
                    printf (" %c ",M[i][j]);
                }
            }
        }
    }
    printf ("\n\t\t\t    Tama%co: 4x8 ",164);
    }
    printf ("\n");
}
    /*puts("\t\t\tPANTALLA\n");
    for(int i=0;i<10;++i)
    {
        printf("   %c\t\t", 65+i);
        for(int j=0;j<8;++j)
        {
            if(j==4)
                printf("\t");
            printf("%c ", M[i][j]);
        }
        puts("");
    }
    puts("\n\t\t1 2 3 4\t\t5 6 7 8");*/


void comprar_boleto(pelicula A, sala B[15], boleto C[1000], int *dir_boletos)
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
        funcion *funcion_aux;
        printf("Introduce el dia de tu funcion:\n1.Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n6.Sabado\n7.Domingo ");
        scanf("%d", &dia_semana);
        printf("A que hora comienza la pelicula? (introduce hora y minutos en formato 24 hrs, en intervalos de 30, no uses \":\""
               "Se abre a las 8:00 am, se cierra a las 1 am, a menos que sea estreno, entonces se cierra a las 3 am): ");
        scanf("%d %d", &h_i, &m_i);
        funcion_aux=buscar_funcion(B, h_i, m_i, A.nombre, --dia_semana, &n_sala);
        if(funcion_aux!=NULL)
        {
            printf("Introduce cuantos boletos vas a comprar: ");
            scanf("%d", &boletos_comprar);
            imprimir_asientos(funcion_aux->asientos);
            for(int i=*dir_boletos; i<*dir_boletos+boletos_comprar; ++i)
            {
                printf("Introduce el precio inicial del boleto: ");
                scanf("%f", &C[*dir_boletos].precio);
                fflush(stdin);
                printf("Introduce la fila: ");
                scanf("%c", &C[*dir_boletos].fila);
                printf("Introduce la columna: ");
                scanf("%d", &C[*dir_boletos].columna);
                funcion_aux->asientos[C[*dir_boletos].fila-65][--C[*dir_boletos].columna]='o';
            }
            C[*dir_boletos].codigo_boleto=1+rand()%1000;
            C[*dir_boletos].h_i=funcion_aux->h_i;
            C[*dir_boletos].min_i=funcion_aux->min_in;
            C[*dir_boletos].num_sala=n_sala;
            strcpy(C[*dir_boletos].nombre_pelicula, funcion_aux->nombre_pelicula);
            printf("Codigo del boleto: %d\n", C[*dir_boletos].codigo_boleto);
            printf("Hora de la pelicula: %d:%d0 \n", C[*dir_boletos].h_i, C[*dir_boletos].min_i);
            printf("Numero de sala: %d\n", C[*dir_boletos].num_sala+1);
            printf("Fila y columna del asiento: %c %d\n", C[*dir_boletos].fila, C[*dir_boletos].columna);
            printf("Nombre de la pelicula: %s", C[*dir_boletos].nombre_pelicula);
            printf("Precio final: %g", C[*dir_boletos].precio);
            (*dir_boletos)+=boletos_comprar;
        }
        else
        {
            puts("No has registrado esa funcion");
            return;
        }
    }
}

void imprimir_botanas(botana C[100], char producto[7][N], char tamanos_palomitas_refresco [3][N])
{
    int i=0;
    printf ("///////////////////////////////////////////////////////////////////////////");
    printf ("\n\t----> M E N U <----");
    printf ("\n- Palomitas\n\tTipos:\n\t\t°Naturales\n\t\t°Light\n\t\t°Especial\n\t Tama%cos:\n\t\t°Peque%co\n\t\t°Mediana\n\t\t°Grande",164,164);
    printf ("\n- Refresco\n\tTipos:\n\t\t°Normal\n\t\t°Light\n\t\t°Agua\n\tTama%cos:\n\t\t°Peque%co\n\t\t°Mediana\n\t\t°Grande",164,164);
    printf ("\n- Nachos\n\tTipos:\n\t\t°Normales\n\t\t°Light\n\t\t°Con queso extra\n\tTama%cos:\n\t\t°Peque%co\n\t\t°Mediana\n\t\t°Grande",164,164);
    printf ("\n- Hot Dog");
    printf ("\n- Chocolate");
    printf ("\n- Helado\n\tTipos:\n\t\t°Vaso\n\t\t°Cono");
    printf ("\n- Crepa\n\tTipos:\n\t\t°Dulce\n\t\t°Salada\n");
    printf ("///////////////////////////////////////////////////////////////////////////");
}
