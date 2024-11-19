#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
//Estructuras tiene un relleno de 6 bytes
#pragma pack(push, 1)
typedef struct
{
	char nom[50];
	long pundata;
	long puntatri;
	long puntsig;
}Enti;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct
{
	char nom[50];
	bool prymary;
	char tipo;
	int tam;
	long puntsig;
}Atri;
#pragma pack(pop) 
//Funciones principales
void agrega_nuevo();
void imprimir();
//Funciones de los menus
void menu2();
void men_ent(FILE *arch);
void men_atri(FILE *arch, char nom1[]);
void men_dat(FILE *arch);
//Funciones de entidades
void agrega_enti(FILE *arch,char nom[]);
void elimina_enti(FILE *arch,char nom[]);
void imprimir_enti(FILE *arch,char nom[]);
void modifica_enti(FILE *arch,char nom[]);
//Funciones de atributos
void agrega_atri(FILE *arch,char atri[],char enti[]);
void elimina_atri(FILE *arch,char atri[],char enti[]);
void imprimir_atri(FILE *arch,char atri[],char enti[]);
void modifica_atri(FILE *arch,char atri[],char enti[]);
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
	long punt,cab,caba,punta;
	FILE *arch;
	Enti entidad;
	Atri atrib;
	char nom[50];
	printf("Dame el nombre del archivo que quieres abrir:");
	scanf("%s",nom);
	arch=fopen(nom,"r");
	if(arch==NULL)
	{
		printf("No se pudo abrir el archivo\n");
		return;
	}
	fseek(arch,0,SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	printf("%ld\n",cab);
	if(cab==-1)
	{
		printf("No hay nada en el diccionario\n");
		fclose(arch);
		return;
	}
	else
	{
		fseek(arch,cab,SEEK_SET);
		while(fread(&entidad,sizeof(Enti),1,arch)==1)
		{
			//Se encarga de atributos
			printf("La entidad: %s %ld %ld %ld\n",entidad.nom,entidad.pundata,entidad.puntatri,entidad.puntsig);
			fseek(arch,0,entidad.puntsig);
			if(entidad.puntatri!=-1)
			{
				printf("Lista de atributos:\n");
				fseek(arch,entidad.puntatri,SEEK_SET);
				while(fread(&atrib,sizeof(Atri),1,arch)==1)
				{
					printf("Atributo: %s %d %d  %c %ld\n",atrib.nom,atrib.prymary,atrib.tam,atrib.tipo,atrib.puntsig);
					fseek(arch,atrib.puntsig,SEEK_SET);
					if(atrib.puntsig==-1)
					{
						break;
					}
				}
			}
			else
			{
				printf("No tiene atributos\n");
			}
			//Agregar datos con while

			if(entidad.puntsig==-1)
			{
				break;
			}
			else
			{
				printf("\n");
				fseek(arch,entidad.puntsig,SEEK_SET);
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
	while(op!=3)
	{
		printf("1. Menu de entidades\n");
		printf("2. Menu de datos\n");
		printf("3. volver al menu\n");
		printf("Dame que opcion quieres:");
		scanf("%d",&op);
	
		switch(op)
		{
			case 1:
				men_ent(arch);
				break;
			case 2:
				men_dat(arch);
				break;
			case 3:
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
			men_atri(arch,nom);
			break;
		case 5:
			break;
		}
	}
}

//Menu de atributos
void men_atri(FILE *arch, char nom1[])
{
	char nom[50],atri[50]="";
	strcat(atri,nom1);
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
			agrega_atri(arch,nom,atri);
			break;
		case 2:
			elimina_atri(arch,nom,atri);
			break;
		case 3:
			imprimir_atri(arch,nom,atri);
			break;
		case 4:
			modifica_atri(arch,nom,atri);
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
		fflush(arch);
		return;
	}
	else
	{
		valant=-1;
		while(val!=-1)
		{	
			fseek(arch, val, SEEK_SET); 
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
				fflush(arch);
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
	fflush(arch);
	}
}
//Elimina entidad
void elimina_enti(FILE *arch,char nom[])
{
	int op=0;
	Enti entidad,act;
	long val,valant=-1,pos,sig,cab;
	fseek(arch,0,SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("El diccionario esta vacio\n");
	}
	fseek(arch,cab,SEEK_SET);
	while(fread(&entidad,sizeof(Enti),1,arch)==1)
	{
		if(strcmp(entidad.nom,nom)==0)
		{
			op=1;
			sig=entidad.puntsig;
			if(valant==-1)
			{
				fseek(arch,0, SEEK_SET);
				fwrite(&sig,sizeof(long),1,arch);
			}
			else
			{
			fseek(arch,valant+offsetof(Enti,puntsig),SEEK_SET);
			fwrite(&sig,sizeof(long),1,arch);
			}
			printf("Entidad eliminada\n");
			return;
		}
		if(entidad.puntsig==-1)
		{
			break;
		}
		valant=ftell(arch)-sizeof(Enti);
		fseek(arch,entidad.puntsig,SEEK_SET);
	}
	if(op==0)
	{
		printf("No esta la entidad que quieres eliminar\n\n");
	}
}

//Imprime Enti
void imprimir_enti(FILE *arch,char nom[])
{
	int op=0;
	Enti entidad,act;
	long val,valant=-1,pos,sig,cab;
	fseek(arch,0,SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("El diccionario esta vacio\n");
	}
	fseek(arch,cab,SEEK_SET);
	while(fread(&entidad,sizeof(Enti),1,arch)==1)
	{
		if(strcmp(entidad.nom,nom)==0)
		{
			op=1;
			printf("La entidad tiene: %s %ld %ld %ld\n",entidad.nom,entidad.pundata,entidad.puntatri,entidad.puntsig);
			return;
		}
		if(entidad.puntsig==-1)
		{
			break;
		}
		valant=ftell(arch)-sizeof(Enti);
		fseek(arch,entidad.puntsig,SEEK_SET);
	}
	if(op==0)
	{
		printf("No esta la entidad que quieres imprimir\n\n");
	}
}




//Funciones de atributos

//Agrega atributo
void agrega_atri(FILE *arch,char atri[],char enti[])
{
	long cab,valant=-1,pos,ini,aux;
	Atri nueva,act;
	Enti entidad;
	strcpy(nueva.nom,atri);
	nueva.prymary=false;
	nueva.tam=0;
	nueva.tipo='c';
	nueva.puntsig=-1;
	fseek(arch, 0, SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("No hay entidades a la cual agregar atributos\n");
		return;
	}
		while(cab!=-1)
		{	
			fseek(arch, cab, SEEK_SET);
			memset(entidad.nom,'\0',sizeof(entidad.nom));
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				if(entidad.puntatri==-1)
				{
					fseek(arch,0,SEEK_END);
					ini=ftell(arch);
					fwrite(&nueva,sizeof(Atri),1,arch);
					fseek(arch,cab+offsetof(Enti,puntatri),SEEK_SET);
					fwrite(&ini,sizeof(long),1,arch);
					fflush(arch);
               		return;
				}
				else
				{
					valant=-1;
					aux=entidad.puntatri;
					while(aux!=-1)
					{
						fseek(arch,aux,SEEK_SET);
						fread(&act,sizeof(Atri),1,arch);
						if(strcmp(act.nom,atri)==0)
						{
							printf("Ya existe este atributo\n");
							return;
						}
						if(strcmp(act.nom,atri)>0)
						{
							fseek(arch, 0, SEEK_END);
							pos=ftell(arch);
							nueva.puntsig=aux;
							fwrite(&nueva,sizeof(Atri),1,arch);
                			if(valant==-1)
							{	
								fseek(arch, cab + offsetof(Enti, puntatri), SEEK_SET);
               					fwrite(&pos,sizeof(long),1,arch);
							}
							else
							{
								fseek(arch, valant + offsetof(Atri, puntsig), SEEK_SET);
								fwrite(&pos,sizeof(long),1,arch);
							}
							fflush(arch);
               				return;
						}
						valant=aux;
						aux=act.puntsig;
					}
					fseek(arch,0,SEEK_END);
					pos=ftell(arch);
					fwrite(&nueva,sizeof(Atri),1,arch);
					fseek(arch, valant + offsetof(Atri, puntsig), SEEK_SET);
					fwrite(&pos,sizeof(long),1,arch);
					fflush(arch);
					return;
				}
			}
			cab=entidad.puntsig;
		}
}
//Elimina atributo
void elimina_atri(FILE *arch,char atri[],char enti[])
{
	int op=0;
	long cab,valant=-1,pos,ini,aux,sig;
	Atri act;
	Enti entidad;
	fseek(arch, 0, SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("No hay entidades a la cual eliminar atributos\n");
		return;
	}
		while(cab!=-1)
		{	
			fseek(arch, cab, SEEK_SET);
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				if(entidad.puntatri==-1)
				{
					printf("No hay atributo para eliminar\n");
               		return;
				}
				else
				{
					valant=-1;
					aux=entidad.puntatri;
					while(aux!=-1)
					{
						fseek(arch,aux,SEEK_SET);
						fread(&act,sizeof(Atri),1,arch);
						if(strcmp(act.nom,atri)==0)
						{
							op=1;
							sig=act.puntsig;
							if(valant==-1)
							{
								fseek(arch,cab+offsetof(Enti,puntatri),SEEK_SET);
								fwrite(&sig,sizeof(long),1,arch);
							}
							else
							{
								fseek(arch,valant+offsetof(Atri,puntsig),SEEK_SET);
								fwrite(&sig,sizeof(long),1,arch);
							}
							printf("Se logro eliminar el atributo\n");
							return;
						}
						valant=aux;
						aux=act.puntsig;
					}
					printf("No existe el atributo\n");
					return;
				}
			}
			cab=entidad.puntsig;
		}
	if(op==0)
	{
		printf("No esta el atributo que quieres eliminar\n");
	}
}

//Imprime atributo
void imprimir_atri(FILE *arch,char atri[],char enti[])
{
	long cab,valant=-1,pos,ini,aux;
	Atri nueva,act;
	Enti entidad;
	strcpy(nueva.nom,atri);
	nueva.prymary=false;
	nueva.tam=0;
	nueva.tipo='c';
	nueva.puntsig=-1;
	fseek(arch, 0, SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("No hay entidades a la cual agregar atributos\n");
		return;
	}
		while(cab!=-1)
		{	
			fseek(arch, cab, SEEK_SET);
			memset(entidad.nom,'\0',sizeof(entidad.nom));
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				if(entidad.puntatri==-1)
				{
					printf("No existe el atributo\n");
               		return;
				}
				else
				{
					valant=-1;
					aux=entidad.puntatri;
					while(aux!=-1)
					{
						fseek(arch,aux,SEEK_SET);
						fread(&act,sizeof(Atri),1,arch);
						if(strcmp(act.nom,atri)==0)
						{
							printf("Atributo: %s %d %d  %c %ld\n",act.nom,act.prymary,act.tam,act.tipo,act.puntsig);
							return;
						}
						valant=aux;
						aux=act.puntsig;
					}
					printf("No existe el atributo\n");
					return;
				}
			}
			cab=entidad.puntsig;
		}
}

