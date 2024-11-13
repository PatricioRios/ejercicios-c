#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui.c"

typedef struct Data Data;
typedef struct Stack Stack;

struct Data
{
  int Number;
  Data *next;
  Data *former;
};
struct Stack
{
  Data *top;
  Data *Bottom;
  int len;
};

// utilities
void mock_numbers(Stack *stack);
void simple_print(Stack *stack);
void push_number_on_top(Stack *stack, int number);
void push_number_on_bottom(Stack *stack, int number);

void order_by_asc(Stack *stack);
void order_by_desc(Stack *stack);

float sum_numbers(Stack *stack);
float prom_numbers(Stack *stack);

void free_data(Data *data);
void free_stack(Stack *stack);

void pop_on_top(Stack *stack);
void pop_on_bottom(Stack *stack);

void delete_data(Data *data);
void delete_data_on_stack(Stack *stack, Data *data);

void delete_by_index(Stack *stack, int index);
void delete_by_number(Stack *stack, int number);


void opt_add_number(void *context);     // opt 0
void opt_view_list(void *context);      // opt 1
void ver_mas_caro_y_barato(void *context);      // opt 2
void menores_a_70(void *context);     // opt 3
void opt_view_prom(void *context);      // opt 4
void opt_view_sum(void *context);       // opt 5
void opt_remove_number(void *context);  // opt 6
void opt_remove_index(void *context);   // opt 7
void opt_liberate_stack(void *context); // opt 8
void opt_mock_numbers(void *context);   // opt 9
void opt_exit(void *context);           // opt 10

int main()
{

  Stack stack;
  stack.len = 0;
  stack.top = NULL;
  stack.Bottom = NULL;
  mock_numbers(&stack);

  WindowOption opts[11] = {
      {"Añadir numero.", 1, opt_add_number},
      {"Mostrar Lista.", 2, opt_view_list},
      {"Ordenar arreglo de manera ascendente.", 1, ver_mas_caro_y_barato},
      {"Ordernar arreglo de manera descendente.", 8, menores_a_70},
      {"Mostrar Promedio.", 2, opt_view_prom},
      {"Mostrar suma de numeros.", 2, opt_view_sum},
      {"Remover numero.", 2, opt_remove_number},
      {"Remover dado indice.", 2, opt_remove_index},
      {"Liberar Lista", 2, opt_liberate_stack},
      {"Mockear numeros.", 2, opt_mock_numbers},
      {"Salir.", 1, opt_exit}};
  WindowOptions window_options = {opts, 11};

  window("Programa de pila de numeros", &stack, window_options);
}

void mock_numbers(Stack *stack)
{
  push_number_on_bottom(stack, 1);
  push_number_on_bottom(stack, 2);
  push_number_on_bottom(stack, 3);
  push_number_on_bottom(stack, 4);
  push_number_on_bottom(stack, 5);
  push_number_on_bottom(stack, 6);
  push_number_on_bottom(stack, 7);
  push_number_on_bottom(stack, 8);
  push_number_on_bottom(stack, 9);
  push_number_on_bottom(stack, 10);
  push_number_on_bottom(stack, 11);
  push_number_on_bottom(stack, 12);
  push_number_on_bottom(stack, 13);
  push_number_on_bottom(stack, 14);
  push_number_on_bottom(stack, 15);

  push_number_on_top(stack, 1);
  push_number_on_top(stack, 2);
  push_number_on_top(stack, 3);
  push_number_on_top(stack, 4);
  push_number_on_top(stack, 5);
}

void simple_print(Stack *stack)
{
  Data *current = stack->top;
  clear();
  topLine();
  content("number ║ index");
  midLine();
  int index = 0;
  for (Data *current = stack->top; current != NULL; current = current->next)
  {
    content("%d ║ %d", current->Number, index);
    current = current->next;
    index++;
  }
  midLine();
  waiting();
}

void push_number_on_top(Stack *stack, int number)
{
  Data *new_data = malloc(sizeof(Data));
  new_data->Number = number;
  if (stack->top == NULL)
  {
    new_data->next = NULL;
    stack->top = new_data;
  }
  else
  {
    new_data->next = stack->top;
    stack->top = new_data;
  }
  stack->len++;
}

void push_number_on_bottom(Stack *stack, int number)
{
  Data *new_data = malloc(sizeof(Data));
  new_data->Number = number;
  new_data->next = NULL;
  new_data->former = NULL;

  if (stack->Bottom == NULL)
  {
    stack->Bottom = new_data;
    stack->top = new_data;
    stack->len++;
    return;
  }
  else
  {
    new_data->former = stack->Bottom;
    stack->Bottom->next = new_data;
    stack->Bottom = new_data;
    stack->len++;
    return;
  }
}

