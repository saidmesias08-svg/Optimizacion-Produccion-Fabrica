
/*
    UNIVERSIDAD DE LAS AMERICAS - UDLA
    Carrera: Ingenieria en Ciberseguridad
    Asignatura: Programacion 1

    Integrantes:
    - Said Andres Mesias Nuñez
    - Joan Velastegui

    Proyecto: Optimizacion de Produccion en una Fabrica de Componentes Electronicos

    Descripcion:
    Programa que permite registrar, mostrar, editar y eliminar productos.
    Tambien calcula el tiempo y los recursos necesarios para su fabricacion
    y verifica si la fabrica puede cumplir con la produccion solicitada.
*/

#include <stdio.h>
#include <string.h>

#define MAX 5

// Declaracion de funciones
void ingresarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total);

void mostrarProductos(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int total);

int buscarProducto(char nombres[MAX][50], int total, char buscado[50]);

void editarProducto(char nombres[MAX][50], int cantidades[MAX],
                    float tiempos[MAX], float recursos[MAX], int total);

void eliminarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total);

float calcularTiempoTotal(int cantidades[MAX], float tiempos[MAX], int total);

float calcularRecursos(int cantidades[MAX], float recursos[MAX], int total);

void evaluarProduccion(int cantidades[MAX], float tiempos[MAX],
                       float recursos[MAX], int total);


// Funcion principal
int main() {

    // Arreglos para almacenar la informacion de los productos
    char nombres[MAX][50];
    int cantidades[MAX] = {0};
    float tiempos[MAX] = {0};
    float recursos[MAX] = {0};

    int total = 0;
    int opcion;

    // Menu principal del programa
    do {
        printf("\n===== SISTEMA DE PRODUCCION =====\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular produccion\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                ingresarProducto(nombres, cantidades, tiempos, recursos, &total);
                break;

            case 2:
                mostrarProductos(nombres, cantidades, tiempos, recursos, total);
                break;

            case 3:
                editarProducto(nombres, cantidades, tiempos, recursos, total);
                break;

            case 4:
                eliminarProducto(nombres, cantidades, tiempos, recursos, &total);
                break;

            case 5:
                evaluarProduccion(cantidades, tiempos, recursos, total);
                break;

            case 6:
                printf("\nPrograma finalizado.\n");
                break;

            default:
                printf("\nOpcion no valida.\n");
        }

    } while (opcion != 6);

    return 0;
}


// Funcion para registrar productos
void ingresarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total) {

    char nuevoNombre[50];

    // Verificar si todavia hay espacio
    if (*total >= MAX) {
        printf("\nNo se pueden registrar mas de 5 productos.\n");
        return;
    }

    printf("\nIngrese el nombre del producto: ");
    scanf(" %49[^\n]", nuevoNombre);

    // Verificar si el producto ya existe
    if (buscarProducto(nombres, *total, nuevoNombre) != -1) {
        printf("\nEl producto ya se encuentra registrado.\n");
        return;
    }

    strcpy(nombres[*total], nuevoNombre);

    printf("Ingrese la cantidad solicitada: ");
    scanf("%d", &cantidades[*total]);

    printf("Ingrese el tiempo de fabricacion por unidad (minutos): ");
    scanf("%f", &tiempos[*total]);

    printf("Ingrese los recursos necesarios por unidad: ");
    scanf("%f", &recursos[*total]);

    // Validar que los valores no sean negativos
    if (cantidades[*total] < 0 || tiempos[*total] < 0 || recursos[*total] < 0) {
        printf("\nNo se permiten valores negativos. Registro cancelado.\n");
        return;
    }

    (*total)++;

    printf("\nProducto registrado correctamente.\n");
}


// Funcion para mostrar los productos registrados
void mostrarProductos(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int total) {

    int i;

    if (total == 0) {
        printf("\nNo existen productos registrados.\n");
        return;
    }

    printf("\n===== PRODUCTOS REGISTRADOS =====\n");

    for (i = 0; i < total; i++) {
        printf("\nProducto: %s\n", nombres[i]);
        printf("Cantidad: %d\n", cantidades[i]);
        printf("Tiempo por unidad: %.2f minutos\n", tiempos[i]);
        printf("Recursos por unidad: %.2f\n", recursos[i]);
    }
}


// Funcion para buscar un producto por su nombre
int buscarProducto(char nombres[MAX][50], int total, char buscado[50]) {

    int i;

    // Recorrer el arreglo para encontrar el producto
    for (i = 0; i < total; i++) {

        if (strcmp(nombres[i], buscado) == 0) {
            return i;
        }
    }

    return -1;
}


