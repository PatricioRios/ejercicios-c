/*
Ejercicio N° 2
Desarrollar un programa que en una lista me permita mediante funciones poder realizar lo siguiente
1° por medio de una función registrar en una lista el precio de 100 productos, validando que todos sean mayor a cero.
2° crear una función que me indique Cuál es el precio más caro y cuál es el precio más barato.
3° por medio de una función que imprima el precio de los productos menor a $70
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


typedef struct Stack Stack;

struct Stack
{
    float *top;
    int len;
    int cap;
};

// utilities
void mock_numbers(Stack *stack);
void simple_print(Stack *stack);
void push_number_on_top(Stack *stack, float number);
void free_data(float *data);
void free_stack(Stack *stack);

void pop_on_top(Stack *stack);

void delete_data(int *data);
void delete_data_on_stack(Stack *stack, float *data);


void opt_add_number(void *context);     // opt 0
void opt_view_list(void *context);      // opt 1
void ver_mas_caro_y_barato(void *context);      // opt 2
void menores_a_70(void *context);     // opt 3
void opt_liberate_stack(void *context); // opt 8
void opt_mock_numbers(void *context);   // opt 9
void opt_exit(void *context);           // opt 10


int main()
{

  Stack stack;
  stack.len = 0;
  stack.cap = 100;
  stack.top = (float *) malloc(stack.cap*sizeof(float));
  mock_numbers(&stack);

  WindowOption opts[7] = {
      {"Añadir numero.", 1, opt_add_number},
      {"Mostrar Lista.", 2, opt_view_list},
      {"Ver el mas caro y el mas barato.", 1, ver_mas_caro_y_barato},
      {"Ver los menores a 70.", 8, menores_a_70},
      {"Liberar Lista", 2, opt_liberate_stack},
      {"Mockear numeros.", 2, opt_mock_numbers},
      {"Salir.", 1, opt_exit}};
  WindowOptions window_options = {opts, 7};

  window("Programa de pila de numeros", &stack, window_options);
}


void mock_numbers(Stack *stack) {
    for (int i = 0; i < 100; i++) { // Cambiado a i < 100
        float num = (float)(rand() % 1001); // Genera un número aleatorio entre 0 y 1000
        push_number_on_top(stack, num);
    }
}

void simple_print(Stack *stack)
{
  clear();
  topLine();
  content("number ║ index");
  midLine();
  for (int index = 0; index < stack->len; index++) { // Cambiado a index < stack->len
    content("%.2f ║ %d", stack->top[index], index); // Cambiado a %.2f
  }
  midLine();
  waiting();
}

void push_number_on_top(Stack *stack, float number)
{
    if (stack->len == stack->cap) {
        stack->cap *= 2;
        float *new_top = realloc(stack->top, stack->cap * sizeof(float));
        if (new_top == NULL) {
            perror("Error al redimensionar la pila");
            free(stack->top);  
            exit(EXIT_FAILURE);
        }
        stack->top = new_top;
    }
    stack->top[stack->len] = number;
    stack->len++;
}


void free_data(float *data)
{
  free(data);
}



void free_stack(Stack *stack)
{
    free(stack->top);
    stack->len = 0;
}



void opt_add_number(void *context){
  Stack *stack = (Stack *)context;
  float number;
  
  do {
    clear();
    topLine();
    content("Ingrese el numero a añadir:");
    midLine();
    inputLine();
    scanf("%f", &number);
    fflush(stdin);
  } while (number <= 0);

  push_number_on_top(stack, number);
  clear();
  topLine();
  content("El numero añadido es %.2f", stack->top[stack->len - 1]);
  midLine();
  waiting();
}
void opt_view_list(void *context) {
  Stack *stack = (Stack *)context;
  clear();
  topLine();
  content("number ║ index (longitud actual: %d) (capacidad: %d)",stack->len,stack->cap);
  midLine();
  int index = 0;
  for(int i=0;i<stack->len;i++){
    content("%f ║ %d",stack->top[i],i);
  }
  midLine();
  waiting();
}
void ver_mas_caro_y_barato(void *context) {
  Stack *stack = (Stack *)context;
  float mas_caro=0;
  float menos_caro=0;
  for(int i=0;i<stack->len;i++){
    if(stack->top[i]> mas_caro){
      mas_caro = stack->top[i];
    }
    if(stack->top[i] < menos_caro){
      menos_caro = stack->top[i];
    }
  }
  clear();
  content("El mas barato es %f, y el mas barato es %f!",menos_caro,mas_caro);
  midLine();
  waiting();
}
void menores_a_70(void *context) {
  Stack *stack = (Stack *)context;
  clear();
  content("Mostrando numeros menores a 70!");
  midLine();
  for(int i=0;i<stack->len;i++){

    if(stack->top[i] < 70){
      content("%f",stack->top[i]);
    }
  }
  midLine();
  waiting();
}

void opt_liberate_stack(void *context){
  Stack *stack = (Stack *)context;
  free_stack(stack);
  clear();
  topLine();
  content("Se libero la lista!");
  midLine();
  waiting();
}
void opt_mock_numbers(void *context){
  Stack *stack = (Stack *)context;
  mock_numbers(stack);
  clear();
  topLine();
  content("Se mockeo la lista!");
  midLine();
  waiting();
}
void opt_exit(void *context){
  clear();
  topLine();
  content("Saliendo del programa...");
  midLine();
  waiting();
  clear();
  exit(0);
}   
