#include <conio.h>
#include <ctype.h>
#include <stdio.h>

/* LISTA SIMPLE CON INSERCION EN EL PPIO y eliminación */
struct lista {
  char dato;           // dato a guardar en la lista
  struct lista *sigue; // campo de enlace al siguiente nodo
} *inicio, *nuevo, *recorre, *aux;

void verlista(struct lista *);
void liblista(struct lista *);
void main() {

  char c;
  inicio = NULL;
  // clrscr();
  printf("Ingrese caracteres hasta el punto \n");
  while ((c = getche()) != '.') {
    if (islower(c)) // Inserci¢n al ppio
    {
      nuevo = malloc(sizeof(struct lista));
      nuevo->dato = c; // GUARDO EL DATO
      nuevo->sigue = inicio;
      inicio = nuevo;

      verlista(inicio);
    } else // eliminacin
    {

      if (inicio != NULL) // la lista no está vacía
      {
        aux = inicio; // paso inicio al nodo siguiente
        inicio = inicio->sigue;
        free(aux);
        verlista(inicio);
      } else // lista vac¡a
      {
        printf("\n---Lista VACIA");
        verlista(inicio);
      }
    }
  }
  liblista(inicio);
  getch();
}

void verlista(struct lista *inicio) {
  struct lista *recorre;
  recorre = inicio; // pone recorre al ppio
  if (recorre)      // SI LA LISTA NO ESTA VACIA
  {
    printf("\n---");
    while (recorre) // MIENTRAS RECORRE APUNTE A UN NODO osea no null
    {
      putch(recorre->dato);
      recorre = recorre->sigue;
    }
    printf("\n");
  }
}

void liblista(struct lista *inicio) {
  struct lista *aux;
  while (inicio) {
    aux = inicio;
    inicio = inicio->sigue;
    free(aux);
  }
}

/*void verlista (struct lista*recorre)  // recursiva
 {
        printf("\n");
        if (recorre)
        {
                verlista(recorre->sigue);
                printf("%c", recorre->c); //IMPRIME EN LA FORMA QUE INGRESO

        }.
}*/
