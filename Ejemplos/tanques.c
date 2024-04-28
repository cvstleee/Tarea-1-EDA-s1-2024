#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void busquedaExhaustiva(int *cargas, int *tanques, int capacidad, int index, int n, int used_tanks, int *min_tanks) {
    // Si hemos distribuido todas las cargas, actualizamos el mínimo de tanques si es menor que el actual
    if (index == n) {
        if (*min_tanks < used_tanks) {
            *min_tanks = *min_tanks;
        } else {
            *min_tanks = used_tanks;
        }
        return;
    }

    // Intentamos colocar la carga actual en cada tanque
    for (int i = 0; i < used_tanks; i++) {
        // Si el tanque actual puede contener la carga
        if (tanques[i] + cargas[index] <= capacidad) {
            // Distribuimos la carga en el tanque
            tanques[i] += cargas[index];
            // Llamamos recursivamente para la siguiente carga
            busquedaExhaustiva(cargas, tanques, capacidad, index + 1, n, used_tanks, min_tanks);
            // Retiramos la carga del tanque para explorar otras posibilidades
            tanques[i] -= cargas[index];
        }
    }

    // Si hay espacio para un nuevo tanque, creamos uno nuevo y continuamos la búsqueda
    if (used_tanks < *min_tanks) {
        tanques[used_tanks] = cargas[index];
        busquedaExhaustiva(cargas, tanques, capacidad, index + 1, n, used_tanks + 1, min_tanks);
    }
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Uso: %s archivo.txt\n", argv[0]);
        return 1;
    }

    FILE *archivo;
    int tanks, capacidad, *cargas, i;
    
    // Abrir el archivo
    archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Leer tanques y capacidad
    fscanf(archivo, "%d %d", &tanks, &capacidad);

    // Contar el número de elementos en la lista
    int n = 0;
    while (fscanf(archivo, "%d", &i) != EOF) {
        n++;
    }
    rewind(archivo); // Regresar al inicio del archivo

    // Saltar las primeras dos líneas
    fscanf(archivo, "%*d %*d");

    // Almacenar las cargas
    cargas = (int *)malloc(n * sizeof(int));
    if (cargas == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }
    
    for (i = 0; i < n; i++) {
        fscanf(archivo, "%d", &cargas[i]);
    }

    // Cerrar el archivo
    fclose(archivo);

    // Imprimir los valores almacenados
    printf("Tanques: %d\n", tanks);
    printf("Capacidad: %d\n", capacidad);
    printf("Cargas: [");
    for (i = 0; i < n; i++) {
        printf("%d", cargas[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    //int m = sizeof(cargas) / sizeof(cargas[0]);

    int m = tanks;


    // Inicialización de variables
    int *tanques = (int *)malloc(m * sizeof(int));
    int min_tanks = m; // Inicializamos con la máxima cantidad de tanques posible

    //calculo de tiempo
    float tiempo_algoritmo = 0;
	clock_t clock_ini, clock_fin;

    clock_ini = clock();

    // Llamada a la función de busquedaExahustiva
    busquedaExhaustiva(cargas, tanques, capacidad, 0, m, 0, &min_tanks);
    

    // Imprimir resultado
    printf("Cantidad minima de tanques necesarios: %d\n", min_tanks);
	
	clock_fin = clock();
	tiempo_algoritmo = (float)((clock_fin - clock_ini) / CLOCKS_PER_SEC);
	
	printf("\nTiempo del algoritmo en segundos: %.2f  \n", tiempo_algoritmo); 




    // Liberar memoria
    free(tanques);

    // Liberar memoria
    free(cargas);

    return 0;
}
