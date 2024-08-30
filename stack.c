#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct Data
 * @brief Nodo de la lista doblemente enlazada que compone la pila.
 * @param *data. puede ser cualquier cosa.
 *
 */
typedef struct Data
{
    void *data;          ///< Puntero genérico al dato almacenado.
    struct Data *next;   ///< Puntero al siguiente nodo.
    struct Data *former; ///< Puntero al nodo anterior.
} Data;

/**
 * @struct Stack
 * @brief Estructura de la pila que contiene punteros a la parte superior e inferior, junto con funciones de manipulación.
 */
typedef struct Stack Stack;

struct Stack
{
    /**
     * @brief Es el elemento que apunta a la parte superior de la pila.
     */
    Data *top; ///< Puntero al nodo superior de la pila.
    /**
     * @brief Es el elemento que apunta a la parte inferior de la pila.
     */
    Data *Bottom; ///< Puntero al nodo inferior de la pila.
    int len;      ///< Longitud actual de la pila.

    // Funciones para operaciones en la parte superior de la pila

    /**
     * @brief Inserta un elemento en la parte superior de la pila.
     *
     * @param self Puntero a la pila.
     * @param value Puntero al valor a insertar.
     */
    void (*push_on_top)(Stack *self, void *value);
    /**
     * @brief Elimina el elemento superior de la pila.
     *
     * @param self Puntero a la pila.
     */
    void (*delete_from_top)(Stack *self);

    // Funciones para operaciones en la parte inferior de la pila

    /**
     * @brief Inserta un elemento en la parte inferior de la pila.
     *
     * @param self Puntero a la pila.
     * @param value Puntero al valor a insertar.
     */
    void (*push_on_bottom)(Stack *self, void *value);
    /**
     * @brief Elimina el elemento inferior de la pila.
     *
     * @param self Puntero a la pila.
     */
    void (*delete_from_bottom)(Stack *self);

    // Operaciones por índice
    /**
     * @brief Elimina un nodo de la pila por su índice.
     *
     * @param self Puntero a la pila.
     * @param index Índice del nodo a eliminar.
     */
    void (*delete_by_index)(Stack *self, int index);
    /**
     * @brief Modifica un elemento de la pila por su índice aplicando una función.
     *
     * @param self Puntero a la pila.
     * @param index Índice del elemento a modificar.
     * @param func Función a aplicar al elemento.
     */
    void (*action_by_index)(Stack *self, int index, void (*func)(void *));
    /**
     * @brief Obtiene un nodo de la pila por su índice.
     *
     * @param self Puntero a la pila.
     * @param index Índice del nodo a obtener.
     * @return Data* Puntero al nodo en la posición especificada.
     */
    Data *(*get_by_index)(Stack *self, int index);

    // Operaciones especiales
    /**
     * @brief Busca el primer elemento que cumpla con un criterio especificado por una función.
     *
     * @param self Puntero a la pila.
     * @param critery Criterio de búsqueda.
     * @param func Función de comparación.
     * @return int Índice del primer elemento que cumple el criterio o -1 si no se encuentra.
     */
    int (*first)(Stack *self, void *critery, int (*func)(void *, void *));

    /**
     * @brief Aplica una función a cada elemento de la pila.
     *
     * @param self Puntero a la pila.
     * @param func Función a aplicar a cada elemento.
     */
    void (*foreach)(Stack *self, void (*func)(void *));
    /**
     * @brief Libera todos los nodos de la pila.
     *
     * @param self Puntero a la pila.
     */
    void (*liberate)(Stack *self);
    /**
     * @brief Aplica una función a cada elemento de la pila.
     *
     * @param self Puntero a la pila.
     * @param func Función a aplicar a cada elemento, este tambien tiene un indice.
     */
    void (*foreach_indexed)(Stack *self, void (*func)(void *, int index));
};

