#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct
{
  char *name;
  int value;
} Option;
typedef struct
{
  Option *options;
  int size;
} Options;

// CLEAR THE HISTORY CONSOLE
void clear()
{
  system("clear");
}

// ╔════════════════════════════════════════\n
void topLine()
{
  printf("╔════════════════════════════════════════\n");
}

// ╚════════════════════════════════════════\n
void bottomLine()
{
  printf("╚════════════════════════════════════════\n");
}
// ╠════════════════════════════════════════\n
void midLine()
{
  printf("╠════════════════════════════════════════\n");
}
// ║CONTENT WITH FORMAT
void content(const char *format, ...)
{
  va_list args;      // Lista de argumentos variables
  char buffer[1024]; // Tamaño adecuado para el mensaje
  int len;

  // Inicializar la lista de argumentos
  va_start(args, format);

  // Formatear el mensaje en el búfer
  len = vsnprintf(buffer, sizeof(buffer), format, args);

  // Verificar si la operación se completó correctamente
  if (len >= 0 && len < sizeof(buffer))
  {
    // Imprimir el mensaje formateado
    printf("║ %s\n", buffer);
  }
  else
  {
    // Manejar el error (por ejemplo, búfer demasiado pequeño)
    printf("Error al formatear el mensaje\n");
  }

  // Finalizar la lista de argumentos
  va_end(args);
}

void inputLine()
{
  printf("╚═ ");
}
/*
  content("Colocar cualquier caracter para continuar");
  inputLine();
  char aux[3];
  scanf("%s", aux);
  fflush(stdin);
*/
void waiting()
{
  content("Colocar cualquier caracter para continuar");
  inputLine();
  char aux[3];
  scanf("%s", aux);
  fflush(stdin);
}

void ordenarOptionsAscendente(Options *opts)
{
  int i, j;
  for (i = 0; i < opts->size - 1; i++)
  {
    for (j = 0; j < opts->size - 1 - i; j++)
    {
      if (opts->options[j].value > opts->options[j + 1].value)
      {
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
                     {"A cuantos le faltan vender 3 producto para que quede el stock mínimo.", 1},
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

  Note: Order according to the order given in the arrangement, no enumeration needed
*/
void menuOptionsEnumerated(Options options)
{
  topLine();
  for (int i = 0; i < options.size; i++)
  {
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
                     {"A cuantos le faltan vender 3 producto para que quede el stock mínimo.", 6},
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
void menuOptions(Options options)
{
  topLine();
  ordenarOptionsAscendente(&options);

  for (int i = 0; i < options.size; i++)
  {
    content("%d - %s", options.options[i].value, options.options[i].name);
    midLine();
  }
}

void window(const char *title, void (*func)())
{
  clear();
  topLine();
  content("%s", title);
  midLine();
  func();
  bottomLine();
}