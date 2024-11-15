#include "ui.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
Realizar un programa que genera una lista en la cual se almacene los promedios de una escuela. 
Se debe indicar cuál es el mayor promedio. 
A partir de esa lista se debe generar una 2da que de be contener solo a los alumnos que tienen promedio mayor a 699. 
Se debe ordenarla de Menor a Mayor. 
También se debe generar otra lista que contenga al resto de los elementos y se la debe ordenar siguiendo el mismo criterio que la anterior.
*/

#define CRITERY (float)699.0

typedef struct Data Data;
typedef struct Stack Stack;

struct Data {
    int value;  // Valor del nodo
    Data *next;
    Data *former;
};

struct Stack {
    Data *top;
    Data *bottom;
    int len;
};

void opt_;

// mock numbers
void mock_numbers(Stack *stack);
// simple print
void simple_print(Stack *stack);

// Add number logic
void opt_add_numbers(void *context);
// Add number infraestructure
void push_number_on_top(Stack *stack, float number);
void incert_number(Stack *stack);

// View list logic
void opt_view_list(void *context);

// Order asc logic
void ver_mas_caro_y_barato(void *context);
void order_by_asc(Stack *stack);

void menores_a_70(void *context);
void order_by_desc(Stack *stack);

// liberate stack option logic
void opt_liberate_list(void *context);

void custom_free(Data *data);
void liberate_stack(Stack *stack);

// exit logic
void opt_exit(void *context);

// NEW CODE
//  Add number on bottom
void push_number_on_bottom(Stack *stack, float number);
void opt_add_number_on_bottom(void *context);

void opt_sum_numbers(void *context);

void opt_calculate_prom(void *context);

void opt_remove_repeated_numbers(void *context);

void opt_order_numbers(void *context);

// NEW CODE
void opt_best_prom(void *context);

void opt_generate_list_with_prom_may_of_699(void *context);

void delete_data(Stack *stack, Data *data);

int main() {

  Stack stack;
  stack.len = 0;
  stack.top = NULL;
  stack.Bottom = NULL;
  mock_numbers(&stack);

  WindowOption opts[7] = {{"Insertar promedio.", 1, opt_add_number_on_bottom},
                          {"Cual es el mayor promedio?.", 1, opt_best_prom},
                          {"Separar listas debido a criterio.", 8,
                           opt_generate_list_with_prom_may_of_699},
                          {"Mostrar numeros.", 2, opt_view_list},
                          {"Salir.", 1, opt_exit}};
  WindowOptions window_options = {opts, 5};

  window("Programa de pila de numeros", &stack, window_options);
}

void opt_generate_list_with_prom_may_of_699(void *context) {
  Stack *stack = (Stack *)context;

  Stack *may_critery = (Stack *)malloc(sizeof(Stack));
  Stack *men_critery = (Stack *)malloc(sizeof(Stack));
  may_critery->len = 0;
  men_critery->len = 0;

  men_critery->top = NULL;
  men_critery->Bottom = NULL;

  may_critery->top = NULL;
  may_critery->Bottom = NULL;

  for (Data *i = stack->top; i != NULL; i = i->next)
    if (i->Number > CRITERY)
      push_number_on_top(may_critery, i->Number);
    else
      push_number_on_top(men_critery, i->Number);

  order_by_asc(may_critery);
  order_by_asc(men_critery);

  clear();
  topLine();
  content("LISTA MAYOR A %f", CRITERY);
  midLine();
  for (Data *i = may_critery->top; i != NULL; i = i->next)
    content("promedio: %f", i->Number);
  midLine();
  content("LISTA MENOR A %f", CRITERY);
  midLine();
  for (Data *i = men_critery->top; i != NULL; i = i->next)
    content("promedio: %f", i->Number);
  midLine();
  waiting();
}

void opt_best_prom(void *context) {
  Stack *stack = (Stack *)context;
  float best_prom = 0;

  for (Data *i = stack->top; i != NULL; i = i->next)
    if (i->Number > best_prom)
      best_prom = i->Number;

  clear();
  topLine();
  content("El mayor promedio es %f", best_prom);
  midLine();
  waiting();
}

void opt_order_numbers(void *context) {
  Stack *stack = (Stack *)context;
  Stack stack_par;
  Stack stack_impar;
  stack_par.top = NULL;
  stack_par.Bottom = NULL;
  stack_par.len = 0;
  stack_impar.top = NULL;
  stack_impar.Bottom = NULL;
  stack_impar.len = 0;
  for (Data *current = stack->top; current != NULL; current = current->next) {
    if (((int)current->Number % (int)2) == 0)
      push_number_on_top(&stack_par, current->Number);
    else
      push_number_on_top(&stack_impar, current->Number);
  }
  order_by_asc(&stack_par);
  order_by_desc(&stack_impar);
  clear();
  topLine();
  content("NUMEROS PARES ORDENADOS DE MENOR A MAYOR");
  for (Data *current = stack_par.top; current != NULL; current = current->next)
    content("%d", current->Number);
  content("NUMEROS IMPARES ORDENADOS DE Mayor A Menor");
  for (Data *current = stack_impar.top; current != NULL;
       current = current->next)
    content("%d", current->Number);
  midLine();
  waiting();
}

