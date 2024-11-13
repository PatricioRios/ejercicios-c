/*
Ejercicio
Realizar un algoritmo que genere una tabla de doble entrada de M  * N elementos y 
se pide resolver lo siguiente:
 	Generar una lista después de haber cargado la tabla, en el cual se cargue el mayor elemento de cada fila y de cada columna.
 	Generar otra lista que indique cuantos elementos pares tiene cada fila
 	Generar otra lista que indique cuantos elementos impares tiene cada fila
 	Generar otra lista que indique cuantos elementos negativos tiene cada fila 
 	Genere otra lista donde cargue en cada celda la cantidad de elementos múltiplos de tres de cada fila.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.c"

#define N 20
#define M 20

typedef struct Board Board;

struct Board
{
    int** data;
    int filas;
    int columnas;
};

Board* new_board(int rows,int columns);

void mock_board(Board *board);

int get_most_value_of_row(int *row,int row_size);

int get_most_value_of_column(int *column, int row_size);

int get_pares_of_row(int *row, int row_size);
int get_impares_of_row(int *row, int row_size);
int get_negativos_of_row(int *row, int row_size);


int* multiple_of_three(Board *board);

void opt_add_number(void* context);
void opt_view_board(void* context);
void opt_view_most_value_of_row(void* context);
void opt_view_most_value_of_column(void* context);
void opt_view_multiple_of_three(void* context);
void opt_view_pares(void* context);
void opt_view_impares(void* context);
void opt_view_negativos(void* context);
void opt_liberate_board(void* context);
void opt_mock_board(void* context);
void opt_exit(void* context);

int main(){
    Board *board = new_board(M,N);
    mock_board(board);

      WindowOption opts[11] = {
      {"Añadir numero.", 1,                     opt_add_number},
      {"Mostrar Lista.", 2,                     opt_view_board},
      {"Ver el mayor valor de las filas.", 1,   opt_view_most_value_of_row},
      {"Ver el mayot valor de las columnas.", 8,opt_view_most_value_of_column},
      {"Mostrar multiplos de 3", 2,             opt_view_multiple_of_three},
      {"Mostrar cantidad de pares por fila", 2,                      opt_view_pares},
      {"Mostrar cantidad de impares por fila", 2,                    opt_view_impares},
      {"Mostrar cantidad de negativos por fila", 2,                  opt_view_negativos},
      {"Liberar tabla", 2,                      opt_liberate_board},
      {"Mockear tabla", 2,                      opt_mock_board},
      {"Salir.", 1,                             opt_exit}};
    WindowOptions window_options = {opts, 11};
    
    window("Programa de tabla de numeros", board, window_options);
    return 0;
}

Board* new_board(int rows,int columns){
    Board *board = malloc(sizeof(Board));
    board->filas = rows;
    board->columnas = columns;
    board->data = malloc(sizeof(int*)*rows);
    for(int i=0;i<rows;i++){
        board->data[i] = malloc(sizeof(int)*columns);
    }
    return board;
}

void mock_board(Board *board){
    for(int i=0;i<board->filas;i++){
        for(int j=0;j<board->columnas;j++){
            board->data[i][j] = rand()%100;
        }
    }
}

int get_most_value_of_row(int *row, int row_size){
    int max = row[0];
    for(int i=0;i<row_size;i++){
        if(row[i] > max){
            max = row[i];
        }
    }
    return max;
}

int get_most_value_of_column(int *column, int row_size){
    int max = column[0];
    for(int i=0;i<M;i++){
        if(column[i] > max){
            max = column[i];
        }
    }
    return max;
}

int get_impares_of_row(int *row, int row_size){
    int *impares = malloc(sizeof(int)*N);

    int number_of_impars=0;

    for(int i=0;i<N;i++){
        if(row[i] % 2 != 0){
            number_of_impars++;
        }
    }
    return number_of_impars;
}

int get_pares_of_row(int *row, int row_size){
    int *pares = malloc(sizeof(int)*N);

    int number_of_pares=0;

    for(int i=0;i<N;i++){
        if(row[i] % 2 == 0){
            number_of_pares++;
        }
    }
    return number_of_pares;
}

int get_negativos_of_row(int *row, int row_size){
    int *negativos = malloc(sizeof(int)*N);

    int number_of_negatives=0;

    for(int i=0;i<N;i++){
        if(row[i] < 0){
            number_of_negatives++;
        }
    }
    return number_of_negatives;
}

int* multiple_of_three(Board *board){
    int *multiplos = malloc(sizeof(int)*board->filas);

    for(int i=0;i<board->filas;i++){
        int count = 0;
        for(int j=0;j<board->columnas;j++){
            if(board->data[i][j] % 3 == 0){
                count++;
            }
        }
        multiplos[i] = count;
    }
    return multiplos;
}


void opt_add_number(void* context){
    Board *board = (Board*)context;
    int row,column,value;
    clear();
    topLine();
    content("Ingrese la fila:");
    midLine();
    inputLine();
    scanf("%d",&row);
    fflush(stdin);
    clear();
    topLine();
    content("Ingrese la columna:");
    midLine();
    inputLine();
    scanf("%d",&column);
    fflush(stdin);
    clear();
    topLine();
    content("Ingrese el valor:");
    midLine();
    inputLine();
    scanf("%d",&value);
    fflush(stdin);

    if(row < 0 || row >= board->filas || column < 0 || column >= board->columnas){
        clear();
        topLine();
        content("Error, fila o columna fuera de rango");
        midLine();
        waiting();
        return;
    }
    board->data[row][column] = value;
    clear();
    topLine();
    content("Valor añadido correctamente!");
    midLine();
    waiting();

}
void opt_view_board(void* context){
    Board *board = (Board*)context;
    clear();
    topLine();

    // Construir y mostrar la cabecera con los números de columna
    char header_str[1024];
    sprintf(header_str, "     ║"); // Espacio para el número de fila
    for(int j = 0; j < board->columnas; j++){
        char temp[32];
        sprintf(temp, " %5d", j); // Ancho de campo para alineación
        strcat(header_str, temp);
    }
    content("%s", header_str);
    midLine();

    // Construir y mostrar cada fila
    for(int i = 0; i < board->filas; i++){
        char row_str[1024];
        sprintf(row_str, "%4d ║", i); // Número de fila con ancho fijo
        for(int j = 0; j < board->columnas; j++){
            char temp[32];
            sprintf(temp, " %5d", board->data[i][j]); // Valor con ancho fijo
            strcat(row_str, temp);
        }
        content("%s", row_str);
    }
    midLine();
    waiting();
}

void opt_view_most_value_of_row(void* context){
    Board *board = (Board*)context;
    int *most_values = malloc(sizeof(int)*board->filas);
    for(int i=0;i<board->filas;i++){
        most_values[i] = get_most_value_of_row(board->data[i],board->columnas);
    }
    clear();
    topLine();
    content("Mayores valores de cada fila:");
    midLine();
    for(int i=0;i<board->filas;i++){
        content("Fila %d: %d",i,most_values[i]);
    }
    midLine();
    waiting();
    free(most_values);

}
void opt_view_most_value_of_column(void* context){
    Board *board = (Board*)context;
    int *most_values = malloc(sizeof(int)*board->columnas);
    for(int i=0;i<board->columnas;i++){
        int *column = malloc(sizeof(int)*board->filas);
        for(int j=0;j<board->filas;j++){
            column[j] = board->data[j][i];
        }
        most_values[i] = get_most_value_of_column(column,board->filas);
        free(column);
    }
    clear();
    topLine();
    content("Mayores valores de cada columna:");
    midLine();
    for(int i=0;i<board->columnas;i++){
        content("Columna %d: %d",i,most_values[i]);
    }
    midLine();
    waiting();
    free(most_values);
}
void opt_view_multiple_of_three(void* context){
    Board *board = (Board*)context;
    int *multiplos = multiple_of_three(board);
    clear();
    topLine();
    content("Multiplos de 3 por fila:");
    midLine();
    for(int i=0;i<board->filas;i++){
        content("Fila %d: %d",i,multiplos[i]);
    }
    midLine();
    waiting();
    free(multiplos);

}
void opt_view_pares(void* context){
    Board *board = (Board*)context;
    int *pares = malloc(sizeof(int)*board->filas);
    for(int i=0;i<board->filas;i++){
        pares[i] = get_pares_of_row(board->data[i],board->columnas);
    }
    clear();
    topLine();
    content("Pares por fila:");
    midLine();
    for(int i=0;i<board->filas;i++){
        content("Fila %d: %d",i,pares[i]);
    }
    midLine();
    waiting();
    free(pares);

}
void opt_view_impares(void* context){
    Board *board = (Board*)context;
    int *impares = malloc(sizeof(int)*board->filas);
    for(int i=0;i<board->filas;i++){
        impares[i] = get_impares_of_row(board->data[i],board->columnas);
    }
    clear();
    topLine();
    content("Impares por fila:");
    midLine();
    for(int i=0;i<board->filas;i++){
        content("Fila %d: %d",i,impares[i]);
    }
    midLine();
    waiting();
    free(impares);
}
void opt_view_negativos(void* context){
    Board *board = (Board*)context;
    int *negativos = malloc(sizeof(int)*board->filas);
    for(int i=0;i<board->filas;i++){
        negativos[i] = get_negativos_of_row(board->data[i],board->columnas);
    }
    clear();
    topLine();
    content("Negativos por fila:");
    midLine();
    for(int i=0;i<board->filas;i++){
        content("Fila %d: %d",i,negativos[i]);
    }
    midLine();
    waiting();
    free(negativos);
}
void opt_liberate_board(void* context){
    Board *board = (Board*)context;
    for(int i=0;i<board->filas;i++){
        free(board->data[i]);
    }
    free(board->data);
    free(board);
    clear();
    topLine();
    content("Tabla liberada!");
    midLine();
    waiting();
}
void opt_mock_board(void* context){
    Board *board = (Board*)context;
    mock_board(board);
    clear();
    topLine();
    content("Tabla mockemada!");
    midLine();
    waiting();
}
void opt_exit(void* context){
    Board *board = (Board*)context;
    for(int i=0;i<board->filas;i++){
        free(board->data[i]);
    }
    free(board->data);
    free(board);
    clear();
    topLine();
    content("Saliendo del programa...");
    midLine();
    waiting();
    clear();
    exit(0);
}

