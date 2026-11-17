
#include <stdio.h>
#include <string.h>

// Definimos la cantidad maxima de productos que puede registrar la fabrica
#define MAX 5

// Declaracion de las funciones que utilizaremos en el programa

// Funcion para ingresar los datos de un producto
void ingresarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total);

// Funcion para mostrar los productos registrados
void mostrarProductos(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int total);

// Funcion para buscar un producto por su nombre
int buscarProducto(char nombres[MAX][50], int total, char buscado[50]);

// Funcion para modificar los datos de un producto
void editarProducto(char nombres[MAX][50], int cantidades[MAX],
                    float tiempos[MAX], float recursos[MAX], int total);

// Funcion para eliminar un producto de los arreglos
void eliminarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total);

// Funcion para calcular el tiempo total de fabricacion
float calcularTiempoTotal(int cantidades[MAX], float tiempos[MAX], int total);

// Funcion para calcular la cantidad total de recursos necesarios
float calcularRecursos(int cantidades[MAX], float recursos[MAX], int total);

// Funcion para comprobar si se puede cumplir con la produccion
void evaluarProduccion(int cantidades[MAX], float tiempos[MAX],
                       float recursos[MAX], int total);


// ======================================================
//                    PROGRAMA PRINCIPAL
// ======================================================

int main() {

    // Declaramos los arreglos para almacenar la informacion de los productos
    // Cada posicion corresponde a un producto registrado
    char nombres[MAX][50];
    int cantidades[MAX] = {0};
    float tiempos[MAX] = {0};
    float recursos[MAX] = {0};

    // Variable para llevar el control de los productos registrados
    int total = 0;

    // Variable para guardar la opcion seleccionada en el menu
    int opcion;

    // Repetimos el menu hasta que el usuario seleccione salir
    do {

        printf("\n===== SISTEMA DE PRODUCCION =====\n");
        printf("1. Registrar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Calcular produccion\n");
        printf("6. Salir\n");

        // Solicitamos al usuario que seleccione una opcion
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        // Ejecutamos la funcion correspondiente segun la opcion elegida
        switch (opcion) {

            case 1:
                ingresarProducto(nombres, cantidades, tiempos,
                                 recursos, &total);
                break;

            case 2:
                mostrarProductos(nombres, cantidades, tiempos,
                                 recursos, total);
                break;

            case 3:
                editarProducto(nombres, cantidades, tiempos,
                               recursos, total);
                break;

            case 4:
                eliminarProducto(nombres, cantidades, tiempos,
                                 recursos, &total);
                break;

            case 5:
                evaluarProduccion(cantidades, tiempos, recursos, total);
                break;

            case 6:
                printf("\nPrograma finalizado.\n");
                break;

            // Si se ingresa una opcion diferente a las disponibles
            default:
                printf("\nOpcion no valida.\n");
        }

    // El menu continua mientras la opcion sea diferente de 6
    } while (opcion != 6);

    // Finalizamos el programa
    return 0;
}


// ======================================================
//              FUNCION PARA INGRESAR PRODUCTOS
// ======================================================

void ingresarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total) {

    // Comprobamos que no se haya alcanzado el limite de productos
    if (*total >= MAX) {
        printf("\nYa se alcanzo el limite de 5 productos.\n");
        return;
    }

    // Solicitamos el nombre del nuevo producto
    printf("\nNombre del producto: ");
    scanf(" %49[^\n]", nombres[*total]);

    // Comprobamos que el producto no se encuentre registrado anteriormente
    if (buscarProducto(nombres, *total, nombres[*total]) != -1) {
        printf("Ese producto ya esta registrado.\n");
        return;
    }

    // Solicitamos la cantidad de productos que necesita fabricar la fabrica
    printf("Cantidad demandada: ");
    scanf("%d", &cantidades[*total]);

    // Evitamos que se ingresen cantidades negativas
    while (cantidades[*total] < 0) {
        printf("Ingrese una cantidad valida: ");
        scanf("%d", &cantidades[*total]);
    }

    // Solicitamos el tiempo necesario para fabricar una unidad
    printf("Tiempo de fabricacion por unidad (minutos): ");
    scanf("%f", &tiempos[*total]);

    // Comprobamos que el tiempo ingresado no sea negativo
    while (tiempos[*total] < 0) {
        printf("Ingrese un tiempo valido: ");
        scanf("%f", &tiempos[*total]);
    }

    // Solicitamos la cantidad de recursos necesarios por unidad
    printf("Recursos necesarios por unidad: ");
    scanf("%f", &recursos[*total]);

    // Evitamos que se ingresen cantidades negativas de recursos
    while (recursos[*total] < 0) {
        printf("Ingrese una cantidad valida: ");
        scanf("%f", &recursos[*total]);
    }

    // Aumentamos el contador porque se registro un nuevo producto
    (*total)++;

    printf("\nProducto registrado correctamente.\n");
}


