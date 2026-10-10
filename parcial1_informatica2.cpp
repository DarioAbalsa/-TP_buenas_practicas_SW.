#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
typedef struct Interseccion{
	char calle_1[51];
	char calle_2[51];
	int cant;
	Interseccion *next;
}Interseccion;

//Prototipo de funciones 
void menu();
Interseccion* agregarInterseccion(Interseccion *lista, int *cantidad);
void mostrarIntersecciones(Interseccion *lista, int cantidad);
void limpiarBuffer();
//Funcion principal

int main(int argc, char *argv[]) {
	FILE *fp;
	fp=fopen("lista_enlazadas.txt","w+");
	if(fp==NULL){
		fputs("error al abrir el archivo",stderr);
		exit(1);
	}
		
		
	int cantidad = 0;
	int opcion;
	Interseccion *inter =NULL;
	if (inter == NULL) {
		inter = (Interseccion *)malloc(sizeof(Interseccion));
	}
	
	do {
		menu();
		printf("Opcion: ");
		scanf("%d", &opcion);
		limpiarBuffer();
		switch(opcion){
		case 1:
			inter=agregarInterseccion(inter,&cantidad);
			break;
		case 2:
			mostrarIntersecciones(inter, cantidad);
			break;
			
		case 3:
			printf("Saliendo...\n");
			break;
			
		default:
			printf("\nOpcion invalida\n");
		}
		
	} while(opcion != 3);   // antes era 6
	return 0;
}


// funcion menu
void menu() {
	printf("\n=== INTERSECCIONES ===\n");
	printf("1. Ingresar Dato\n");
	printf("2. mostrar intersecciones\n");
	printf("3. Salir\n");
	//printf("4. Redimensionar tablero\n");
	//printf("5. Mostrar disparos realizados\n");
	//printf("6. Ver ranking de ganadores\n");   
	//printf("7. Salir\n");                        
}
void limpiarBuffer() {
	int c;
	while ((c = getchar()) != EOF && c != '\n');
	//fseek(stdin, 0, SEEK_END);
	//rewind(stdin);
	//fflush(stdin);
}

Interseccion* agregarInterseccion(Interseccion *lista, int *cantidad) {
	int nuevaCantidad = 0;
	char calle_1[51];
	char calle_2[51];
	//int cantidad = 0;
	int trafico;
	nuevaCantidad = *cantidad + 1;
	
	// realloc funciona como malloc la primera vez si 'lista' es NULL
Interseccion *temporal = (Interseccion *) realloc(lista, nuevaCantidad * sizeof(Interseccion));
	
	if (temporal == NULL) {
		printf("Error: No se pudo asignar memoria para el nueva Interseccion.\n");
		return lista; 	// Si falla, retornamos el valor viejo sin cambiar nada
	}
	
	// Si todo sali? bien, actualizamos nuestro puntero de trabajo (ahora hay una nueva zona de
	// memoria que contiene todos los anteriores, y espacio para uno mas).
	lista = temporal;
	
	// Ingreso de datos en la ?ltima posici?n creada (lo que dice cantidad, que todavia no cambia)
	printf("\nIngrese el nombre de la primera calle(hasta 50 caracteres): ");
	fgets(calle_1, 51, stdin);
	calle_1[strlen(calle_1)-1]='\0';
	strcpy(lista[*cantidad].calle_1, calle_1);
	limpiarBuffer();
	printf("\nIngrese el nombre de la segunda calle(hasta 50 caracteres): ");
	fgets(calle_2, 51, stdin);
	calle_2[strlen(calle_2)-1]='\0';
	strcpy(lista[*cantidad].calle_2, calle_2);
	do{
	printf("Ingrese el trafico entre 1 y 100: ");
	
	scanf("%d", &trafico);
	if(trafico>0 && trafico<100){
	limpiarBuffer();
	lista[*cantidad].cant = trafico;
	break;
	}
	}while(1);
	
	// Incrementamos la cantidad total de jugadores
	(*cantidad)++;
	printf("Interseccion agregada\n");
	
	// Devolvemos el nuevo puntero (podria ser el mismo si habia espacio a continuacion)
	return lista; 
}

// Listado de jugadores
void mostrarIntersecciones(Interseccion *lista, int cantidad) {
	if (cantidad == 0 || lista == NULL) {
		printf("\nLa lista esta vacia.\n");
		return;
	}
	
	printf("\n=== LISTA DE ACTUAL ===\n");
	printf("Trafico   | Calle 1       |     calle 2  \n");
	printf("-----------------------------------------\n");
	for (int i = 0; i < cantidad; i++) {
		printf("%d | %s | %s\n", lista[i].cant, lista[i].calle_1,lista[i].calle_2);
	}
}

