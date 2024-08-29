#include "string50.c"
#include <stdio.h>
#include <stdlib.h>

struct Product {
  char dato;
  struct Product *sig;
} *inicio, *nuevo, *recorre, *aux;

void viewList(struct Product *products);

void freeList(struct Product *products);

void view(struct Product *pila);

int main() {
  char aux;
  int cont = 0;
  while (0 == 0) {
    scanf("%c", &aux);
    fflush(stdin);

    nuevo = malloc(sizeof(struct Product));
    nuevo->dato = aux;
    nuevo->sig = inicio;
    inicio = nuevo;
    fflush(stdin);

    printf("========== %d \n", cont);

    view(inicio);
    cont++;
    fflush(stdin);
    scanf("%c", &aux);
    
  }
}

void viewList(struct Product *products) {
  struct Product *recorre;
  recorre = inicio; // pone recorre al ppio
  if (recorre)      // SI LA LISTA NO ESTA VACIA
  {
    printf("LISTA ===============\n");
    while (recorre) // MIENTRAS RECORRE APUNTE A UN NODO osea no null
    {
      printf("Dato: %c\n", recorre->dato);
      recorre = recorre->sig;
    }
  }
}

void view(struct Product *pila) {
  if (pila) {
    putc(pila->dato, stdout);
    view(pila->sig);
  } else {
    printf("\n");
    return;
  }
}

void freeList(struct Product *products) {
  struct Product *aux;
  while (aux) {
    aux = inicio;
    inicio = inicio->sig;
    free(aux);
  }
}
