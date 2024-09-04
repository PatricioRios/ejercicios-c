#include "boolconst.c"
#include "ui.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Persona Persona;
struct Persona {
  int edad;
  char *nombre;
};

typedef struct Data Stack;

struct Data {
  Stack *next;
  Persona *persona;
};

void push(Stack **top, Persona *persona);
void print_Stack(Stack *top);
void custom_free(Stack *top);
void get_person(Stack **top);

int main() {
  Stack *top = NULL;
  int option;
  while (TRUE) {
    printf("1 para agregar persona 2 para ver personas, 3 para eliminar una "
           "persona, 4 para salir\n");
    scanf("%d", &option);
    switch (option) {
    case 1:
      get_person(&top);
      continue;
    case 2:
      print_Stack(top);
      continue;
    case 3:
      // TODO
      continue;

    case 4:
      custom_free(top);
      return 0;
    default:
      custom_free(top);
      return 0;
    }

    print_Stack(top);
    custom_free(top);
  }
}

void get_person(Stack **top) {
  fflush(stdin);
  int edad;
  char *nombre = malloc(sizeof(char) * 200);
  Persona *new_person = malloc(sizeof(Persona));
  topLine();
  content("Dame, el nombre de la persona");
  midLine();
  inputLine();
  if (scanf("%199s", nombre) != 1) {
    fprintf(stderr, "Error: No se pudo leer el nombre\n");
    free(nombre);
    free(new_person);
    exit(1);
  }
  new_person->nombre = nombre;
  fflush(stdin);
  // clear();
  topLine();
  content("Dame, la edad de la persona");
  midLine();
  inputLine();
  scanf("%d", &edad);
  new_person->edad = edad;

  push(top, new_person);
}

void push(Stack **top, Persona *persona) {
  Stack *new_stack = malloc(sizeof(Stack));
  new_stack->persona = persona;

  new_stack->next = *top;
  *top = new_stack;
}

void print_Stack(Stack *top) {
  Stack *current = top;
  int ac = 0;
  printf("PRINT\n");
  while (current != NULL) {

    printf("Persona edad %d = %s\n", current->persona->edad,
           current->persona->nombre);
    current = current->next;
    ac++;
  }
}

void custom_free(Stack *top) {

  if (top != NULL) {
    printf("liberando %s\n", top->persona->nombre);
    custom_free(top->next);
    free(top->persona->nombre);
    free(top->persona);

    free(top);
  }
}
