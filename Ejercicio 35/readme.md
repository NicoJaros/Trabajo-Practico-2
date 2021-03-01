# Ejercicio 35

# Enunciado
Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, 
en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", 
de organización secuencial, los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.

# Archivo main
```
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct data_t{
	char nomyape[40], mail[30];
	short edad;
	long tel;
};

struct stack_t {
	struct data_t datos;
	struct stack_t *lazo;
};

int main (){

	struct stack_t *pila=NULL, *aux;
	struct data_t consulta;
	FILE *fp;
	char opc;

	do{
		system("cls");
		fflush(stdin);
		printf("   ***DATOS DE INTERNOS***   ");
		printf("\n1_Agregar un interno");
		printf("\n2_Imprimir listado");
		printf("\n3_Salir");
        scanf("%c", &opc);

		switch ( opc ){
		    case '1':
	    		aux = (struct stack_t *) malloc (sizeof (struct stack_t));
		    	if (aux == NULL){
		    		printf("\n\nMemoria Insuficiente***\n\n");
		    		return 3;
		    	}
		   		fflush(stdin);
		   		printf("\n\nNombre y apellido: ");
		   		gets (aux->datos.nomyape);
		   		fflush(stdin);
		   		printf("\nEdad: ");
		   		scanf("%i", &aux->datos.edad);
	    		fflush(stdin);
	    		printf("\nTelefono: ");
	    	    scanf("%ld", &aux->datos.tel);
		    	fflush(stdin);
		   		printf("\nMail: ");
		   		gets (aux->datos.mail);

		   		aux->lazo = pila;
		   		pila = aux;

		   		fp = fopen("contactos.dat", "ab");
		   		if(fp == NULL){
		       	   	printf("\n\n***No existe el archivo***\n\n");
		   	   	   	break;
		       	}
		    	if( (aux->datos.edad) >= 21)
		    		fwrite(&aux->datos, sizeof (struct data_t), 1, fp);

		    	fclose (fp);
		    	system ("pause");
		    	break;

		    case '2': // PARA RECCORER LA PILA Y NO ELIMINAR LOS DATOS DE LA MEMORIA, SOLO TENGO QUE RECORRERLA UTILIZANDO AUX
		    	      // SI QUISIERA ELIMINAR LOS DATOS, MUESTRO EL DATO USANDO LA PILA Y LIBERO USANDO FREE (AUX)
		    	fp = fopen("contactos.dat", "rb");
		    	if(fp == NULL){
		      	   	printf("\n\n***No existe el archivo***\n\n");
		   	   	   	break;
		       	}
		 		fread (&consulta, sizeof (struct data_t), 1, fp);
		 		printf("\n\nNombre y Apellido        Edad       Telefono          Mail");

		 		while ( !feof (fp) ){
		 			printf ("\n%-30s  %i  %ld   %-30s", consulta.nomyape, consulta.edad, consulta.tel, consulta.mail);
		 			fread (&consulta, sizeof (struct data_t), 1, fp);
		 		}
		    	fclose (fp);
		    	system ("pause");
		    	break;

		}
	}while ( opc != '3');


    return 0;
}

```
