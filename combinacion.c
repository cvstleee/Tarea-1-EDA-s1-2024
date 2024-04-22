#include <stdio.h>
#include <stdlib.h>

int count = 0; //contar combinaciones
//Dominio: objects es el arreglo con las distintas cargas, num_objects es su largo, matrix es la matriz con 0, container_size es la cantidad de containers??
//index es la posición inicial?
//Descripción: realiza las distintas combinaciones de los containers

void print_combinations(int *objects, int num_objects, int **matrix, int container_size, int index) {
    int *prueba[4];
    int i, j = 0;

    //imprime la matriz que va quedando en cada iteración
    if (index == num_objects) {
        for (i = 0; i < container_size; i++) {
            for (j = 0; j < num_objects; j++) {
                printf("%d ", matrix[i][j]);


            }
            printf("\n");
        }


        printf("\n");
        //da el número de la combinación para saber donde va
        count++;
        printf("combinacion numero: %d\n", count);
        

        return;
    }


    for (int i = 0; i < container_size; i++) {
        //se coloca el objeto actual en el contenedor i. index probablemente indica el índice del objeto actual en el arreglo 
        //objects, y matrix es una matriz que representa las combinaciones de objetos en los contenedores.
        matrix[i][index] = objects[index];

        //incrementando index en 1. Esto permite considerar el próximo objeto en la siguiente llamada recursiva.
        print_combinations(objects, num_objects, matrix, container_size, index + 1);
        // se vuelve atrás (backtrack) eliminando el objeto que se había colocado en el contenedor i. 
        //Esto es importante para asegurar que todas las combinaciones sean consideradas correctamente.
        matrix[i][index] = 0; // backtrack
    }

   /**prueba = sumaCombinacion(i,j,matrix,container_size);

            printf("Suma combinacion %d", prueba);*/

}


//Realiza la suma de las combinaciones y filtra las que cumplen con el criterio de <100 (capacidad de c/contenedor)
// se va a ir guardando según la posición i (pos_fila) de la matriz y solo se moverá la j (pos_columna al hacer la suma

//y si llamamos a la suma en el main en vez de en la función??

//falta ver como filtrarlas y encontrar el óptimo
int *sumaCombinacion(int pos_fila, int pos_columna, int **matrix, int container_size){
    //container_size == número de containers 
    int *arregloSumas[container_size];
    int suma = 0;
    int aux = 0;

    //el for solo va moviendo el j, asumiendo que i = 0
    for(int i = pos_fila; i < container_size; i++){
        //el i solo aumenta dsp de que el 2do for termina
        for(int j = pos_columna; j < container_size; j++){
        suma += matrix[pos_fila][j];
        }
        arregloSumas[i] = suma;
    }

    /*for(int i = pos_fila; i <  container_size; i++){
        //aux = matrix[i][pos_columna];
        printf("AUXILIAR SUMA: %d\n",aux);
        suma = suma + matrix[i][pos_columna];
        printf("SUMA: %d\n",suma);
    }*/
    return arregloSumas;
}



int main() {
    int objects[] = {25,93,72,94}; // Puedes cambiar esto a cualquier conjunto de objetos
    int num_objects = sizeof(objects) / sizeof(objects[0]);
    int container_size = 4; // Puedes cambiar esto al número de contenedores que desees
    //llenar la matriz de 0
    int **matrix = (int **)malloc(container_size * sizeof(int *));

    //matriz del contenedor con solo 0
    for (int i = 0; i < container_size; i++) {
        matrix[i] = (int *)malloc(num_objects * sizeof(int));
        for (int j = 0; j < num_objects; j++) {
            matrix[i][j] = 0; // Inicializamos todos los contenedores a 0
        }
    }


    //aqui ocurre la magia

    print_combinations(objects, num_objects, matrix, container_size, 0);

    for (int i = 0; i < container_size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