void order_by_asc(Stack *stack)
{
  if (stack->top == NULL || stack->top->next == NULL)
  {
    // La pila está vacía o tiene solo un elemento, ya está ordenada
    return;
  }

  int swapped;
  Data *ptr1;
  Data *lptr = NULL;

  do
  {
    swapped = 0;
    ptr1 = stack->top;

    while (ptr1->next != lptr)
    {
      if (ptr1->Number > ptr1->next->Number)
      {
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

void order_by_desc(Stack *stack)
{
  if (stack->top == NULL || stack->top->next == NULL)
  {
    // La pila está vacía o tiene solo un elemento, ya está ordenada
    return;
  }

  int swapped;
  Data *ptr1;
  Data *lptr = NULL;

  do
  {
    swapped = 0;
    ptr1 = stack->top;

    while (ptr1->next != lptr)
    {
      if (ptr1->Number < ptr1->next->Number)
      {
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

float sum_numbers(Stack *stack)
{
  float sum = 0;
  for (Data *current = stack->top; current != NULL; current = current->next)
    sum = sum + (float)current->Number;
  return sum;
}
float prom_numbers(Stack *stack)
{
  return sum_numbers(stack) / stack->len;
}

void free_data(Data *data)
{
  free(data);
}

void pop_on_top(Stack *stack)
{
  if (stack->top == NULL)
    return;
  Data *temp = stack->top;
  stack->top = stack->top->next;
  stack->top->former = NULL;
  if (stack->top == NULL)
  {
    stack->Bottom = NULL;
    stack->top = NULL;
  }
  free_data(temp);
  stack->len--;
}
void pop_on_bottom(Stack *stack)
{
  if (stack->Bottom == NULL)
    return;
  Data *temp = stack->Bottom;
  stack->Bottom = stack->Bottom->former;
  stack->Bottom->next = NULL;
  if (stack->Bottom == NULL)
  {
    stack->top = NULL;
    stack->Bottom = NULL;
  }
  free_data(temp);
  stack->len--;
}

void delete_data(Data *data)
{
  data->former->next = data->next;
  data->next->former = data->former;
  free_data(data);
}
void delete_data_on_stack(Stack *stack, Data *data)
{

  if (stack->top == NULL || stack->Bottom == NULL)
    return;

  if (stack->len == 1)
  {
    pop_on_top(stack);
    stack->top = NULL;
    stack->Bottom = NULL;
    stack->len = 0;
    return;
  }
  else
  {
    delete_data(data);
    stack->len--;
    return;
  }
}

void delete_by_index(Stack *stack, int index)
{
  if (stack->top == NULL || stack->Bottom == NULL)
    return;
  if (index < 0 || index >= stack->len)
    return;
  if (index == 0)
  {
    pop_on_top(stack);
    return;
  }
  if (index == stack->len - 1)
  {
    pop_on_bottom(stack);
    return;
  }
  int i = 0;
  for (Data *current = stack->top; current != NULL; current = current->next)
  {
    if (i == index)
    {
      delete_data_on_stack(stack, current);
      return;
    }
    i++;
  }
}
void delete_by_number(Stack *stack, int number)
{
  if (stack->top == NULL || stack->Bottom == NULL)
    return;
  for (Data *current = stack->top; current != NULL; current = current->next)
  {
    if (current->Number == number)
    {
      delete_data_on_stack(stack, current);
      return;
    }
  }
  return;
}

void recursive_delete_data(Data *data)
{
  if (data == NULL)
    return;
  recursive_delete_data(data->next);
  free(data);
}
void free_stack(Stack *stack)
{
  recursive_delete_data(stack->top);
  stack->top = NULL;
  stack->Bottom = NULL;
  stack->len = 0;
}


void opt_add_number(void *context){
  Stack *stack = (Stack *)context;
  int number;
  clear();
  topLine();
  content("Ingrese el numero a añadir:");
  midLine();
  inputLine();
  scanf("%d", &number);
  fflush(stdin);
  push_number_on_top(stack, number);
  clear();
  topLine();
  content("El numero añadido es %d",stack->top->Number);
  midLine();
  waiting();
}
void opt_view_list(void *context) {
  Stack *stack = (Stack *)context;
  clear();
  topLine();
  content("number ║ index (longitud actual: %d)",stack->len);
  midLine();
  int index = 0;
  for(Data * current= stack->top;current!=NULL;current = current->next){
    content("%d ║ %d",current->Number,index);
    index++;
  }
  midLine();
  waiting();
}
void ver_mas_caro_y_barato(void *context) {
  Stack *stack = (Stack *)context;
  order_by_asc(stack);
  clear();
  content("Se ordeno el stack de manera ascendente!");
  midLine();
  waiting();
}
void menores_a_70(void *context) {
  Stack *stack = (Stack *)context;
  order_by_desc(stack);
  clear();
  content("Se ordeno el stack de manera descendente!");
  midLine();
  waiting();
}
void opt_view_prom(void *context) {
  Stack *stack = (Stack *)context;
  clear();
  topLine();
  content("El promedio es: %.2f", prom_numbers(stack));
  midLine();
  waiting();
}
void opt_view_sum(void *context) {
  Stack *stack = (Stack *)context;
  clear();
  topLine();
  content("La suma de todos los numeros es es: %.2f", sum_numbers(stack));
  midLine();
  waiting();
}
void opt_remove_number(void *context) {
  Stack *stack = (Stack *)context;
  int number;
  clear();
  topLine();
  content("Ingrese el numero a remover:");
  midLine();
  inputLine();
  scanf("%d", &number);
  fflush(stdin);
  delete_by_number(stack, number);
  clear();
  topLine();
  content("Se elimino el numero %d !",number);
  waiting();
}
void opt_remove_index(void *context) {
  Stack *stack = (Stack *)context;
  int index;
  clear();
  topLine();
  content("Ingrese el indice a remover:");
  midLine();
  inputLine();
  scanf("%d", &index);
  fflush(stdin);
  if(index > stack->len -1 || index < 0){
    clear();
    topLine();
    content("Ingresaste un indice no valido!, el menor indice es 0 y el mayor es %d",stack->len-1);
    midLine();
    waiting();
    return;
  }
  delete_by_index(stack, index);
  clear();
  topLine();
  content("Se elimino el numero en el indice %d !",index);
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
