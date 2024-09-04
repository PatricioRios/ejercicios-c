#include "boolconst.c"
#include "ui.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Person Person;
struct Person
{
    int edad;
    char *nombre;
};

typedef struct Data Data;

struct Data
{
    Data *next;
    Data *previous;

    Person *persona;
};

typedef struct Stack Stack;

struct Stack
{
    Data *top;
    Data *bottom;
    int len;
};

void get_person_on_bottom(Stack *stack);
void atender_persona(Stack *stack);
void print_persons(Stack *stack);

void liberate_stack(Stack *stack);
void custom_free(Data **data);

void pop_person_on_top(Stack *stack);
void push_on_bottom(Stack *top, Person *persona);

int main()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    stack->bottom = NULL;
    stack->len = 0;
    int option = 0;
    Option arr[4] = {
        {"añadir una persona en la fila.", 1},
        {"Atender una persona.", 2},
        {"Ver personas", 1},
        {"Salir.", 8}};

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
            get_person_on_bottom(stack);
            break;
        case 2:
            atender_persona(stack);
            break;
        case 3:
            print_persons(stack);
            break;
        case 4:
            liberate_stack(stack);
            break;
        default:
            break;
        }
    }
}

void print_persons(Stack *stack)
{
    Data *current = stack->top;
    clear();
    topLine();
    int ac = 0;
    while (current != NULL)
    {
        content("Persona %d, nombre: %s, edad %d", ac++, current->persona->nombre, current->persona->edad);
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
        custom_free(&current);
        stack->top = stack->top->next;
        current = stack->top;
    }
}

void custom_free(Data **data)
{
    if (data == NULL || *data == NULL)
    {
        return; // Guard against NULL pointers
    }

    if ((*data)->persona != NULL)
    {
        free((*data)->persona->nombre);
        free((*data)->persona);
    }

    free(*data);
    *data = NULL; // Set the pointer to NULL after freeing
}
void atender_persona(Stack *stack)
{
    clear();
    topLine();
    content("Se va a atender a la persona %s, de edad %d", stack->top->persona->nombre, stack->top->persona->edad);
    midLine();
    waiting();
    pop_person_on_top(stack);
}

void pop_person_on_top(Stack *stack)
{
    Data *current = stack->top;
    stack->top = stack->top->next;
    custom_free(&current);
}

void push_on_bottom(Stack *stack, Person *persona)
{
    Data *new_data = malloc(sizeof(Data));
    new_data->persona = persona;
    if (stack->bottom == NULL)
    {
        stack->bottom = new_data;
        stack->top = new_data;
        return;
    }
    stack->bottom->next = new_data;
    new_data->previous = stack->bottom;
    stack->bottom = new_data;
}

void get_person_on_bottom(Stack *Stack)
{
    Person *new_person = malloc(sizeof(Person));
    new_person->nombre = malloc(sizeof(char) * 200);
    new_person->edad = 0;
    clear();
    topLine();
    content("Dame, el nombre de la persona");
    midLine();
    inputLine();
    if (scanf("%199s", new_person->nombre) != 1)
    {
        fprintf(stderr, "Error: No se pudo leer el nombre\n");
        free(new_person);
        exit(1);
    }
    clear();
    topLine();
    content("Dame, la edad de la persona");
    midLine();
    inputLine();
    scanf("%d", &new_person->edad);
    push_on_bottom(Stack, new_person);
    clear();
    topLine();
    content("Nombre de la persona incertada: %s, edad: %d", Stack->bottom->persona->nombre, Stack->bottom->persona->edad);
    midLine();
    waiting();
}