// ======================================================
//             FUNCION PARA MOSTRAR PRODUCTOS
// ======================================================

void mostrarProductos(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int total) {

    int i;

    // Comprobamos si existen productos registrados
    if (total == 0) {
        printf("\nNo hay productos registrados.\n");
        return;
    }

    printf("\n===== PRODUCTOS REGISTRADOS =====\n");

    // Recorremos los arreglos para mostrar la informacion de cada producto
    for (i = 0; i < total; i++) {

        printf("\nProducto: %s\n", nombres[i]);
        printf("Cantidad demandada: %d\n", cantidades[i]);
        printf("Tiempo por unidad: %.2f minutos\n", tiempos[i]);
        printf("Recursos por unidad: %.2f\n", recursos[i]);
    }
}


// ======================================================
//              FUNCION PARA BUSCAR PRODUCTOS
// ======================================================

int buscarProducto(char nombres[MAX][50], int total, char buscado[50]) {

    int i;

    // Recorremos los nombres de los productos registrados
    // para comparar cada uno con el nombre que desea buscar el usuario
    for (i = 0; i < total; i++) {

        // Comparamos ambos nombres
        if (strcmp(nombres[i], buscado) == 0) {

            // Devolvemos la posicion donde se encontro el producto
            return i;
        }
    }

    // Si termina el recorrido y no se encuentra, devolvemos -1
    return -1;
}


// ======================================================
//              FUNCION PARA EDITAR PRODUCTOS
// ======================================================

void editarProducto(char nombres[MAX][50], int cantidades[MAX],
                    float tiempos[MAX], float recursos[MAX], int total) {

    // Variable para almacenar el nombre que se desea buscar
    char buscado[50];

    // Variable para guardar la posicion del producto encontrado
    int posicion;

    // Verificamos que existan productos registrados
    if (total == 0) {
        printf("\nNo hay productos para editar.\n");
        return;
    }

    // Solicitamos el nombre del producto que se desea modificar
    printf("\nIngrese el nombre del producto que desea editar: ");
    scanf(" %49[^\n]", buscado);

    // Utilizamos la funcion de busqueda para encontrar el producto
    posicion = buscarProducto(nombres, total, buscado);

    // Si el resultado es -1 significa que el producto no existe
    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    // Solicitamos los nuevos datos del producto encontrado
    printf("\nIngrese los nuevos datos del producto.\n");

    printf("Nuevo nombre: ");
    scanf(" %49[^\n]", nombres[posicion]);

    printf("Nueva cantidad demandada: ");
    scanf("%d", &cantidades[posicion]);

    // Validamos que la nueva cantidad no sea negativa
    while (cantidades[posicion] < 0) {
        printf("Ingrese una cantidad valida: ");
        scanf("%d", &cantidades[posicion]);
    }

    printf("Nuevo tiempo por unidad: ");
    scanf("%f", &tiempos[posicion]);

    // Validamos que el tiempo ingresado sea correcto
    while (tiempos[posicion] < 0) {
        printf("Ingrese un tiempo valido: ");
        scanf("%f", &tiempos[posicion]);
    }

    printf("Nuevos recursos por unidad: ");
    scanf("%f", &recursos[posicion]);

    // Validamos que los recursos no tengan valores negativos
    while (recursos[posicion] < 0) {
        printf("Ingrese una cantidad valida: ");
        scanf("%f", &recursos[posicion]);
    }

    printf("\nProducto actualizado correctamente.\n");
}


// ======================================================
//              FUNCION PARA ELIMINAR PRODUCTOS
// ======================================================

