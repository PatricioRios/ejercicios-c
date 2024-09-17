#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolconst.c"
#include "ui.c"

#define FILENAME "consultorio.txt"
#define MAX_FILENAME_LENGTH 256

FILE *get_file_instance() {
  static FILE *file = NULL;
  if (file == NULL) {
    file = fopen(FILENAME, "a+");
    if (file == NULL) {
      perror("Error opening file");
      exit(1);
    }
  }
  return file;
}

void close_file() {
  FILE *file = get_file_instance();
  fclose(file);
}

typedef struct Person Person;
struct Person {
  int DNI;
  char *name;
  char *social_work;
};

typedef struct Data Data;

struct Data {
  Data *next;
  Data *previous;

  Person *persona;
};

typedef struct Stack Stack;

struct Stack {
  Data *top;
  Data *bottom;
  int len;
};

void get_person_for_bottom(Stack *stack);
void atender_persona(Stack *stack);
void print_persons(Stack *stack);

void liberate_stack(Stack *stack);
void custom_free(Data **data);

void pop_person_on_top(Stack *stack);
void push_on_bottom(Stack *top, Person *persona);

void mock_persons(Stack *stack);

int main() {
  Stack *stack = malloc(sizeof(Stack));
  stack->top = NULL;
  stack->bottom = NULL;
  stack->len = 0;
  int option = 0;
  mock_persons(stack);
  Option arr[5] = {{"añadir una persona en la fila.", 1},
                   {"Atender una persona.", 2},
                   {"Ver personas", 1},
                   {"Borrar personas en la pila.", 8},
                   {"Salir.", 1}};

  Options options = {arr, 5};
  while (TRUE) {
    clear();
    menuOptionsEnumerated(options);
    inputLine();
    scanf("%d", &option);
    switch (option) {
    case 1:
      get_person_for_bottom(stack);
      continue;
    case 2:
      atender_persona(stack);
      continue;
    case 3:
      print_persons(stack);
      continue;
    case 4:
      liberate_stack(stack);
      continue;
    case 5:
      liberate_stack(stack);
      close_file();
      return 0;
    default:

      continue;
    }
  }
}

void print_persons(Stack *stack) {
  Data *current = stack->top;
  clear();
  topLine();
  int ac = 0;
  content("Cantidad de personas %d", stack->len);
  midLine();
  while (current != NULL) {
    content("Turno %d, nombre: %s, DNI: %d, Obra social: %s", ++ac,
            current->persona->name, current->persona->DNI,
            current->persona->social_work);
    midLine();
    current = current->next;
  }
  waiting();
}
void liberate_stack(Stack *stack)

{
  Data *current = stack->top;
  while (current != NULL) {
    printf("free: %s\n", current->persona->name);
    stack->top = stack->top->next;
    custom_free(&current);
    current = stack->top;
  }
  stack->top = NULL;
  stack->bottom = NULL;
  stack->len = 0;
}

void custom_free(Data **data) {
  if (data == NULL || *data == NULL) {
    return;
  }

  if ((*data)->persona != NULL) {
    free((*data)->persona->name);
    free((*data)->persona->social_work);
    free((*data)->persona);
  }

  free(*data);
  *data = NULL;
}
void atender_persona(Stack *stack) {
  clear();
  topLine();
  if (stack->top == NULL) {
    content("No hay personas para atender!");
    midLine();
    waiting();
    return;
  }
  content("Se va a atender a la persona %s, DNI: %d, obra social: %s",
          stack->top->persona->name, stack->top->persona->DNI,
          stack->top->persona->social_work);
  content("Ya se guardo en la base de datos!");
  midLine();
  FILE *file = get_file_instance();
  if (file != NULL) {
    fprintf(file, "DNI:%d, Nombre:%s,Obra social:%s\n",
            stack->top->persona->DNI, stack->top->persona->name,
            stack->top->persona->social_work);
    fflush(file); // Asegurarse de que los datos se escriban
  } else {
    printf("No se pudo abrir el archivo\n");
    return;
  }

  waiting();
  pop_person_on_top(stack);
}

