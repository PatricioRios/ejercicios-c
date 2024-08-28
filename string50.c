#include <stdio.h>
#include <string.h>

struct string50
{
    char str[50];
    char frstChar;
    int value;
} typedef string50;

// Compara 2 strings, devuelve 0 si son iguales
int my_strcmp(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    if (*str1 == '\0')
    {
        return *str2 - '\0';
    }
    else
    {
        return '\0' - *str1;
    }
}

// copia la string de origin a la string destino.
void my_strcpy(char *destino, char *origen)
{
    while (*origen != '\0')
    {
        *destino = *origen;
        destino++;
        origen++;
    }
    *destino = '\0';
}

// devuelve una struct de string50.
string50 newString50(char *str)
{
    char patron[53];
    patron[0] = 'A';
    patron[1] = 'a';
    patron[2] = 'B';
    patron[3] = 'b';
    patron[4] = 'C';
    patron[5] = 'c';
    patron[6] = 'D';
    patron[7] = 'd';
    patron[8] = 'E';
    patron[9] = 'e';
    patron[10] = 'F';
    patron[11] = 'f';
    patron[12] = 'G';
    patron[13] = 'g';
    patron[14] = 'H';
    patron[15] = 'h';
    patron[16] = 'I';
    patron[17] = 'i';
    patron[18] = 'J';
    patron[19] = 'j';
    patron[20] = 'K';
    patron[21] = 'k';
    patron[22] = 'L';
    patron[23] = 'l';
    patron[24] = 'M';
    patron[25] = 'm';
    patron[26] = 'N';
    patron[27] = 'n';
    // patron[28]='Ñ';patron[29]='ñ';
    patron[30] = 'O';
    patron[31] = 'o';
    patron[32] = 'P';
    patron[33] = 'p';
    patron[34] = 'Q';
    patron[35] = 'q';
    patron[36] = 'R';
    patron[37] = 'r';
    patron[38] = 'S';
    patron[39] = 's';
    patron[40] = 'T';
    patron[41] = 't';
    patron[42] = 'U';
    patron[43] = 'u';
    patron[44] = 'V';
    patron[45] = 'v';
    patron[46] = 'W';
    patron[47] = 'w';
    patron[48] = 'X';
    patron[49] = 'x';
    patron[50] = 'Y';
    patron[51] = 'y';
    patron[52] = 'Z';
    patron[53] = 'z';

    string50 string;
    my_strcpy(string.str, str);

    string.frstChar = str[0];

    for (int j = 0; j < 54; j++)
    {
        if (str[0] == patron[j])
        {
            string.value = j;
        }
    }
    return string;
}

int strcmp50(string50 a, string50 b)
{
    if (a.value != b.value)
    {
        return 1;
    }
    if (a.frstChar != b.frstChar)
    {
        return 1;
    }

    return my_strcmp(a.str, b.str);
}
