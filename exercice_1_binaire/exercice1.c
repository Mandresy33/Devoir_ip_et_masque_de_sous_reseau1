#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int puissance(int exposant);
void fillup(int num1, int num2, int num3, int num4, int *binaire);
void reseau_bin(int *bin_ip, int *bin_msr, int* bin_net);
void bin_to_deci(int *bin, int *deci);
void recupere()
{
	///Variable pour le masque de sous réseau
	int binaire[33];
    char saisie[100];
    char* part1;
    char* part2;
    char* part3;
    char* part4;
    int num1;
    int num2;
    int num3;
    int num4;
    int i=0;
    int cont = 0;
    int j = 0; 
    int arret = 0;
    int zero = 0;
    int test = 0;
    ///Variable pour l'adresse IP
    int ip[5];
    int ipbin[33];
    char saisie1[100]; 
    int cont1 = 0;
    int k = 0;
    ///Variable pour l'adresse reseau
    int bin_net[33];
    int deci_net[5];
    int bin_broad[33];
    int broadcast;
    int deci_broad[5];
    int bin_pass[33];
    //Entrer de l'adresse ip
    printf("Entrer l'adresse IP: ");
    scanf("%s", saisie1);
    
    //Entrer du masque de sous réseau
        printf("Entrez le masque de sous réseau: \n");
        scanf("%s", saisie);
        ///Analyse du masque
        //Contage des points;
        while(saisie[i]!= '\0')
        {
            if(saisie[i] == '.')
			{
                cont++;
            }
            i++;
        }
        
        //séparation des quatres champs
        if(cont == 3)
        {
            part1 = strtok(saisie, ".");
            part2 = strtok(NULL, ".");
            part3 = strtok(NULL,".");
            part4 = strtok(NULL,".");
            num1 = atoi(part1);
            num2 = atoi(part2);
            num3 = atoi(part3);
            num4 = atoi(part4);
            if((num1<0 && num1>255)||(num2 < 0 || num2 > 255)||(num3<0 || num3>255)||(num4<0 || num4>255))
            {
				printf("MSR NON VALIDE!! \n");
			}
			else
			{
				//Transformation en binaire et le mettre dans un tableau
				fillup(num1, num2, num3,num4, binaire);
				//Analyse des zéros vers la fin
				for(j = 0; j<32; j++)
				{
					if(binaire[j] == 1)
					{
						zero = 1;
						arret = j;
						break;
					}
				}
				if(zero == 0)
				{
					printf("\nMASQUE DE SOUS RESEAU INVALIDE!!!");
					exit (1);
				}
				else if(zero == 1)
				{
					for(i=arret+1; i<32; i++)
					{
						if(binaire[i] == 0)
						{
							printf("\nMasque de sous reseau non valide\n");
							test = 1;
							break;
						}
					}
					if(test != 1)
					{
						while(saisie1[k] != '\0')
						{
							if(saisie1[k] == '.')
								cont1++;
							k++;
						}
						if(cont1 == 3)
						{
							part1 = strtok(saisie1, ".");
							part2 = strtok(NULL, ".");
							part3 = strtok(NULL,".");
							part4 = strtok(NULL,".");
							ip[0] = atoi(part1);
							ip[1] = atoi(part2);
							ip[2] = atoi(part3);
							ip[3] = atoi(part4);
							if((ip[0]<0 && ip[0]>255)||(ip[1] < 0 || ip[1] > 255)||(ip[2]<0 || ip[2]>255)||(ip[3]<0 || ip[3]>255))
							{
								printf("ADRESSE IP NON VALIDE!! \n");
								exit (1);
							}
							else
							{
								int hote = 0;
								int nombre_machine = 0;
								fillup(ip[0],ip[1],ip[2],ip[3], ipbin);
								reseau_bin(ipbin, binaire, bin_net);
								if(bin_net[0] == 1)
								{
									printf("\nMasque de sous reseau invalide car aucun appareil ne peut se connecter: nombre de hote 0\n");
									exit (1);
								}
								printf("\n\nAdresse reseau en binaire: ");
								for(int o = 31; o>=0; o--)
								{
									printf("%d", bin_net[o]);
								} 
								for (i=0; i<32; i++)
								{
									if(binaire[i]==1)
									{
										hote=i;
										break;
									}
								}
								nombre_machine = puissance(hote);
								nombre_machine = nombre_machine - 2;
								if(nombre_machine > 0)
								{
									bin_to_deci(bin_net, deci_net);
									printf("\n\nAdresse reseau: %d.%d.%d.%d \nHote: %d \nNombre de machine: %d",deci_net[0],deci_net[1],deci_net[2],deci_net[3], hote, nombre_machine);
									for(i=0; i<32; i++)
									{
										if(binaire[i] == 0)
										{
											bin_pass[i] = 1;
										}
										else if(binaire[i] == 1)
										{
											bin_pass[i] = 0;
										}
									}
									for(i = 0; i<32; i++)
									{
										if(ipbin[i] == 1 || bin_pass[i] == 1)
										{
											bin_broad[i] = 1;
										}
										else
										{
											bin_broad[i] = 0;
										}
									}
									printf("\n\nBroadcast en binaire: \n");
									for(int o = 31; o>=0; o--)
									{
										printf("%d", bin_broad[o]);
									} 
									printf("\nBroadcast en decimal: \n");
									bin_to_deci(bin_broad, deci_broad);
									printf("%d.%d.%d.%d\n", deci_broad[0],deci_broad[1],deci_broad[2],deci_broad[3] );
								}
								else
								{
									printf("\nInvalide IP ou Masque de sous reseau: aucun appareil ne peut se connecter!! \n");
								}
							}
						}
						else{
							printf("ADRESSE IP NON VALIDE!! \n");
							exit (1);
						}
					}
				}
			}
        }
        else
        {
			printf("\nMasque de sous reseau INVALIDE !! \n");
		}
}
void bin_to_deci(int *bin, int *deci)
{
	int i = 0; 
	int j = 0;
	int puissance = 1;
	deci[2] = 0;
	deci[3] = 0;
	deci[1] = 0;
	deci[0] = 0;
	for(i = 15; i>=8; i--)
	{
		for(j = 8; j<i; j++)
		{
			puissance = puissance * 2;
		}
		puissance = bin[i] * puissance;
		deci[2] = deci[2] + puissance;
		puissance = 1;
	}
	for(i = 23; i>=16; i--)
	{
		for(j = 16; j<i; j++)
		{
			puissance = puissance * 2;
		}
		puissance = bin[i] * puissance;
		deci[1] = deci[1] + puissance;
		puissance = 1;
	}
	for(i = 31; i>=24; i--)
	{
		for(j = 24; j<i; j++)
		{
			puissance = puissance * 2;
		}
		puissance = bin[i] * puissance;
		deci[0] = deci[0] + puissance;
		puissance = 1;
	}
	for(i=7; i>=0; i--)
	{
		for(j = 0; j<i; j++)
		{
			puissance = puissance * 2;
		}
		puissance = bin[i] * puissance;
		deci[3] = deci[3] + puissance;
		puissance = 1;
	}
}
void reseau_bin(int *bin_ip, int *bin_msr,int *bin_net)
{
	int i;
	for(i = 0; i<32; i++)
	{
		if(bin_ip[i] == 1 && bin_msr[i] == 1)
		{
			bin_net[i] = 1;
		}
		else
		{
			bin_net[i] = 0;
		}
	}
	
}
void fillup(int num1, int num2, int num3, int num4, int *binaire)
{
	int j = 0;
	for(j = 0; j<8; j++)
	{
		binaire[j] = num4 % 2;
		num4 = num4 / 2;
	}
	for(j = 8; j<16; j++)
	{
		binaire[j] = num3 % 2;
		num3 = num3 / 2;
	}
	for(j = 16; j<24; j++)
	{
		binaire[j] = num2 % 2;
		num2 = num2 / 2;
	}
	for(j=24; j<32; j++)
	{
		binaire[j] = num1 % 2;
		num1 = num1 / 2;
	}
}
int puissance(int exposant)
{
	int i = 0;
	int nombre = 1;
	for(i=0; i<exposant; i++)
	{
		nombre = nombre * 2;
	}
	return nombre;
}
