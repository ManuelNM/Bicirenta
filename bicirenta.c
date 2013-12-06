#include "funciones.h"

void main(int argc, char *argv[])
{
	if (argc==1)
	{
		Tipo_Usuario *Tat;
		Tipo_Estacion *Estacion;
		Tipo_Bicicleta *Bici;
		Tat=Carga_memoria_usuarios();
		Bici=Carga_memoria_bicicleta();
		Estacion=Carga_memoria_estacion();
		system("clear");
		printf("\t\t\t\t\t\tDesarrollado por: Alonso de Cosio y Manuel Nader\n");
		Logo();
		printf("\n\n\t\t\t\t\t\t\t\t:D Bienvenido :D\n\n");
		printf("\t\t\t\t\t\tPor favor llene los siguientes campos correctamente\n\n");
		Acceso(Tat,Estacion,Bici);
	}
	else
	{
		if(argc>3)
		{
			printf("Esos parametros no son validos. Usa -h para obtener ayuda.\n");
		}
		switch(argv[1][1])
		{
			case 'h': case 'H': Ayuda();
				break;
			case 'c': case 'C': Creditos();
				break;
			case 'u': case 'U': 
				if((argv[1][2]=='s' && argv[1][3]=='u') || (argv[1][2]=='S' && argv[1][3]=='U'))
				{
					Usuarios();
				}
				else
				{
					printf("Esos parametros no son validos. Usa -h para obtener ayuda.\n");				
				}
				break;
			default: 
				printf("Esos parametros no son validos. Usa -h para obtener ayuda.\n");
				break;
		}
	}
}