void pop_person_on_top(Stack *stack) {
  if (stack->top == NULL)
    return;

  Data *current = stack->top;
  if (stack->len == 1 || stack->len == 0) {
    stack->top = NULL;
    stack->bottom = NULL;
    stack->len = 0;
    if (current != NULL) {
      custom_free(&current);
    }
  } else {
    stack->top = stack->top->next;
    stack->top->previous = NULL;
    stack->len--;
    if (stack->len == 1) {
      stack->bottom = stack->top;
      stack->top->next = NULL;
    }
    custom_free(&current);
  }
}

void push_on_bottom(Stack *stack, Person *persona) {
  Data *new_data = malloc(sizeof(Data));
  new_data->persona = persona;
  if (stack->bottom == NULL) {
    stack->bottom = new_data;
    stack->top = new_data;
    stack->top->next = NULL;
    stack->top->previous = NULL;
    stack->len++;
    return;
  }
  stack->bottom->next = new_data;
  new_data->previous = stack->bottom;
  stack->bottom = new_data;
  stack->bottom->next = NULL;
  stack->len++;
}

void get_person_for_bottom(Stack *Stack) {
  Person *new_person = malloc(sizeof(Person));
  new_person->name = malloc(sizeof(char) * 200);
  new_person->social_work = malloc(sizeof(char) * 200);
  new_person->DNI = 0;

  clear();
  topLine();
  content("Dame, el nombre de la persona");
  midLine();
  inputLine();
  if (scanf("%199s", new_person->name) != 1) {
    fprintf(stderr, "Error: No se pudo leer el nombre\n");
    free(new_person);
    exit(1);
  }

  clear();
  topLine();
  content("Dame, el DNI de %s", new_person->name);
  midLine();
  inputLine();
  scanf("%d", &new_person->DNI);

  clear();
  topLine();
  content("Dame, el La obra social de la persona de %s", new_person->name);
  midLine();
  inputLine();
  if (scanf("%199s", new_person->social_work) != 1) {
    fprintf(stderr, "Error: No se pudo leer el nombre\n");
    free(new_person);
    exit(1);
  }

  push_on_bottom(Stack, new_person);

  clear();
  topLine();
  content("persona incertada: DNI: %d, nombre: %s, obra social: %s",
          Stack->bottom->persona->DNI, Stack->bottom->persona->name,
          Stack->bottom->persona->social_work);
  midLine();
  waiting();
}

void mock_persons(Stack *stack) {
  Person *person1 = malloc(sizeof(Person));
  person1->name = strdup("Pato");
  person1->social_work = strdup("APOS");
  person1->DNI = 44329343;
  push_on_bottom(stack, person1);

  Person *person2 = malloc(sizeof(Person));
  person2->name = strdup("Juan");
  person2->social_work = strdup("OSDE");
  person2->DNI = 34329343;
  push_on_bottom(stack, person2);

  Person *person3 = malloc(sizeof(Person));
  person3->name = strdup("Pedro");
  person3->social_work = strdup("Swiss");
  person3->DNI = 24329343;
  push_on_bottom(stack, person3);

  Person *person4 = malloc(sizeof(Person));
  person4->name = strdup("Mateo");
  person4->social_work = strdup("OSECAC");
  person4->DNI = 14329343;
  push_on_bottom(stack, person4);
  
  Person *person5 = malloc(sizeof(Person));
  person5->name = strdup("Santiago");
  person5->social_work = strdup("PAMI");
  person5->DNI = 54329343;
  push_on_bottom(stack, person5);

  Person *person6 = malloc(sizeof(Person));
  person6->name = strdup("Lucas");
  person6->social_work = strdup("IOMA");
  person6->DNI = 64329343;
  push_on_bottom(stack, person6);

  Person *person7 = malloc(sizeof(Person));
  person7->name = strdup("Tomas");
  person7->social_work = strdup("OSPAC");
  person7->DNI = 74329343;
  push_on_bottom(stack, person7);

  Person *person8 = malloc(sizeof(Person));
  person8->name = strdup("Marcos");
  person8->social_work = strdup("MEDIFE");
  person8->DNI = 84329343;
  push_on_bottom(stack, person8);

  Person *person9 = malloc(sizeof(Person));
  person9->name = strdup("Juan Cruz");
  person9->social_work = strdup("GALENO");
  person9->DNI = 94329343;
  push_on_bottom(stack, person9);
}
