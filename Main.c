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
void cambnom_enti(FILE *arch,char nom[]);
void modifica_enti(FILE *arch,char nom[]);
//Funciones de atributos
void agrega_atri(FILE *arch,char atri[],char enti[]);
void elimina_atri(FILE *arch,char atri[],char enti[]);
void imprimir_atri(FILE *arch,char atri[],char enti[]);
void modifica_atri(FILE *arch,char atri[],char enti[]);
//Funciones de datos
void agrega_dato(FILE *arch,char enti[]);
void elimina_datos(FILE *arch,char enti[]);
void modifica_datos(FILE *arch,char enti[]);

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
	long punt,cab,caba,punta,pos,fin,fin1;
	FILE *arch;
	Enti entidad;
	Atri atrib;
	char nom[50];
	int val;
	float val1;
	char val2[120];
	long val3,puntdat;
	bool val4;
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
			if(entidad.pundata!=-1)
			{
				printf("Lista de datos:\n");
				fseek(arch,entidad.pundata,SEEK_SET);
				fin=entidad.pundata;
				fin1=fin;
				while(fin!=-1)
				{
					fseek(arch,entidad.puntatri,SEEK_SET);
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						if(atrib.tipo=='i')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val,sizeof(int),1,arch);
							printf("%d-",val);
							fin1=fin1+sizeof(int);
						}
						if(atrib.tipo=='f')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val1,sizeof(float),1,arch);
							printf("%.2f-",val1);
							fin1=fin1+sizeof(float);
						}
						if(atrib.tipo=='c')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val2,sizeof(val2),1,arch);
							printf("%s-",val2);
							fin1=fin1+sizeof(val2);
						}
						if(atrib.tipo=='l')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val3,sizeof(long),1,arch);
							printf("%ld-",val3);
							fin1=fin1+sizeof(long);
						}
						if(atrib.tipo=='b')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val4,sizeof(bool),1,arch);
							printf("%d-",val4);
							fin1=fin1+sizeof(bool);
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
						fseek(arch,atrib.puntsig,SEEK_SET);
					}
					fread(&fin,sizeof(long),1,arch);
					printf("%ld",fin);
					printf("\n");
					fin1=fin;
					fseek(arch,fin1,SEEK_SET);
				}
			}
			else
			{
				printf("No tiene datos\n");
			}
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
		printf("3. Cambiar nombre entidad\n");
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
			cambnom_enti(arch,nom);
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
	char nom[50];
	printf("Dame el nombre la entidad a usar:");
	scanf("%s",nom);
	int op=0;
	while(op!=4)
	{
		printf("1. Agregar dato\n");
		printf("2. Eliminar dato\n");
		printf("3. Modificar dato\n");
		printf("4. volver al menu\n");
		printf("Dame que opcion quieres:");
		scanf("%d",&op);
		
		switch(op)
		{
		case 1:
			agrega_dato(arch,nom);
			break;
		case 2:
			elimina_datos(arch,nom);
			break;
		case 3:
			modifica_datos(arch,nom);
			break;
		case 4:
			fclose(arch);
			main();
			break;
		}
	}
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
void cambnom_enti(FILE *arch,char nom[])
{
	int op=0;
	char vacio[50]="",nuev[50];
	Enti entidad,act;
	long val,valant=-1,pos,sig,cab;
	printf("Dame el nombre que le quieres cambiar a la entidad:");
	scanf("%s",nuev);
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
			fseek(arch,cab,SEEK_SET);
			fwrite(vacio,sizeof(vacio),1,arch);
			fseek(arch,cab,SEEK_SET);
			fwrite(nuev,sizeof(nuev),1,arch);
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
		printf("No esta la entidad que quieres modificar\n\n");
	}
}




//Funciones de atributos

