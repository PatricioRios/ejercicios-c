#include <stdio.h>
#include "ui.c"

// Definimos una "interfaz" para operaciones básicas de figuras geométricas
typedef struct
{
    double (*area)(void *self);
    double (*perimeter)(void *self);
} ShapeInterface;
/*
  int (*hablar)(void *self);
  void (*andar)(void *self);
  void (*dormir)(void *self);*/
typedef struct
{
    void (*hablar)(void *self);
    void (*andar)(void *self);
    void (*dormir)(void *self);
} AnimalInterface;
/*
    int edad;
    int peso;
    int altura;
    int raza;
    AnimalInterface *vtable;
*/
typedef struct
{
    int edad;
    int peso;
    int altura;
    char *raza;
    // AnimalInterface *vtable;
} Perro;
/*
    int edad;
    int peso;
    int altura;
    int tipo_pez;
    AnimalInterface *vtable;
*/
typedef struct
{
    int edad;
    int peso;
    int altura;
    char *tipo_pez;
    // AnimalInterface *vtable;
} Pez;
/*
    int edad;
    int peso;
    int altura;
    int plumas;
    AnimalInterface *vtable;
*/
typedef struct
{
    int edad;
    int peso;
    int altura;
    int plumas;
    // AnimalInterface *vtable;
} Pajaro;

typedef struct
{
    AnimalInterface *vtable;
    union
    {
        Pez pez;
        Pajaro pajaro;
        Perro perro;
    };
} Animal;

void perro_hablar(void *self)
{
    Animal *perro = (Animal *)self;
    printf("Wau Wau!, soy un perro\ntengo la edad %d,peso %d,altura %d y raza %s\n", perro->perro.edad, perro->perro.peso, perro->perro.altura, perro->perro.raza);
}
void perro_andar(void *self)
{
    Animal *perro = (Animal *)self;
    printf("Voy a empezar a correr en cuatro patas!\n");
}
void perro_dormir(void *self)
{
    Animal *perro = (Animal *)self;
    printf("voy a dar cuatro vueltas y echarme a dormir\n");
}

void pez_hablar(void *self)
{
    Animal *pez = (Animal *)self;
    printf("Soy un pez!\ntengo la edad %d,peso %d,altura %d y tipo_pez %s\n",
           pez->pez.edad,
           pez->pez.peso,
           pez->pez.altura,
           pez->pez.tipo_pez);
}
void pez_andar(void *self)
{
    Animal *pez = (Animal *)self;
    printf("Voy a nadar muy rapido!\n");
}
void pez_dormir(void *self)
{
    Animal *pez = (Animal *)self;
    printf("voy a acostarme en una alga!\n");
}

void pajaro_hablar(void *self)
{
    Animal *pajaro = (Animal *)self;
    printf("Soy un pajaro!\ntengo la edad %d,peso %d,altura %d y tengo %d plumas.\n",
           pajaro->pajaro.edad,
           pajaro->pajaro.peso,
           pajaro->pajaro.altura,
           pajaro->pajaro.plumas);
}
void pajaro_andar(void *self)
{
    Animal *pajaro = (Animal *)self;
    printf("Voy a volar hasta los cielos!\n");
};
void pajaro_dormir(void *self)
{
    Animal *pajaro = (Animal *)self;
    printf("voy a ir a mi nido y dormir!\n");
};

AnimalInterface perro_vtable = {
    .hablar = perro_hablar,
    .dormir = perro_dormir,
    .andar = perro_andar};
AnimalInterface pez_vtable = {
    .hablar = pez_hablar,
    .dormir = pez_dormir,
    .andar = pez_andar};
AnimalInterface pajaro_vtable = {
    .hablar = pajaro_hablar,
    .dormir = pajaro_dormir,
    .andar = pajaro_andar};

void hacer_algo(void *animal, AnimalInterface *vtable);
void hacer_algo_arr(Animal *animal);

int main()
{
    Animal perro = {
        .vtable = &perro_vtable,
        .perro = {
            10,
            30,
            20,
            "asdasd"}};
    Animal pez = {
        .vtable = &pez_vtable,
        .pez = {
            1,
            2,
            10,
            "Pez globo",
        }};
    Animal pajaro = {
        .vtable = &pajaro_vtable,
        .pajaro = {
            20,
            5,
            10,
            120,
        }};
    Animal animales[] = {perro, pez, pajaro};
    hacer_algo_arr(animales);
    return 0;
}

void hacer_algo(void *animal, AnimalInterface *vtable)
{
    vtable->hablar(animal);
    vtable->andar(animal);
    vtable->dormir(animal);
    midLine();
}

void hacer_algo_arr(Animal *animals)
{
    topLine();
    for (int i = 0; i < 3; i++)
    {
        hacer_algo(&animals[i], animals[i].vtable);
    };
    /*
        vtable->hablar(animals);
        vtable->andar(animals);
        vtable->dormir(animals);
        */
}
