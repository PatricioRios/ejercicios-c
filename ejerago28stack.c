#include "boolconst.c"
#include "rand.c"
#include "string50.c"
#include "ui.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.c"
#include "stack.h"

/*
COMO EJECUTAR EL CODIGO.
gcc ejerago28stack.c stack.c -o ejeragostack
*/

/*
int cod;
float price;
String *name;
int stock;
int minStock
*/
typedef struct
{
    int id;
    int cod;
    float price;
    String name;
    int stock;
    int minStock;
} Product;

void printProducts(Stack *products);

void setProductName(Product *product);
void setProductCode(Product *product);
void setProductPrice(Product *product);
void setProductStock(Product *product);
void setProductMinStock(Product *product);
void loadProduct(Stack *stack);

void findProductByCode(Stack *products);

void ralizePurchase(Stack *products);
void modifyPriceProduct(Stack *products);

void analizeStock(Stack *products);

void cuantosLesFaltanVender3(Stack *products);

void mockProducts(Stack *products);

// lambda funcs
void printProduct_on_foreach_indexed(void *product, int index);
int compare_by_code(void *a, void *b);
void print_product_with_waiting(void *product);
void decrementStock(void *data);

void print_product(void *data);
void for_analize_stock_zero(void *product);
void for_analize_stock_min(void *product);
void for_analize_stock_with_tree(void *data);

void custom_free(void *data);

int main()
{
    Stack productos = new_stack(custom_free);
    int option = 0;

    Option arr[8] = {
        {"Dar de alta un producto nuevo.", 1},
        {"Buscar un producto por su Código.", 2},
        {"Modificar el stock por venta.", 3},
        {"Modificar el Precio de un producto.", 4},
        {"Cuantos productos tiene faltante.", 5},
        {"A cuantos le faltan vender 3 producto para que quede el stock mínimo.",
         6},
        {"Mostrar productos.", 7},
        {"Salir.", 8}};

    Options options = {arr, 8};

    mockProducts(&productos);
    while (TRUE)
    {
        clear();
        menuOptions(options);
        inputLine();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loadProduct(&productos);
            continue;
        case 2:
            findProductByCode(&productos);
            continue;
        case 3:
            ralizePurchase(&productos);
            continue;
        case 4:
            modifyPriceProduct(&productos);
            continue;
        case 5:
            analizeStock(&productos);
            continue;
        case 6:
            cuantosLesFaltanVender3(&productos);
            continue;
        case 7:
            printProducts(&productos);
            continue;
        case 8:
            productos.liberate(&productos);
            printf("Goodbye!\n");
            return 0;
            break;
        default:
            productos.liberate(&productos);
            printf("Goodbye!\n");
            return 0;
            break;
        }
    };
}

void custom_free(void *data)
{
    Product *product = (Product *)data;
    print_product(product);
    if (product != NULL)
    {
        if (product->name.str != NULL)
        {
            free(product->name.str);
        }
        free(product);
    }
}

