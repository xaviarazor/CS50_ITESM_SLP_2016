#include <stdio.h>
#include <cs50.h>
// Programa que corre burbuja
int main(void){
    // Esto lo usas para inicializar un arreglo con
    // valores predeterminados
    int arreglo[] = {10, 8, 1, 9, 11, 0, 2, 7};
    printf("Arreglo sin ordenar:\n");
    // i debe ser menor al tamanho del arreglo para
    // seguir corriendo el ciclo for
    for(int i = 0;i < 8;i++){
        printf("%i ", arreglo[i]);
    }
    printf("\n");
    
    
    
    // Burbuja!
    // sorted indica si se hizo algun cambio
    // al arreglo
    bool sorted = false;
    // Compara que sorted sea falso para
    // continuar ordenando
    while(!sorted){
        sorted = true;
        // Se corre n-1 veces, porque el elemento
        // 8 no existe (i=7->arreglo[i+1])
        for(int i = 0;i < 7;i++){
            // Variable temporal para guardar el valor
            // i de arreglo
            int temp = arreglo[i];
            if(temp > arreglo[i+1]){
                // Se intercambian los numeros en
                // el arreglo
                arreglo[i] = arreglo[i+1];
                arreglo[i+1] = temp;
                // indica que se hizo un cambio al
                // ciclo principal
                sorted = false;
            }
        }
    }
    
    
    // Exito!
    printf("Arreglo ordenado:\n");
    for(int i = 0;i < 8;i++){
        printf("%i ", arreglo[i]);
    }
    printf("\n");
    // Esto de aqui no regresa al inicio
    // por favor no interpreten lo que quieran
    // del ingles usado en un lenguaje de programacion
    // puede ser algo muy especifico.
    // En realidad esto "regresa" o manda un resultado
    // del programa al sistema operativo.
    // 0 siginifica que todo esta bien. En caesar
    // regresar 1 significa un error debido a
    // que el usuario no les dio los argumentos
    // necesarios.
    return 0;
}
