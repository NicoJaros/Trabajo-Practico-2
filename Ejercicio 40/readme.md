# Ejercicio 40

## Enunciado

Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro, 
entre otros datos, la clave del registro (id).

La función ubicará el registro correspondiente al id pasado como parámetro, y utilizando punteros imprimirá la 
+primera palabra del campo "desc" en forma inversa, además cambiará el estado del bit 3 para luego actualizar el archivo. 
Además, se agregará a una pila la potencia cuando los bits 0 y 2, del campo estado, estén encendidos, en caso contrario 
se agregará el registro al archivo “salida.dat” de organización secuencial.


## Codigo
```c
#include <stdio.h>
#include <stdlib.h>
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
int access ( long pass, struct lista_t *files );

int main (){

	FILE *fp;
	struct lista_t *pila = NULL, *aux;
	struct data_t datos;
	long clave;
	char opc;
	int flag;

	do{
		switch ( opc = Menu () ){

		case '1':
			system ("cls");
			printf("Ingrese la clave: ");
			scanf("%ld", &clave);

			flag = access (clave, pila);

			if ( flag == 2 ){
				printf("\n***No se encontro la clave***\n\n");
				system ("pause");
			}
			if ( flag == 1 ){
					printf("\n***Consulta exitosa***\n\n");
					system ("pause");
			}
			break;

		case '2':
			system("cls");
			if ( (fp = fopen("potencia.dat","rb") ) == NULL){
				printf("\n\n***Error al abrir el archivo potencia.dat***\n\n");
				system ("pause");
				break;
			}
			fread (&datos, sizeof (struct data_t), 1, fp);
			while ( !feof (fp) ){
				printf("%-60s    %3c   %d\n", datos.desc, datos.potencia, datos.estado);
				fread (&datos, sizeof (struct data_t), 1, fp);
			}
			fclose (fp);
			system ("pause");
			break;

		case '3':
			system("cls");
			if(pila == NULL){
				printf("\n***Pila vacia***\n\n");
	 			system("pause");
	  			break;
			}
			aux = pila;
			do {
				printf ("%-60s    %3c   %d\n", aux->datos.desc, aux->datos.potencia, aux->datos.estado);
				aux = aux->lazo;
			}
			while (aux->lazo != NULL);
			printf ("%-60s    %3c   %d\n", aux->datos.desc, aux->datos.potencia, aux->datos.estado);
			system ("pause");
			break;

		case '4':
			system("cls");
			if ( (fp = fopen("salida.dat","rb") ) == NULL){
				printf("\n\n***Error al abrir el archivo salida.dat***\n\n");
				system ("pause");
				break;
			}
			fread (&datos, sizeof (struct data_t), 1, fp);
			while ( !feof (fp) ){
				printf("%-60s    %3c   %d\n", datos.desc, datos.potencia, datos.estado);
				fread (&datos, sizeof (struct data_t), 1, fp);
				}
			fclose (fp);
			system ("pause");
			break;
		}
	} while (opc != '5');

	return 0;
}


char Menu (void){
	system ("cls");
	printf ("\n***Ejercicio 40***");
	printf("\n1_Consultar Id");
	printf("\n2_Listar Actualizacion de archivo");
	printf("\n3_Listar pila");
	printf("\n4_Listar archivo salida");
	printf("\n5_Salir");

	return getchar ();
}

int access ( long pass, struct lista_t *files ){

	FILE *arc, *exit;
	struct lista_t *aux;
	struct data_t dat;
	char *cpy, c = 'a';
	int i, j = 0, status = 0;

	if ( (arc = fopen("potencia.dat","rb+") ) == NULL){
		printf("\n\n***Error al abrir el archivo potencia.dat***\n\n");
		system ("pause");
		return status=0;
	}
	fseek(arc, (1L)*sizeof (struct data_t)*(pass-1), 0);
	fread (&dat, sizeof (struct data_t), 1, arc);
	if (dat.id == pass){
		// Comenzamos por invertir la primer palabra del campo "desc"
			// Copiamos la primer palabra y guardamos la direccion en el puntero cpy

			for ( i=0; i < strlen (dat.desc) ; i++ ){ // Copia en el puntero "cpy" la primer palabra de dat.desc
				if ( c == ' ' )
					break;
				else {
				c = dat.desc [i];
				cpy = &dat.desc[i];
				j++;
				}
			}

			for ( i = 0; i < ( j - 1 ); i++){ // Impresion invertida sobre el puntero cpy
				cpy--;
				printf ("%c", *cpy);
			}
			printf ("\n\n");

		// Cambio de estado del 3er bit de la variable "estado"

			dat.estado = dat.estado ^ ( 3<<1 ); // Logica xOR

		// Actualizacion del archivo

			fseek (arc, (-1L) * sizeof (struct data_t), 1);
			fwrite (&dat, sizeof (struct data_t), 1, arc);

		// Bit 0 y 2 del campo "estado" | Apilado

			if ( (dat.estado & (2<<1) ) && (dat.estado & (0<<1) ) ){

				aux = malloc ( sizeof (struct lista_t) );
				if (aux == NULL){
					printf("\n\n***No hay memoria disponible\n\n");
					system("pause");
					return status = 3;
				}
				aux->datos.potencia = dat.potencia;

				// Apilo
				aux->lazo = files;
				files = aux;
			}

		// Guardado en el archivo "salida.dat"
			else {
				if ( (exit = fopen("salida.dat","ab") ) == NULL){
					printf("\n\n***Error al abrir el archivo salida.dat***\n\n");
					system ("pause");
					return status=0;
				}
				fwrite (&dat, sizeof (struct data_t), 1, exit);
				fclose (exit);
			}
			system ("pause");
		// Final del primer if
			return status = 1;
		}

	fclose (arc);
	return status = 2;
}



```
