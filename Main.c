#include <stdio.h>


//Estructuras 
typedef struct
{
	char nom[50];
	long pundata;
	long puntatri;
	long puntsig;
}Enti;
//Funciones principales
void agrega_nuevo();
void imprimir();
//Funciones de los menus
void menu2();
void men_ent();
void men_atri();
void men_dat();
//Funciones de entidades
void agrega_enti(char nom[]);
void elimina_enti(char nom[]);
void imprimir_enti(char nom[]);
void modifica_enti(char nom[]);
//Funciones de atributos
void agrega_atri(char nom[]);
void elimina_atri(char nom[]);
void imprimir_atri(char nom[]);
void modifica_atri(char nom[]);
//Funciones de datos
int main() 
{
	int op=0;
	while(op!=4)
	{
		printf("1. Agregar nuevo diccionario\n");
		printf("2. Usar diccionario\n");
		printf("3. imrpimir diccionario\n");
		printf("4. Salir\n");
		printf("Dame que opcion quieres:");
		scanf("%d",&op);
		printf("\n");
		
		switch(op)
		{
			case 1:
				agrega_nuevo();
				break;
			case 2:
				menu2();
				break;
			case 3:
				imprimir();
				break;
			case 4:
				return(1);
		}
		
	}
	return 0;
}

//Crea un nuevo diccionario inicializado
void agrega_nuevo()
{
	FILE *arch;
	char nom[50];
	printf("Dame el nombre del nuevo diccionario:");
	scanf("%s",nom);
	arch=fopen(nom,"w");
	if(arch!=NULL)
	{
	fwrite("-1",sizeof(long),1,arch);
	fclose(arch);
	}
	else
	{
		printf("Error al abrir el archivo\n");
	}
}

//Imprime un diccionario
void imprimir()
{
	FILE *arch;
	char nom[50];
	printf("Dame el nombre del archivo que quieres abrir:");
	scanf("%s",nom);
	arch=fopen(nom,"r");
	if(arch!=NULL)
	{
		
	}
	/*
	Imprime los datos 
	*/
	else
	{
		printf("Error al abrir el archivo\n");
	}
	fclose(arch);
}


//Segundo menu de atributos
void menu2()
{
	char nom[50];
	printf("Dame el nombre del diccionario que quieres usar:");
	scanf("%s",nom);
	int op=0;
	while(op!=4)
	{
		printf("1. Menu de entidades\n");
		printf("2. Menu de atributos\n");
		printf("3. Menu de datos\n");
		printf("4. volver al menu\n");
		printf("Dame que opcion quieres:");
		scanf("%d",&op);
	
		switch(op)
		{
			case 1:
				men_ent();
				break;
			case 2:
				men_atri();
				break;
			case 3:
				men_dat();
				break;
			case 4:
				break;
		}
	}
}

//Menu de entidades
void men_ent()
{
	char nom[50];
	printf("Dame el nombre la entidad a usar:");
	scanf("%s",nom);
	int op=0;
	while(op!=5)
	{
		printf("1. Agregar entidad\n");
		printf("2. Eliminar entidad\n");
		printf("3. Imprimir entidad\n");
		printf("4. Modificar entidad\n");
		printf("5. volver al menu\n");
		printf("Dame que opcion quieres:");
		scanf("%d",&op);
		
		switch(op)
		{
		case 1:
			agrega_enti(nom);
			break;
		case 2:
			elimina_enti(nom);
			break;
		case 3:
			imprimir_enti(nom);
			break;
		case 4:
			modifica_enti(nom);
			break;
		case 5:
			break;
		}
	}
}

//Menu de atributos
void men_atri()
{
	char nom[50];
	printf("Dame el nombre el atributo a usar:");
	scanf("%s",nom);
	int op=0;
	while(op!=5)
	{
		printf("1. Agregar atributo\n");
		printf("2. Eliminar atributo\n");
		printf("3. Imprimir atributo\n");
		printf("4. Modificar atributo\n");
		printf("5. volver al menu\n");
		printf("Dame que opcion quieres:");
		scanf("%d",&op);
		
		switch(op)
		{
		case 1:
			agrega_atri(nom);
			break;
		case 2:
			elimina_atri(nom);
			break;
		case 3:
			imprimir_atri(nom);
			break;
		case 4:
			modifica_atri(nom);
			break;
		case 5:
			break;
		}
	}
}

//Menu de datos
void men_dat()
{
	
}



//Funciones de entidades

//Agrega entidad
void agrega_enti(char nom[])
{
	
}
//Elimina entidad
void elimina_enti(char nom[])
{
	
}

//Imprime Enti
void imprimir_enti(char nom[])
{
	
}

//modifica entidad
void modifica_enti(char nom[])
{
	
}


//Funciones de atributos

//Agrega entidad
void agrega_atri(char nom[])
{
	
}
//Elimina entidad
void elimina_atri(char nom[])
{
	
}

//Imprime Enti
void imprimir_atri(char nom[])
{
	
}

//modifica entidad
void modifica_atri(char nom[])
{
	
}
