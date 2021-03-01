#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

struct data_t {
	long cl;
	int  valor;
	char d[30], b;
	unsigned int tipo;
};

struct stack_t {
	long password, ubi;
	struct stack_t *lazo;
};

struct stack_t * apilar ( struct stack_t *local, long pass);

int main (){

	FILE *bf;
	struct stack_t *prim;
	struct data_t datos;
	long clave [5];
	int i;

	for (i = 0; i < sizeof (clave) ; i++){
		fflush (stdin);
		printf("\nIngresar las claves: ");
		scanf("%ld", &clave[i]);
	}

	for (i = 0; i < sizeof (clave); i++)
		prim = apilar (prim, clave[i]);

	if(prim == NULL){
		printf("\n\n***No se encontro ningun registro con esas claves | Pila vacia***\n");
		return 0;
	}

	do {
		if( (bf = fopen ("datos.dat","rb")) == NULL ){
			printf("\n\n***Error al abrir el archivo***\n");
		    return 0;
		}
		fseek (bf, prim->ubi * sizeof (struct data_t), 0); // Sin casteo ya que "ubi" es del tipo long
		fread (&datos, sizeof(datos), 1, bf);
		printf ("Descripcion: %s\n", datos.d);

	} while (prim->lazo != NULL);

	fclose(bf);
	return 0;
}

struct stack_t * apilar (struct stack_t *local, long pass) {

	FILE *fp;
	struct stack_t *aux;
	struct data_t dato;
	long ubicacion = 0;

	if ( (fp = fopen("datos.dat","rb+") ) == NULL){
		printf("\n\n***Error al abrir el archivo***\n");
		return NULL;
	}
	// Busqueda del registro en el archivo mediante el ID

	fread ( &dato, sizeof (struct data_t), 1, fp );
	while ( !feof (fp) ){
		if ( dato.cl == pass && ( dato.tipo & (4<<1) ) ){ // Condiciones de apilado

			aux = malloc (sizeof (struct stack_t));
			if (aux == NULL){
			printf("\n\n***No hay memoria disponible\n");
			system("pause");
			return NULL;
			}
			// Guardo los datos solicitados en el enunciado
		    aux->ubi = ubicacion;
		    aux->password = dato.cl;
		// Apilo el registro

		    if ( local == NULL )       // Si es el primero elemento
		    	aux -> lazo = NULL;
		    else                       // Desplazo la pila
		    	aux -> lazo = local;

		    fclose(fp);
		    return aux;     // Retorno el ultimo elemento de la pila
		}
		fread (&dato, sizeof(struct data_t), 1, fp);
		ubicacion ++;
	}

	// Se recorrio tod el archivo por lo que el puntero se encuentra al final del mismo

	printf("***\n\nRegistro no encontrado\n***");
	system ("pause");
	fseek ( fp, (-1L) * sizeof (struct data_t), 1);
	fwrite (&dato, sizeof (struct data_t), 1, fp);

	fclose(fp);

	return local; // Ultimo elemento
}
