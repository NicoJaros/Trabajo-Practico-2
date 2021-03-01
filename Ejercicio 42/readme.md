# Ejercicio 42

## Enunciado

El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y debe ser devuelta. 
Para identificar la partida, el proveedor indicó que la falla fue en el partNumber: 1234 que tiene números de serie con el 
bit 3 y 5 en 1.

Para estas tareas se solicita:

Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.

## Codigo
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion [40];
   char ubicacion [100];
}repuestos_t;

// Implementamos una cola con doble lazo
struct cola_t {
	repuestos_t dato;
	struct cola_t *sig, *ant;
};

char Menu (void);

int main (){

	FILE *fp, *fpn, *finv;
	struct cola_t *prim = NULL, *ult = NULL, *aux;
	repuestos_t rep, repinv;
	char opc;

	do{
		switch ( opc = Menu () ){
			case '1':
				system("cls");
				fp = fopen ("Stock.dat", "rb");
				fpn = fopen ("Stockn.dat", "ab");
				if ( !fp || !fpn ){
					printf ("\n\n***Error al abrir el/los archivo/s***\n");
					system ("pause");
					break;
				}
				fread (&rep, sizeof (repuestos_t), 1, fp );
				while ( !feof (fp) ){
					if ( rep.partNumber == 1234){
						if ( (rep.serialNumber & (3<<1)) && (rep.serialNumber & (5<<1)) ){

							aux = (struct cola_t *) malloc (sizeof (struct cola_t) );
							if (aux == NULL){
								printf("\n\n***No hay suficiente memoria***\n");
								break;
							}
							strcpy (aux->dato.descripcion, rep.descripcion);
		                    strcpy (aux->dato.ubicacion, rep.ubicacion);
		                    aux->dato.serialNumber = rep.serialNumber;
		                    aux->dato.partNumber = rep.partNumber;

							if (prim == NULL)
								prim = ult = aux;
							else{
								aux->ant = ult;
								ult->sig = aux;
								ult = aux;
							}
							ult->sig = NULL;
							prim->ant = NULL;
						}
					}
					else {
						fwrite (&rep, sizeof (repuestos_t), 1, fpn); // Si no es un producto fallado, lo guardamos en un nuevo archivo
					}
					fread (&rep, sizeof (repuestos_t), 1, fp );
				}
				fclose (fp);
				fclose (fpn);

			// Para realizar la baja fisica, cambiaremos el nombre del nuevo archivo de stock

				if (remove ("Stock.dat") ) //  Elimino archivo original
					printf ("\n\n***No se puede eliminar el archivo original***\n");

				if (rename ("Stockn.dat", "Stock.dat") ) // Renombro el archivo
					printf ("\n\n***Error al renombrar el archivo nuevo\n");

				fpn = fopen ("Stockn.dat", "wb"); // Creo el archivo de stock nuevo
				if ( !fpn ){
					printf("\n\n***Error en la creacion del nuevo archivo***\n");
					system("pause");
					break;
				}
				fclose (fpn);

			// Guardamos los registro de la cola en orden inverso
				finv = fopen ("StockInverso.dat", "ab");
				if ( !finv ){
					printf("\n\n***Error en la apertura del archivo inv***\n");
					system("pause");
					break;
				}
				// recorro la pila desde el ultimo elemento
				aux = ult;
				while(aux){
					strcpy (repinv.descripcion,aux->dato.descripcion);
					strcpy (repinv.ubicacion, aux->dato.ubicacion);
				    repinv.serialNumber = aux->dato.serialNumber;
				    repinv.partNumber = aux->dato.partNumber;

				    fwrite (&repinv, sizeof (repuestos_t), 1, finv); //

				    aux = aux->ant;
				}
				fclose (finv);
				system ("pause");
				break;

			case '2':
				// Lectura del archivo de stock sin los repuestos fallados
				fp = fopen ("Stock.dat", "rb");
				if ( !fp ){
					printf("\n\n***Error en la apertura del archivo Stock***\n");
					system("pause");
					break;
				}
				printf ("\n\nPart Number     Serial Number     Descripcion                     Ubicacion");

				fread (&rep, sizeof ( repuestos_t), 1, fp);
				while ( !feof (fp) ){
					printf ("\n%-15ld    %-10ld    %-30s    %-10s", rep.partNumber, rep.serialNumber, rep.descripcion, rep.ubicacion);
					fread (&rep, sizeof ( repuestos_t), 1, fp);
				}
				system ("pause");
				fclose (fp);
				break;

			case '3':
				// Lectura del archivo de stock inverso
				finv = fopen ("StockInverso.dat", "rb");
				if ( !finv ){
					printf("\n\n***Error en la apertura del archivo inv***\n");
					system("pause");
					break;
				}
				printf ("\n\nPart Number     Serial Number     Descripcion                     Ubicacion");

				fread (&repinv, sizeof ( repuestos_t), 1, finv);
				while ( !feof (finv) ){
					printf ("\n%-15ld    %-10ld    %-30s    %-10s", repinv.partNumber, repinv.serialNumber, repinv.descripcion, repinv.ubicacion);
					fread (&repinv, sizeof ( repuestos_t), 1, finv);
				}
				system ("pause");
				fclose (finv);
				break;
		}
	} while (opc != '4');

	return 0;
}

char Menu (void){
	system ("cls");

	printf ("***Respuestos CosmeFulanito***");
	printf ("\n1_iniciar busqueda de parte 1234 fallada");
	printf ("\n2_Listar Nuevo Stock");
	printf ("\n3_Listar Stock Inverso");
	printf ("\n4_Salir");
	return getchar ();
}

```