//modifica atributo
void modifica_atri(FILE *arch,char atri[],char enti[])
{
	int val;
	long cab,valant=-1,pos,ini,aux,dire;
	Atri nueva,act,nuevoatri;
	Enti entidad;
	char vacio[50]="";
	strcpy(nueva.nom,atri);
	//Pido datos del nuevo atributo
	printf("Dame el nombre:");
	scanf("%s",nuevoatri.nom);
	fflush(stdin);
	printf("Dame el valor boleano 1 o 0:");
	scanf("%d",&val);
	if(val==1)
	{
		nuevoatri.prymary=true;
	}
	else
	{
		nuevoatri.prymary=false;
	}
	printf("Dame el tipo:");
	scanf("%s",&nuevoatri.tipo);
	printf("Dame el tamaño:");
	scanf("%d",&nuevoatri.tam);
	nuevoatri.puntsig=-1;
	nueva.prymary=false;
	nueva.tam=0;
	nueva.tipo='c';
	nueva.puntsig=-1;
	fseek(arch, 0, SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("No hay entidades a la cual agregar atributos\n");
		return;
	}
		while(cab!=-1)
		{	
			fseek(arch, cab, SEEK_SET);
			memset(entidad.nom,'\0',sizeof(entidad.nom));
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				if(entidad.puntatri==-1)
				{
					fseek(arch,0,SEEK_END);
					ini=ftell(arch);
					fwrite(&nuevoatri,sizeof(Atri),1,arch);
					fseek(arch,cab+offsetof(Enti,puntatri),SEEK_SET);
					fwrite(&ini,sizeof(long),1,arch);
					fflush(arch);
               		return;
				}
				else
				{
					valant=-1;
					aux=entidad.puntatri;
					while(aux!=-1)
					{
						fseek(arch,aux,SEEK_SET);
						fread(&act,sizeof(Atri),1,arch);
						if(strcmp(act.nom,atri)==0)
						{
							nuevoatri.puntsig=act.puntsig;
							fseek(arch,aux,SEEK_SET);
							fwrite(vacio,sizeof(vacio),1,arch);
							fseek(arch,aux,SEEK_SET);
							fwrite(&nuevoatri,sizeof(Atri),1,arch);
							return;
						}
						valant=aux;
						aux=act.puntsig;
					}
					return;
				}
			}
			cab=entidad.puntsig;
		}
}
