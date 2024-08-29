#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*
    char *str;
    int len;
    int capacity;
*/
struct String
{
    char *str;
    int len;
    int capacity;
} typedef String;

String StrNewFrom(char *str);
String StrNewFromStr(char *str);
int StrCompare(String a, String b);
int StrInsert(String *dest, char *str);
int StrPushChar(String *s, char c);
int StrPopChar(String *s);
int StrReplace(String *s, char *new_str);
int StrTo(String *s, char *new_str);
int StrToUpper(String *s);
int StrToLower(String *s);

String StrNewFrom(char *str)
{
    int len = strlen(str);
    char *new_str = malloc(sizeof(char) * (len + 1)); // +1 para el carácter nulo
    if (new_str == NULL)
    {
        exit(1); // Salir si la memoria no se pudo asignar
    }
    strcpy(new_str, str); // Copia la cadena
    String result;
    result.len = len;
    result.capacity = len;
    result.str = new_str;
    return result;
}

String StrNewFromStr(char *str)
{
    return StrNewFrom(str);
}

int StrCompare(String a, String b)
{
    if (strcmp(a.str, b.str) == 0)
    {
        return 1; // Las cadenas son iguales
    }
    return 0; // Las cadenas son diferentes
}

int StrInsert(String *dest, char *str)
{
    int len = strlen(str);
    if (dest->len + len > dest->capacity)
    {
        char *new_str = realloc(dest->str, sizeof(char) * (dest->len + len + 1)); // +1 para el carácter nulo
        if (new_str == NULL)
        {
            return 0; // No se pudo redimensionar
        }
        dest->str = new_str;
        dest->capacity = dest->len + len;
    }
    strcat(dest->str, str);
    dest->len += len;
    return 1; // Confirmar éxito
}

int StrPushChar(String *s, char c)
{
    if (s->len + 1 > s->capacity)
    {
        char *new_str = realloc(s->str, sizeof(char) * (s->len + 2)); // +2: uno para el nuevo carácter, uno para el '\0'
        if (new_str == NULL)
        {
            return 0; // No se pudo redimensionar
        }
        s->str = new_str;
        s->capacity = s->len + 1;
    }
    s->str[s->len] = c;
    s->len++;
    s->str[s->len] = '\0'; // Asegura el carácter nulo al final
    return 1;              // Confirmar éxito
}

int StrPopChar(String *s)
{
    if (s->len == 0)
    {
        return 0; // No hay caracteres para eliminar
    }
    s->len--;
    s->str[s->len] = '\0'; // Asegura el carácter nulo al final
    return 1;              // Confirmar éxito
}

int StrReplace(String *s, char *new_str)
{
    int new_len = strlen(new_str);

    // Verifica si la nueva cadena cabe en la capacidad actual
    if (new_len > s->capacity)
    {
        // Redimensiona la memoria
        char *resized_str = realloc(s->str, sizeof(char) * (new_len + 1)); // +1 para el carácter nulo
        if (resized_str == NULL)
        {
            return 0; // Fallo en la reasignación de memoria
        }
        s->str = resized_str;
        s->capacity = new_len;
    }

    // Copia la nueva cadena a la estructura
    strcpy(s->str, new_str);
    s->len = new_len;

    return 1; // Confirmar éxito
}

int StrTo(String *s, char *new_str)
{
    return StrReplace(s, new_str);
}

int StrToUpper(String *s)
{
    for (int i = 0; i < s->len; i++)
    {
        s->str[i] = toupper(s->str[i]); // Convierte cada carácter a mayúscula
    }
    return 1; // Confirmar éxito
}
int StrToLower(String *s)
{
    for (int i = 0; i < s->len; i++)
    {
        s->str[i] = tolower(s->str[i]); // Convierte cada carácter a mayúscula
    }
    return 1; // Confirmar éxito
}

/*
int main()
{
    String s1 = StrNewFrom("Hola");
    String s2 = StrNewFromStr("Mundo");

    printf("Comparar s1 y s2: %d\n", StrCompare(s1, s2)); // Debería imprimir 0 (diferentes)

    StrInsert(&s1, " Mundo");
    printf("Después de insertar: %s\n", s1.str); // Debería imprimir "Hola Mundo"

    StrPushChar(&s1, '!');
    printf("Después de añadir un carácter: %s\n", s1.str); // Debería imprimir "Hola Mundo!"

    StrPopChar(&s1);
    printf("Después de eliminar un carácter: %s\n", s1.str); // Debería imprimir "Hola Mundo"

    StrReplace(&s1, "Adiós Mundo");
    printf("Después de reemplazar: %s\n", s1.str); // Debería imprimir "Adiós Mundo"

    StrTo(&s1, "Hello World");
    printf("Después de StrTo: %s\n", s1.str); // Debería imprimir "Hello World"

    StrToUpperCase(&s1);
    printf("Después de StrToUpperCase: %s\n", s1.str); // Debería imprimir "HELLO WORLD"

    // Liberar memoria
    free(s1.str);
    free(s2.str);

    return 0;
}
*/