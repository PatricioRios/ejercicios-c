/*
    Realizar un programa que gestione los datos de stock de una tienda de comestibles,
    la información a recoger será: Código del producto, precio, cantidad en stock,
    Stock Mínimo.
    La tienda dispone de N productos distintos. El programa debe ser capaz de:
    - Dar de alta un producto nuevo
    - Buscar un producto por su Código
    - Modificar el stock por venta
    - Modificar el Precio de un producto
    - Cuantos productos tiene faltante
    - Cuantos tienen menos del stock mínimo
    - A cuantos le faltan vender 3 producto para que quede el stock mínimo
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string50.c"
#include "rand.c"
#include "boolconst.c"
#include "ui.c"

/*
int cod;
float price;
char *name;
int stock;
int minStock
*/
typedef struct
{
    int id;
    int cod;
    float price;
    string50 name;
    int stock;
    int minStock;
} Product;

int position = 0;
int max = 10;

void printProducts(Product *products);

void setProductName(Product *product);
void setProductCode(Product *product);
void setProductPrice(Product *productos);
void setProductStock(Product *productos);
void setProductMinStock(Product *productos);
void loadProduct(Product *);

void findProductByCode(Product *products);

void ralizePurchase(Product *products);

void modifyPriceProduct(Product *products);

void analizeStock(Product *products);

void cuantosLesFaltanVender3(Product *products);

int main()
{
    Product *productos = malloc(sizeof(Product) * max);
    int option = 0;

    while (TRUE)
    {
        clear();
        topLine();
        content("hay %d personas en el sistema", option);
        midLine();
        content("1 - Dar de alta un producto nuevo");
        midLine();
        content("2 - Buscar un producto por su Código");
        midLine();
        content("3 - Modificar el stock por venta");
        midLine();
        content("4 - Modificar el Precio de un producto");
        midLine();
        content("5 - Cuantos productos tiene faltante");
        midLine();
        content("6 - A cuantos le faltan vender 3 producto para que quede el stock mínimo");
        midLine();
        content("7 - Mostrar productos.");
        midLine();
        content("8 - Salir.");
        midLine();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loadProduct(productos);
            continue;
        case 2:
            findProductByCode(productos);
            continue;
        case 3:
            realizePurchase(productos);
            continue;
        case 4:
            modifyPriceProduct(productos);
            continue;
        case 5:
            analizeStock(productos);
            break;
        case 6:
            /* code */
            break;
        case 7:
            printProducts(productos);
            break;
        case 8:
            free(productos);
            printf("Goodbye!");
            return 0;
            break;

        default:
            free(productos);
            printf("Goodbye!");
            return 0;
            break;
        }
    };
}

void loadProduct(Product *productos)
{
    productos[position].id = position;
    if (position == max)
    {
        max = max * 2;
        productos = realloc(productos, max * sizeof(Product));
    }
    clear();
    setProductName(&productos[position]);
    setProductCode(&productos[position]);
    setProductPrice(&productos[position]);
    setProductStock(&productos[position]);
    setProductMinStock(&productos[position]);
    position++;
}

void setProductName(Product *product)
{
    topLine();
    char name[50];

    while (TRUE)
    {
        content("Dame el nombre del producto");
        midLine();
        inputLine();
        scanf("%s", name);
        if (strcmp(name, "") != 0)
        {
            product->name = newString50(name);
            break;
        }
        clear();
        topLine();
        content("El nombre del producto no puede ser vacio");
        midLine();
    }
}

void setProductCode(Product *product)
{
    clear();
    topLine();
    while (TRUE)
    {
        content("Dame el codigo del producto %s", product->name.str);
        midLine();
        inputLine();
        scanf("%d", &product->cod);
        if (product->cod > 0)
        {
            break;
        }
        clear();
        topLine();
        content("El codigo del producto debe ser mayor que 0");
        midLine();
    }
}

void setProductPrice(Product *productos)
{
    clear();
    topLine();
    while (TRUE)
    {
        content("Dame el precio del producto %s", productos->name.str);
        midLine();
        inputLine();
        scanf("%f", &productos->price);
        if (productos->price > 0)
        {
            break;
        }
        clear();
        topLine();
        content("El precio del producto debe ser mayor que 0");
        midLine();
    }
}

void setProductStock(Product *productos)
{
    clear();
    topLine();
    while (TRUE)
    {
        content("Dame el stock del producto %s", productos->name.str);
        midLine();
        inputLine();
        scanf("%d", &productos->stock);
        if (productos->stock >= 0)
        {
            break;
        }
        clear();
        topLine();
        content("El stock del producto debe ser mayor o igual que 0");
        midLine();
    }
}

void setProductMinStock(Product *productos)
{
    clear();
    topLine();
    while (TRUE)
    {
        content("Dame el stock minimo del producto %s", productos->name.str);
        midLine();
        inputLine();
        scanf("%d", &productos->minStock);
        if (productos->minStock >= 0)
        {
            break;
        }
        clear();
        topLine();
        content("El stock minimo del producto debe ser mayor o igual que 0");
        midLine();
    }
}

