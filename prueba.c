#include <stdio.h>
#include <stdlib.h>

void busquedaExahustiva(int *cargas, int *tanques, int capacidad, int index, int n, int used_tanks, int *min_tanks) {
    // Si hemos distribuido todas las cargas, actualizamos el mínimo de tanques si es menor que el actual
    if (index == n) {
        *min_tanks = (*min_tanks < used_tanks) ? *min_tanks : used_tanks;
        return;
    }

    // Intentamos colocar la carga actual en cada tanque
    for (int i = 0; i < used_tanks; i++) {
        // Si el tanque actual puede contener la carga
        if (tanques[i] + cargas[index] <= capacidad) {
            // Distribuimos la carga en el tanque
            tanques[i] += cargas[index];
            // Llamamos recursivamente para la siguiente carga
            busquedaExahustiva(cargas, tanques, capacidad, index + 1, n, used_tanks, min_tanks);
            // Retiramos la carga del tanque para explorar otras posibilidades
            tanques[i] -= cargas[index];
        }
    }

    // Si hay espacio para un nuevo tanque, creamos uno nuevo y continuamos la búsqueda
    if (used_tanks < *min_tanks) {
        tanques[used_tanks] = cargas[index];
        busquedaExahustiva(cargas, tanques, capacidad, index + 1, n, used_tanks + 1, min_tanks);
    }
}

int main() {
    // Datos de ejemplo
    int cargas[] = {4, 98, 5, 65};
    int capacidad = 100;
    int n = sizeof(cargas) / sizeof(cargas[0]);

    // Inicialización de variables
    int *tanques = (int *)malloc(n * sizeof(int));
    int min_tanks = n; // Inicializamos con la máxima cantidad de tanques posible

    // Llamada a la función de busquedaExahustiva
    busquedaExahustiva(cargas, tanques, capacidad, 0, n, 0, &min_tanks);

    // Liberar memoria
    free(tanques);

    // Imprimir resultado
    printf("Cantidad mínima de tanques necesarios: %d\n", min_tanks);

    return 0;
}
