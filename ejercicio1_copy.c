#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string50.c"
#include "rand.c"
#include "boolconst.c"
#include "ui.c"

/*

Confeccionar un programa que permina el ingreso de un apellido un nombre, el legajo de 10 empleados.

a) se debe asegurar que el apellido debera ser registrado en mayuscula
B) el nombre, la primera letra con mayuscula y el resto con minuscula
c) el legajo se construira a partir de las iniciales del apellido y nombre mas un numero de 3 cifras aleatorios
d) generar tablas por genero

*/

// gcc ejercicio1\ copy.c -o ejerciciocopi.e

typedef struct
{
    string50 name;
    string50 lastName;
    string50 legajo;
    int genre; // 1 masculino 0 femenino
} employee;

int lastIndex = 0;

int isUpperCase(char character)
{
    if (character >= 65 && character <= 90)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isLowerCase(char character)
{
    if (character >= 97 && character <= 122)
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
    while (*lastName != '\0')
    {
        if (isUpperCase(*lastName) == 1)
        {
            lastName++;
            continue;
        }
        else
        {
            return 0;
        }
        lastName++;
    }
    return 1;
}

void getLastName(employee *employee)
{
    clear();
    topLine();
    content("Dame el apellido de el empleado %s", employee->name.str);
    midLine();
    inputLine();
    while (0 == 0)
    {
        char lastName[50];
        scanf("%s", lastName);
        if (validationLastName(lastName) == 1)
        {
            employee->lastName = newString50(lastName);
            return;
        }
        clear();
        topLine();
        content("Dame el apellido de el empleado %s", employee->name.str);
        midLine();
        content("error: todo debe ser en MAYUSCULA");
        midLine();
        inputLine();
    }
}

int validationName(char *name)
{
    if (isUpperCase(*name) != 1)
    {
        return 0;
    }
    name++;
    while (*name != '\0')
    {
        if (isLowerCase(*name) == 1)
        {
            name++;
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void getName(employee *employee)
{
    clear();

    topLine();
    content("Ingresar el nombre de el empleado");
    content("( primera en Mayuscula y las demas en minuscula)");
    midLine();
    inputLine();
    while (0 == 0)
    {
        char name[50];

        scanf("%s", name);

        if (validationName(name) == 1)
        {
            printf("true\n");
            employee->name = newString50(name);
            break;
        }
        clear();

        topLine();
        content("El nombre ingresado no tiene la primera letra en mayuscula y el resto en minuscula");
        midLine();
        content("Ingresar el nombre de el empleado");
        content("( primera en Mayuscula y las demas en minuscula)");
        midLine();
        inputLine();
    }
}

void printEmployee(employee employee)
{
    content("nombre: %s", employee.name.str);
    content("apellido: %s", employee.lastName.str);
    content("legajo: %s", employee.legajo.str);
    if (employee.genre == 1)
    {
        content("genero: Hombre");
    }
    else
    {
        content("genero: Mujer");
    }
}

void printEmployees(employee *employees)
{
    clear();
    topLine();
    content("HOMBRES");
    for (int i = 0; i < lastIndex + 1; i++)
    {
        if (employees[i].genre == 1)
        {
            midLine();
            printEmployee(employees[i]);
        }
    }
    midLine();
    content("Mujeres");
    for (int i = 0; i < lastIndex + 1; i++)
    {
        if (employees[i].genre == 0)
        {
            if (employees[i].name.str[0] != '\0')
            {
                midLine();
                printEmployee(employees[i]);
            }
        }
    }
    midLine();
    content("Coloca cualquier caracter para continuar");
    midLine();
    inputLine();
    char aux[3];
    scanf("%s", aux);
    fflush(stdin);
}
void getGenre(employee *employee)
{
    clear();
    topLine();
    content("Dame el genero de el empleado %s %s (1 = hombre, 0 = mujer)", employee->name.str, employee->lastName.str);
    midLine();
    inputLine();
    int genre;
    while (0 == 0)
    {
        scanf("%d", &genre);
        if (genre == 0 || genre == 1)
        {
            employee->genre = genre;
            return;
        }
        clear();
        topLine();
        content("Dame el genero de el empleado %s %s (0 = mujer , 1 = hombre)", employee->name.str, employee->lastName.str);
        midLine();
        content("error: la entrada debe ser 1 o 0");
        midLine();
        inputLine();
    }
}
void generateId(employee *employee)
{
    char legajo[50];
    legajo[0] = employee->lastName.str[0];
    legajo[1] = employee->lastName.str[1];
    legajo[2] = employee->lastName.str[2];

    legajo[3] = employee->name.str[0];
    legajo[4] = employee->name.str[1];
    legajo[5] = employee->name.str[2];

    legajo[6] = (char)getRand(48, 57);
    legajo[7] = (char)getRand(48, 57);
    legajo[8] = (char)getRand(48, 57);

    legajo[9] = '\0';
    employee->legajo = newString50(legajo);
}

void loadEmployees(employee *employees)
{
    getName(&employees[lastIndex]);
    getLastName(&employees[lastIndex]);
    getGenre(&employees[lastIndex]);
    generateId(&employees[lastIndex]);

    lastIndex++;
}

int main()
{
    employee *employees = malloc(sizeof(employee) * 10);

    while (TRUE)
    {
        int option;
        // printf("hay %d personas cargadas en el sistema\n", lastIndex);
        // printf("1 para ingresar una persona\n");
        // printf("2 para mostrar las personas ingresadas\n");
        // printf("3 para fin de programa\n");
        clear();
        topLine();
        content("hay %d personas en el sistema", lastIndex);
        midLine();
        content("1 para ingresar una persona");
        midLine();
        content("2 para mostrar las personas ingresadas");
        midLine();
        content("3 para fin de programa");
        midLine();
        if (option < 0 || option > 3)
        {
            content("Opcion no valida, eliga un numero entre el 0 y 3");
            midLine();
        }
        inputLine();

        scanf("%d", &option);
        if (option == 1)
        {
            loadEmployees(employees);
            continue;
        }
        if (option == 2)
        {
            printEmployees(employees);
            continue;
        }
        if (option == 3)
        {
            system("clear");
            printf("\nGoodbye!\n\n");
            return 0;
        }
    }
}