void eliminarProducto(char nombres[MAX][50], int cantidades[MAX],
                      float tiempos[MAX], float recursos[MAX], int *total) {

    // Variable para almacenar el nombre del producto que se desea eliminar
    char buscado[50];

    // Variable para guardar la posicion donde se encuentra el producto
    int posicion;

    int i;

    // Verificamos que existan productos registrados
    if (*total == 0) {
        printf("\nNo hay productos para eliminar.\n");
        return;
    }

    // Solicitamos el nombre del producto que se desea eliminar
    printf("\nIngrese el nombre del producto que desea eliminar: ");
    scanf(" %49[^\n]", buscado);

    // Buscamos el producto dentro de los arreglos
    posicion = buscarProducto(nombres, *total, buscado);

    // Si no existe, mostramos un mensaje y terminamos la funcion
    if (posicion == -1) {
        printf("\nProducto no encontrado.\n");
        return;
    }

    // Desplazamos los productos siguientes una posicion hacia atras
    // para ocupar el espacio del producto que se va a eliminar
    for (i = posicion; i < *total - 1; i++) {

        // Copiamos el nombre y los demas datos del siguiente producto
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    // Disminuimos el total de productos registrados
    (*total)--;

    printf("\nProducto eliminado correctamente.\n");
}


// ======================================================
//          FUNCION PARA CALCULAR EL TIEMPO TOTAL
// ======================================================

float calcularTiempoTotal(int cantidades[MAX], float tiempos[MAX], int total) {

    // Variable para acumular el tiempo de fabricacion de todos los productos
    float suma = 0;

    int i;

    // Recorremos los productos registrados
    for (i = 0; i < total; i++) {

        // Multiplicamos la cantidad demandada por el tiempo de cada unidad
        suma = suma + cantidades[i] * tiempos[i];
    }

    // Devolvemos el tiempo total calculado
    return suma;
}


// ======================================================
//         FUNCION PARA CALCULAR LOS RECURSOS TOTALES
// ======================================================

float calcularRecursos(int cantidades[MAX], float recursos[MAX], int total) {

    // Variable para acumular los recursos necesarios
    float suma = 0;

    int i;

    // Recorremos todos los productos registrados
    for (i = 0; i < total; i++) {

        // Multiplicamos la cantidad demandada por los recursos de cada unidad
        suma = suma + cantidades[i] * recursos[i];
    }

    // Devolvemos la cantidad total de recursos necesarios
    return suma;
}


// ======================================================
//             FUNCION PARA EVALUAR LA PRODUCCION
// ======================================================

void evaluarProduccion(int cantidades[MAX], float tiempos[MAX],
                       float recursos[MAX], int total) {

    // Variables para almacenar los valores disponibles de la fabrica
    float tiempoDisponible;
    float recursosDisponibles;

    // Variables para guardar los resultados de los calculos
    float tiempoNecesario;
    float recursosNecesarios;

    // Verificamos que existan productos para realizar los calculos
    if (total == 0) {
        printf("\nNo hay productos registrados para evaluar.\n");
        return;
    }

    // Solicitamos el tiempo maximo disponible para fabricar los productos
    printf("\nTiempo disponible de produccion (minutos): ");
    scanf("%f", &tiempoDisponible);

    // Solicitamos la cantidad de recursos que tiene disponible la fabrica
    printf("Cantidad de recursos disponibles: ");
    scanf("%f", &recursosDisponibles);

    // Llamamos a las funciones para obtener los totales necesarios
    tiempoNecesario = calcularTiempoTotal(cantidades, tiempos, total);
    recursosNecesarios = calcularRecursos(cantidades, recursos, total);

    // Mostramos los resultados obtenidos
    printf("\n===== RESULTADOS DE PRODUCCION =====\n");
    printf("Tiempo total necesario: %.2f minutos\n", tiempoNecesario);
    printf("Recursos totales necesarios: %.2f\n", recursosNecesarios);

    // Comprobamos si el tiempo y los recursos disponibles son suficientes
    if (tiempoNecesario <= tiempoDisponible &&
        recursosNecesarios <= recursosDisponibles) {

        printf("\nLa fabrica SI puede cumplir con la demanda.\n");

    } else {

        // Si alguna condicion no se cumple, indicamos que no es posible
        printf("\nLa fabrica NO puede cumplir con toda la demanda.\n");

        // Comprobamos si el tiempo disponible es insuficiente
        if (tiempoNecesario > tiempoDisponible) {
            printf("No hay suficiente tiempo de produccion.\n");
        }

        // Comprobamos si los recursos disponibles son insuficientes
        if (recursosNecesarios > recursosDisponibles) {
            printf("No hay suficientes recursos.\n");
        }
    }
}
