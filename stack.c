#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int num;
} Numero;

typedef struct Data
{
    void *data;
    struct Data *next;
    struct Data *former; // Puntero al siguiente elemento de la pila
} Data;

typedef struct Stack Stack;

struct Stack
{
    Data *top;    // Puntero al elemento superior de la pila
    Data *Bottom; // Puntero al elemento inferior de la pila
    int len;      // Longitud actual de la pila
    void (*foreach)(Stack *self, void (*func)(void *));
    void (*modify_by_index)(Stack *self, int index, void (*func)(void *));
    Data *(*get_by_index)(Stack *self, int index);
    void (*liberate)(Stack *self);
};

// Función foreach que aplica una función a cada elemento de la pila
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

// Función modify_by_index que aplica una función al elemento en un índice dado
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

// Función get_by_index que retorna un puntero a Data en un índice dado
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

    return current; // Retornas el nodo Data en el índice solicitado.
}

void delete_by_index(Stack *self, int index)
{
    if (self->len == 0 || index < 0 || index >= self->len)
    {
        printf("Invalid index: %d\n", index);
        return;
    }

    Data *current = self->top;

    // Si es el primer elemento (top)
    if (index == 0)
    {
        self->top = current->next;
        if (self->top != NULL)
        {
            self->top->former = NULL;
        }
        else
        {
            self->Bottom = NULL; // Si solo hay un elemento
        }
    }
    else if (index == self->len - 1) // Si es el último elemento (bottom)
    {
        current = self->Bottom;
        self->Bottom = current->former;
        if (self->Bottom != NULL)
        {
            self->Bottom->next = NULL;
        }
        else
        {
            self->top = NULL; // Si solo hay un elemento
        }
    }
    else
    {
        // Recorre hasta el índice deseado
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        Data *former = current->former;
        Data *next = current->next;

        // Ajusta los punteros del nodo anterior y el siguiente
        if (former != NULL)
        {
            former->next = next;
        }
        if (next != NULL)
        {
            next->former = former;
        }
    }

    // Libera el nodo actual
    free(current);

    // Decrementa la longitud de la pila
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

void print_num(void *data)
{
    Numero *num = (Numero *)data;
    printf("Element: %d\n", num->num);
}

typedef struct
{
    void (*print_stack)(void *data);
} Printer;

void print_stack_perzonalized(Stack *self, Printer *printer)
{
    Data *current = self->top;
    for (int i = 0; i < self->len; i++)
    {
        printer->print_stack(current->data);
        current = current->next;
    }
}

Printer num_printer = {
    .print_stack = print_num};

void modify(void *data)
{
    Numero *numero = (Numero *)data;
    numero->num = 125;
}

Stack new_stack()
{
    Stack stack;
    stack.len = 0;
    stack.top = NULL;
    stack.Bottom = NULL;
    stack.foreach = foreach; // Inicializa el puntero a la función foreach
    stack.get_by_index = get_by_index;
    stack.modify_by_index = modify_by_index;
    stack.liberate = liberate;
    return stack;
}

int main()
{
    Stack stack = new_stack();

    for (int i = 0; i < 12; i++)
    {
        Numero *numero = malloc(sizeof(Numero));
        numero->num = i;
        push(&stack, numero);
    }

    Numero *top_num = (Numero *)stack.top->data;
    printf("Top element: %d\n", top_num->num);

    Numero *bottom_num = (Numero *)stack.Bottom->data;
    printf("Bottom element: %d\n", bottom_num->num);

    delete_from_top(&stack);
    printf("=========\n");

    Numero *numero = malloc(sizeof(Numero));
    numero->num = 22;
    push_on_bottom(&stack, numero);
    printf("=========\n");

    print_stack_perzonalized(&stack, &num_printer);

    delete_from_top(&stack);
    delete_from_bottom(&stack);
    printf("=========\n");
    print_stack_perzonalized(&stack, &num_printer);
    delete_from_bottom(&stack);
    printf("=========\n");
    print_stack_perzonalized(&stack, &num_printer);

    printf("foreach\n");
    stack.foreach (&stack, print_num);

    printf("len =%d\n", stack.len);
    printf("foreach\n");
    stack.foreach (&stack, print_num);

    printf("len =%d\n", stack.len);

    Numero *numero1 = (Numero *)stack.get_by_index(&stack, 7)->data;

    printf("Numero = %d\n", numero1->num);

    numero1->num = 44;
    printf("Numero = %d\n", numero1->num);

    stack.modify_by_index(&stack, 7, modify);
    printf("Numero = %d\n", numero1->num);

    printf("=========\n");

    stack.foreach (&stack, print_num);
    printf("=========\n");

    delete_by_index(&stack, 4);
    printf("=========after\n");

    stack.foreach (&stack, print_num);

    return 0;
}