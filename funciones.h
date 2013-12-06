#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Usuario
{
	char Nombre[50];
	char Calle[30];
	char Password[20];
	long Tarjeta;
	int Administrador;
	int ID;
	int Bicicleta;
	struct Usuario* Siguiente;
	struct Usuario* Anterior;
} Tipo_Usuario;

typedef struct Bicicleta
{
	int ID;
	int ID_estacion;
	int Rentas;
	long Timestamp;
	struct Bicicleta* Siguiente;
	struct Bicicleta* Anterior;
} Tipo_Bicicleta;

typedef struct Estacion
{
	char Nombre[50];
	char Calle[30];
	char Ciudad[30];
	int ID_estacion;
	int CP;
	int Lugares_disponibles;
	int Bicicletas[10];
	struct Estacion* Siguiente;
	struct Estacion* Anterior;
} Tipo_Estacion;

void Logo();
void Menu_usuario(Tipo_Usuario *Usuario,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici);
void Menu_administrador(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu);
Tipo_Usuario *Carga_memoria_usuarios();
Tipo_Estacion *Carga_memoria_estacion();
Tipo_Bicicleta *Carga_memoria_bicicleta();
void Acceso(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici);
void Rentar(Tipo_Usuario *Usuario,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici);
void Estacionar(Tipo_Usuario *Usuario,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici);
void Menu_estado(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu);
void Estado_estacion(int ID_usu);
void Estado_general(int ID_usu);
void Timestamp(int Quien, int Que);
void Reasignar(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu);
void Menu_crear_usuario(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu);
void Alta_usuario(Tipo_Usuario *Tat, int ID_usu);
void Baja_usuario(Tipo_Usuario *Tat, int ID_usu);
void Menu_bicicleta(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu);
void Alta_bicicleta(Tipo_Bicicleta *Bici,Tipo_Estacion *Estacion, int ID_usu);
void Baja_bicicleta(Tipo_Bicicleta *Bici,Tipo_Estacion *Estacion, int ID_usu);
void Usuarios();
void Ayuda();
void Creditos();
void Menu_estacion(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu);
void Alta_estacion(Tipo_Estacion *Estacion, int ID_usu);
void Baja_estacion(Tipo_Estacion *Estacion, int ID_usu);

/*Funciones*/

Tipo_Usuario *Carga_memoria_usuarios()
{
	char Nombre[50], Calle[30], Password[20];
	int Bicicleta, Administrador, ID;
	long Tarjeta;
	Tipo_Usuario *Temp,*Primero=NULL, *Tat;
	FILE *Archivo;
	if(fopen("Usuarios.txt","rt")==NULL)
	{/*Si el archivo Usuarios.txt no existe crea uno con ID: 1 Password: 1*/
		Archivo=fopen("Usuarios.txt","at");
		fprintf(Archivo,"1 4999999999999999 0 1\n");
		fprintf(Archivo,"Admin\n",Temp->Nombre);
		fprintf(Archivo,"Calle Admin\n",Temp->Calle);
		fprintf(Archivo,"1\n",Temp->Password);
		fclose(Archivo);
	}
	Archivo = fopen("Usuarios.txt","rt");
	do
	{/*se lee el archivo. Se crea una estructura dinamica.*/
		fscanf(Archivo,"%d %ld %d %d\n",&ID,&Tarjeta,&Bicicleta,&Administrador);
		fgets(Nombre,50,Archivo);
		fgets(Calle,30,Archivo);
		fgets(Password,20,Archivo);
		Temp=(Tipo_Usuario *)malloc(sizeof(Tipo_Usuario));
		if(Primero==NULL)
		{
			strcpy(Temp->Nombre,Nombre);
			strcpy(Temp->Calle,Calle);
			strcpy(Temp->Password,Password);
			Temp->Tarjeta=Tarjeta;
			Temp->Bicicleta=Bicicleta;
			Temp->Administrador=Administrador;
			Temp->ID=ID;
			Primero=Temp;
			Tat=Temp;
			Temp->Siguiente=NULL;
			Temp->Anterior=NULL;
		}
		else
		{
			strcpy(Temp->Nombre,Nombre);
			strcpy(Temp->Calle,Calle);
			strcpy(Temp->Password,Password);
			Temp->Tarjeta=Tarjeta;
			Temp->Bicicleta=Bicicleta;
			Temp->Administrador=Administrador;
			Temp->ID=ID;
			Temp->Anterior=Tat;
			Temp->Siguiente=NULL;
			Tat->Siguiente=Temp;
			Tat=Temp;
		}
	}while(fscanf(Archivo,"%d %ld %d %d\n",&ID,&Tarjeta,&Bicicleta,&Administrador)==4);
	fclose(Archivo);
	return Tat;
}
Tipo_Bicicleta *Carga_memoria_bicicleta()
{
	Tipo_Bicicleta *Tat, *Primero=NULL, *Temp;
	FILE *Archivo;
	if(fopen("Bicicletas.dat","r+b")==NULL)
	{/*Si el archivo Bicicletas.dat no existe crea uno en blanco*/
		Archivo=fopen("Bicicletas.dat","w+b");
		fclose(Archivo);
	}
	Archivo = fopen("Bicicletas.dat","r+b");
	Temp=(Tipo_Bicicleta *)malloc(sizeof(Tipo_Bicicleta));
	while(fread(Temp,sizeof(Tipo_Bicicleta),1,Archivo)==1)
	{/*se lee el archivo. Se crea una estructura dinamica.*/
		if(Primero==NULL)
		{
			Primero=Temp;
			Tat=Temp;
			Temp->Siguiente=NULL;
			Temp->Anterior=NULL;
		}
		else
		{
			Temp->Anterior=Tat;
			Temp->Siguiente=NULL;
			Tat->Siguiente=Temp;
			Tat=Temp;
		}
	Temp=(Tipo_Bicicleta *)malloc(sizeof(Tipo_Bicicleta));		
	}
	fclose(Archivo);
	return Tat;
}
Tipo_Estacion *Carga_memoria_estacion()
{
	int ID_estacion, CP, Lugares_disponibles,i,Bicicletas[10],NO;
	char Nombre[50], Calle[30], Ciudad[30],Ignorar;

	Tipo_Estacion *Temp,*Primero=NULL, *Tat;
	FILE *Archivo;
	if(fopen("Estaciones.txt","rt")==NULL)
	{/*Si el archivo Estaciones.txt no existe crea uno en blanco*/
		Archivo=fopen("Estaciones.txt","wt");
		fclose(Archivo);
	}
	Archivo = fopen("Estaciones.txt","rt");
	while((fscanf(Archivo,"%d %d %d\n",&ID_estacion,&Lugares_disponibles,&CP))==3)
	{/*se lee el archivo. Se crea una estructura dinamica.*/
		for(i=0;i<10;i++)
		{
			__fpurge(stdin);
			fscanf(Archivo,"-%d",&Bicicletas[i]);
		}
		fscanf(Archivo,"\n",&Ignorar);
		fgets(Nombre,50,Archivo);
		fgets(Calle,30,Archivo);
		fgets(Ciudad,20,Archivo);
		Temp=(Tipo_Estacion *)malloc(sizeof(Tipo_Estacion));
		if(Primero==NULL)
		{
			strcpy(Temp->Nombre,Nombre);
			strcpy(Temp->Calle,Calle);
			strcpy(Temp->Ciudad,Ciudad);
			Temp->ID_estacion=ID_estacion;
			Temp->CP=CP;
			Temp->Lugares_disponibles=Lugares_disponibles;
			for(i=0;i<10;i++)
			{
				Temp->Bicicletas[i]=Bicicletas[i];
			}
			printf("\n");
			Primero=Temp;
			Tat=Temp;
			Temp->Siguiente=NULL;
			Temp->Anterior=NULL;
		}
		else
		{
			strcpy(Temp->Nombre,Nombre);
			strcpy(Temp->Calle,Calle);
			strcpy(Temp->Ciudad,Ciudad);
			Temp->ID_estacion=ID_estacion;
			Temp->CP=CP;
			Temp->Lugares_disponibles=Lugares_disponibles;
			for(i=0;i<10;i++)
			{
				Temp->Bicicletas[i]=Bicicletas[i];
			}
			printf("\n");
			Temp->Anterior=Tat;
			Temp->Siguiente=NULL;
			Tat->Siguiente=Temp;
			Tat=Temp;
		}
	}
	fclose(Archivo);
	return Tat;
}
void Logo()
{
printf("\n\n");
printf("\x1b[32m\t\t\tEEEEEEEEEEEEE	CCCCCCCCCCCCC	OOOOOOOOOOOOOO\x1b[0m	\x1b[31mBBBBBBBBBBB	IIIIIIIIIIIII	CCCCCCCCCCCCC	IIIIIIIIIIIII\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEEEEEEEEEE	CCCCCCCCC	OOOO      OOOO\x1b[0m	\x1b[31mBBB	   BBB	     III	CCCCCCCCC	     III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEE		CCCCCC		OOO	   OOO\x1b[0m	\x1b[31mBBB	    BBB      III	CCCCCC		     III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEE		CCCC		OO	    OO\x1b[0m	\x1b[31mBBB	    BBB	     III	CCCC                 III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEEEEEEEEEE	CCC		OO	    OO\x1b[0m	\x1b[31mBBB	   BBB       III	CCC                  III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEEEEEEEEEE	CCC		OO	    OO\x1b[0m	\x1b[31mBBB	 BBB         III	CCC                  III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEE		CCCC		OO	    OO\x1b[0m	\x1b[31mBBB	    BBB      III	CCCC                 III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEE		CCCCCC		OOO	   OOO\x1b[0m	\x1b[31mBBB	    BBB      III	CCCCCC               III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEEEEEEEEEE	CCCCCCCCC	OOOO	  OOOO\x1b[0m	\x1b[31mBBB	   BBB	     III	CCCCCCCCC            III\n\x1b[0m");
printf("\x1b[32m\t\t\tEEEEEEEEEEEEE	CCCCCCCCCCCCC	OOOOOOOOOOOOOO\x1b[0m	\x1b[31mBBBBBBBBBBB 	IIIIIIIIIIIII	CCCCCCCCCCCCC	IIIIIIIIIIIII\n\n\n\x1b[0m");
}

