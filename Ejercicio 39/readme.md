# Ejercicio 39

##
Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.

Los datos que cargará el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;
Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia. 
Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia. Una vez 
finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en 
pantalla los datos.

## Codigo
```
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct data_t {
	char desc[60];
	unsigned char potencia;
	unsigned int estado;
	int id;
};

struct lista_t {
	struct data_t datos;
	struct lista_t *lazo;
};

char Menu (void);

int main () {
	FILE *fp;
	struct lista_t *primero = NULL, *ultimo = NULL, *aux, *recorrido;
	struct data_t doc;
	char opc;

	do {
		opc = Menu ();
		switch (opc) {
			case '1':
				system ("cls");
				aux = (struct lista_t *) malloc (sizeof (struct lista_t) );
				if (aux == NULL){
					printf("\n\n***No hay suficiente memoria***\n");
					break;
				}

			// Carga de datos en la variable doc
				fflush (stdin);
				printf("Ingrese la descripcion: ");
				gets (doc.desc);
				fflush (stdin);
				printf("\nIngrese la potencia [0-255W]: ");
				scanf ("%c", &doc.potencia);

				aux->datos.estado = doc.desc[0] * aux->datos.potencia;
				fflush (stdin);

			// Copiado de los datos al aux de la lista
				aux->datos.potencia = doc.potencia;
				aux->datos.estado = doc.estado;
				strcpy (aux->datos.desc, doc.desc);

				if (primero == NULL){    // Primer elemento de la lista
					primero = ultimo = aux;
					ultimo->lazo = NULL;
				}
				else{    // Si no es el primer elemento, debo buscar en que lugar lo insertare
					recorrido = primero;
					while (recorrido->lazo != NULL){   // Busco si se encuentra adelante (rutina de la pila)
						if ( aux->datos.potencia >  recorrido->datos.potencia ){   // Si se cumple, colocamos el dato en el primer lugar
							aux->lazo = primero;
							primero = aux;
							break;
						}
					// Buscamos un lugar en el centro o el ultimo
						while (recorrido->lazo){
							if ( aux->datos.potencia < recorrido->lazo->datos.potencia )
								recorrido = recorrido->lazo;
							else
								break;
						}

						if (recorrido == ultimo){   // Ultimo lugar
							ultimo->lazo = aux;
							ultimo = aux;
							ultimo->lazo = NULL;
							break;
						}

					// Si no es el ultimo lugar, debera ser uno central

						aux->lazo = recorrido->lazo;
						recorrido->lazo = aux;
						break;
					}
					// Cierro el While. Si recorrido->lazo = NULL   -> Es el ultimo lugar

					if (recorrido == ultimo){   // Ultimo lugar
						ultimo->lazo = aux;
						ultimo = aux;
						ultimo->lazo = NULL;
						break;
					}
				}
			break;

			case '2':
				system ("cls");

				fp = fopen ("potencia.dat", "wb+");
				if (fp == NULL){
						printf("No se puede crear el archivo potencia.dat\n");
						system("pause");
						break;
				}
			// Recorrido de la lista -> Impresion en pantalla y guardado en el archivo
				doc.id = 0;
				printf("Descripcion         Potencia        Estado");
				aux = primero;
				while (aux) {
					doc.id ++;
					aux->datos.id = doc.id;
					fwrite(&aux->datos, sizeof (struct data_t), 1, fp);
					printf("\n%-20s    %-5c   %d   %i", aux->datos.desc, aux->datos.potencia, aux->datos.estado, doc.id);
					aux = aux->lazo;
				}
				system ("pause");
				fclose (fp);
				break;
		}
	} while (opc != '3');


	return 0;
}

char Menu (void){

	system ("cls");
	printf("***MEDIDOR DE POTENCIA***");
	printf("\n1_Agregar datos");
	printf("\n2_Listar");
	printf("\n3_Salir");
	fflush (stdin);

	return getchar ();
}

```
