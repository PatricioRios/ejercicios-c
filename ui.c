/*
compilar para windows
i686-w64-mingw32-gcc -o molina-sep.exe molina-sep-25.c

i686-w64-mingw32-gcc -o name.exe src.c

ejecutar en entorno virtual windows
wine molina-sep.exe
*/
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * TODO: Hacer un winter, en donde elijas el tamaño de la ventana
 * El el texto de la ventana, u cualquier cuadro va a tener que ser acomodado
 * con \n para que siempre calce con la longitud especificada.
 * */
/*
char *nameOption;
  int value;
  void (* funcOption)(void * context)
*/
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
        out = 1;  
        opt.options[i].funcOption(context);
        out = 1;
        out = 1;
        out = 1;
        out = 1;
        break;
      } else {
        out = 0;
      }
    }
  }
}
