/*
Ejercicio N° 1
Generar una matriz de m por n elementos en los cuales m no puede ser inferior a 100 y n a 50.
Se pide:
Crear una funcion para obtener el promedio por fila y cargarlo en un vector.
Crear una función para obtener el mayor y el menor de cada fila y también cargarlo a cada uno en un vector distinto.
Por final del ejercicio indicar cuál fue el mayor elemento Como así también el menor elemento encontrado y también el promedio general
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>


//funciones propias

typedef struct {
  char *nameOption;
  int value;
  void (*funcOption)(void *context);
} WindowOption;
/*
  WindowOption *options;
  int len;
*/
typedef struct {
  WindowOption *options;
  int len;
} WindowOptions;

typedef struct {
  char *name;
  int value;
} Option;

typedef struct {
  Option *options;
  int size;
} Options;

// CLEAR THE HISTORY CONSOLE
void clear() {
#ifdef _WIN32
  system("cls");
#elif __linux__
  system("clear");
#endif
}

// ╔════════════════════════════════════════\n
void topLine() {
#ifdef _WIN32
  printf("||=======================================\n");
#elif __linux__
  printf("╔════════════════════════════════════════\n");
#endif
}

// ╚════════════════════════════════════════\n
void bottomLine() {
#ifdef _WIN32
  printf("||=======================================\n");
#elif __linux__
  printf("╚════════════════════════════════════════\n");
#endif
}
// ╠════════════════════════════════════════\n
void midLine() {
#ifdef _WIN32
  printf("||=======================================\n");
#elif __linux__
  printf("╠════════════════════════════════════════\n");
#endif
}
// ║CONTENT WITH FORMAT
void content(const char *format, ...) {
  va_list args;      // Lista de argumentos variables
  char buffer[1024]; // Tamaño adecuado para el mensaje
  int len;

  // Inicializar la lista de argumentos
  va_start(args, format);

  // Formatear el mensaje en el búfer
  len = vsnprintf(buffer, sizeof(buffer), format, args);

  // Verificar si la operación se completó correctamente
  if (len >= 0 && len < sizeof(buffer)) {
// Imprimir el mensaje formateado
#ifdef _WIN32
    printf("||%s\n", buffer);
#elif __linux__
    printf("║ %s\n", buffer);
#endif
  } else {
    // Manejar el error (por ejemplo, búfer demasiado pequeño)
    printf("Error al formatear el mensaje\n");
  }

  // Finalizar la lista de argumentos
  va_end(args);
}
/*
  ╚═
*/
void inputLine() {
#ifdef _WIN32
  printf("||= ");

#elif __linux__
  printf("╚═ ");
#endif
}
/*
  content("Colocar cualquier caracter para continuar");
  inputLine();
  char aux[3];
  scanf("%s", aux);
  fflush(stdin);

  ║ 1 - Dar de alta un producto nuevo.
  ╠════════════════════════════════════════
  ╚═
*/
void waiting() {
  content("Colocar cualquier caracter para continuar");
  midLine();
  inputLine();
  char aux[3];
  scanf("%s", aux);
  fflush(stdin);
}

void ordenarOptionsAscendente(Options *opts) {
  int i, j;
  for (i = 0; i < opts->size - 1; i++) {
    for (j = 0; j < opts->size - 1 - i; j++) {
      if (opts->options[j].value > opts->options[j + 1].value) {
        // Intercambiar las posiciones
        Option temp = opts->options[j];
        opts->options[j] = opts->options[j + 1];
        opts->options[j + 1] = temp;
      }
    }
  }
}
/*
Example:
    Option arr[8] = {{"Dar de alta un producto nuevo.", 1},
                     {"Buscar un producto por su Código.", 1},
                     {"Modificar el stock por venta.", 1},
                     {"Modificar el Precio de un producto.", 1},
                     {"Cuantos productos tiene faltante.", 1},
                     {"A cuantos le faltan vender 3 producto para que quede el
stock mínimo.", 1},
                     {"Mostrar productos.", 1},
                     {"Salir.", 1}};
    Options options = {arr, 8};
    menuOptions(options);
    output:
    ╔════════════════════════════════════════
    ║ 1 - Dar de alta un producto nuevo.
    ╠════════════════════════════════════════
    ║ 2 - Buscar un producto por su Código.
    ╠════════════════════════════════════════
    ║ 3 - Modificar el stock por venta.
    ╠════════════════════════════════════════
    ║ 4 - Modificar el Precio de un producto.
    ╠════════════════════════════════════════
    ║ 5 - Cuantos productos tiene faltante.
    ╠════════════════════════════════════════
    ║ 6 - A cuantos le faltan vender 3 producto para que quede el stock mínimo.
    ╠════════════════════════════════════════
    ║ 7 - Mostrar productos.
    ╠════════════════════════════════════════
    ║ 8 - Salir.
    ╠════════════════════════════════════════

  Note: Order according to the order given in the arrangement, no enumeration
needed
*/
void menuOptionsEnumerated(Options options) {
  topLine();
  for (int i = 0; i < options.size; i++) {
    content("%d - %s", i + 1, options.options[i].name);
    midLine();
  }
}
/*
Example:
    Option arr[8] = {{"Dar de alta un producto nuevo.", 1},
                     {"Buscar un producto por su Código.", 2},
                     {"Modificar el stock por venta.", 3},
                     {"Modificar el Precio de un producto.", 4},
                     {"Cuantos productos tiene faltante.", 5},
                     {"A cuantos le faltan vender 3 producto para que quede el
stock mínimo.", 6},
                     {"Mostrar productos.", 7},
                     {"Salir.", 8}};
    Options options = {arr, 8};
    menuOptions(options);
    output:
    ╔════════════════════════════════════════
    ║ 1 - Dar de alta un producto nuevo.
    ╠════════════════════════════════════════
    ║ 2 - Buscar un producto por su Código.
    ╠════════════════════════════════════════
    ║ 3 - Modificar el stock por venta.
    ╠════════════════════════════════════════
    ║ 4 - Modificar el Precio de un producto.
    ╠════════════════════════════════════════
    ║ 5 - Cuantos productos tiene faltante.
    ╠════════════════════════════════════════
    ║ 6 - A cuantos le faltan vender 3 producto para que quede el stock mínimo.
    ╠════════════════════════════════════════
    ║ 7 - Mostrar productos.
    ╠════════════════════════════════════════
    ║ 8 - Salir.
    ╠════════════════════════════════════════

  Note: No need order
*/
void menuOptions(Options options) {
  topLine();
  ordenarOptionsAscendente(&options);

  for (int i = 0; i < options.size; i++) {
    content("%d - %s", options.options[i].value, options.options[i].name);
    midLine();
  }
}

