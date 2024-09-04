#include "stack.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Numero Numero;
struct Numero
{
  int num;
};

void print_num(void *data)
{
  Numero *num = (Numero *)data;
  printf("Element: %d\n", num->num);
}

void custom_free(void *data)
{
  Numero *numero = (Numero *)data;
  free(numero);
}

int compare_nums_asc(const void *a, const void *b)
{
  Numero *num_a = *(Numero **)a;
  Numero *num_b = *(Numero **)b;
  return num_a->num - num_b->num;
}

// Función de búsqueda binaria
int binary_search(Stack *stack, int target)
{
  int left = 0;
  int right = stack->len - 1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    Numero *mid_num = (Numero *)stack->get_by_index(stack, mid)->data;

    if (mid_num->num == target)
    {
      return mid; // Elemento encontrado
    }
    else if (mid_num->num < target)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return -1; // Elemento no encontrado
}

int main()
{
  Stack stack = new_stack(custom_free);

  // Agregar números a la pila
  int values[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
  int num_values = sizeof(values) / sizeof(values[0]);

  for (int i = 0; i < num_values; i++)
  {
    Numero *numero = malloc(sizeof(Numero));
    numero->num = values[i];
    stack.push_on_top(&stack, numero);
  }

  printf("Pila original:\n");
  stack.foreach (&stack, print_num);

  // Ordenar la pila
  stack.order_by(&stack, compare_nums_asc);

  printf("\nPila ordenada:\n");
  stack.foreach (&stack, print_num);

  // Realizar búsquedas binarias
  int targets[] = {3, 6, 10};
  int num_targets = sizeof(targets) / sizeof(targets[0]);

  for (int i = 0; i < num_targets; i++)
  {
    int result = binary_search(&stack, targets[i]);
    if (result != -1)
    {
      printf("\nEl número %d se encontró en la posición %d\n", targets[i], result);
    }
    else
    {
      printf("\nEl número %d no se encontró en la pila\n", targets[i]);
    }
  }

  // Liberar la memoria de la pila
  stack.liberate(&stack);

  return 0;
}