#include <stdio.h>
#include <string.h>
#include <stddef.h>
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
	long puntf=-1;
	FILE *arch;
	char nom[50];
	printf("Dame el nombre del nuevo diccionario:");
	scanf("%s",nom);
	arch=fopen(nom,"w");
	if(arch!=NULL)
	{
	fwrite(&puntf,sizeof(long),1,arch);
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
	long punt,cab;
	FILE *arch;
	Enti entidad;
	char nom[50];
	printf("Dame el nombre del archivo que quieres abrir:");
	scanf("%s",nom);
	arch=fopen(nom,"r");
	fseek(arch,0,SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	printf("%ld\n",cab);
	if(cab==-1)
	{
		printf("No hay nada en el diccionario\n");
		return;
	}
	else
	{
		fseek(arch,sizeof(long),SEEK_SET);
		while(fread(&entidad,sizeof(Enti),1,arch)==1)
		{
			printf("La entidad: %s %ld %ld %ld\n",entidad.nom,entidad.pundata,entidad.puntatri,entidad.puntsig);
			fseek(arch,0,entidad.puntsig);

			//Agregar imprimir atributos y datos con while

			if(entidad.puntsig==-1)
			{
				break;
			}
		}
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
    arch=fopen(nom,"r+");
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
	long puntf=-1,val,valant,pos;
	Enti entidad,nueva;
	strcpy(nueva.nom,nom);
	nueva.pundata=-1;
	nueva.puntatri=-1;
	nueva.puntsig=-1;
	fseek(arch, 0, SEEK_SET);
	fread(&val,sizeof(long),1,arch);
	if(val==-1)
	{
		fseek(arch, 0, SEEK_END);
		pos=ftell(arch);
		fwrite(&nueva,sizeof(Enti),1,arch);
		fseek(arch, 0, SEEK_SET);
		fwrite(&pos,sizeof(long),1,arch);
		return;
	}
	else
	{
		valant=-1;
		while(val!=-1)
		{	
			fseek(arch, sizeof(long), SEEK_SET); 
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(nom,entidad.nom)<0)
			{	
				fseek(arch, 0, SEEK_END);
				pos=ftell(arch);
				nueva.puntsig=val;
				fwrite(&nueva,sizeof(Enti),1,arch);
                if(valant==-1)
				{	
					fseek(arch,0, SEEK_SET);
					fwrite(&pos,sizeof(long),1,arch);
				}
				else
				{
					fseek(arch, valant + offsetof(Enti, puntsig), SEEK_SET);
               		fwrite(&pos,sizeof(long),1,arch);
				}
                return;
			}
			valant=val;
			val=entidad.puntsig;
		}
	}	
	fseek(arch,0,SEEK_END);	
	pos=ftell(arch);
	fwrite(&nueva,sizeof(Enti),1,arch);
	if(valant!=-1)
	{
	fseek(arch,valant+offsetof(Enti,puntsig),SEEK_SET);  		
	fwrite(&pos,sizeof(long),1,arch);
	}
}
//Elimina entidad
void elimina_enti(FILE *arch,char nom[])
{
	int op=0;
	Enti entidad,act;
	long puntf=-1,val,valant,pos;
	fseek(arch, sizeof(long), SEEK_SET);
	while(fread(&entidad,sizeof(Enti),1,arch)==1&&strcmp(entidad.nom,nom)!=0)
	{
		if(strcmp(entidad.nom,nom)==0)
		{
			val = ftell(arch-sizeof(Enti)-sizeof(Enti));
			op=1;
			fscanf(arch,"%50s%ld%ld",act.nom,&act.pundata,&act.puntatri);
			fwrite(&entidad.puntsig,sizeof(long),1,arch);
		}
	}
	if(op==0)
	{
		printf("No esta la entidad que quieres eliminar\n\n");
	}
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

//Agrega atributo
void agrega_atri(FILE *arch,char nom[])
{
	
}
//Elimina atributo
void elimina_atri(FILE *arch,char nom[])
{
	
}

//Imprime atributo
void imprimir_atri(FILE *arch,char nom[])
{
	
}

//modifica atributo
void modifica_atri(FILE *arch,char nom[])
{
	
}
