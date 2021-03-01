# Ejercicio 44

## Enunciado
El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la 
pila y genera un orden de extracción de repuestos al depósito. Para optimizar los viajes al depósito se arma una lista 
con los repuestos que cada orden necesita utilizando la siguiente estructura:

typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;
Se pide cargar la lista de repuestos solicitados por los técnicos. Tener en cuenta que varios técnicos pueden necesitar 
la misma parte, y en esos casos se debe incrementar la cantidad pedida en la lista.

## Codigo
```c
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

struct extraccion {
    repuestos_t dato;
    int cantidad;
    struct extraccion *lazo;
};

char Menu (void);
long ordenamiento (struct lista_t *date); // Funcion para transformar la fecha y hora a numeros, en una sola variable
int at0i (char ascii); // conversion ASCII a int

int main (){

	FILE *reg;
	struct lista_t *primero = NULL, *ultimo = NULL, *aux, *recorrido, *pila = NULL, *paux;
	struct extraccion *prim_ext = NULL, *ult_ext = NULL, *aux_ext, *recor_ext;
	repuestos_t orden;
	long temp, temp_r;
	char opc;
	int FlagModelo = 1;


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


		//       ************    COMIENZO DEL EJERCICIO 44         ***********

			//Recorrido de la pila
				paux = pila;
				while ( paux ){
					// Incrementamos la cantidad de Modelos iguales solicitados por los tecnicos
				        aux_ext = prim_ext;
				        while(aux_ext) {
				            if (strcmp (aux_ext->dato.modelo, paux->dato.modelo) == 0){
				                aux_ext->cantidad++;
				             	FlagModelo = 0;
				            }
				            aux_ext = aux_ext->lazo;
				        }
				   // Solicitud por una unidad
				        if ( FlagModelo ){
				            aux_ext = (struct extraccion*) malloc (sizeof  (struct extraccion) );
				            if ( aux_ext ){
				            	aux_ext->dato = paux->dato; // Carga de los datos en la orden de extraccion
				                aux_ext->cantidad = 1;

				   // Comenzamos la carga de los datos en la lista

				                if ( prim_ext == NULL ){   // Primer elemento de la lista
				                	prim_ext = ult_ext = aux_ext;
				                    ult_ext->lazo = NULL;
				                }
				                // Si no es el primer elemento, debemos buscar donde guardarlo

				                else {
				                    recor_ext = prim_ext;
				                    while ( recor_ext->lazo ){
				                    	if( strcmp (recor_ext->dato.modelo, aux_ext->dato.modelo) > 0 ){ // Colocamos en el primer lugar
				                    		aux_ext->lazo = prim_ext;
				                    		prim_ext = aux_ext;
				                    		break;
				                    	}

				                    while ( recorrido->lazo){
				                    	if ( strcmp (recor_ext->lazo->dato.modelo, aux_ext->dato.modelo) < 0  )
				                           	recor_ext = recor_ext->lazo;
				                        else
				                        	break;
				                    }

				                        if ( recor_ext == ult_ext ){ // Ultimo lugar en la lista
				                            ult_ext->lazo = aux_ext;
				                            ult_ext = aux_ext;
				                            ult_ext->lazo = NULL;
				                        }
				                        // Lugar Central en la lista
				                        aux_ext->lazo = recor_ext->lazo;
				                        recor_ext->lazo = aux_ext;
				                    }
				                }
				            }
				        }
				    paux = paux->lazo;
				}

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

```
