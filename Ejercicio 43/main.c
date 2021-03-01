#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

struct lista_t {
	repuestos_t dato;
	struct lista_t *lazo;
};

char Menu (void);
long ordenamiento (struct lista_t *date); // Funcion para transformar la fecha y hora a numeros, en una sola variable
int at0i (char ascii); // conversion ASCII a int

int main (){

	FILE *reg;
	struct lista_t *primero = NULL, *ultimo = NULL, *aux, *recorrido, *pila = NULL, *paux;
	repuestos_t orden;
	long temp, temp_r;
	char opc;


	do{
		switch ( opc = Menu () ){
			case '1':
				system ("cls");
				reg = fopen ("ordenes.dat", "ab+");
				if (reg == NULL){
					printf ("\n\n***No se pudo abrir el archivo***\n");
					system ("pause");
					break;
				}
				aux = (struct lista_t *) malloc (sizeof (struct lista_t) );
				if (aux == NULL){
					printf("\n\n***No hay suficiente memoria***\n");
					break;
				}
				// Ingreso de datos por teclado

				printf("***ORDEN DE TRABAJO");
				printf("\nIngrese el numero de orden: ");
				scanf("%ld", &aux->dato.numeroDeOrden);
				fflush (stdin);
				printf("\nCliente: ");
				gets (aux->dato.cliente);
				fflush (stdin);
				printf("\nDescripcion de la falla: ");
				gets (aux->dato.descripciondeFalla);
				fflush (stdin);
				printf("\nModelo: ");
				gets (aux->dato.modelo);
				fflush (stdin);
				printf("\nFecha |AAAA/MM/DD|: ");
				gets (aux->dato.fecha);
				fflush (stdin);
				printf("\nHora |HH.MM (24hs)|: ");
				gets (aux->dato.hora);
				fflush (stdin);

				temp = ordenamiento (aux);

				// Guardamos el registro que esta cargado en Aux lista, en el archivo
				fwrite (&aux->dato, sizeof (repuestos_t), 1, reg);

				//Cargamos en una lista, el dato ordenado de menor a mayor los campos fecha y hora

				if (primero == NULL){    // Primer elemento de la lista
					primero = ultimo = aux;
					ultimo->lazo = NULL;
					}
				else{    // Si no es el primer elemento, debo buscar en que lugar lo insertare
					recorrido = primero;
					temp_r = ordenamiento (recorrido);

		            while (recorrido->lazo != NULL){   // Busco si se encuentra adelante (rutina de la pila)
						if ( temp <  temp_r ){   // Si fecha y hora ingresadas son menores a la de recorrido, colocamos en primer lugar
							aux->lazo = primero;
							primero = aux;
							break;
						}
				// Buscamos un lugar en el centro o el ultimo
						while ( recorrido->lazo ){
							if ( temp >  temp_r )
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

				fclose (reg);

				break;

			case '2':
				// Apilamos los datos de menor a mayor en la pila quedando la orden mas vieja en el tope

				if (primero == NULL){
					printf("\n\n***Lista vacia***\n");
					break;
				}
				// Apilado
				aux = primero;
				while ( aux ){
					paux = (struct lista_t *) malloc (sizeof (struct lista_t) );
				    if ( paux ){
				    	paux->dato = aux->dato;
				        paux->lazo = pila;
				        pila = paux;
				     }
				    else {
				    	printf("Memoria insuficiente\n");
				    }
				    aux = aux->lazo;
				}
				break;

			case '3':
				reg = fopen ("ordenes.dat", "rb");
				if (reg == NULL){
					printf ("\n\n***No se pudo abrir el archivo***\n");
					system ("pause");
					break;
				}
				fread (&orden, sizeof (repuestos_t), 1, reg);
				while ( !feof (reg) ){
					printf("\n%-ld   %10s     %10s     %10s      %10s      %10s",orden.numeroDeOrden, orden.cliente, orden.descripciondeFalla, orden.modelo, orden.fecha, orden.hora);
					fread (&orden, sizeof (repuestos_t), 1, reg);
				}
				system ("pause");
				fclose (reg);
				break;

			case '4':
				aux = pila;
				while (aux){
					printf("\n%-ld   %10s     %10s     %10s      %10s      %10s", aux->dato.numeroDeOrden, aux->dato.cliente, aux->dato.descripciondeFalla, aux->dato.modelo, aux->dato.fecha, aux->dato.hora);
					aux = aux->lazo;
				}
				system ("pause");
				break;
			}
		} while (opc != '5');

	return 0;
}

char Menu (void){

	system ("cls");
	printf ("\n***Respuestos CosmeFulanito***");
	printf("\n1_Agregar Orden de trabajo");
	printf ("\n2_Cargar Pila Ordenada");
	printf  ("\n3_Imprimir Archivo");
	printf ("\n4_Imprimir Pila");
	printf ("\n5_Salir");
	return getchar ();
}

long ordenamiento (struct lista_t *date){

	long dia, mes, anio, hora, min, tiempo;

		anio = 1000 * at0i (date->dato.fecha[0]) + 100 * at0i (date->dato.fecha[1]) + 10 * at0i (date->dato.fecha[2]) + 1 * at0i (date->dato.fecha[3]);
		mes = 10 * at0i (date->dato.fecha[4]) + 1 * at0i (date->dato.fecha[5]);
		dia = 10 * at0i (date->dato.fecha[0]) + 1 * at0i (date->dato.fecha[1]);
		hora = 10 * at0i (date->dato.hora[0]) + 1 * at0i (date->dato.hora[1]);
        min = 10 * at0i (date->dato.hora[3]) + 1 * at0i (date->dato.hora[4]);

	    tiempo = 100000000*anio + 1000000*mes + 10000*dia + 100*hora + min;
	    return tiempo;
}

int at0i ( char ascii ){

	int caracter = 0;
    switch ( ascii )
    {
        case '0':
        	caracter = 0;
        	break;

        case '1':
        	caracter = 1;
        	break;

        case '2':
        	caracter = 2;
            break;

        case '3':
        	caracter = 3;
            break;

        case '4':
        	caracter = 4;
        	break;

        case '5':
        	caracter = 5;
        	break;

        case '6':
        	caracter = 6;
        	break;
        case '7':
        	caracter = 7;
        	break;

        case '8':
        	caracter = 8;
        	break;

        case '9':
        	caracter = 9;
        	break;
    }
    return caracter;
}
