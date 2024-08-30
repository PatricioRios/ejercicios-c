#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Data
{
    void *data;
    struct Data *next;
    struct Data *former;
} Data;

typedef struct Stack Stack;

struct Stack
{
    Data *top;
    Data *Bottom;
    int len;
    void (*foreach)(Stack *self, void (*func)(void *));
    void (*modify_by_index)(Stack *self, int index, void (*func)(void *));
    Data *(*get_by_index)(Stack *self, int index);
    void (*liberate)(Stack *self);
};

void foreach (Stack *self, void (*func)(void *))
{
    if (self->top == NULL)
    {
        return;
    }
    Data *current = self->top;
    while (current != NULL)
    {
        func(current->data);
        current = current->next;
    }
}

void modify_by_index(Stack *self, int index, void (*func)(void *))
{
    if (index < 0 || index >= self->len)
    {
        printf("Invalid index: %d\n", index);
        return;
    }

    Data *current = self->top;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    func(current->data);
}

Data *get_by_index(Stack *self, int index)
{
    if (index < 0 || index >= self->len)
    {
        printf("Invalid index: %d\n", index);
        return NULL;
    }

    Data *current = self->top;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current;
}

void delete_by_index(Stack *self, int index)
{
    if (self->len == 0 || index < 0 || index >= self->len)
    {
        printf("Invalid index: %d\n", index);
        return;
    }

    Data *current = self->top;

    if (index == 0)
    {
        self->top = current->next;
        if (self->top != NULL)
        {
            self->top->former = NULL;
        }
        else
        {
            self->Bottom = NULL;
        }
    }
    else if (index == self->len - 1)
    {
        current = self->Bottom;
        self->Bottom = current->former;
        if (self->Bottom != NULL)
        {
            self->Bottom->next = NULL;
        }
        else
        {
            self->top = NULL;
        }
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        Data *former = current->former;
        Data *next = current->next;

        if (former != NULL)
        {
            former->next = next;
        }
        if (next != NULL)
        {
            next->former = former;
        }
    }

    // todo
    // free(((Numero *)current->data)->num); // Libera el entero
    free(current->data);
    free(current);

    self->len--;
}

void push(Stack *self, void *value)
{
    Data *new_data = malloc(sizeof(Data));
    if (new_data == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    if (self->top != NULL)
    {
        self->top->former = new_data;
    }
    new_data->data = value;
    new_data->next = self->top;
    new_data->former = NULL;
    if (self->len == 0)
    {
        self->Bottom = new_data;
    }
    self->top = new_data;
    self->len++;
}

void delete_from_top(Stack *self)
{
    if (self->len == 0)
    {
        printf("Stack underflow: no elements to pop\n");
        return;
    }

    Data *top_data = self->top;
    self->top = top_data->next;
    if (self->top != NULL)
    {
        self->top->former = NULL;
    }
    // TODO:free(((Numero *)top_data->data)->num); // Libera el entero
    free(top_data->data);
    free(top_data);

    self->len--;
}

void delete_from_bottom(Stack *self)
{
    if (self->len == 0)
    {
        printf("Stack underflow: no elements to pop\n");
        return;
    }

    Data *bottom_data = self->Bottom;
    self->Bottom = bottom_data->former;
    if (self->Bottom != NULL)
    {
        self->Bottom->next = NULL;
    }
    // TODO:free(((Numero *)top_data->data)->num); // Libera el entero
    free(bottom_data->data);
    free(bottom_data);

    self->len--;
}

void push_on_bottom(Stack *self, void *value)
{
    Data *new_data = malloc(sizeof(Data));
    if (new_data == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_data->data = value;
    new_data->next = NULL;
    if (self->Bottom != NULL)
    {
        self->Bottom->next = new_data;
        new_data->former = self->Bottom;
    }
    else
    {
        self->top = new_data;
        new_data->former = NULL;
    }
    self->Bottom = new_data;
    self->len++;
}

void liberate(Stack *self)
{
    while (self->len > 0)
    {
        delete_from_top(self);
    }
}

int first(Stack *self, void *critery, int (*func)(void *, void *))
{
    if (self->top == NULL)
    {
        return -1;
    }
    Data *current = self->top;
    int index = 0;
    while (current != NULL)
    {
        if (func(current->data, critery) == 1)
        {
            critery = current->data;
            return index;
        }
        index++;
        current = current->next;
    }
    return -1; // No se encontró ningún elemento que coincida
}

Stack new_stack()
{
    Stack stack;
    stack.len = 0;
    stack.top = NULL;
    stack.Bottom = NULL;
    stack.foreach = foreach;
    stack.get_by_index = get_by_index;
    stack.modify_by_index = modify_by_index;
    stack.liberate = liberate;
    return stack;
}
