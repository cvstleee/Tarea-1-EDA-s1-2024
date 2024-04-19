#include <stdio.h>
#include <stdlib.h>

int count = 0; //contar combinaciones
void print_combinations(int *objects, int num_objects, int **matrix, int container_size, int index) {
    int prueba = 0;
    int i, j = 0;
    //ARREGLO VACIO
    if (index == num_objects) {
        for (i = 0; i < container_size; i++) {
            for (j = 0; j < num_objects; j++) {
                printf("%d ", matrix[i][j]);


            }
            printf("\n");
            
        }
        printf("\n");

        count++;
        printf("combinacion numero: %d\n", count);
        

        return;
    }

    for (int i = 0; i < container_size; i++) {
        matrix[i][index] = objects[index];
        print_combinations(objects, num_objects, matrix, container_size, index + 1);
        matrix[i][index] = 0; // backtrack
        prueba = sumaCombinacion(j,i,matrix,container_size);
            printf("Suma combinacion %d\n", prueba);
    }

}


int sumaCombinacion(int pos_fila, int pos_columna, int **matrix, int container_size){
    //int *arregloSumas[];
    int suma = 0;
    int aux = 0;
    for(int i = pos_fila; i <  container_size; i++){
        //aux = matrix[i][pos_columna];
        printf("AUXILIAR SUMA: %d\n",aux);
        suma = suma + matrix[i][pos_columna];
        printf("SUMA: %d\n",suma);
    }
    return suma;
}



int main() {
    int objects[] = {25,93,72,94}; // Puedes cambiar esto a cualquier conjunto de objetos
    int num_objects = sizeof(objects) / sizeof(objects[0]);
    int container_size = 4; // Puedes cambiar esto al número de contenedores que desees
    //llenar la matriz de 0
    int **matrix = (int **)malloc(container_size * sizeof(int *));
    for (int i = 0; i < container_size; i++) {
        matrix[i] = (int *)malloc(num_objects * sizeof(int));
        for (int j = 0; j < num_objects; j++) {
            matrix[i][j] = 0; // Inicializamos todos los contenedores a 0
        }
    }

    print_combinations(objects, num_objects, matrix, container_size, 0);

    for (int i = 0; i < container_size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
