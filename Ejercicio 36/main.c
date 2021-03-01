#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct data_t{
	char nomyape[40], mail[40];
	short edad;
	long tel;
};

struct lista_t {
	struct data_t datos;
	struct lista_t *lazo;
};

char Menu (void);

int main (){

	FILE *fp, *reg;
	struct lista_t *primero = NULL, *ultimo = NULL, *aux, *recorrido;
	struct data_t dato;
	char opc;

	do {
		switch ( opc = Menu () ){

		case '1':

			if ((fp = fopen("contactos.dat", "rb")) == NULL ){
				printf("\n\n***No existe el archivo***\n\n");
				system ("pause");
				break;
			}

			// Leemos el archivo donde estan almacenados los datos, hasta el fin del archivo e iremos almacenando los datos en una lista dinamica

			fread (&dato, sizeof (struct data_t), 1, fp);

			while ( !feof (fp) ){

				aux = (struct lista_t *) malloc (sizeof (struct lista_t));
				if (aux == NULL){
					printf("\n\nMemoria Insuficiente***\n\n");
					break;
				}

				aux->datos = dato;     // Cargo el dato del archivo en la estructura lista_t aux

			// Buscamos donde insertaremos el dato

				if (primero == NULL){    // Primer elemento de la lista
					primero = ultimo = aux;
					ultimo->lazo = NULL;
				}
				else{    // Si no es el primer elemento, debo buscar en que lugar lo insertare
					recorrido = primero;
					while (recorrido->lazo != NULL){   // Busco si se encuentra adelante (rutina de la pila)
						if (strcmp (aux->datos.nomyape,  recorrido->datos.nomyape) < 0 ){   // Si se cumple, colocamos el dato en el primer lugar
							aux->lazo = primero;
							primero = aux;
							break;
						}
					// Buscamos un lugar en el centro o el ultimo
						while (recorrido->lazo){
							if (strcmp (aux->datos.nomyape,  recorrido->lazo->datos.nomyape) > 0 )
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
				fread(&dato, sizeof (struct data_t), 1, fp);
			}

			fclose (fp);
			break;

		case '2':
			// Impresion en pantalla y guardado de la lista en contactos_ordenados.dat

			reg = fopen ("contactos_ordenados.dat", "wb");
			if ( !reg ){
				printf("\n\n***No existe el archivo***\n\n");
				system ("pause");
				break;
			}

			printf("\n\nNombre y Apellido        Edad       Telefono          Mail");
			aux = primero;
			while (aux) {
				printf ("\n%-30s  %i  %ld   %-30s", aux->datos.nomyape, aux->datos.edad, aux->datos.tel, aux->datos.mail);
				fwrite (&aux->datos, sizeof (struct data_t), 1, reg);
				aux = aux->lazo;
				}

			fclose (reg);
			system ("pause");
			break;
		}

	} while (opc != '3');

	return 0;
}

char Menu (){

	fflush(stdin);
	system ("cls");
	printf("***Ejercicio 36***");
	printf("\nPresione 1 para continuar ");
	printf("\nPresione 2 para listar alfabeticamente ");
	printf("\nPresione 3 para salir ");
	return getchar ();
}
