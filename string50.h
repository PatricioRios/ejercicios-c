#ifndef string50H
#define string50H

/*
Una estructura que contiene una string, su primer caracter
y el valor de abcdario de el caracter
*/

struct string50
{
    char str[50];
    char frstChar;
    int value;
} typedef string50;

int my_strcmp(char *str1, char *str2);
void my_strcpy(char *destino, char *origen);
string50 newString50(char *str);

#endif