//Agrega atributo
void agrega_atri(FILE *arch,char atri[],char enti[])
{
	int val,v=0;
	long cab,valant=-1,pos,ini,aux;
	Atri nueva,act;
	Enti entidad;
	memset(nueva.nom,'\0',sizeof(nueva.nom));
	strcat(nueva.nom,atri);
	printf("Dame el valor boleano 1 o 0:");
	scanf("%d",&val);
	if(val==1&&v==0)
	{
		v=1;
		nueva.prymary=true;
	}
	else
	{
		nueva.prymary=false;
	}
	printf("Dame el tipo:");
	scanf("%s",&nueva.tipo);
	printf("Dame el tamaño:");
	scanf("%d",&nueva.tam);
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
				if(entidad.pundata!=-1)
				{
					return;
				}
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
	int val,v=0;
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
	if(val==1&&v==0)
	{
		v=1;
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


//Funciones de datos
void agrega_dato(FILE *arch,char enti[])
{

//Variables para el primer caso 
	Atri aux3;
	int val,op;
	float val1;
	char val2[120]="";
	long val3;
	bool val4;
//
	long cab,valant=-1,pos,ini,aux,fin,fin1,constante=-1,cont;
	Atri atrib;
	Enti entidad;
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
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				if(entidad.pundata==-1)
				{
					fseek(arch,0,SEEK_END);
					fin=ftell(arch);
					ini=fin;
					fseek(arch,entidad.puntatri,SEEK_SET);
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						fseek(arch,0,SEEK_END);
						pos=ftell(arch);
						if(atrib.tipo=='i')
						{
							printf("Dame el valor entero:");
							scanf("%d",&val);
							fwrite(&val,sizeof(int),1,arch);
						}
						if(atrib.tipo=='f')
						{
							printf("Dame el valor flotante:");
							scanf("%f",&val1);
							fwrite(&val1,sizeof(float),1,arch);
						}
						if(atrib.tipo=='c')
						{
							printf("Dame el valor de cadena:");
							scanf("%s", val2);
							fwrite(val2,sizeof(val2),1,arch);
						}
						if(atrib.tipo=='l')
						{
							printf("Dame el valor long:");
							scanf("%ld",&val3);
							fwrite(&val3,sizeof(long),1,arch);
							
						}
						if(atrib.tipo=='b')
						{
							printf("Dame el valor booleano 1 o 0:");
							scanf("%d",&op);
							val4=(op==1);
							fwrite(&val4,sizeof(bool),1,arch);
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
						fseek(arch,atrib.puntsig,SEEK_SET);
					}
					fseek(arch,0,SEEK_END);
					pos=ftell(arch);
					fwrite(&constante,sizeof(long),1,arch);
					fseek(arch,cab+offsetof(Enti,pundata),SEEK_SET);
					fwrite(&ini,sizeof(long),1,arch);
					fflush(arch);
               		return;
				}
				else
				{
					valant=-1;
					aux=entidad.puntatri;
					fin=entidad.pundata;
					fin1=fin;
					//Va a buscar dato en orden
					while(fin!=-1)
					{
						fseek(arch,aux,SEEK_SET);
						while(fread(&atrib,sizeof(Atri),1,arch)==1)
						{
							fseek(arch,fin1,SEEK_SET);
							if(atrib.tipo=='i')
							{
								fin1=fin1+sizeof(int);
							}
							if(atrib.tipo=='f')
							{
								fin1=fin1+sizeof(float);
							}
							if(atrib.tipo=='c')
							{
								fin1=fin1+sizeof(val2);
							}
							if(atrib.tipo=='l')
							{
								fin1=fin1+sizeof(long);
							}
							if(atrib.tipo=='b')
							{
								fin1=fin1+sizeof(bool);
							}
							if(atrib.puntsig==-1)
							{
								break;
							}
							fseek(arch,atrib.puntsig,SEEK_SET);
						}
						fseek(arch,fin1,SEEK_SET);
						fin1=ftell(arch);
						cont=fin1;
						fread(&fin,sizeof(long),1,arch);
						fin1=fin;
					}
					//Pega el dato
					fseek(arch,0,SEEK_END);
					ini=ftell(arch);
					fseek(arch,entidad.puntatri,SEEK_SET);
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						fseek(arch,0,SEEK_END);
						pos=ftell(arch);
						if(atrib.tipo=='i')
						{
							printf("Dame el valor entero:");
							scanf("%d",&val);
							fwrite(&val,sizeof(int),1,arch);
						}
						if(atrib.tipo=='f')
						{
				
							printf("Dame el valor flotante:");
							scanf("%f",&val1);
							fwrite(&val1,sizeof(float),1,arch);
							
						}
						if(atrib.tipo=='c')
						{
							
							printf("Dame el valor entero:");
							scanf("%s", val2);
							fwrite(val2,sizeof(atrib.tam)+1,1,arch);
							
						}
						if(atrib.tipo=='l')
						{
							
							printf("Dame el valor long:");
							scanf("%ld",&val3);
							fwrite(&val3,sizeof(long),1,arch);
							
						}
						if(atrib.tipo=='b')
						{
							
							printf("Dame el valor booleano 1 o 0:");
							scanf("%d",&op);
							val4=(op==1);
							fwrite(&val4,sizeof(bool),1,arch);
							
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
						fseek(arch,atrib.puntsig,SEEK_SET);
					}
					fseek(arch,0,SEEK_END);
					fwrite(&constante,sizeof(long),1,arch);
					fseek(arch,cont,SEEK_SET);
					fwrite(&ini,sizeof(long),1,arch);
					fflush(arch);
               		return;
				}
			}
			cab=entidad.puntsig;
		}
		fflush(stdin);
}