void printProducts(Product *products)
{
    clear();
    topLine();
    for (int i = 0; i < position; i++)
    {
        content("nombre: %s", products[i].name.str);
        midLine();
        content("codigo: %d", products[i].cod);
        midLine();
        content("precio: %f", products[i].price);
        midLine();
        content("stock: %d", products[i].stock);
        midLine();
        content("stock minimo: %d", products[i].minStock);
        midLine();
    }
    content("Coloca cualquier caracter para continuar");
    midLine();
    inputLine();
    char aux[3];
    scanf("%s", aux);
    fflush(stdin);
}

void findProductByCode(Product *products)
{
    clear();
    topLine();
    content("Dame el codigo del producto a buscar");
    midLine();
    inputLine();
    int code;
    scanf("%d", &code);
    for (int i = 0; i < position; i++)
    {
        if (products[i].cod == code)
        {
            clear();
            topLine();
            content("nombre: %s", products[i].name.str);
            midLine();
            content("codigo: %d", products[i].cod);
            midLine();
            content("precio: %f", products[i].price);
            midLine();
            content("stock: %d", products[i].stock);
            midLine();
            content("stock minimo: %d", products[i].minStock);
            midLine();
            content("Coloca cualquier caracter para continuar");
            midLine();
            inputLine();
            char aux[3];
            scanf("%s", aux);
            fflush(stdin);
            return;
        }
    }
    clear();
    topLine();
    content("No se encontro el producto con el codigo %d", code);
    midLine();
    content("Coloca cualquier caracter para continuar");
    midLine();
    inputLine();
    char aux[3];
    scanf("%s", aux);
    fflush(stdin);
}

void ralizePurchase(Product *products)
{
    clear();
    int code;
    topLine();
    while (TRUE)
    {
        content("Dame el codigo del producto que se vendio");
        inputLine();
        scanf("%d", &code);
        if (code >= 0)
        {
            for (int i = 0; i < position; i++)
            {
                if (products[i].cod == code)
                {
                    products[i].stock--;
                    clear();
                    topLine();
                    content("se decremento en 1 el stock de nombre: %s", products[i].name.str);
                    midLine();
                    break;
                }
            }
            topLine();
            content("Codigo no encontrado, ingresa otro.");
            midLine();
        }
        topLine();
        content("Codigo invalido, ingresa otro.");
        midLine();
    }
}

void modifyPriceProduct(Product *products)
{
    clear();
    int code;
    topLine();
    while (TRUE)
    {
        content("Dame el codigo del producto que queres cambiar el precio");
        inputLine();
        scanf("%d", &code);
        if (code >= 0)
        {
            for (int i = 0; i < position; i++)
            {
                if (products[i].cod == code)
                {

                    clear();
                    topLine();
                    content("Producto encontrado: %s", products[i].name.str);
                    midLine();
                    content("Precio aterior: %f, incerte el nuevo precio", products[i].price);
                    midLine();
                    inputLine();
                    float price;
                    scanf("%f", &price);
                    products[i].price = price;
                    clear();
                    topLine();
                    content("Precio del producto %s modificado, ahora es $%f", products[i].name.str, products[i].price);
                    content("coloque cualquier caracter para continuar");
                    midLine();
                    inputLine();
                    char aux[3];
                    scanf("%s", aux);
                    fflush(stdin);
                    break;
                }
            }
            topLine();
            content("Codigo no encontrado, ingresa otro.");
            midLine();
        }
        topLine();
        content("Codigo invalido, ingresa otro.");
        midLine();
    }
}

void analizeStock(Product *products)
{
    clear();
    topLine();
    content("Productos con stock 0");
    for (int i = 0; i < position; i++)
    {
        if (products[i].stock == 0)
        {
            midLine();
            content("nombre: %s, stock: %d,codico %d, precio: %f, stock minimo: %d", products[i].name.str, products[i].stock, products[i].cod, products[i].price, products[i].minStock);
        }
    }
    midLine();
    content("Productos con stock menor al minimo");
    for (int i = 0; i < position; i++)
    {
        if (products[i].stock < products[i].minStock)
        {
            midLine();
            content("nombre: %s, stock: %d,codico %d, precio: %f, stock minimo: %d", products[i].name.str, products[i].stock, products[i].cod, products[i].price, products[i].minStock);
        }
    }
    midLine();
    content("Colocar cualquier caracter para continuar");
    inputLine();
    char aux[3];
    scanf("%s", aux);
    fflush(stdin);
}

void cuantosLesFaltanVender3(Product *products)
{

    clear();
    topLine();
    content("Productos que les falta 3 para tener el stock minimo");
    for (int i = 0; i < position; i++)
    {
        if (products[i].stock - 3 == products[i].minStock)
        {
            midLine();
            content("nombre: %s, stock: %d,codico %d, precio: %f, stock minimo: %d", products[i].name.str, products[i].stock, products[i].cod, products[i].price, products[i].minStock);
        }
    }
    midLine();
    content("Colocar cualquier caracter para continuar");
    inputLine();
    char aux[3];
    scanf("%s", aux);
    fflush(stdin);
}