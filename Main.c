#include <stdio.h>
#include <string.h>
#define puntf  -1

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
void men_ent(FILE *arch);
void men_atri(FILE *arch);
void men_dat(FILE *arch);
//Funciones de entidades
void agrega_enti(FILE *arch,char nom[]);
void elimina_enti(FILE *arch,char nom[]);
void imprimir_enti(FILE *arch,char nom[]);
void modifica_enti(FILE *arch,char nom[]);
//Funciones de atributos
void agrega_atri(FILE *arch,char nom[]);
void elimina_atri(FILE *arch,char nom[]);
void imprimir_atri(FILE *arch,char nom[]);
void modifica_atri(FILE *arch,char nom[]);
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
	fwrite(puntf,sizeof(long),1,arch);
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
	long punt;
	FILE *arch;
	Enti entidad;
	char nom[50];
	printf("Dame el nombre del archivo que quieres abrir:");
	scanf("%s",nom);
	arch=fopen(nom,"r");
	if(arch!=NULL)
	{
		fscanf(arch,"%ld",&punt);
		if(punt==-1)
		{
			printf("No hay nada en el diccionario\n");
		}
		else
		{
			while(entidad.puntsig!=-1)
			{
				fscanf(arch,"%s%ld%ld%ld",entidad.nom,&entidad.pundata,&entidad.puntatri,&entidad.puntsig);
				printf("Nombre: %s\n",nom);
				if(entidad.pundata==-1)
				{
					printf("No tiene datos\n");
				}
				else
				{
					//Agrega datos
				}
				if(entidad.puntatri==-1)
				{
					printf("No tiene atributos\n");
				}
				else
				{
					//Agrega atributos
				}
				if(entidad.puntsig==-1)
				{
					printf("Termino la lista\n");
					return;
				}
				else
				{
					fseek(arch, entidad.puntsig, SEEK_CUR);
				}
			}
		}
	}
	else
	{
		printf("Error al abrir el archivo\n");
	}
	fclose(arch);
}


//Segundo menu de atributos
void menu2()
{
    FILE *arch;
	char nom[50];
	printf("Dame el nombre del diccionario que quieres usar:");
	scanf("%s",nom);
    arch=fopen(nom,"r");
    if(arch==NULL)
    {
        printf("Error al abrir el archivo\n\n");
        return;
    }
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
				men_ent(arch);
				break;
			case 2:
				men_atri(arch);
				break;
			case 3:
				men_dat(arch);
				break;
			case 4:
				break;
		}
	}
	fclose(arch);
}

//Menu de entidades
void men_ent(FILE *arch)
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
			agrega_enti(arch,nom);
			break;
		case 2:
			elimina_enti(arch,nom);
			break;
		case 3:
			imprimir_enti(arch,nom);
			break;
		case 4:
			modifica_enti(arch,nom);
			break;
		case 5:
			break;
		}
	}
}

//Menu de atributos
void men_atri(FILE *arch)
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
			agrega_atri(arch,nom);
			break;
		case 2:
			elimina_atri(arch,nom);
			break;
		case 3:
			imprimir_atri(arch,nom);
			break;
		case 4:
			modifica_atri(arch,nom);
			break;
		case 5:
			break;
		}
	}
}

//Menu de datos
void men_dat(FILE *arch)
{
	
}



//Funciones de entidades

//Agrega entidad
void agrega_enti(FILE *arch,char nom[])
{

	int op=1;
	Enti entidad;
	char nomb [50];
	printf("Dame el nombre de la entidad:");
	scanf("%s",nomb);
	while(entidad.puntsig!=-1)
	{
		fscanf(arch,"%s%ld%ld%ld",entidad.nom,&entidad.pundata,&entidad.puntatri,&entidad.puntsig);
		if(strcmp(nom,entidad.nom)<0)
		{
			fseek(arch, 0, SEEK_END);
			fwrite(nomb,50,1,arch);
			fwrite(puntf,sizeof(long),1,arch);
			fwrite(puntf,sizeof(long),1,arch);
			//aqui cambia el puntero en orden
		}
	}				
}
//Elimina entidad
void elimina_enti(FILE *arch,char nom[])
{
	
}

//Imprime Enti
void imprimir_enti(FILE *arch,char nom[])
{
	
}

//modifica entidad
void modifica_enti(FILE *arch,char nom[])
{
	
}


//Funciones de atributos

//Agrega entidad
void agrega_atri(FILE *arch,char nom[])
{
	
}
//Elimina entidad
void elimina_atri(FILE *arch,char nom[])
{
	
}

//Imprime Enti
void imprimir_atri(FILE *arch,char nom[])
{
	
}

//modifica entidad
void modifica_atri(FILE *arch,char nom[])
{
	
}
