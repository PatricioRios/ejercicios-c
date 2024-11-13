#include "ui.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
Se tiene dos listas de precio de m elementos en las cuales están los códigos de 
cada artículo estando algunos repetidos en las dos listas se desea realizar a través 
de un algoritmo una sola lista con los artículos sin estar repetidos

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Data Data;
typedef struct Stack Stack;

struct Data {
    int code;       // Código del artículo
    float price;    // Precio del artículo
    Data *next;
    Data *former;
};

struct Stack {
    Data *top;
    Data *bottom;
    int len;
};

// Función para inicializar una pila vacía
void init_stack(Stack *stack) {
    stack->top = NULL;
    stack->bottom = NULL;
    stack->len = 0;
}

// Función para agregar un artículo al final de la pila
void push_bottom(Stack *stack, int code, float price) {
    Data *new_data = (Data*)malloc(sizeof(Data));
    new_data->code = code;
    new_data->price = price;
    new_data->next = NULL;
    new_data->former = stack->bottom;

    if (stack->len == 0) {
        stack->top = new_data;
        stack->bottom = new_data;
    } else {
        stack->bottom->next = new_data;
        stack->bottom = new_data;
    }
    stack->len++;
}

// Función para buscar si un código de artículo ya está en la pila
int contains(Stack *stack, int code) {
    Data *current = stack->top;
    while (current != NULL) {
        if (current->code == code) {
            return 1; // Encontrado
        }
        current = current->next;
    }
    return 0; // No encontrado
}

// Función para combinar dos pilas en una sin duplicados
void merge_stacks(Stack *stack1, Stack *stack2, Stack *result) {
    Data *current;

    // Agregar todos los elementos de stack1 a la pila resultante
    current = stack1->top;
    while (current != NULL) {
        if (!contains(result, current->code)) {
            push_bottom(result, current->code, current->price);
        }
        current = current->next;
    }

    // Agregar todos los elementos de stack2 a la pila resultante (evitando duplicados)
    current = stack2->top;
    while (current != NULL) {
        if (!contains(result, current->code)) {
            push_bottom(result, current->code, current->price);
        }
        current = current->next;
    }
}

// Función para imprimir la pila
void print_stack(Stack *stack) {
    Data *current = stack->top;
    printf("Elementos de la pila:\n");
    while (current != NULL) {
        printf("Código: %d, Precio: %.2f\n", current->code, current->price);
        current = current->next;
    }
}

int main() {
    Stack lista1, lista2, lista_resultante;

    init_stack(&lista1);
    init_stack(&lista2);
    init_stack(&lista_resultante);

    // Insertar algunos artículos en la lista1
    push_bottom(&lista1, 101, 100.50);
    push_bottom(&lista1, 102, 200.75);
    push_bottom(&lista1, 103, 300.10);
    push_bottom(&lista1, 101, 100.50); // Artículo repetido

    // Insertar algunos artículos en la lista2
    push_bottom(&lista2, 101, 100.50);
    push_bottom(&lista2, 104, 400.20);
    push_bottom(&lista2, 102, 200.75); // Artículo repetido
    push_bottom(&lista2, 105, 500.60);

    printf("Listas anteriores \n");
    print_stack(&lista1);
    print_stack(&lista2);
    printf("\n");
    
    // Combinar las dos listas sin duplicados
    merge_stacks(&lista1, &lista2, &lista_resultante);

    // Imprimir la lista resultante
    print_stack(&lista_resultante);

    return 0;
}
