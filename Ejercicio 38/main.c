#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

struct cola_t{
	char ang;
	struct cola_t *lazo;
};

int main () {

	struct cola_t *prim = NULL, *ult = NULL, *aux;
	char sup;
	int i, j = 0, val;

	for (i=1; i <= 9; i++){

		aux = (struct cola_t *) malloc (sizeof (struct cola_t) );

		if(aux == NULL){
			printf("\n\n***Espacio de memoria insuficiente***\n");
			return 0;
		}
		// Carga en la cola de los valores del seno para el primer cuarto de ciclo
		aux->ang = sin ( (i*10*3.141592) / 180) * 127;;

		if (prim == NULL){
			prim = aux;
			ult = aux;
		}
		else {
			ult->lazo = aux;
			ult = aux;
		}
		aux->lazo = NULL;
	}

	// Impresion de la cola original
	i = 0;
	aux = prim;
	while ( aux ){
	    i = i+10;
	    printf("%-5d | %d°\n", aux->ang, i); // Impresion cada 10° y su valor
	    if(i == 90)
	    	sup = aux->ang;

	    aux = aux->lazo;
	    }
	// Impresion de pos a minimo
	for ( j = 8 ; j >= 0 ; j-- ){
		i = i+10;
	    val = sin ( (j*10*3.141592) / 180) * sup;
	    printf ("%-5d | %d°\n", val, i); // Impresion de la cola de manera invertida
	}
	// Impresion del minimo a neg
	for ( j = 1 ; j <= 9 ; j++ ){
	   i = i+10;
	   val = sin ( (j*10*3.141592) / 180) * sup;
	   printf("%-5d | %d°\n", -val, i); // Impresion de valores negativos
	}
	// Impresion de neg a minimo
    for ( j = 8 ; j >= 0 ; j-- ){
    	i = i+10;
	    val = sin ( (j*10*3.141592) / 180) * sup;
	    printf("%-5d | %d°\n", -val, i); // Impresion de valores negativos
	}

	return 0;
}
