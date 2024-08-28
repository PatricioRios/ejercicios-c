#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string50.c"
#include "rand.c"

/*

Confeccionar un programa que permina el ingreso de un apellido un nombre, el legajo de 10 empleados.

a) se debe asegurar que el apellido debera ser registrado en mayuscula
B) el nombre, la primera letra con mayuscula y el resto con minuscula
c) el legajo se construira a partir de las iniciales del apellido y nombre mas un numero de 3 cifras aleatorios
d) generar tablas por genero

*/

typedef struct
{
    string50 name;
    string50 apellido;
    string50 legajo;
    int genero; // 1 masculino 0 femenino
} empleado;

int lastIndex = 0;

int esMayuscula(char caracter)
{
    if (caracter >= 65 && caracter <= 90)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int esMinuscula(char caracter)
{
    if (caracter >= 97 && caracter <= 122)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validationLastName(char *lastName)
{
    int i = 0;
    while (lastName[i] != '\0')
    {
        if (esMayuscula(lastName[i]) == 1)
        {
            i++;
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void getLastName(empleado *empleados)
{
    while (0 == 0)
    {
        char lastName[50];
        printf("\nDame el apellido de el empleado %s\n", empleados[lastIndex].name.str);
        scanf("%s", lastName);
        printf("AGARRO\n");
        if (validationLastName(lastName) == 1)
        {
            printf("ENTRO\n");

            empleados[lastIndex].apellido = newString50(lastName);
            break;
        }
    }
}

int validationName(char *name)
{
    if (esMayuscula(name[0]) != 1)
    {
        printf("isMay[0]");
        return 0;
    }
    int i = 1;
    while (name[i] != '\0')
    {
        if (esMinuscula(name[i]) == 1)
        {
            i++;
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void getName(empleado *empleados)
{
    while (0 == 0)
    {
        char name[50];
        printf("\nIngresar el nombre de el empleado ( primera en Mayuscula y las demas en minuscula)\n");
        scanf("%s", name);

        if (validationName(name) == 1)
        {
            printf("true\n");
            empleados[lastIndex].name = newString50(name);
            break;
        }
        printf("flase\n");

        continue;
    }
}
// 1 okay, 0 error

void printEmpleados(empleado *empleados)
{
    printf("HOMBRES\n");
    for (int i = 0; i < lastIndex + 1; i++)
    {
        if (empleados[i].genero == 1)
        {
            printf("nombre: %s\n", empleados[i].name.str);
            printf("apellido: %s\n", empleados[i].apellido.str);
            printf("legajo: %s\n", empleados[i].legajo.str);
            printf("genero: %d\n", empleados[i].genero);
        }
    }

    printf("MUJERES\n");

    for (int i = 0; i < lastIndex + 1; i++)
    {
        if (empleados[i].genero == 0)
        {
            printf("nombre: %s\n", empleados[i].name.str);
            printf("apellido: %s\n", empleados[i].apellido.str);
            printf("legajo: %s\n", empleados[i].legajo.str);
            printf("genero: %d\n", empleados[i].genero);
        }
    }
}

void cargarEmpleados(empleado *empleados)
{
    getName(empleados);
    getLastName(empleados);
    printf("Dame el genero de el empleado\n");
    int genero;
    scanf("%d", &genero);
    empleados[lastIndex].genero = genero;

    char legajo[50];
    legajo[0] = empleados[lastIndex].apellido.str[0];
    legajo[1] = empleados[lastIndex].apellido.str[1];
    legajo[2] = empleados[lastIndex].apellido.str[2];

    legajo[3] = empleados[lastIndex].name.str[0];
    legajo[4] = empleados[lastIndex].name.str[1];
    legajo[5] = empleados[lastIndex].name.str[2];
    legajo[6] = (char)getRand(48, 57);
    legajo[7] = (char)getRand(48, 57);
    legajo[8] = (char)getRand(48, 57);

    legajo[9] = '\0';
    empleados[lastIndex].legajo = newString50(legajo);

    lastIndex++;
}

int main()
{
    empleado *empleados = malloc(sizeof(empleado) * 10);

    for (int i = 0; i < 10; i++)
    {
        int option;
        printf("hay %d personas cargadas en el sistema\n", lastIndex);

        printf("1 para ingresar una persona\n");
        printf("2 para mostrar las personas ingresadas\n");
        printf("3 para fin de programa\n");

        scanf("%d", &option);
        if (option == 1)
        {
            cargarEmpleados(empleados);
        }
        if (option == 2)
        {
            printEmpleados(empleados);
        }
        if (option == 3)
        {
            printf("Goodbye!");
            return 0;
        }
        printf("Opcion no valida Ingrese 1, 2 o 3\n");
    }
}