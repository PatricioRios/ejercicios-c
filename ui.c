#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// CLEAR THE HISTORY CONSOLE
void clear()
{
  system("clear");
}

// ╔════════════════════════════════════════\n
void topLine()
{
  printf("╔════════════════════════════════════════\n");
}

// ╚════════════════════════════════════════\n
void bottomLine()
{
  printf("╚════════════════════════════════════════\n");
}
// ╠════════════════════════════════════════\n
void midLine()
{
  printf("╠════════════════════════════════════════\n");
}
// ║CONTENT WITH FORMAT
void content(const char *format, ...)
{
  va_list args;      // Lista de argumentos variables
  char buffer[1024]; // Tamaño adecuado para el mensaje
  int len;

  // Inicializar la lista de argumentos
  va_start(args, format);

  // Formatear el mensaje en el búfer
  len = vsnprintf(buffer, sizeof(buffer), format, args);

  // Verificar si la operación se completó correctamente
  if (len >= 0 && len < sizeof(buffer))
  {
    // Imprimir el mensaje formateado
    printf("║ %s\n", buffer);
  }
  else
  {
    // Manejar el error (por ejemplo, búfer demasiado pequeño)
    printf("Error al formatear el mensaje\n");
  }

  // Finalizar la lista de argumentos
  va_end(args);
}

void inputLine()
{
  printf("╚═ ");
}
/*
  content("Colocar cualquier caracter para continuar");
  inputLine();
  char aux[3];
  scanf("%s", aux);
  fflush(stdin);
*/
void waiting()
{
  content("Colocar cualquier caracter para continuar");
  inputLine();
  char aux[3];
  scanf("%s", aux);
  fflush(stdin);
}

/*

Confeccionar un programa que permina el ingreso de un apellido un nombre, el legajo de 10 empleados.

a) se debe asegurar que el apellido debera ser registrado en mayuscula
B) el nombre, la primera letra con mayuscula y el resto con minuscula
c) el legajo se construira a partir de las iniciales del apellido y e nombre mas de un numero de 3 cifras aleatorios
d) generar tablas por genero

*/