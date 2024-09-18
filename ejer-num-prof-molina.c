#include "boolconst.c"
#include "ui.c"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Ejercicio 1:Hacer un programa para agregar números enteros a una pila,
            hasta que el usuario lo decida, después mostrar todos los
            números introducidos en la pila.
*/

typedef struct Number Number;
struct Number
{
  int number;
};

typedef struct Data Data;

struct Data
{
  Data *next;
  Number *number;
};

typedef struct Stack Stack;

struct Stack
{
  Data *top;
  int len;
};

void get_number_for_top(Stack *stack);

void print_numbers(Stack *stack);

void liberate_stack(Stack *stack);
void custom_free(Data **data);

void push_on_top(Stack *top, Number *number);

void liberar_pila(Stack *stack);

void mock_numbers(Stack *stack);

int main()
{
  Stack *stack = malloc(sizeof(Stack));
  stack->top = NULL;
  stack->len = 0;
  int option = 0;
  mock_numbers(stack);
  Option arr[4] = {{"añadir un numero a la pila.", 1},
                   {"Mostrar pila.", 2},
                   {"Borrar pila.", 1},
                   {"Salir.", 1}};

  Options options = {arr, 4};
  while (TRUE)
  {
    clear();
    menuOptionsEnumerated(options);
    inputLine();
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      get_number_for_top(stack);
      continue;
    case 2:
      print_numbers(stack);
      continue;
    case 3:
      liberar_pila(stack);
      continue;
    case 4:
      liberate_stack(stack);
      return 0;
    default:
      continue;
    }
  }
}
void liberar_pila(Stack *stack)
{
  clear();
  liberate_stack(stack);
  topLine();
  content("Pila liberada con exito");
  midLine();
  waiting();
}

void print_numbers(Stack *stack)
{
  Data *current = stack->top;
  clear();
  topLine();
  int ac = 0;
  content("Cantidad de numeros %d", stack->len);
  midLine();
  while (current != NULL)
  {
    content("Numero: %d, lugar en la pila %d", current->number->number, ac++);
    midLine();
    current = current->next;
  }
  waiting();
}
void liberate_stack(Stack *stack)
{
  Data *current = stack->top;
  while (current != NULL)
  {
    stack->top = stack->top->next;
    custom_free(&current);
    current = stack->top;
  }
  stack->top = NULL;
  stack->len = 0;
}

void custom_free(Data **data)
{
  if (data == NULL || *data == NULL)
  {
    return;
  }

  if ((*data)->number != NULL)
  {
    free((*data)->number);
  }

  free(*data);
  *data = NULL;
}
void push_on_top(Stack *stack, Number *number)
{

  Data *new_data = malloc(sizeof(Data));
  new_data->number = number;
  if (stack->top == NULL)
  {
    stack->top = new_data;
    stack->top->next = NULL;
    stack->len++;
    return;
  }
  else
  {

    new_data->next = stack->top;
    stack->top = new_data;
    stack->len++;
  }
}

void get_number_for_top(Stack *Stack)
{
  Number *number = malloc(sizeof(Number));
  number->number = 0;

  clear();
  topLine();
  content("Dame, el numero");
  midLine();
  inputLine();
  scanf("%d", &number->number);

  // cambiar por push on top

  push_on_top(Stack, number);

  clear();
  topLine();
  content("Numero incertado %d",
          Stack->top->number->number);
  midLine();
  waiting();
}

void mock_numbers(Stack *stack)
{
  Number *number = malloc(sizeof(Number));
  number->number = 44329343;
  push_on_top(stack, number);

  Number *number2 = malloc(sizeof(Number));
  number2->number = 34329343;
  push_on_top(stack, number2);

  Number *number3 = malloc(sizeof(Number));
  number3->number = 24329343;
  push_on_top(stack, number3);

  Number *number4 = malloc(sizeof(Number));
  number4->number = 14329343;
  push_on_top(stack, number4);

  Number *number5 = malloc(sizeof(Number));
  number5->number = 54329343;
  push_on_top(stack, number5);

  Number *number6 = malloc(sizeof(Number));
  number6->number = 64329343;
  push_on_top(stack, number6);

  Number *number7 = malloc(sizeof(Number));
  number7->number = 74329343;
  push_on_top(stack, number7);

  Number *number8 = malloc(sizeof(Number));
  number8->number = 84329343;
  push_on_top(stack, number8);

  Number *number9 = malloc(sizeof(Number));
  number9->number = 94329343;
  push_on_top(stack, number9);
}
