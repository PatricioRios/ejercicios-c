#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.c"

typedef struct
{
    int *num; // Puntero a entero
} Numero;

void print_num(void *data)
{
    Numero *num = (Numero *)data;
    printf("Element: %d\n", *(num->num)); // Desreferencia el puntero para obtener el valor
}

void modify(void *data)
{
    Numero *numero = (Numero *)data;
    *(numero->num) = 125; // Modifica el valor apuntado por el puntero
}

int searcher(void *data, void *critery)
{
    Numero *num = (Numero *)data;
    Numero *crit = (Numero *)critery;

    if (crit->num != NULL && *(crit->num) == *(num->num))
    {

        return 1; // Elemento encontrado
    }

    return 0; // No encontrado
}

int main()
{
    Stack stack = new_stack();

    for (int i = 0; i < 12; i++)
    {
        Numero *numero = malloc(sizeof(Numero));
        numero->num = malloc(sizeof(int)); // Reserva memoria para el entero
        *(numero->num) = i;
        push(&stack, numero);
    }

    Numero *top_num = (Numero *)stack.top->data;
    printf("Top element: %d\n", *(top_num->num));

    Numero *bottom_num = (Numero *)stack.Bottom->data;
    printf("Bottom element: %d\n", *(bottom_num->num));

    delete_from_top(&stack);
    printf("=========\n");

    Numero *numero = malloc(sizeof(Numero));
    numero->num = malloc(sizeof(int));
    *(numero->num) = 22;
    push_on_bottom(&stack, numero);
    printf("=========\n");

    delete_from_bottom(&stack);
    printf("=========\n");
    stack.foreach (&stack, print_num);

    printf("foreach\n");
    stack.foreach (&stack, print_num);

    printf("len =%d\n", stack.len);

    Numero *numero1 = (Numero *)stack.get_by_index(&stack, 7)->data;

    printf("Numero = %d\n", *(numero1->num));

    *(numero1->num) = 44;
    printf("Numero = %d\n", *(numero1->num));

    stack.modify_by_index(&stack, 7, modify);
    printf("Numero = %d\n", *(numero1->num));

    stack.foreach (&stack, print_num);
    printf("=========\n");

    delete_by_index(&stack, 4);
    printf("=========after\n");

    stack.foreach (&stack, print_num);

    Numero *founded = malloc(sizeof(Numero));
    founded->num = malloc(sizeof(int));
    *founded->num = 3;

    printf("Found : %d\n", *(founded->num));

    int index = first(&stack, founded, searcher);

    if (index != -1)
    {
        printf("Founded : %d, index: %d\n", *(founded->num), index);
    }
    else
    {
        printf("Element not found\n");
    }
    stack.modify_by_index(&stack, index, print_num);
    return 0;
}