void loadProduct(Stack *stack)
{
    Product *product = malloc(sizeof(Product));
    setProductName(product);
    setProductCode(product);
    setProductPrice(product);
    setProductStock(product);
    setProductMinStock(product);
    stack->push_on_top(stack, product);
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
            product->name = StrNewFrom(name);
            StrToUpper(&product->name);
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

void for_analize_stock_with_tree(void *data)
{
    Product *product = (Product *)data;
    if (product->stock - 3 == product->minStock)
    {
        print_product(product);
    }
}

void cuantosLesFaltanVender3(Stack *products)
{
    clear();
    topLine();
    content("productos a los cuales les falta 3 para tener el stock min");
    midLine();
    products->foreach (products, for_analize_stock_with_tree);
    waiting();
}

void print_product(void *data)
{
    Product *product = (Product *)data;
    content("Codigo: %d", product->cod);
    content("nombre: %s", product->name.str);
    content("precio: %f", product->price);
    content("stock: %d", product->stock);
    content("stock minimo: %d", product->minStock);
    midLine();
}

void for_analize_stock_zero(void *product)
{
    Product *this = (Product *)product;
    if (this->stock == 0)
    {
        print_product(this);
    }
}
void for_analize_stock_min(void *product)
{
    Product *this = (Product *)product;
    if (this->stock < this->minStock)
    {
        print_product(this);
    }
}
void analizeStock(Stack *products)
{
    clear();
    topLine();
    content("Productos con stock 0");
    midLine();
    products->foreach (products, for_analize_stock_zero);
    content("Productos con menos del minimo");
    midLine();
    products->foreach (products, for_analize_stock_min);
    waiting();
}

void modifyPriceProduct(Stack *products)
{
    clear();
    int code;
    topLine();
    while (TRUE)
    {
        content("Dame el codigo del producto al cual queres modificar el precio");
        midLine();
        inputLine();
        scanf("%d", &code);
        if (code >= 0)
        {
            Product *searched = malloc(sizeof(Product));
            searched->cod = code;
            int index = products->first(products, searched, compare_by_code);
            searched = (Product *)products->get_by_index(products, index)->data;
            if (index == -1)
            {
                clear();
                topLine();
                content("Codigo no encontrado, ingresa otro.");
                midLine();
                continue;
            }
            while (TRUE)
            {
                clear();
                topLine();
                content("Producto encontrado: %s", searched->name.str);
                midLine();
                content("Precio aterior: $%f, incerte el nuevo precio", searched->price);
                midLine();
                inputLine();
                float price;
                scanf("%f", &price);
                if (price > 0)
                {
                    searched->price = price;
                    clear();
                    topLine();
                    content("Precio del producto %s modificado, ahora es $%f", searched->name.str, searched->price);
                    midLine();
                    waiting();
                    return;
                }
                else
                {
                    clear();
                    topLine();
                    content("El precio debe ser mayor que 0");
                    midLine();
                    continue;
                }
            }
        }
        else
        {
            clear();
            topLine();
            content("Ingrese un codigo valido\n");
            midLine();
        }
    }
}

// Esta funcion tambien funciona, pero da un warning.
void decrementStock(void *data)
{
    Product *product = (Product *)data;

    printf("product:%s\n", product->name.str);
    product->stock--;
}

// void decrementStock(void *data)
//{
//     Product *product = (Product *)product;
//     printf("product:%s\n", product->name.str);
//     product->stock--;
// }

void ralizePurchase(Stack *products)
{
    clear();
    int code;
    topLine();
    while (TRUE)
    {
        content("Dame el codigo del producto que se vendio");
        midLine();
        inputLine();
        scanf("%d", &code);
        if (code >= 0)
        {
            Product *searched = malloc(sizeof(Product));
            searched->cod = code;
            int index = products->first(products, searched, compare_by_code);
            searched = (Product *)products->get_by_index(products, index)->data;
            printf("Stock anterior: %d\n", searched->stock);
            // searched->stock--;
            products->action_by_index(products, index, decrementStock);
            printf("Stock nuevo: %d\n", searched->stock);
            topLine();
            content("Stock decrementado de :%s", searched->name.str);
            midLine();
            waiting();
            return;
        }
        else
        {
            clear();
            topLine();
            content("Ingrese un codigo valido\n");
            midLine();
        }
    }
}

void printProduct_on_foreach_indexed(void *product, int index)
{
    Product *this = (Product *)product;

    if (index == 0)
    {
        clear();
        topLine();
    }
    content("NOMBRE: %s", this->name.str);
    content("codigo: %d", this->cod);
    content("precio: $%f", this->price);
    content("stock: %d", this->stock);
    content("stock minimo: %d", this->minStock);
    midLine();
}

void findProductByCode(Stack *products)
{
    clear();
    topLine();
    content("Dame el codigo del producto a buscar");
    midLine();
    inputLine();
    int code;
    scanf("%d", &code);
    Product *searched = malloc(sizeof(Product));
    searched->cod = code;
    int index = products->first(products, searched, compare_by_code);
    searched = (Product *)products->get_by_index(products, index)->data;
    print_product_with_waiting(searched);
    // la linea de abajo hace exatamente lo mismo :D.
    //   products->action_by_index(products, index, printProduct);
}

int compare_by_code(void *a, void *b)
{
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    printf("code a : %d - ", productA->cod);
    printf("code b : %d\n", productB->cod);

    printf("name a : %s - ", productA->name.str);
    printf("name b : %s\n", productB->name.str);

    if (productA->cod == productB->cod)
    {
        return 1;
    }
    return 0;
}

void print_product_with_waiting(void *product)
{
    clear();
    Product *searched = (Product *)product;
    topLine();
    content("Codigo: %d", searched->cod);
    midLine();
    content("nombre: %s", searched->name.str);
    midLine();
    content("precio: %f", searched->price);
    midLine();
    content("stock: %d", searched->stock);
    midLine();
    content("stock minimo: %d", searched->minStock);
    midLine();
    waiting();
}

void printProducts(Stack *products)
{
    products->foreach_indexed(products, printProduct_on_foreach_indexed);
    waiting();
}

void mockProducts(Stack *stack)
{
    Product *product = malloc(sizeof(Product));
    product->name = StrNewFrom("CocaCola");
    product->cod = 1;
    product->price = 100;
    product->stock = 10;
    product->minStock = 5;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Pepsi");
    product->cod = 2;
    product->price = 120;
    product->stock = 15;
    product->minStock = 10;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Sprite");
    product->cod = 3;
    product->price = 110;
    product->stock = 20;
    product->minStock = 15;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Fanta");
    product->cod = 4;
    product->price = 130;
    product->stock = 25;
    product->minStock = 20;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Manaos");
    product->cod = 5;
    product->price = 80;
    product->stock = 30;
    product->minStock = 25;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Pepsi");
    product->cod = 6;
    product->price = 180;
    product->stock = 3;
    product->minStock = 3;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Monster");
    product->cod = 7;
    product->price = 180;
    product->stock = 2;
    product->minStock = 3;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("RedBull");
    product->cod = 8;
    product->price = 180;
    product->stock = 0;
    product->minStock = 3;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Papel higienico");
    product->cod = 9;
    product->price = 1080;
    product->stock = 10;
    product->minStock = 2;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Servilletas");
    product->cod = 10;
    product->price = 200;
    product->stock = 10;
    product->minStock = 2;
    stack->push_on_top(stack, product);
    product = malloc(sizeof(Product));

    product->name = StrNewFrom("Servilletas");
    product->cod = 11;
    product->price = 200;
    product->stock = 6;
    product->minStock = 3;
    stack->push_on_top(stack, product);
}