/**
 * @brief Aplica una función a cada elemento de la pila.
 *
 * @param self Puntero a la pila.
 * @param func Función a aplicar a cada elemento, este contiene el indice.
 */
void foreach_indexed(Stack *self, void (*func)(void *, int index))
{
    if (self->top == NULL)
    {
        return;
    }
    Data *current = self->top;
    int index = 0;
    while (current != NULL)
    {
        func(current->data, index);
        index++;
        current = current->next;
    }
}
/**
 * @brief Aplica una función a cada elemento de la pila.
 *
 * @param self Puntero a la pila.
 * @param func Función a aplicar a cada elemento.
 */
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

/**
 * @brief Modifica un elemento de la pila por su índice aplicando una función.
 *
 * @param self Puntero a la pila.
 * @param index Índice del elemento a modificar.
 * @param func Función a aplicar al elemento.
 */
void action_by_index(Stack *self, int index, void (*func)(void *))
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

/**
 * @brief Obtiene un nodo de la pila por su índice.
 *
 * @param self Puntero a la pila.
 * @param index Índice del nodo a obtener.
 * @return Data* Puntero al nodo en la posición especificada.
 */
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

/**
 * @brief Elimina un nodo de la pila por su índice.
 *
 * @param self Puntero a la pila.
 * @param index Índice del nodo a eliminar.
 */
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

    free(current->data); ///< Libera la memoria del dato almacenado en el nodo.
    free(current);       ///< Libera la memoria del nodo.

    self->len--;
}

/**
 * @brief Inserta un elemento en la parte superior de la pila.
 *
 * @param self Puntero a la pila.
 * @param value Puntero al valor a insertar.
 */
void push_on_top(Stack *self, void *value)
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

/**
 * @brief Elimina el elemento superior de la pila.
 *
 * @param self Puntero a la pila.
 */
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

    free(top_data->data); ///< Libera la memoria del dato almacenado.
    free(top_data);       ///< Libera la memoria del nodo.

    self->len--;
}

/**
 * @brief Elimina el elemento inferior de la pila.
 *
 * @param self Puntero a la pila.
 */
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

    free(bottom_data->data); ///< Libera la memoria del dato almacenado.
    free(bottom_data);       ///< Libera la memoria del nodo.

    self->len--;
}

/**
 * @brief Inserta un elemento en la parte inferior de la pila.
 *
 * @param self Puntero a la pila.
 * @param value Puntero al valor a insertar.
 */
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

/**
 * @brief Busca el primer elemento que cumpla con un criterio especificado por una función.
 *
 * @param self Puntero a la pila.
 * @param critery Criterio de búsqueda.
 * @param func Función de comparación.
 * @return int Índice del primer elemento que cumple el criterio o -1 si no se encuentra.
 */
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
            // todo, cambiar critery a lo encontrado critery = (current->data);
            return index;
        }
        index++;
        current = current->next;
    }
    return -1; // No se encontró ningún elemento que coincida
}

/**
 * @brief Libera todos los nodos de la pila.
 *
 * @param self Puntero a la pila.
 */
void liberate(Stack *self)
{
    while (self->len > 0)
    {
        delete_from_top(self);
    }
}

/**
 * @brief Crea e inicializa una nueva pila.
 *
 * @return Stack Una nueva pila inicializada.
 */
Stack new_stack()
{
    Stack stack;
    stack.len = 0;
    stack.top = NULL;
    stack.Bottom = NULL;

    // Inicializa las funciones
    stack.delete_from_top = delete_from_top;
    stack.push_on_top = push_on_top;

    stack.push_on_bottom = push_on_bottom;
    stack.delete_from_bottom = delete_from_bottom;

    stack.get_by_index = get_by_index;
    stack.action_by_index = action_by_index;
    stack.delete_by_index = delete_by_index;

    stack.first = first;
    stack.foreach = foreach;
    stack.foreach_indexed = foreach_indexed;
    stack.liberate = liberate;

    return stack;
}