void elimina_datos(FILE *arch,char enti[])
{
	//Variables para el primer caso 
	Atri aux3;
	int val,op,ta=0;
	float val1;
	char val2[120]="";
	long val3,prueb;
	long arr[200];
	bool val4;
//
	long cab,valant=-1,pos,ini,aux,fin,fin1,constante=-1,ops;
	Atri atrib;
	Enti entidad;
	fseek(arch, 0, SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("No hay entidades a la cual agregar atributos\n");
		return;
	}
	//Le da las opciones de los datos que puede eliminar
		while(cab!=-1)
		{	
			fseek(arch, cab, SEEK_SET);
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				valant=-1;
				aux=entidad.puntatri;
				fin=entidad.pundata;
				fin1=fin;
				//Va a buscar dato en orden
				while(fin!=-1)
				{
					printf("%d)",ta);
					fseek(arch,aux,SEEK_SET);
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						if(atrib.tipo=='i')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val,sizeof(int),1,arch);
							printf("%d-",val);
							fin1=fin1+sizeof(int);
						}
						if(atrib.tipo=='f')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val1,sizeof(float),1,arch);
							printf("%.2f-",val1);
							fin1=fin1+sizeof(float);
						}
						if(atrib.tipo=='c')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val2,sizeof(val2),1,arch);
							printf("%s-",val2);
							fin1=fin1+sizeof(val2);
						}
						if(atrib.tipo=='l')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val3,sizeof(long),1,arch);
							printf("%ld-",val3);
							fin1=fin1+sizeof(long);
						}
						if(atrib.tipo=='b')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val4,sizeof(bool),1,arch);
							printf("%d-",val4);
							fin1=fin1+sizeof(bool);
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
					fseek(arch,atrib.puntsig,SEEK_SET);
					}
					fseek(arch,fin1,SEEK_SET);
					fin1=ftell(arch);
					arr[ta]=fin1;
					fread(&fin,sizeof(long),1,arch);
					fin1=fin;
					ta++;
					printf("\n");
				}
				if(ta==0)
				{
					printf("No tiene datos para eliminar\n");
					return;
				}
				printf("Dame que elemento quieres eliminar:");
				scanf("%d",&op);	
				if(op==0&&ta==1)
				{
					fseek(arch,cab+offsetof(Enti,pundata),SEEK_SET);
					prueb=ftell(arch);
					fwrite(&constante,sizeof(long),1,arch);
					return;
				}
				else
				{
					fseek(arch,arr[op],SEEK_SET);
					fread(&ops,sizeof(long),1,arch);
					fseek(arch,arr[op-1],SEEK_SET);
					prueb=ftell(arch);
					fwrite(&ops,sizeof(long),1,arch);
					return;
				}
			}
			cab=entidad.puntsig;
		}
		printf("No se encontro\n");
}

