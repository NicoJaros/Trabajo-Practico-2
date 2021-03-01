# Ejercicio 41

## Enunciado
El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada. Para dicha tarea se 
solicitó categorizar a los respuestos bajo la siguiente estructura de datos:

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   chat ubicacion[100];        
}repuestos_t;

Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos 
para luego guardarlos en un archivo de stock con organización secuencial.

Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.

## Codigo
```c
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion [40];
   char ubicacion [100];
}repuestos_t;

struct lista_t {
	repuestos_t dato;
	struct lista_t *lazo;
};

char Menu (void);

int main (){

	FILE *fp, *sto;
	struct lista_t *primero=NULL, *ultimo=NULL, *aux=NULL, *recorrido;
	repuestos_t rep;
	char opc, exit;
	do{
		switch ( opc = Menu () ){
			case '1':
				do {
					system ("cls");
					aux = (struct lista_t *) malloc (sizeof (struct lista_t) );
					if (aux == NULL){
						printf("\n\n***No hay suficiente memoria***\n");
						break;
					}
					fflush (stdin);
					printf ("Ingrese el numero de parte: ");
					scanf ("%ld", &aux->dato.partNumber);
					fflush (stdin);
					printf ("\nIngrese el numero de serie: ");
					scanf ("%ld", &aux->dato.serialNumber);
					fflush (stdin);
					printf ("\nIngrese la descripcion: ");
					gets (aux->dato.descripcion);
					fflush (stdin);
					printf ("\nIngrese la ubicacion: ");
					gets (aux->dato.ubicacion);
					fflush (stdin);

					if (primero == NULL){    // Primer elemento de la lista
						primero = ultimo = aux;
						ultimo->lazo = NULL;
						printf("\nPrimer elemento ");
						getchar ();
						fflush(stdin);
						}
					else{    // Si no es el primer elemento, debo buscar en que lugar lo insertare
						recorrido = primero;
						while (recorrido->lazo != NULL){   // Busco si se encuentra adelante (rutina de la pila)
							if (strcmp (aux->dato.descripcion,  recorrido->dato.descripcion) < 0 ){   // Si se cumple, colocamos el dato en el primer lugar
								printf("\nPrimer Lugar");
								getchar ();
								fflush(stdin);
								aux->lazo = primero;
								primero = aux;
								break;
							}

							while (recorrido->lazo){
								if (strcmp (aux->dato.descripcion,  recorrido->lazo->dato.descripcion) > 0 )
									recorrido = recorrido->lazo;
								else
									break;
							}

							if (recorrido == ultimo){   // Ultimo lugar
								ultimo->lazo = aux;
								ultimo = aux;
								ultimo->lazo = NULL;
								printf("\nUltimo Lugar");
								getchar ();
								fflush(stdin);
								break;
							}

						// Si no es el primero o el ultimo lugar, debera ser uno central

							aux->lazo = recorrido->lazo;
							recorrido->lazo = aux;
							printf("\nLugar central");
							getchar ();
							fflush(stdin);
							break;
						}
						// Cierro el While si recorrido->lazo = NULL   -> Es el ultimo lugar

						if (recorrido == ultimo){   // Ultimo lugar
							ultimo->lazo = aux;
							ultimo = aux;
							ultimo->lazo = NULL;
							printf("\nUltimo Lugar");
							getchar ();
							fflush(stdin);
							break;
						}
					}
					printf ("\n\nPart Number     Serial Number     Descripcion                     Ubicacion");
					printf("\n%-15ld    %-10ld    %-30s    %-10s", aux->dato.partNumber, aux->dato.serialNumber, aux->dato.descripcion, aux->dato.ubicacion);
					printf ("\n\nDesea cargar otro item? Presione 'N' si desea salir" );
					scanf ("%c", &exit);
					fflush (stdin);
					system ("pause");

				} while (exit != 'N');

			// Creo el archivo de stock y guardamos la lista

				fp = fopen ("Stock.dat", "wb+");
				if ( fp == NULL ){
					printf("\n\n***Error al abrir el archivo de Stock***\n");
					system ("pause");
					break;
				}
				aux = primero;
				while (aux){

					fwrite(&aux->dato, sizeof (repuestos_t), 1, fp);
					aux = aux->lazo;
				}
				fclose (fp);

			break;

			case '2': // Impresion por pantalla del archivo stock
				system ("cls");
				sto = fopen ("Stock.dat", "rb");
				if ( sto == NULL ){
					printf ("\n\n***Error al abrir el archivo de Stock***\n");
					system ("pause");
					break;
				}
				printf ("\n\nPart Number     Serial Number     Descripcion                     Ubicacion");

				fread (&rep, sizeof (repuestos_t), 1, sto );
				while ( !feof (sto) ){
					printf ("\n%-15ld    %-10ld    %-30s    %-10s", rep.partNumber, rep.serialNumber, rep.descripcion, rep.ubicacion);
					fread (&rep, sizeof (repuestos_t), 1, sto );
				}
				fclose (sto);
				system ("pause");
				break;

			case '3':
				return 0;
		}
	} while (opc != 3);

	return 0;
}

char Menu (void){
	system ("cls");

	printf ("***Respuestos CosmeFulanito***");
	printf("\n1_Cargar repuesto");
	printf("\n2_Listar Stock");
	printf("\n3_Salir");
	return getchar ();
}



```