void Menu_usuario(Tipo_Usuario *Usuario,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici)
{
	int Opcion;
	printf("\n\t\t\t\t\t\tPor favor elige la opción que deseas:\n\n");
	if (Usuario->Bicicleta==0)
	{/*dependiendo de si el ususario tiene bicicletas o no, te manda a cada caso*/
		printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m	 Rentar bicicleta\n");
	}
	else
	{
		printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m	 Estacionar bicicleta\n");
	}
	printf("\t\t\t\t\t\t\x1b[31m99)\x1b[0m	 Salir\n");
	printf("\n\t\t\t\t\t\tQue opcion quiere:");
	while(scanf("%d",&Opcion) == 0)
	{
		printf("\n\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	switch(Opcion)
	{/*dependiendo de si el ususario tiene bicicletas o no, te manda a cada caso*/
		case 1:	if (Usuario->Bicicleta==0)
			{
				system("clear");
				Logo();
				Rentar(Usuario,Estacion,Bici);
			}
			else
			{
				system("clear");
				Logo();
				Estacionar(Usuario,Estacion,Bici);
			}
			break;
		case 99:system("clear");
			break;
		default:system("clear");
			Logo();
			printf ("\n\n\t\t\t\t\t\tEsa opción no es válida. Intenta nuevamente.\n\n");
			Menu_usuario(Usuario,Estacion,Bici);
			break;
	}
	
}

void Menu_administrador(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu)
{
	int Opcion;
	printf("\n\t\t\t\t\t\tPor favor elige la opción que deseas: \n");
	printf("\n\n\t\t\t\t\t\tLas opciones son:\n");
	printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m Alta/Baja de una nueva bici-estación\n");
	printf("\t\t\t\t\t\t\x1b[31m2)\x1b[0m Alta/Baja de bicicletas en una bici-estación\n");
	printf("\t\t\t\t\t\t\x1b[31m3)\x1b[0m Reasignar bicicletas entre bici-estaciones\n");
	printf("\t\t\t\t\t\t\x1b[31m4)\x1b[0m Mostrar el estatus de una o todas las bici-estaciones\n");
	printf("\t\t\t\t\t\t\x1b[31m5)\x1b[0m Alta/Baja de un usuario del servicio\n");
	printf("\n\t\t\t\t\t\t\x1b[31m99)\x1b[0m Salir\n");
	printf("\n\t\t\t\t\t\tQue opcion quiere:");
	while(scanf("%d",&Opcion) == 0)
	{
		printf("Por favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	switch(Opcion)
	{
		case 1:	system("clear");
			Logo();
			Menu_estacion(Tat,Estacion,Bici,ID_usu);
			Menu_administrador(Tat,Estacion,Bici,ID_usu);
			break;
		case 2:	system("clear");
			Logo();
			Menu_bicicleta(Tat,Estacion,Bici,ID_usu);
			Menu_administrador(Tat,Estacion,Bici,ID_usu);
			break;
		case 3:	system("clear");
			Logo();
			if(Estacion==NULL || Estacion->Anterior==NULL || Bici==NULL)
			{/*se valida que existan estaciones y/o bicicletas dadas de alta*/
				printf("\t\t\t\t\t\t\033[1mNo se podra hacer el reacomodo:\x1b[0m\n\n\t\t\t\t\t\t    \033[1m¤\x1b[0m Ya que no existen 2 o mas estaciones.\n");
				printf("\t\t\t\t\t\t    \033[1m¤\x1b[0m O no existen bicicletas.\n");
			}
			else
			{
				Reasignar(Tat,Estacion,Bici,ID_usu);
			}
			Estacion=Carga_memoria_estacion();
			Menu_administrador(Tat,Estacion,Bici,ID_usu);
			break;
		case 4:	system("clear");
			Logo();
			Menu_estado(Tat,Estacion,Bici,ID_usu);
			Menu_administrador(Tat,Estacion,Bici,ID_usu);
			break;
		case 5:	system("clear");
			Logo();
			Menu_crear_usuario(Tat,Estacion,Bici,ID_usu);
			Menu_administrador(Tat,Estacion,Bici,ID_usu);
			break;
		case 99:system("clear");
			break;
		default:system("clear");
			Logo();
			printf ("\t\t\t\t\t\tEsa opción no es válida. Intenta nuevamente.\n\n");
			Menu_administrador(Tat,Estacion,Bici,ID_usu);
			break;
	}
}

void Acceso(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici)
{
	char Nombre[50], Password[20];
	int ID;
	Tipo_Usuario *Temp;
	Temp=Tat;
	__fpurge(stdin);
	printf("\t\t\t\t\t\t\t\tCual es su ID:\t");
	while(scanf("%d",&ID) == 0)
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t\n");
		printf("\t\t\t\t\t\t\t\tCual es su ID:\t");
		__fpurge(stdin);
	}
	printf("\t\t\t\t\t\t\t\tContraseña:\t");
	__fpurge(stdin);
	fgets(Password,19,stdin);
	while(Temp->ID!=ID && strcmp(Temp->Password,Password)!=0 && Temp->Anterior!=NULL)
	{
		__fpurge(stdin);
		Temp=Temp->Anterior;
	}
	if(Temp->ID==ID && strcmp(Temp->Password,Password)==0)
	{ 
		if(Temp->Administrador==1)
		{
			system("clear");
			Logo();
			/*Llama al menu administrador. Y manda las estructuras en su ultima posicion. Y el ID del usuario que hizo login.*/
			Timestamp(ID,401);
			Menu_administrador(Tat,Estacion,Bici,ID);
			Timestamp(ID,402);
		}
		if(Temp->Administrador==0)
		{
			system("clear");
			Logo();
			/*Llama al menu usuario y le manda la estructura del usuario actual*/
			Menu_usuario(Temp,Estacion,Bici);
		}
	}
	else
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor revise su usuario y/o contraseña\n\n");
		Acceso(Tat,Estacion,Bici);
	}
}

void Rentar(Tipo_Usuario *Usuario,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici)
{
	FILE *Archivo;
	int ID_Estacion=999,ID_Bici,i,Encontro_ID=0,Bicicletas[10];
	Tipo_Estacion *Temp;
	Tipo_Bicicleta *Temp2;
	Temp=Estacion;
	Temp2=Bici;
	while(Temp->ID_estacion!=ID_Estacion)
	{/*Pide la estacion donde te encuentras*/
		if(Temp->Siguiente==NULL)
		{
			printf("\n\t\t\t\t\t\tIntroduce el ID de la estación dónde te encuentras\n");
			printf("\t\t\t\t\t\t");
			__fpurge(stdin);
			while(scanf("%d",&ID_Estacion) == 0)
			{/*Valida que la respuesta sea un numero*/
				printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
				__fpurge(stdin);
			}
		}
		if(Temp->ID_estacion!=ID_Estacion)
		{/*Si la estacion actual no es la correcta, recorre.*/
			Temp=Temp->Anterior;
		}
		if(Temp==NULL)
		{/*Regresa Temp la estacion de inicio (que es la ultima) para evitar el segmentation fault y volver a pedir una estacion. */
			Temp=Estacion;
		}
	}
	if ((Temp->Lugares_disponibles)<10)
	{/*Comprueba que la estacion donde se encuentra el usuario tenga lugares bicicletas para renta.*/
		Temp->Lugares_disponibles=Temp->Lugares_disponibles+1;
		/*Quita una bicicleta, o sea, agrega un lugar disponible*/
		for (i=0;i<10;i++)
		{
			printf("Bicicletas[1] %d\n",Bicicletas[1]);
			if (Temp->Bicicletas[i]!=0 && Encontro_ID==0)
			{
				printf("Bicicletas[i]: %d\n",Temp->Bicicletas[i]);
				ID_Bici=Temp->Bicicletas[i];
				Temp->Bicicletas[i]=0;
				Encontro_ID=1;
			}
		}
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPuedes sacar la bicicleta con el ID \x1b[31m%d\x1b[0m \n",ID_Bici);
		printf("\n\t\t\t\t\t\tGracias por usar el sistema. Tenga buen viaje.\n\n\n");
		while(Temp2->ID!=ID_Bici)
		{
			Temp2=Temp2->Anterior;
		}
		Bici->Timestamp = time(NULL);
		Bici->Rentas=Bici->Rentas+1;
		Usuario->Bicicleta=ID_Bici;

		/*Empieza para guardar en archivos los cambios*/

		/*Guarda bicicletas*/
		while(Bici->Anterior!=NULL)
		{/*Pone a Bici en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Bici=Bici->Anterior;
		}
		Archivo=fopen("Bicicletas.dat","w+b");
		do
		{
			fwrite(Bici,sizeof(Tipo_Bicicleta),1,Archivo);
			Bici=Bici->Siguiente;
		}while(Bici!=NULL);
		fclose(Archivo);

		/*Guarda Estacion*/
		while(Temp->Anterior!=NULL)
		{/*Pone a Temp en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Temp=Temp->Anterior;
		}
		Archivo=fopen("Estaciones.txt","wt");
		do
		{
			fprintf(Archivo,"%d %d %d\n",Temp->ID_estacion,Temp->Lugares_disponibles,Temp->CP);
			for (i=0;i<10;i++)
			{
				fprintf(Archivo,"-%d",Temp->Bicicletas[i]);
			}
			fprintf(Archivo,"\n");
			fprintf(Archivo,"%s",Temp->Nombre);
			fprintf(Archivo,"%s",Temp->Calle);
			fprintf(Archivo,"%s",Temp->Ciudad);
			Temp=Temp->Siguiente;
		}while(Temp!=NULL);
		fclose(Archivo);

		/*Guarda Usuarios*/
		while(Usuario->Anterior!=NULL)
		{/*Pone a Usuario en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Usuario=Usuario->Anterior;
		}
		Archivo=fopen("Usuarios.txt","wt");
		do
		{
			fprintf(Archivo,"%d %ld %d %d\n",Usuario->ID,Usuario->Tarjeta,Usuario->Bicicleta,Usuario->Administrador);
			fprintf(Archivo,"%s",Usuario->Nombre);
			fprintf(Archivo,"%s",Usuario->Calle);
			fprintf(Archivo,"%s",Usuario->Password);
			Usuario=Usuario->Siguiente;
		}while(Usuario!=NULL);
		fclose(Archivo);
	}
	else
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tEsta estacion no cuenta con bicicletas para rentar. \n\t\t\t\t\t\tPor favor ve a otra estacion.\n\n\n");
	}
}

void Estacionar(Tipo_Usuario *Usuario,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici)
{
	FILE *Archivo;
	int ID_Estacion,ID_Bici,i,Encontro_ID=0,Bicicletas[10],Continua=0;
	Tipo_Estacion *Temp;
	Temp=Estacion;
	printf("\n\t\t\t\t\t\tIntroduce el ID de la estación dónde te encuentras\n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	while(Temp->ID_estacion!=ID_Estacion)
	{/*Pide la estacion donde te encuentras*/
		if(Temp->Siguiente==NULL)
		{
			printf("\n\t\t\t\t\t\tIntroduce el ID de la estación dónde te encuentras\n");
			printf("\t\t\t\t\t\t");
			__fpurge(stdin);
			while(scanf("%d",&ID_Estacion) == 0)
			{/*Valida que la respuesta sea un numero*/
				printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
				__fpurge(stdin);
			}
		}
		if(Temp->ID_estacion!=ID_Estacion)
		{/*Si la estacion actual no es la correcta, recorre.*/
			Temp=Temp->Anterior;
		}
		if(Temp==NULL)
		{/*Regresa Temp la estacion de inicio (que es la ultima) para evitar el segmentation fault y volver a pedir una estacion. */
			Temp=Estacion;
		}
	}
	if ((Temp->Lugares_disponibles)>0)
	{
	/*Comprueba que la estacion tenga minimo un lugar disponible para estacionarse.*/
		ID_Bici=Usuario->Bicicleta;
		Temp->Lugares_disponibles=Temp->Lugares_disponibles-1;
		for (i=0;i<10;i++)
		{
			if (Temp->Bicicletas[i]==0 && Encontro_ID==0)
			{
				Temp->Bicicletas[i]=ID_Bici;
				Encontro_ID=1;
			}
		}
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tGracias por regresar la bicicleta con el ID \x1b[31m%d\x1b[0m \n",ID_Bici);
		printf("\n\t\t\t\t\t\tGracias por usar el sistema.\n\n\n");
		while(Bici->ID!=ID_Bici)
		{
			Bici=Bici->Anterior;
		}
		Bici->Timestamp = 0;
		Usuario->Bicicleta=0;

		/*Empieza para guardar en archivos los cambios*/

		/*Guarda bicicletas*/
		while(Bici->Anterior!=NULL)
		{/*Pone a Bici en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Bici=Bici->Anterior;
		}
		Archivo=fopen("Bicicletas.dat","w+b");
		do
		{
			fwrite(Bici,sizeof(Tipo_Bicicleta),1,Archivo);
			Bici=Bici->Siguiente;
		}while(Bici!=NULL);
		fclose(Archivo);

		/*Guarda Estacion*/
		while(Temp->Anterior!=NULL)
		{/*Pone a Temp en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Temp=Temp->Anterior;
		}
		Archivo=fopen("Estaciones.txt","wt");
		do
		{
			fprintf(Archivo,"%d %d %d\n",Temp->ID_estacion,Temp->Lugares_disponibles,Temp->CP);
			for (i=0;i<10;i++)
			{
				fprintf(Archivo,"-%d",Temp->Bicicletas[i]);
			}
			fprintf(Archivo,"\n");
			fprintf(Archivo,"%s",Temp->Nombre);
			fprintf(Archivo,"%s",Temp->Calle);
			fprintf(Archivo,"%s",Temp->Ciudad);
			Temp=Temp->Siguiente;
		}while(Temp!=NULL);
		fclose(Archivo);

		/*Guarda Usuarios*/
		while(Usuario->Anterior!=NULL)
		{/*Pone a Usuario en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Usuario=Usuario->Anterior;
		}
		Archivo=fopen("Usuarios.txt","wt");
		do
		{
			fprintf(Archivo,"%d %ld %d %d\n",Usuario->ID,Usuario->Tarjeta,Usuario->Bicicleta,Usuario->Administrador);
			fprintf(Archivo,"%s",Usuario->Nombre);
			fprintf(Archivo,"%s",Usuario->Calle);
			fprintf(Archivo,"%s",Usuario->Password);
			Usuario=Usuario->Siguiente;
		}while(Usuario!=NULL);
		fclose(Archivo);
	}
	else
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tEsta estacion no cuenta con lugares para estacionarse libres. \n\t\t\t\t\t\tPor favor ve a otra estacion.\n\n\n");
	}
}

void Menu_bicicleta(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu)
{
	int Opcion;
	printf("\n\t\t\t\t\t\tPor favor elige la opción que deseas: \n");
	printf("\n\t\t\t\t\t\tLas opciones son:\n\n");
	printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m Alta bicicleta\n");
	printf("\t\t\t\t\t\t\x1b[31m2)\x1b[0m Baja bicicleta\n");
	printf("\t\t\t\t\t\t\x1b[31m9)\x1b[0m Regresar\n");
	printf("\n\t\t\t\t\t\tQue opcion quiere:");
	while(scanf("%d",&Opcion) == 0)
	{
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	switch(Opcion)
	{
		case 1:	system("clear");
			Logo();
			if(Estacion==NULL )
			{
				printf("\t\t\t\tNo se puede dar de alta porque no existe ninguna estacion en el sistema.\n");
			}
			else
			{
				Alta_bicicleta(Bici,Estacion,ID_usu);
				Bici=Carga_memoria_bicicleta();
			}
			Menu_bicicleta(Tat,Estacion,Bici,ID_usu);
			break;
		case 2:	system("clear");
			Logo();
			if(Bici==NULL )
			{
				printf("\t\t\t\tNo se puede dar de baja porque no existe ninguna bicicleta en el sistema.\n");
			}
			else
			{
				Baja_bicicleta(Bici,Estacion,ID_usu);
				Bici=Carga_memoria_bicicleta();
			}
			Menu_bicicleta(Tat,Estacion,Bici,ID_usu);
			break;
		case 9: system("clear");
			Logo();
			break;
		default:system("clear");
			Logo();
			printf ("\n\t\t\t\t\t\tEsa opción no es válida. Intenta nuevamente.\n\n");
			Menu_bicicleta(Tat,Estacion,Bici,ID_usu);
			break;
	}
}
void Menu_estado(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu)
{
	int Opcion;
	printf("\n\t\t\t\t\t\tPor favor elige la opción que deseas:\n");
	printf("\n\t\t\t\t\t\tLas opciones son:\n\n");
	printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m Estado de una estacion\n");
	printf("\t\t\t\t\t\t\x1b[31m2)\x1b[0m Estado de todas las estaciones\n");
	printf("\t\t\t\t\t\t\x1b[31m9)\x1b[0m Regresar\n");
	printf("\n\t\t\t\t\t\tQue opcion quiere:");
	while(scanf("%d",&Opcion) == 0)
	{
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	switch(Opcion)
	{
		case 1:	system("clear");
			Estado_estacion(ID_usu);
			Menu_estado(Tat,Estacion,Bici,ID_usu);
			break;
		case 2:	system("clear");
			Estado_general(ID_usu);
			Menu_estado(Tat,Estacion,Bici,ID_usu);
			break;
		case 9: system("clear");
			Logo();
			break;
		default:system("clear");
			Logo();
			printf ("\n\t\t\t\t\t\tEsa opción no es válida. Intenta nuevamente.\n");
			Menu_estado(Tat,Estacion,Bici,ID_usu);
			break;
	}
}
void Estado_estacion(int ID_usu)
{
	FILE *Estaciones;
	int Estacion,ID_estacion,Disponibles,CP,Encontro,ID_estacion_2,Disponibles_2,CP_2,i,Bicicletas[10],Bicicletas2[10],Alguna=0;
	char Nombre[50],Calle[30],Ciudad[20],Nombre_2[50],Calle_2[30],Ciudad_2[20],Ignorar;
	Logo();
	do
	{/*se valida que la estacion exista*/

		printf("\n\t\t\t\t\t\tIntroduce el ID de la estación de la cual quiere ver su estado  ");
		__fpurge(stdin);
		while(scanf("%d",&Estacion) == 0)
		{
			printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
			__fpurge(stdin);
		}
		Estaciones=fopen("Estaciones.txt","rt");
		while ((fscanf(Estaciones,"%d %d %d\n",&ID_estacion,&Disponibles,&CP))==3) 
		{
			for(i=0;i<10;i++)
			{
				__fpurge(stdin);
				fscanf(Estaciones,"-%d",&Bicicletas[i]);
			}
			fscanf(Estaciones,"\n",&Ignorar);
			fgets(Nombre,50,Estaciones);
			fgets(Calle,30,Estaciones);
			fgets(Ciudad,20,Estaciones);
			if(ID_estacion==Estacion)
			{
				Encontro=1;
				Disponibles_2=Disponibles;
				CP_2=CP;
				strcpy(Nombre_2,Nombre);
				strcpy(Calle_2,Calle);
				strcpy(Ciudad_2,Ciudad);
				for(i=0;i<10;i++)
				{
					Bicicletas2[i]=Bicicletas[i];
				}
			}
		}
		if (Encontro==1)
		{
			system("clear");
			Logo();
			printf("\n\t\t\t\t\t\tLos datos de la estación con el ID %d son: \n ",Estacion);
			printf("\t\t\t\t\t\tNombre: %s \t\t\t\t\t\tTiene %d lugares disponibles.",Nombre_2,Disponibles_2);
			printf("\n\t\t\t\t\t\tLos ID de la(s) bicicleta(s) disponible(s) en esa estacion son: \n");
			printf("\t\t\t\t\t\t");
			for(i=0;i<10;i++)
			{
				if(Bicicletas2[i]!=0)
				{
					printf(" %d ",Bicicletas2[i]);
					Alguna=1;
				}
			}
			if (Alguna==0)
			{
				printf("\n\t\t\t\t\t\tNo existen bicicletas en esta estacion.");
			}
			printf("\n\t\t\t\t\t\tSu dirección es:\n \t\t\t\t\t\tCalle: %s \t\t\t\t\t\tCódigo Postal: %d \n \t\t\t\t\t\tCiudad: %s \n\n",Calle_2,CP_2,Ciudad_2);
		}
		else
		{
			printf("\n\t\t\t\t\t\tNo se encontró esa estación. Intenta nuevamente. \n");
		}
		fclose(Estaciones);
		Timestamp(ID_usu,502);
		printf("\t\t\t\t==============================================================================================\n\n");
	}while (Encontro==0);
}

void Estado_general(int ID_usu)
{
	FILE *Estaciones;
	int Estacion,ID_estacion,Disponibles,No,Bicicletas[10],i;
	char Nombre[50],NO[30],Ignorar;
	Logo();
	printf("\n\t\t\t\t\t\tEl estado general de las bici-estaciones es: \n\n");
	printf("\n\t\t\t\t\tID \t Lugares Disponibles \t Bicicletas en Renta \t\t Nombre\n\n");
	Estaciones=fopen("Estaciones.txt","rt");
	while ((fscanf(Estaciones,"%d %d %d\n",&ID_estacion,&Disponibles,&No))==3) 
	{
		for(i=0;i<10;i++)
		{
			__fpurge(stdin);
			fscanf(Estaciones,"-%d",&Bicicletas[i]);
		}
		fscanf(Estaciones,"\n",&Ignorar);
		fgets(Nombre,50,Estaciones);
		fgets(NO,30,Estaciones);
		fgets(NO,20,Estaciones);
		printf("\t\t\t\t\t%d \t\t %d  \t\t\t %d \t\t %s",ID_estacion,Disponibles,10-Disponibles,Nombre);
	}
	fclose(Estaciones);
	Timestamp(ID_usu,501);
	printf("\n\t\t\t\t==============================================================================================\n\n");
}

void Reasignar(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu)
{
	int ID, ID2, numbici, numbici2, mover, maximo,Continua=0,Continua2=0;
	char Respuesta;	
	Tipo_Estacion *Temp, *Temp2, *Temp3;
	FILE *Archivo;
	Temp=Estacion;
	Temp2=Estacion;
	Temp3=Estacion;
	do
	{
		printf("\n\t\t\t\t\t\tCual es el ID de la estacion de la que quiere mover las bicicletas:\n");
		printf("\t\t\t\t\t\t");
		while(scanf("%d",&ID) == 0)
		{
			printf("\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
			__fpurge(stdin);
		}
		while(Temp->ID_estacion!=ID && Continua ==0)
		{/*se busca y se valida. que exista la estacion*/
			__fpurge(stdin);
			Temp=Temp->Anterior;
			if(Temp==NULL)
			{
				system("clear");
				Logo();
				printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que la primera estacion no existe.\n");
				Continua=1;
				Reasignar(Tat,Estacion,Bici,ID_usu);
			}
		}
		if(Temp->Lugares_disponibles==10)
		{/*solo entraras aqui, si no existen bicicletas asignadas a esta estacion*/
			system("clear");
			Logo();
			printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que esta estacion no cuenta con bicicletas.\n");
			Reasignar(Tat,Estacion,Bici,ID_usu);
		}
		else
		{
			printf("\t\t\t\t\t\tEsta estacion cuenta con:\x1b[31m %d\x1b[0m bicicletas\n",10-Temp->Lugares_disponibles);
			numbici=10-Temp->Lugares_disponibles;
			printf("\n\t\t\t\t\t\tCual es el ID de la estacion a la que quiere mover las bicicletas:\n");
			printf("\t\t\t\t\t\t");
			__fpurge(stdin);
			while(scanf("%d",&ID2) == 0)
			{
				printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
				__fpurge(stdin);
			}
			while(Temp2->ID_estacion!=ID2 && Continua2==0)
			{
				__fpurge(stdin);
				Temp2=Temp2->Anterior;
				if(Temp2==NULL)
				{
					system("clear");
					Logo();
					printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que la segunda estacion no existe.\n");
					Continua2=1;
					Reasignar(Tat,Estacion,Bici,ID_usu);
				}
			}
			if(Temp2->Lugares_disponibles==0)
			{
				system("clear");
				Logo();
				printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que esta estacion no cuenta con lugares disponibles.\n");
				Reasignar(Tat,Estacion,Bici,ID_usu);
			}
			printf("\t\t\t\t\t\tEsta estacion cuenta con:\x1b[31m %d\x1b[0m bicicletas\n",10-Temp2->Lugares_disponibles);
			numbici2=10-Temp2->Lugares_disponibles;
			if(ID==ID2)
			{
				system("clear");
				Logo();
				printf("\n\t\t\t\t\t\tUsted esta seleccionando la misma estacion dos veces.\n");
			}
		}
	}while(ID==ID2);
	do
	{/*se hace lo mismo que en la primera estacion, solo que con los datos de la segunda*/
		printf("\n\t\t\t\t\t\tCuantas bicicletas quiere mover:\n");
		printf("\t\t\t\t\t\t");
		__fpurge(stdin);
		while(scanf("%d",&mover) == 0)
		{
			printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
			__fpurge(stdin);
		}
		maximo=10-numbici2;
		if(numbici2+mover>10)
		{
			printf("\n\t\t\t\t\t\tLa segunda estacion no cuenta con suficientes espacios para mover %d bicicletas\n",mover);		
			printf("\t\t\t\t\t\tSolo puede mover un maximo de %d bicicletas\n",maximo);
		}
		if(numbici-mover<0)
		{
			printf("\n\t\t\t\t\t\tLa primera estacion no cuenta con suficientes bicicletas.\n");		
			printf("\t\t\t\t\t\tSolo puede mover un maximo de %d bicicletas\n",numbici);
		}	
	}while(numbici2+mover>10 || numbici-mover<0);
	system("clear");
	Logo();
	printf("\n\t\t\t\t\t\tEl reacomodo quedaria:\n");
	printf("\t\t\t\t\t\t\x1b[31m%d\x1b[0m bicicletas en la primera estacion\n\t\t\t\t\t\t\x1b[31m%d\x1b[0m bicicletas en la segunda estacion.\n",numbici-mover,numbici2+mover);
	printf("\t\t\t\t\t\t¿Esta seguro que quier hacer este  reacomodo? (Y/N) (S) para salir.\n  ");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	scanf("%c",&Respuesta);
	while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='s' && Respuesta!='S')
	{	
		__fpurge(stdin);	
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n");
		__fpurge(stdin);
		printf("\t\t\t\t\t\t");
		scanf("%c",&Respuesta);
	}
	if (Respuesta=='Y' || Respuesta=='y')
	{	
		Temp->Lugares_disponibles=Temp->Lugares_disponibles+mover;
		Temp2->Lugares_disponibles=Temp2->Lugares_disponibles-mover;
		Archivo = fopen("Estaciones.txt","wt");
		while(Temp3->Anterior!=NULL)
		{
			Temp3=Temp3->Anterior;
		}
		do
		{
			fprintf(Archivo,"%d %d %d\n",Temp3->ID_estacion,Temp3->Lugares_disponibles,Temp3->CP);
			fprintf(Archivo,"%s",Temp3->Nombre);
			fprintf(Archivo,"%s",Temp3->Calle);
			fprintf(Archivo,"%s",Temp3->Ciudad);
			Temp3=Temp3->Siguiente;
		}while(Temp3!=NULL);
		fclose(Archivo);
		Timestamp(ID_usu,203);
	}
	if (Respuesta=='N' || Respuesta=='n')
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
		Reasignar(Tat,Estacion,Bici,ID_usu);
	}
	if (Respuesta=='S' || Respuesta=='s')
	{
		system("clear");
		Logo();
	}
}
void Menu_crear_usuario(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu)
{
	int Opcion;
	printf("\n\t\t\t\t\t\tPor favor elige la opción que deseas:\n\n");
	printf("\n\t\t\t\t\t\tLas opciones son:\n\n");
	printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m Alta usuario\n");
	printf("\t\t\t\t\t\t\x1b[31m2)\x1b[0m Baja usuario\n");
	printf("\n\t\t\t\t\t\t\x1b[31m9)\x1b[0m Regresar\n");
	printf("\n\t\t\t\t\t\tQue opcion quiere:");
	while(scanf("%d",&Opcion) == 0)
	{	
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	switch(Opcion)
	{
		case 1:	system("clear");
			Logo();
			Alta_usuario(Tat,ID_usu);
			Tat=Carga_memoria_usuarios();
			Menu_crear_usuario(Tat,Estacion,Bici,ID_usu);
			break;
		case 2:	system("clear");
			Logo();
			Baja_usuario(Tat,ID_usu);
			Tat=Carga_memoria_usuarios();
			Menu_crear_usuario(Tat,Estacion,Bici,ID_usu);
			break;
		case 9:system("clear");
			Logo();
			break;
		default:system("clear");
			Logo();
			printf ("\n\t\t\t\t\t\tEsa opción no es válida. Intenta nuevamente.\n");
			Menu_crear_usuario(Tat,Estacion,Bici,ID_usu);
			break;
	}
}

void Alta_usuario(Tipo_Usuario *Tat, int ID_usu)
{
	char Respuesta,Administrador;
	Tipo_Usuario *Temp;
	FILE *Archivo;
	Temp=(Tipo_Usuario *)malloc(sizeof(Tipo_Usuario));
	printf("\n\t\t\t\t\t\tIntroduce el nombre del usuario. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	fgets(Temp->Nombre,49,stdin);
	printf("\t\t\t\t\t\tIntroduce la calle del usuario. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	fgets(Temp->Calle,29,stdin);
	printf("\t\t\t\t\t\tIntroduce la contraseña deseada. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	fgets(Temp->Password,19,stdin);
	do
	{/*se valida que la tarjeta este dentro de los rangos dados por visa y master card*/
		printf("\t\t\t\t\t\tIntroduce el numero de su tarjeta (16 digitos). \n");
		__fpurge(stdin);
		printf("\t\t\t\t\t\t");
		while(scanf("%ld",&Temp->Tarjeta) == 0)
		{
			printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
			__fpurge(stdin);
		}
		__fpurge(stdin);
	}while((Temp->Tarjeta)<4000000000000000 || (Temp->Tarjeta)>5599999999999999);
	printf("\t\t\t\t\t\t¿Este usurio va a ser administrador? (Y/N) \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	scanf("%c",&Administrador);
	while (Administrador!='Y' && Administrador!='y' && Administrador!='N' && Administrador!='n')
	{		
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y o N.\n\t\t\t\t\t\t");
		__fpurge(stdin);
		scanf("%c",&Administrador);
	}
	if(Administrador=='y' || Administrador=='Y')
	{
		Temp->Administrador=1;
	}
	if(Administrador=='n' || Administrador=='N')
	{
		Temp->Administrador=0;
	}
	Temp->Bicicleta=0;
	system("clear");
	Logo();
	printf("\n\t\t\t\t\t\tSus datos son:\n\n");
	printf("\t\t\t\t\t\tNombre %s\t\t\t\t\t\tCalle %s\t\t\t\t\t\tPassword %s\t\t\t\t\t\tTarjeta %ld\n",Temp->Nombre, Temp->Calle,Temp->Password,Temp->Tarjeta);
	if(Temp->Administrador==0)
	{
		printf("\t\t\t\t\t\tAdministrador: No\n\n");
	}
	else
	{
		printf("\t\t\t\t\t\tAdministrador: Si\n\n");
	}
	printf("\n\t\t\t\t\t\t¿Son correctos los datos? (Y/N) (S) para salir.  ");
	printf("\t\t\t\t\t\t");
	scanf("%c",&Respuesta);
	while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='S' && Respuesta!='s')
	{		
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n\t\t\t\t\t\t");
		__fpurge(stdin);
		scanf("%c",&Respuesta);
	}
	if (Respuesta=='Y' || Respuesta=='y')
	{
		Archivo=fopen("Usuarios.txt","at");
		Tat->Siguiente=Temp;
		Temp->Anterior=Tat;
		Temp->Siguiente=NULL;
		Temp->ID=Tat->ID+1;
		Tat=Temp;
		system("clear");
		Logo();
		printf("\033[1m\n\t\t\t\t\t\tESTE USUARIO TIENE EL ID\033[1m \x1b[31m %d\n\x1b[0m",Temp->ID);
		fprintf(Archivo,"%d %ld %d %d\n",Temp->ID,Temp->Tarjeta,Temp->Bicicleta,Temp->Administrador);
		fprintf(Archivo,"%s",Temp->Nombre);
		fprintf(Archivo,"%s",Temp->Calle);
		fprintf(Archivo,"%s",Temp->Password);
		printf("\n\t\t\t\t\t\tLos datos fueron guardados exitosamente.\n");
		fclose(Archivo);
		Timestamp(ID_usu,301);
	}
	if (Respuesta=='N' || Respuesta=='n')
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
		Alta_usuario(Tat,ID_usu);
	}
	if (Respuesta=='S' || Respuesta=='s')
	{
		system("clear");
		Logo();
	}
}

void Baja_usuario(Tipo_Usuario *Tat, int ID_usu)
{
	int ID,Continuar=1;
	char Respuesta;
	Tipo_Usuario *Temp;
	FILE *Archivo;
	Temp=Tat;
	printf("\n\t\t\t\t\t\tCual es el ID del usuario que quiere borrar:\n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);	
	while(scanf("%d",&ID) == 0)
		{
			printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
			__fpurge(stdin);
		}
	while(Temp->ID!=ID && Continuar==1)
	{/*se busca, que exista el usuario*/
		Temp=Temp->Anterior;
		if(Temp==NULL)
		{
			system("clear");
			Logo();
			printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que ese ID no existe.\n");
			Continuar=0;
			Baja_usuario(Tat,ID_usu);
		}
	}
	if (Temp->Bicicleta!=0 && Temp->ID == ID)
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tNo se puede dar de baja ese usuario, ya que tiene una bicicleta en renta.\n");
		Continuar=0;
		Baja_usuario(Tat,ID_usu);
		return;
	}
	system("clear");
	Logo();
	printf("\n\t\t\t\t\t\tSus datos son:\n\n");
	printf("\t\t\t\t\t\t\033[1mID\x1b[0m %d\n\t\t\t\t\t\t\033[1mNombre\x1b[0m %s\t\t\t\t\t\t\033[1mCalle\x1b[0m %s\t\t\t\t\t\t\033[1mPassword\x1b[0m %s\t\t\t\t\t\t\033[1mTarjeta\x1b[0m %ld\n\t\t\t\t\t\t\033[1mAdministrador\x1b[0m %d \n\n",Temp->ID,Temp->Nombre, Temp->Calle,Temp->Password,Temp->Tarjeta,Temp->Administrador);
	printf("\t\t\t\t\t\t¿Son correctos los datos? (Y/N) (S) para salir. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	scanf("%c",&Respuesta);
	while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='S' && Respuesta!='s')
	{		
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n");
		printf("\t\t\t\t\t\t");
		__fpurge(stdin);
		scanf("%c",&Respuesta);
	}
	if (Respuesta=='Y' || Respuesta=='y')
	{
		if(Temp!=Tat &&(Temp->Anterior!=NULL))
		{/*Caso elemento a borrar en medio*/
			Temp->Anterior->Siguiente=Temp->Siguiente;
			Temp->Siguiente->Anterior=Temp->Anterior;
			Tat=Temp;
		}
		if(Temp->Anterior==NULL)
		{/*Caso elemento a borrar es el primero*/
			Temp=Temp->Siguiente;
			Temp->Anterior=NULL;
		}
		if(Temp==Tat)
		{ /*Caso elemento a borrar es el ultimo*/
			Temp=Temp->Anterior;
			Temp->Siguiente=NULL;
			Tat=Temp;
		}
		while(Temp->Anterior!=NULL)
		{/*Pone a temporal en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Temp=Temp->Anterior;
		}
		Archivo=fopen("Usuarios.txt","wt");
		do
		{
			fprintf(Archivo,"%d %ld %d %d\n",Temp->ID,Temp->Tarjeta,Temp->Bicicleta,Temp->Administrador);
			fprintf(Archivo,"%s",Temp->Nombre);
			fprintf(Archivo,"%s",Temp->Calle);
			fprintf(Archivo,"%s",Temp->Password);
			Temp=Temp->Siguiente;
		}while(Temp!=NULL);
		fclose(Archivo);
		Timestamp(ID_usu,302);
	}
	if (Respuesta=='N' || Respuesta=='n')
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
		Baja_usuario(Tat,ID_usu);
	}
	if (Respuesta=='S' || Respuesta=='s')
	{
		system("clear");
		Logo();
	}
}

void Alta_bicicleta(Tipo_Bicicleta *Bici,Tipo_Estacion *Estacion, int ID_usu)
{
	char Respuesta;
	int Estacion2,ID,Encontro=0,ID_estacion,Ignora,Disponibles,Flag=0,i,Bicicletas[10];
	char No[50];
	long Ignora2;
	Tipo_Bicicleta *Temp;
	Tipo_Estacion *Temp2;
	Temp2=Estacion;
	FILE *Archivo, *Estaciones;
	Temp=(Tipo_Bicicleta *)malloc(sizeof(Tipo_Bicicleta));
	do
	{

		printf("\n\t\t\t\t\t\tIntroduce el ID de la estacion a la que pertenecera la bicicleta:\n ");
		printf("\t\t\t\t\t\t");
		__fpurge(stdin);
		while(scanf("%d",&Estacion2) == 0)
		{
			printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
			__fpurge(stdin);
		}
		Estaciones=fopen("Estaciones.txt","rt");
		while ((fscanf(Estaciones,"%d %d %d\n",&ID_estacion,&Disponibles,&Ignora))==3) 
		{/*Abre el archivo Estaciones.txt y busca que tenga lugares disponibles la estacion que el usuario dijo*/
			for(i=0;i<10;i++)
			{
				fscanf(Estaciones,"-%d",&Bicicletas[i]);
			}
			fscanf(Estaciones,"\n",Ignora);
			fgets(No,50,Estaciones);
			fgets(No,30,Estaciones);
			fgets(No,20,Estaciones);
			if(ID_estacion==Estacion2)
			{
				if(Disponibles>0)
				{
					Encontro=1;	
					Temp->ID_estacion=Estacion2;
				}
				else
				{
					system("clear");
					Logo();
					printf("\n\t\t\t\t\t\t\tEsta estacion no cuenta con lugares disponibles.\n");
				}
			}
		}
		if (Encontro==1)
		{}
		else
		{
			system("clear");
			Logo();
			printf("\n\t\t\t\t\t\t\tNo se encontró esa estación. Intenta nuevamente. \n");
		}
		fclose(Estaciones);
	}while (Encontro==0);
	/*Buscar que estacion tenga lugares y asignar alli.*/
	if(Bici==NULL)
	{
		Temp->ID=1;
	}
	else
	{
		Temp->ID=Bici->ID+1;
	}
	Temp->Rentas=0;
	Temp->Timestamp=0;
	system("clear");
	Logo();
	printf("\n\t\t\t\t\t\t\033[1mLa nueva bicicleta quedara con el ID:\x1b[0m \x1b[31m%d\x1b[0m \n\t\t\t\t\t\tEstacion: %d \n",Temp->ID,Temp->ID_estacion);
	printf("\n\t\t\t\t\t\t¿Son correctos los datos? (Y/N) (S) para salir.\n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	scanf("%c",&Respuesta);
	while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='S' && Respuesta!='s')
	{		
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n");
		printf("\t\t\t\t\t\t");
		__fpurge(stdin);
		scanf("%c",&Respuesta);
	}
	if (Respuesta=='Y' || Respuesta=='y')
	{
		while(Temp2->ID_estacion!=Temp->ID_estacion)
		{
			Temp2=Temp2->Anterior;
		}
		for(i=0;i<10;i++)
		{
			if(Temp2->Bicicletas[i]==0 && Flag==0)
			{/*Busca -0 y lo remplaza por el ID de la nueva bicicleta y resta uno a lugares disponibles. Activa una bandera para que solo se 				haga una vez el proceso*/
				Temp2->Bicicletas[i]=Temp->ID;
				Temp2->Lugares_disponibles=Temp2->Lugares_disponibles-1;
				Flag=1;
			}
		}
		Estaciones=fopen("Estaciones.txt","wt");
		while(Temp2->Anterior!=NULL)
		{/*Pone a temporal en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
			Temp2=Temp2->Anterior;
		}
		do
		{
			fprintf(Estaciones,"%d %d %d\n",Temp2->ID_estacion,Temp2->Lugares_disponibles,Temp2->CP);
			for(i=0;i<10;i++)
			{
				fprintf(Estaciones,"-%d",Temp2->Bicicletas[i]);
			}
			fprintf(Estaciones,"\n");
			fprintf(Estaciones,"%s",Temp2->Nombre);
			fprintf(Estaciones,"%s",Temp2->Calle);
			fprintf(Estaciones,"%s",Temp2->Ciudad);
			Temp2=Temp2->Siguiente;
		}while(Temp2!=NULL);
		fclose(Estaciones);
		Archivo=fopen("Bicicletas.dat","a+b");
		if(Bici==NULL)
		{
			Bici=Temp;
			Bici->Siguiente=NULL;
			Bici->Anterior=NULL;
		}
		else
		{
			Bici->Siguiente=Temp;
			Temp->Anterior=Bici;
			Temp->Siguiente=NULL;
			Bici=Temp;
		}
		system("clear");
		Logo();
		printf("\033[1m\n\t\t\t\t\t\tESTA BICICLETA TIENE EL ID\x1b[0m	 \x1b[31m%d\n\x1b[0m",Temp->ID);
		fwrite(Bici,sizeof(Tipo_Bicicleta),1,Archivo);
		printf("\n\n\t\t\t\t\t\tLos datos fueron guardados exitosamente.\n");
		fclose(Archivo);
		Timestamp(ID_usu,201);
	}
	if (Respuesta=='N' || Respuesta=='n')
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
		Alta_bicicleta(Bici,Estacion,ID_usu);
	}
	if (Respuesta=='S' || Respuesta=='s')
	{
		system("clear");
		Logo();
	}
}

void Baja_bicicleta(Tipo_Bicicleta *Bici,Tipo_Estacion *Estacion, int ID_usu)
{
	int ID,i,Flag=0;
	char Respuesta;
	Tipo_Bicicleta *Temp;
	Tipo_Estacion *Temp2;
	FILE *Archivo, *Estaciones;
	Temp=Bici;
	Temp2=Estacion;
	printf("\n\t\t\t\t\t\tIntroduce el ID de la bicicleta que quieres dar de baja\n  ");
	printf("\t\t\t\t\t\t");
	while(scanf("%d",&ID) == 0)
	{
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	while(Temp->ID!=ID)
	{/*valida que exista el ID de la bicicleta*/
		Temp=Temp->Anterior;
		if(Temp==NULL)
			{
				system("clear");
				Logo();
				printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que ese ID no existe.\n");
				Baja_bicicleta(Bici,Estacion,ID_usu);
			}
	}
	if (Temp->Timestamp==0)
	{

		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tSus datos son:\n\n");
		printf("\t\t\t\t\t\tID %d\n\t\t\t\t\t\tEstacion %d\n\t\t\t\t\t\tNumero de rentas %d \n\n",Temp->ID,Temp->ID_estacion,Temp->Rentas);
		printf("\t\t\t\t\t\t¿Son correctos los datos? (Y/N) (S) para salir.\n  ");
		printf("\t\t\t\t\t\t");
		__fpurge(stdin);
		scanf("%c",&Respuesta);
		while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='S' && Respuesta!='s')
		{		
			printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n");
			printf("\t\t\t\t\t\t");
			__fpurge(stdin);
			scanf("%c",&Respuesta);
		}
		if (Respuesta=='Y' || Respuesta=='y')
		{
			while(Flag==0)
			{
				for(i=0;i<10;i++)
				{
					if(Temp2->Bicicletas[i]==Temp->ID)
					{
						Temp2->Bicicletas[i]=0;
						Temp2->Lugares_disponibles=Temp2->Lugares_disponibles+1;
						Flag=1;
					}
				}
				if(Flag==0)
				{
					Temp2=Temp2->Anterior;
				}
			}
			Estaciones=fopen("Estaciones.txt","wt");
			while(Temp2->Anterior!=NULL)
			{/*Pone a temporal en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
				Temp2=Temp2->Anterior;
			}
			do
			{
				fprintf(Estaciones,"%d %d %d\n",Temp2->ID_estacion,Temp2->Lugares_disponibles,Temp2->CP);
				for(i=0;i<10;i++)
				{
					fprintf(Estaciones,"-%d",Temp2->Bicicletas[i]);
				}
				fprintf(Estaciones,"\n");
				fprintf(Estaciones,"%s",Temp2->Nombre);
				fprintf(Estaciones,"%s",Temp2->Calle);
				fprintf(Estaciones,"%s",Temp2->Ciudad);
				Temp2=Temp2->Siguiente;
			}while(Temp2!=NULL);
			fclose(Estaciones);

			if(Temp!=Bici &&(Temp->Anterior!=NULL))
			{/*Caso elemento a borrar en medio*/
				Temp->Anterior->Siguiente=Temp->Siguiente;
				Temp->Siguiente->Anterior=Temp->Anterior;
				Temp=Bici;
			}
			if(Temp->Anterior==NULL)
			{/*Caso elemento a borrar es el primero*/
				Temp=Temp->Siguiente;
				Temp->Anterior=NULL;
			}
			if(Temp==Bici)
			{ /*Caso elemento a borrar es el ultimo*/
				Temp=Temp->Anterior;
				Temp->Siguiente=NULL;
				Bici=Temp;
			}

			while(Temp->Anterior!=NULL)
			{/*Pone a temporal en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
				Temp=Temp->Anterior;
			}
			Archivo=fopen("Bicicletas.dat","w+b");
			while (Temp!=NULL)
			{
				fwrite(Temp,sizeof(Tipo_Bicicleta),1,Archivo);
				Temp=Temp->Siguiente;
			}
			fclose(Archivo);
			Timestamp(ID_usu,202);
		}
		if (Respuesta=='N' || Respuesta=='n')
		{
			system("clear");
			Logo();
			printf("\n\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
			Baja_bicicleta(Bici,Estacion,ID_usu);
		}
		if (Respuesta=='S' || Respuesta=='s')
		{
			system("clear");
			Logo();
		}
	}
	else
	{
		printf("\n\t\t\t\t\t\tNo se puede borrar la bicicleta porque esta en renta. \n");
	}
}

void Menu_estacion(Tipo_Usuario *Tat,Tipo_Estacion *Estacion,Tipo_Bicicleta *Bici, int ID_usu)
{
	int Opcion;
	printf("\n\t\t\t\t\t\tPor favor elige la opción que deseas: \n\n");
	printf("\t\t\t\t\t\tLas opciones son:\n");
	printf("\t\t\t\t\t\t\x1b[31m1)\x1b[0m Alta bici-estacion\n");
	printf("\t\t\t\t\t\t\x1b[31m2)\x1b[0m Baja bici-estacion\n");
	printf("\n\t\t\t\t\t\t\x1b[31m9)\x1b[0m Regresar\n");
	printf("\n\t\t\t\t\t\tQue opcion quiere:");
	while(scanf("%d",&Opcion) == 0)
	{
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	switch(Opcion)
	{
		case 1:	system("clear");
			Logo();
			Alta_estacion(Estacion,ID_usu);
			Bici=Carga_memoria_bicicleta();
			Estacion=Carga_memoria_estacion();
			Menu_estacion(Tat,Estacion,Bici,ID_usu);
			break;
		case 2:	system("clear");
			Logo();
			if(Estacion==NULL)
			{/*valida que el archivo txt no este en blanco*/
				printf("\t\t\t\tNo se puede dar de baja porque no existe ninguna bicicleta en el sistema.\n");
			}
			else
			{
				Baja_estacion(Estacion,ID_usu);
				Bici=Carga_memoria_bicicleta();
				Estacion=Carga_memoria_estacion();
			}
			Menu_estacion(Tat,Estacion,Bici,ID_usu);
			break;
		case 9: system("clear");
			Logo();
			break;
		default:system("clear");
			Logo();
			printf ("\n\t\t\t\t\t\tEsa opción no es válida. Intenta nuevamente. \n");
			Menu_estacion(Tat,Estacion,Bici,ID_usu);
			break;
	}
}

void Alta_estacion (Tipo_Estacion *Estacion, int ID_usu)
{
	char Respuesta;
	int ID;
	Tipo_Estacion *Temp;
	FILE *Archivo,*Estaciones;
	Temp=(Tipo_Estacion *)malloc(sizeof(Tipo_Estacion));
	printf("\n\t\t\t\t\t\tIntroduce el nombre de la estacion. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	fgets(Temp->Nombre,49,stdin);
	printf("\t\t\t\t\t\tIntroduce la calle del estacion. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	fgets(Temp->Calle,29,stdin);
	printf("\t\t\t\t\t\tIntroduce la ciudad de la estacion. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	fgets(Temp->Ciudad,29,stdin);
	printf("\t\t\t\t\t\tIntroduce el CP de la estacion. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	while(scanf("%d",&Temp->CP) == 0)
	{
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	Temp->Lugares_disponibles=10;
	system("clear");
	Logo();
	printf("\n\t\t\t\t\t\tSus datos son:\n");
	printf("\n\t\t\t\t\t\tNombre %s\t\t\t\t\t\tCalle %s\t\t\t\t\t\tCiudad %s\t\t\t\t\t\tCP %d\n\n",Temp->Nombre, Temp->Calle,Temp->Ciudad,Temp->CP);
	printf("\n\t\t\t\t\t\t¿Son correctos los datos? (Y/N) (S) para salir. \n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	scanf("%c",&Respuesta);
	while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='S' && Respuesta!='s')
	{		
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n");
		__fpurge(stdin);
		printf("\t\t\t\t\t\t");
		scanf("%c",&Respuesta);
	}
	if (Respuesta=='Y' || Respuesta=='y')
	{
		Archivo=fopen("Estaciones.txt","at");

		if(Estacion==NULL)
		{/*se crea el primer campo de la estructura dinamica*/
			Temp->ID_estacion=1;
			Estacion=Temp;
			Estacion->Siguiente=NULL;
			Estacion->Anterior=NULL;
		}
		else
		{
			Temp->ID_estacion=Estacion->ID_estacion+1;
			Estacion->Siguiente=Temp;
			Temp->Anterior=Estacion;
			Temp->Siguiente=NULL;
			Estacion=Temp;
		}
		system("clear");
		Logo();
		printf("\033[1m	\n\t\t\t\t\t\tESTA ESTACION TIENE EL ID\x1b[0m \x1b[31m%d\n\x1b[0m	",Temp->ID_estacion);
		fprintf(Archivo,"%d %d %d\n",Temp->ID_estacion,Temp->Lugares_disponibles,Temp->CP);
		fprintf(Archivo,"%s",Temp->Nombre);
		fprintf(Archivo,"%s",Temp->Calle);
		fprintf(Archivo,"%s",Temp->Ciudad);
		printf("\n\n\t\t\t\t\t\tLos datos fueron guardados exitosamente.\n");
		fclose(Archivo);
		Timestamp(ID_usu,101);
	}
	if (Respuesta=='N' || Respuesta=='n')
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
		Alta_estacion(Estacion,ID_usu);
	}
	if (Respuesta=='S' || Respuesta=='s')
	{
		system("clear");
	}
}
void Baja_estacion (Tipo_Estacion *Estacion, int ID_usu)
{
	int ID;
	char Respuesta;
	Tipo_Estacion *Temp;
	FILE *Archivo;
	Temp=Estacion;
	printf("\n\t\t\t\t\t\tCual es el ID del la estacion que quiere borrar:\n");
	printf("\t\t\t\t\t\t");
	while(scanf("%d",&ID) == 0)
	{
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Recuerda que las respuestas son numeros.\n\t\t\t\t\t\t\t\t\t\t\t\t");
		__fpurge(stdin);
	}
	while(Temp->ID_estacion!=ID)
	{
		Temp=Temp->Anterior;
		if(Temp==NULL)
			{
				system("clear");
				Logo();
				printf("\n\t\t\t\t\t\tPor favor revise su datos. Ya que ese ID no existe.\n");
				Baja_estacion(Estacion,ID_usu);
			}
	}
	system("clear");
	Logo();	
	printf("\n\t\t\t\t\t\tSus datos son:\n\n");
	printf("\t\t\t\t\t\tID %d\n\t\t\t\t\t\tNombre %s\t\t\t\t\t\tCalle %s\t\t\t\t\t\tCiudad %s\n\t\t\t\t\t\tCP %d\n\t\t\t\t\t\tLugares disponibles %d \n\n",Temp->ID_estacion,Temp->Nombre, Temp->Calle,Temp->Ciudad,Temp->CP,Temp->Lugares_disponibles);
	printf("\n\t\t\t\t\t\t¿Seguro que la quiere borrar? (Y/N) (S) para salir.\n");
	printf("\t\t\t\t\t\t");
	__fpurge(stdin);
	scanf("%c",&Respuesta);
	while (Respuesta!='Y' && Respuesta!='y' && Respuesta!='N' && Respuesta!='n' && Respuesta!='S' && Respuesta!='s')
	{		
		printf("\n\t\t\t\t\t\tPor favor introduce una respuesta valida. Las opciones son Y, N o S.\n");
		printf("\t\t\t\t\t\t");
		__fpurge(stdin);
		scanf("%c",&Respuesta);
	}
	if (Respuesta=='Y' || Respuesta=='y')
	{
		if(Temp->Lugares_disponibles!=10)
		{
			system("clear");
			Logo();
			printf("\n\t\t\t\t\t\tLa estacion no puede ser borrada, ya que cuenta con bicicletas estacionadas.\n");
			printf("\n\t\t\t\t\t\tPara que esta estacion pueda ser borrada no debe de tener ninguna bicicleta.\n\n");
		}
		else
		{
			if(Temp!=Estacion &&(Temp->Anterior!=NULL))
			{/*Caso elemento a borrar en medio*/
				Temp->Anterior->Siguiente=Temp->Siguiente;
				Temp->Siguiente->Anterior=Temp->Anterior;
				Estacion=Temp;
			}
			if(Temp->Anterior==NULL)
			{/*Caso elemento a borrar es el primero*/
				Temp=Temp->Siguiente;
				Temp->Anterior=NULL;
			}
			if(Temp==Estacion)
			{ /*Caso elemento a borrar es el ultimo*/
				Temp=Temp->Anterior;
				Temp->Siguiente=NULL;
				Estacion=Temp;
			}
			while(Temp->Anterior!=NULL)
			{/*Pone a temporal en el primero elemento. Sirve para la escritura del archivo que sea en orden.*/
				Temp=Temp->Anterior;
			}
			Archivo=fopen("Estaciones.txt","wt");
			do
			{
				fprintf(Archivo,"%d %d %d\n",Temp->ID_estacion,Temp->Lugares_disponibles,Temp->CP);
				fprintf(Archivo,"%s",Temp->Nombre);
				fprintf(Archivo,"%s",Temp->Calle);
				fprintf(Archivo,"%s",Temp->Ciudad);
				Temp=Temp->Siguiente;
			}while(Temp!=NULL);
			fclose(Archivo);
			Timestamp(ID_usu,102);
		}
	}
	if (Respuesta=='N' || Respuesta=='n')
	{
		system("clear");
		Logo();
		printf("\n\t\t\t\t\t\tPor favor introduce nuevamente los datos.\n\n\n");
		Baja_estacion(Estacion,ID_usu);
	}
	if (Respuesta=='S' || Respuesta=='s')
	{
		system("clear");
	}
}
void Usuarios()
{
	char Nombre[50], Calle[30], Password[20];
	int Bicicleta, Administrador, ID;
	long Tarjeta;

	Tipo_Usuario *Temp,*Primero=NULL, *Tat;
	FILE *Archivo;
	Archivo = fopen("Usuarios.txt","rt");
	printf("Los usuarios en el sistema con sus contraseñas son: \n");
	printf("\n\tID\t\t\tPassword\n\n");	
	while(fscanf(Archivo,"%d %ld %d %d\n",&ID,&Tarjeta,&Bicicleta,&Administrador)==4)
	{
		fscanf(Archivo,"%d %ld %d %d\n",&ID,&Tarjeta,&Bicicleta,&Administrador);
		fgets(Nombre,50,Archivo);
		fgets(Calle,30,Archivo);
		fgets(Password,20,Archivo);
		printf("\t%d\t\t\t%s",ID,Password);
	}
	printf("\n");
	fclose(Archivo);

}
void Ayuda()
{
	printf("Usage: bicirenta.exe [Parametros]\n");
	printf("Bicirenta es un programa que permite la creación y administración de una red de bici-estaciones en distintas zonas de una ciudad.\n\n");
	printf("Los parametros disponibles son:\n");
	printf("\t-h Despliega un menu de ayuda.\n");
	printf("\t-c Despliega los creditos.\n");
	printf("\t-usu Despliega una lista de usuarios en el sistema.\n");
	printf("Ejemplo: \n");
	printf("\tbicirenta.exe\n");
	printf("\tbicirenta.exe -c\n");
	printf("\tbicirenta.exe -h\n");
	printf("\tbicirenta.exe -usu\n");
}

void Creditos()
{
	printf("\nEl programa bicirenta fue desarollado en el segundo semestre del 2013 por:\n");
	printf("\tAlonso de Cosio <alonso.decosio@gmail.com>\n");
	printf("\tManuel Nader <manuelmeljem@gmail.com>\n\n");
}

void Timestamp(int Quien, int Que)
{
	time_t t = time(NULL);
	struct tm *Fecha = localtime(&t);
	FILE *Archivo;
	Archivo=fopen("bitacora.txt","at");
	fprintf(Archivo,"%d%d%d-%d:%d:%d %d %d \n", Fecha->tm_year+1900,Fecha->tm_mon+1,Fecha->tm_mday,Fecha->tm_hour,Fecha->tm_min,Fecha->tm_sec, Que, Quien);
	/*Todos los que y quien son numeros.*/
	fclose(Archivo);
}