void modifica_datos(FILE *arch,char enti[])
{
	//Variables para el primer caso 
	Atri aux3;
	int val,op,ta=0;
	float val1;
	char val2[120]="";
	long val3,prueb;
	long arr[200];
	bool val4;
//
	long cab,valant=-1,pos,ini,aux,fin,fin1,constante=-1;
	Atri atrib;
	Enti entidad;
	fseek(arch, 0, SEEK_SET);
	fread(&cab,sizeof(long),1,arch);
	if(cab==-1)
	{
		printf("No hay entidades a la cual agregar atributos\n");
		return;
	}
	//Le da las opciones de los datos que puede eliminar
		while(cab!=-1)
		{	
			fseek(arch, cab, SEEK_SET);
			fread(&entidad,sizeof(Enti),1,arch);
			if(strcmp(enti,entidad.nom)==0)
			{	
				valant=-1;
				aux=entidad.puntatri;
				fin=entidad.pundata;
				fin1=fin;
				//Va a buscar dato en orden
				while(fin!=-1)
				{
					printf("%d)",ta);
					fseek(arch,aux,SEEK_SET);
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						if(atrib.tipo=='i')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val,sizeof(int),1,arch);
							printf("%d-",val);
							fin1=fin1+sizeof(int);
						}
						if(atrib.tipo=='f')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val1,sizeof(float),1,arch);
							printf("%.2f-",val1);
							fin1=fin1+sizeof(float);
						}
						if(atrib.tipo=='c')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val2,sizeof(val2),1,arch);
							printf("%s-",val2);
							fin1=fin1+sizeof(val2);
						}
						if(atrib.tipo=='l')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val3,sizeof(long),1,arch);
							printf("%ld-",val3);
							fin1=fin1+sizeof(long);
						}
						if(atrib.tipo=='b')
						{
							fseek(arch,fin1,SEEK_SET);
							fread(&val4,sizeof(bool),1,arch);
							printf("%d-",val4);
							fin1=fin1+sizeof(bool);
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
					fseek(arch,atrib.puntsig,SEEK_SET);
					}
					fseek(arch,fin1,SEEK_SET);
					fin1=ftell(arch);
					arr[ta]=fin1;
					fread(&fin,sizeof(long),1,arch);
					fin1=fin;
					ta++;
					printf("\n");
				}
				printf("Dame que elemento quieres modificar:");
				scanf("%d",&op);	
				if(op==0)
				{
					fseek(arch,entidad.puntatri,SEEK_SET);
					prueb=entidad.pundata;
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						fseek(arch,prueb,SEEK_SET);
						pos=ftell(arch);
						if(atrib.tipo=='i')
						{
							printf("Dame el valor entero:");
							scanf("%d",&val);
							fwrite(&val,sizeof(int),1,arch);
							prueb=prueb+sizeof(int);
						}
						if(atrib.tipo=='f')
						{
							printf("Dame el valor flotante:");
							scanf("%f",&val1);
							fwrite(&val1,sizeof(float),1,arch);
							prueb=prueb+sizeof(float);
						}
						if(atrib.tipo=='c')
						{
							printf("Dame el valor cadena:");
							scanf("%s", val2);
							fwrite(val2,sizeof(val2),1,arch);
							prueb=prueb+sizeof(val2);
						}
						if(atrib.tipo=='l')
						{
							printf("Dame el valor long:");
							scanf("%ld",&val3);
							fwrite(&val3,sizeof(long),1,arch);
							prueb=prueb+sizeof(long);
						}
						if(atrib.tipo=='b')
						{
							printf("Dame el valor booleano 1 o 0:");
							scanf("%d",&op);
							val4=(op==1);
							fwrite(&val4,sizeof(bool),1,arch);
							prueb=prueb+sizeof(bool);
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
						fseek(arch,atrib.puntsig,SEEK_SET);
					}
					return;
				}
				else
				{
					fseek(arch,arr[op-1],SEEK_SET);
					fread(&prueb,sizeof(long),1,arch);
					fseek(arch,entidad.puntatri,SEEK_SET);
					while(fread(&atrib,sizeof(Atri),1,arch)==1)
					{
						fseek(arch,prueb,SEEK_SET);
						pos=ftell(arch);
						if(atrib.tipo=='i')
						{
							printf("Dame el valor entero:");
							scanf("%d",&val);
							fwrite(&val,sizeof(int),1,arch);
							prueb=prueb+sizeof(int);
						}
						if(atrib.tipo=='f')
						{
				
							printf("Dame el valor flotante:");
							scanf("%f",&val1);
							fwrite(&val1,sizeof(float),1,arch);
							prueb=prueb+sizeof(float);
						}
						if(atrib.tipo=='c')
						{
							
							printf("Dame el valor entero:");
							scanf("%s", val2);
							fwrite(val2,sizeof(val2),1,arch);
							prueb=prueb+sizeof(val2);
						}
						if(atrib.tipo=='l')
						{
							
							printf("Dame el valor long:");
							scanf("%ld",&val3);
							fwrite(&val3,sizeof(long),1,arch);
							prueb=prueb+sizeof(long);
						}
						if(atrib.tipo=='b')
						{
							printf("Dame el valor booleano 1 o 0:");
							scanf("%d",&op);
							val4=(op==1);
							fwrite(&val4,sizeof(bool),1,arch);
							prueb=prueb+sizeof(bool);
						}
						if(atrib.puntsig==-1)
						{
							break;
						}
						fseek(arch,atrib.puntsig,SEEK_SET);
					}
					return;
				}
			}
			cab=entidad.puntsig;
		}
		printf("No se encontro\n");
}