// Funcion para editar un producto
void editarProducto(char nombres[MAX][50], int cantidades[MAX],
                    float tiempos[MAX], float recursos[MAX], int total) {

    char buscado[50];
    char nuevoNombre[50];
    int posicion;
    int repetido;

    if (total == 0) {
        printf("\nNo existen productos para editar.\n");
        return;
    }

    printf("\nIngrese el nombre del producto que desea editar: ");
    scanf(" %49[^\n]", buscado);

    posicion = buscarProducto(nombres, total, buscado);

    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    printf("\nIngrese el nuevo nombre del producto: ");
    scanf(" %49[^\n]", nuevoNombre);

    repetido = buscarProducto(nombres, total, nuevoNombre);

    // Evitar nombres duplicados
    if (repetido != -1 && repetido != posicion) {
        printf("\nYa existe otro producto con ese nombre.\n");
        return;
    }

    strcpy(nombres[posicion], nuevoNombre);

    printf("Ingrese la nueva cantidad: ");
    scanf("%d", &cantidades[posicion]);

    printf("Ingrese el nuevo tiempo por unidad: ");
    scanf("%f", &tiempos[posicion]);

    printf("Ingrese los nuevos recursos por unidad: ");
    scanf("%f", &recursos[posicion]);

    // Validar los nuevos valores
    if (cantidades[posicion] < 0 || tiempos[posicion] < 0 || recursos[posicion] < 0) {
        printf("\nNo se permiten valores negativos.\n");
        return;
    }

    printf("\nProducto actualizado correctamente.\n");
}


// Funcion para eliminar un producto
void eliminarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total) {

    char buscado[50];
    int posicion;
    int i;

    if (*total == 0) {
        printf("\nNo existen productos para eliminar.\n");
        return;
    }

    printf("\nIngrese el nombre del producto que desea eliminar: ");
    scanf(" %49[^\n]", buscado);

    posicion = buscarProducto(nombres, *total, buscado);

    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    // Desplazar los datos para ocupar el espacio eliminado
    for (i = posicion; i < *total - 1; i++) {

        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    (*total)--;

    printf("\nProducto eliminado correctamente.\n");
}


// Funcion para calcular el tiempo total de fabricacion
float calcularTiempoTotal(int cantidades[MAX], float tiempos[MAX], int total) {

    int i;
    float suma = 0;

    for (i = 0; i < total; i++) {
        suma = suma + (cantidades[i] * tiempos[i]);
    }

    return suma;
}


// Funcion para calcular los recursos totales necesarios
float calcularRecursos(int cantidades[MAX], float recursos[MAX], int total) {

    int i;
    float suma = 0;

    for (i = 0; i < total; i++) {
        suma = suma + (cantidades[i] * recursos[i]);
    }

    return suma;
}


// Funcion para evaluar si se puede cumplir con la produccion
void evaluarProduccion(int cantidades[MAX], float tiempos[MAX],
                       float recursos[MAX], int total) {

    float tiempoDisponible;
    float recursosDisponibles;
    float tiempoNecesario;
    float recursosNecesarios;

    if (total == 0) {
        printf("\nNo existen productos registrados para calcular.\n");
        return;
    }

    printf("\nIngrese el tiempo disponible de produccion (minutos): ");
    scanf("%f", &tiempoDisponible);

    printf("Ingrese la cantidad de recursos disponibles: ");
    scanf("%f", &recursosDisponibles);

    // Verificar que los valores sean validos
    if (tiempoDisponible < 0 || recursosDisponibles < 0) {
        printf("\nNo se permiten valores negativos.\n");
        return;
    }

    // Calcular los valores necesarios
    tiempoNecesario = calcularTiempoTotal(cantidades, tiempos, total);
    recursosNecesarios = calcularRecursos(cantidades, recursos, total);

    printf("\n===== RESULTADOS DE PRODUCCION =====\n");
    printf("Tiempo necesario: %.2f minutos\n", tiempoNecesario);
    printf("Recursos necesarios: %.2f\n", recursosNecesarios);

    printf("\nTiempo disponible: %.2f minutos\n", tiempoDisponible);
    printf("Recursos disponibles: %.2f\n", recursosDisponibles);

    // Comparar los valores necesarios con los disponibles
    if (tiempoNecesario <= tiempoDisponible && recursosNecesarios <= recursosDisponibles) {

        printf("\nLa fabrica SI puede cumplir con la produccion solicitada.\n");

    } else {

        printf("\nLa fabrica NO puede cumplir con la produccion solicitada.\n");

        if (tiempoNecesario > tiempoDisponible) {
            printf("No existe suficiente tiempo de produccion.\n");
        }

        if (recursosNecesarios > recursosDisponibles) {
            printf("No existen suficientes recursos disponibles.\n");
        }
    }
}