void delete_data(Stack *stack, Data *data) {
  if (data == NULL)
    return;

  if (stack->top == stack->Bottom) {
    if (stack->top == NULL) {
      return;
    } else {
      stack->top = NULL;
      stack->Bottom = NULL;
      stack->len = 0;
      free(data);
      return;
    }
  }

  if (data->former != NULL)
    data->former->next = data->next;
  else
    stack->top = data->next;

  if (data->next != NULL)
    data->next->former = data->former;
  else
    stack->Bottom = data->former;

  stack->len--;
  free(data);
}

void opt_calculate_prom(void *context) {
  Stack *stack = (Stack *)context;
  int ac = 0;
  Data *current = stack->top;
  while (current != NULL) {
    ac += current->Number;
    current = current->next;
  }
  clear();
  topLine();
  content("El promedio de todos los numeros es: %f",
          (float)ac / (float)stack->len);
  midLine();
  waiting();
}

void opt_remove_repeated_numbers(void *context) {
  Stack *stack = (Stack *)context;
  Data *first = stack->top;
  Data *second = stack->top;
  // printf("comparison %d - %d on entry\n",first->Number, second->Number);

  while (first != NULL) {
    second = first->next;
    while (second != NULL) {
      Data *next_second = second->next;
      // printf("comparison %d - %d , addres %p - %p\n",first->Number,
      // second->Number, first, second);
      if (first != second) {
        if (first->Number == second->Number) {
          delete_data(stack, second);
        }
      }

      second = next_second;
    }
    first = first->next;
  }

  // clear();
  // simple_print(stack);
  topLine();
  content("Se eliminaron los numeros repetidos!");
  midLine();
  waiting();
}

void opt_sum_numbers(void *context) {
  Stack *stack = (Stack *)context;
  int ac = 0;
  Data *current = stack->top;
  while (current != NULL) {
    ac += current->Number;
    current = current->next;
  }
  clear();
  topLine();
  content("La suma de todos los numeros es: %d", ac);
  midLine();
  waiting();
}

void push_number_on_bottom(Stack *stack, float number) {
  Data *new_data = malloc(sizeof(Data));

  if (new_data == NULL) {
    exit(202);
  }
  new_data->Number = number;
  new_data->next = NULL;
  new_data->former = NULL;

  if (stack->Bottom == NULL) {
    stack->Bottom = new_data;
    stack->top = new_data;
  } else {
    new_data->former = stack->Bottom;
    stack->Bottom->next = new_data;
    stack->Bottom = new_data;
  }
  stack->len++;
}
void opt_add_number_on_bottom(void *context) {
  Stack *stack = (Stack *)context;
  float new_number = 0;
  clear();
  topLine();
  content("Dame el numero que queres añadir en el final de la pila (cantidad "
          "de numeros %d)",
          stack->len);
  midLine();
  inputLine();
  scanf("%f", &new_number);
  push_number_on_bottom(stack, new_number);

  clear();
  simple_print(stack);
  topLine();
  content("numero incertado: %d", stack->Bottom->Number);
  midLine();
  waiting();
}

void mock_numbers(Stack *stack) {
  push_number_on_bottom(stack, 4.0);
  push_number_on_bottom(stack, 1.0);
  push_number_on_bottom(stack, 4.0);
  push_number_on_bottom(stack, 20.0);
  push_number_on_bottom(stack, 322.0);
  push_number_on_bottom(stack, 5.0);
  push_number_on_bottom(stack, 2.0);
  push_number_on_bottom(stack, 7.0);
  push_number_on_bottom(stack, 20.0);
  push_number_on_bottom(stack, 9.0);
  push_number_on_bottom(stack, 10.0);
  push_number_on_bottom(stack, 11.0);
  push_number_on_bottom(stack, 12.0);
  push_number_on_bottom(stack, 2.0);
  push_number_on_bottom(stack, 14.0);
  push_number_on_bottom(stack, 11.0);

  push_number_on_bottom(stack, 1002.0);
  push_number_on_bottom(stack, 10014.0);
  push_number_on_bottom(stack, 10011.0);
}

void opt_view_list(void *context) {

  Stack *stack = (Stack *)context;
  Data *current = stack->top;
  int index = 0;

  clear();
  topLine();
  content("numver ║ index (len = %d)", stack->len);
  midLine();

  while (current != NULL) {
    content("%f ║ %f", current->Number, index);
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
  content("number ║ index");
  midLine();
  int index = 0;
  while (current != NULL) {
    content("%d ║ %d", current->Number, index);
    current = current->next;
    index++;
  }
  midLine();
}

void push_number_on_top(Stack *stack, float number) {
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
  float new_number = 0;
  clear();
  topLine();
  content("Dame el numero a incertar ( indice %d)", stack->len);
  midLine();
  inputLine();
  scanf("%f", &new_number);
  push_number_on_top(stack, new_number);
}

void opt_add_numbers(void *context) {
  Stack *stack = (Stack *)context;
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

void ver_mas_caro_y_barato(void *context) {
  Stack *stack = (Stack *)context;

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
        float temp = ptr1->Number;
        ptr1->Number = ptr1->next->Number;
        ptr1->next->Number = temp;
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

void menores_a_70(void *context) {
  Stack *stack = (Stack *)context;
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
        float temp = ptr1->Number;
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
  stack->Bottom = NULL;
  stack->len = 0;
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
