#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string50.c"
#include "rand.c"

typedef struct
{
    string50 nombre;
    string50 apellido;
} Persona;

void cargarPersona(Persona *persona, char *name, char *lastName){
    persona->nombre = newString50(name);
    persona->apellido = newString50(lastName);
}

void cargarPersonas(Persona *personas)
{
    cargarPersona(personas,"patricio","rios");
    personas++;
    cargarPersona(personas,"claudio","reynoso");
    personas++;
    cargarPersona(personas,"ronaldo","nazari");
    personas++;
    cargarPersona(personas,"jaun","facundo");
    personas++;
    cargarPersona(personas,"yoel","navarro");
    personas++;
    cargarPersona(personas,"leo","messi");
}

void printPersonas(Persona *personas)
{
    printf("=======================\n");
    for (int i = 0; i < 6; i++)
    {
        printf("PERSONA NRO: %d  ", i);
        printf("nombre: %s  ", personas[i].nombre.str);
        printf("apellido: %s  \n", personas[i].apellido.str);
    }
}

void removerPersona(Persona *personas, int index)
{
    for (int i = 0; i < 6; i++)
    {
        if (i == index)
        {
            strcpy(personas[i].nombre.str, "");
            strcpy(personas[i].apellido.str, "");
        }
    }
}

void movePersonas(Persona *personas)
{
    Persona aux;
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(personas[i].nombre.str, "") == 0)
        {
            aux = personas[i];
            personas[i] = personas[i + 1];
            personas[i + 1] = aux;
        }
    }
}

void reorderPersons(Persona *personas)
{
    int i = 0, j = 0;
    Persona aux;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
            if (personas[i].apellido.value < personas[j].apellido.value)
            {
                aux = personas[i];
                personas[i] = personas[j];
                personas[j] = aux;
            }
        }
    }
    
}

int main()
{
    srand(NULL);

    Persona *personas = malloc(10*sizeof(Persona));
    cargarPersonas(personas);
    printPersonas(personas);

    movePersonas(personas);
    reorderPersons(personas);
    printPersonas(personas);

    char str[50];
    my_strcpy(str, "holajuan123");
    printf("\n COMPARACION %d\n", my_strcmp("holaaa", "holaaa"));
    printf("\n%s \n", str);
    printf("NUEVO ============================\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Rand %d \n", getRandBit());
    }
    printf("NUEVO ============================\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Rand %d \n", getRand(5,10));
    }
    printf("NUEVO ============================\n");

    printf("%d\n",&personas[0]);
    printf("%d\n",&personas[1]);
    printf("%d\n",&personas[2]);





    return 0;
}                                                                      