void window_menu_option(WindowOptions options) {
  topLine();
  for (int i = 0; i < options.len; i++) {
    content("%d - %s", i + 1, options.options[i].nameOption);
    midLine();
  }
}

void window(const char *title, void *context, WindowOptions opt) {
  int option = 0;
  int out = 1;
  while (true) {
    if (out == 1) {
      clear();
      topLine();
      content(title);
    } else {
      clear();
      topLine();
      content("Opcion no valida, ingresa otra.");
    }
    midLine();
    for (int i = 0; i < opt.len; i++) {
      content("%d - %s", i, opt.options[i].nameOption);
      midLine();
    }
    inputLine();
    scanf("%d", &option);
    fflush(stdin);

    for (int i = 0; i < opt.len; i++) {
      if (i == option) {
        opt.options[i].funcOption(context);
        out = 1;
        break;
      } else {
        out = 0;
      }
    }
  }
}
//fin de funciones propias

#define M 110
#define N 60

void generarMatriz(int matriz[M][N], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = (rand() % (101-0+1) + 0); 
        }
    }
}

void obtenerPromedioPorFila(int matriz[M][N], int filas, int columnas, float promedio[]) {
    for (int i = 0; i < filas; i++) {
        int suma = 0;
        for (int j = 0; j < columnas; j++) {
            suma += matriz[i][j];
        }
        promedio[i] = suma / (float)columnas;
    }
}

void obtenerMayorYMenorPorFila(int matriz[M][N], int filas, int columnas, int mayor[], int menor[]) {
    for (int i = 0; i < filas; i++) {
        mayor[i] = matriz[i][0];
        menor[i] = matriz[i][0];
        for (int j = 1; j < columnas; j++) {
            if (matriz[i][j] > mayor[i]) {
                mayor[i] = matriz[i][j];
            }
            if (matriz[i][j] < menor[i]) {
                menor[i] = matriz[i][j];
            }
        }
    }
}

void obtenerMayorYMenorDeMatriz(int matriz[M][N], int filas, int columnas, int *mayor, int *menor) {
    *mayor = matriz[0][0];
    *menor = matriz[0][0];
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] > *mayor) {
                *mayor = matriz[i][j];
            }
            if (matriz[i][j] < *menor) {
                *menor = matriz[i][j];
            }
        }
    }
}

float obtenerPromedioGeneral(int matriz[M][N], int filas, int columnas) {
    int suma = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            suma += matriz[i][j];
        }
    }
    return suma / (float)(filas * columnas);
}

int main() {
    int matriz[M][N];
    float promedio[M];
    int mayor[M], menor[M];
    int maximoGlobal, minimoGlobal;

    generarMatriz(matriz, M, N);

    obtenerPromedioPorFila(matriz, M, N, promedio);

    obtenerMayorYMenorPorFila(matriz, M, N, mayor, menor);

    obtenerMayorYMenorDeMatriz(matriz, M, N, &maximoGlobal, &minimoGlobal);

    float promedioGeneral = obtenerPromedioGeneral(matriz, M, N);

    clear(); 
    for(int i =0 ;i<M;i++){
        printf("fila %d : ",i);
        for(int j=0;j<N;j++){
            printf("%d|",matriz[i][j]);
        }
        printf("\n");
    }
    topLine();
    content("Resultados del Ejercicio N° 1");
    midLine();
    content("Promedio por fila:");
    for (int i = 0; i < M; i++) {
        content("Fila %d: %.2f", i, promedio[i]);
    }
    midLine();
    content("Mayor y menor por fila:");
    for (int i = 0; i < M; i++) {
        content("Fila %d - Mayor: %d, Menor: %d", i, mayor[i], menor[i]);
    }
    midLine();
    content("Resumen final:");
    content("Mayor elemento en la matriz: %d", maximoGlobal);
    content("Menor elemento en la matriz: %d", minimoGlobal);
    content("Promedio general de la matriz: %.2f", promedioGeneral);
    midLine();
    waiting(); 

    return 0;
}
