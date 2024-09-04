#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definición de la estructura Data
typedef struct Data
{
    void *data;          // Puntero genérico al dato almacenado
    struct Data *next;   // Puntero al siguiente nodo
    struct Data *former; // Puntero al nodo anterior
} Data;

// Declaración anticipada de la estructura Stack
typedef struct Stack Stack;

// Definición de la estructura Stack
struct Stack
{
    Data *top;          // Puntero al nodo superior de la pila
    Data *Bottom;       // Puntero al nodo inferior de la pila
    int len;            // Longitud actual de la pila

    // Funciones para operaciones en la parte superior de la pila
    void (*push_on_top)(Stack *self, void *value);
    void (*delete_from_top)(Stack *self);

    // Funciones para operaciones en la parte inferior de la pila
    void (*push_on_bottom)(Stack *self, void *value);
    void (*delete_from_bottom)(Stack *self);

    // Operaciones por índice
    void (*delete_by_index)(Stack *self, int index);
    void (*action_by_index)(Stack *self, int index, void (*func)(void *));
    Data *(*get_by_index)(Stack *self, int index);

    // Operaciones especiales
    int (*first)(Stack *self, void *critery, int (*func)(void *, void *));
    void (*foreach)(Stack *self, void (*func)(void *));
    void (*liberate)(Stack *self);
    void (*custom_free)(void *data);
    void (*foreach_indexed)(Stack *self, void (*func)(void *, int index));
};

// Funciones disponibles para operar sobre la pila
void foreach_indexed(Stack *self, void (*func)(void *, int index));
void foreach(Stack *self, void (*func)(void *));
void action_by_index(Stack *self, int index, void (*func)(void *));
Data *get_by_index(Stack *self, int index);
void delete_by_index(Stack *self, int index);
void push_on_top(Stack *self, void *value);
void delete_from_top(Stack *self);
void delete_from_bottom(Stack *self);
void push_on_bottom(Stack *self, void *value);
int first(Stack *self, void *critery, int (*func)(void *, void *));
void liberate(Stack *self);
Stack new_stack(void (*custom_free)(void *data));

#endif // STACK_H
