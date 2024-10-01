#include "ui.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
Generar un programa que cree una lista mínimo de 15 elementos a esa
lista mañana con números Posteriormente se le debe agregar elemento
Una vez que se la ha completado por el usuario, se la debe ordenar MAYOR a MENOR
y VICEVERSA.-
*/

typedef struct Data Data;
typedef struct Stack Stack;

struct Data {
  int Number;
  Data *next;
};
struct Stack {
  Data *top;
  int len;
};

void mock_numbers(Stack *stack);

void simple_print(Stack *stack);

void push_number(Stack *stack, int number);
void get_number(Stack *stack);
void incert_number(Stack *stack);

void print_numbers(Stack *stack);

void option_order_asc(Stack *stack);
void order_by_asc(Stack *stack);

void option_order_desc(Stack *stack);
void order_by_desc(Stack *stack);

void custom_free(Data *data);
void liberate_stack(Stack *stack);

void opt_add_numbers(void *context);

void opt_view_list(void *context);

void opt_order_asc(void *context);

void opt_order_desc(void *context);

void opt_liberate_list(void *context);

void opt_exit(void *context);

int main() {

  Stack stack;
  stack.len = 0;
  stack.top = NULL;
  mock_numbers(&stack);

  int option = 0;

  WindowOption opts[6] = {
      {"Añadir 15 numeros. (individualmente despues de los 15).", 1, opt_add_numbers},
      {"Mostrar Lista.", 2, opt_view_list},
      {"Ordenar arreglo de manera ascendente.", 1, opt_order_asc},
      {"Ordernar arreglo de manera descendente.", 8, opt_order_desc},
      {"Liberar Lista", 2, opt_liberate_list},
      {"Salir.", 1, opt_exit}};
  WindowOptions window_options = {opts, 6};

  window("Programa de pila de numeros", &stack, window_options);
}
void mock_numbers(Stack *stack) {
  push_number(stack, 4);
  push_number(stack, 1);
  push_number(stack, 4);
  push_number(stack, 322);
  push_number(stack, 5);
  push_number(stack, 2);
  push_number(stack, 7);
  push_number(stack, 20);
  push_number(stack, 9);
  push_number(stack, 10);
  push_number(stack, 11);
  push_number(stack, 12);
  push_number(stack, 2);
  push_number(stack, 14);
  push_number(stack, 11);
}

void print_numbers(Stack *stack) {
  Data *current = stack->top;
  clear();
  topLine();
  content("numver / index (len = %d)",stack->len);
  midLine();
  int index = 0;
  while (current != NULL) {
    content("%d / %d", current->Number, index);
    current = current->next;
    index++;
  }
  midLine();
  waiting();
}

void simple_print(Stack *stack) {
  Data *current = stack->top;
  clear();
  topLine();
  content("number / index");
  midLine();
  int index = 0;
  while (current != NULL) {
    content("%d / %d", current->Number, index);
    current = current->next;
    index++;
  }
  midLine();
}

void push_number(Stack *stack, int number) {
  Data *new_data = malloc(sizeof(Data));
  new_data->Number = number;
  if (stack->top == NULL) {

    new_data->next = NULL;
    stack->top = new_data;
  } else {

    new_data->next = stack->top;
    stack->top = new_data;
  }

  stack->len++;
};
void incert_number(Stack *stack) {
  int new_number = 0;
  clear();
  topLine();
  content("Dame el numero a incertar ( indice %d)", stack->len);
  midLine();
  inputLine();
  scanf("%d", &new_number);
  push_number(stack, new_number);
}

void get_number(Stack *stack) {
  if (stack->len <= 15) {
    while (stack->len <= 15) {
      incert_number(stack);
      simple_print(stack);
      waiting();
    }
  } else {
    incert_number(stack);
    simple_print(stack);
    waiting();
  }
}

void option_order_asc(Stack *stack) {
  order_by_asc(stack);
  clear();
  topLine();
  content("Se ordeno la pila de manera ascendente!");
  midLine();
  waiting();
}

void order_by_asc(Stack *stack) {
  if (stack->top == NULL || stack->top->next == NULL) {
    // La pila está vacía o tiene solo un elemento, ya está ordenada
    return;
  }

  int swapped;
  Data *ptr1;
  Data *lptr = NULL;

  do {
    swapped = 0;
    ptr1 = stack->top;

    while (ptr1->next != lptr) {
      if (ptr1->Number > ptr1->next->Number) {
        // Intercambiar los números
        int temp = ptr1->Number;
        ptr1->Number = ptr1->next->Number;
        ptr1->next->Number = temp;
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

void option_order_desc(Stack *stack) {
  order_by_desc(stack);
  clear();
  topLine();
  content("Se ordeno la pila de manera descendente!");
  midLine();
  waiting();
}
void order_by_desc(Stack *stack) {
  if (stack->top == NULL || stack->top->next == NULL) {
    // La pila está vacía o tiene solo un elemento, ya está ordenada
    return;
  }

  int swapped;
  Data *ptr1;
  Data *lptr = NULL;

  do {
    swapped = 0;
    ptr1 = stack->top;

    while (ptr1->next != lptr) {
      if (ptr1->Number < ptr1->next->Number) {
        // Intercambiar los números
        int temp = ptr1->Number;
        ptr1->Number = ptr1->next->Number;
        ptr1->next->Number = temp;
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}
void custom_free(Data *data) {
  if (data != NULL) {
    custom_free(data->next);
    free(data);
  }
}

void liberate_stack(Stack *stack) {
  custom_free(stack->top);
  clear();
  topLine();
  content("se libero el stack!");
  midLine();
  waiting();
  stack->top = NULL;
  stack->len =0;
}

void opt_add_numbers(void *context) {
  Stack *stack = (Stack *)context;
  get_number(stack);
}

void opt_view_list(void *context) {
  Stack *stack = (Stack *)context;
  print_numbers(stack);
}

void opt_order_asc(void *context) {
  Stack *stack = (Stack *)context;
  option_order_asc(stack);
}
void opt_order_desc(void *context) {
  Stack *stack = (Stack *)context;
  option_order_desc(stack);
}

void opt_liberate_list(void *context) {
  Stack *stack = (Stack *)context;
  liberate_stack(stack);
}

void opt_exit(void *context) {
  Stack *stack = (Stack *)context;
  liberate_stack(stack);
  exit(0);
}
