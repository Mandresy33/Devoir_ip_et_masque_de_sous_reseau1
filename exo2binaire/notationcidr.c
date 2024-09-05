#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DIM 100
int slash_verification(char* chaine);
void ip_tok(int *adresse, char* chaine, char* chaine1[]);
int ip_validation(char* ip);
int verification_ip(int* tab);
void deci_to_bin(int *tab, int *binaire);
void construct_msr(int nombre_reseau, int *msr_bin);
void construct_reseau(int *net_bin, int *ip_bin, int *msr_bin);
void construct_broadcast(int *binaire, int *ipbin, int *bin_broad, int *bin_pass);
void recupere()
{
    //Variable pour récuperer les données saisies
    char donner[DIM];
    char* adresse_ip;
    char* char_reseau;
    //Variable pour les boucles et incrémentation
    int slash = 0;
    int point = 0; 
    int i;
    int valide = 0;
    //Variables pour manipuler les adresses ip
    char* ip_char[5];
    int ip_deci[5];
    int ip_bin[33];
    //Variable pour manipuler le reseau
    int nombre_reseau = 0;
    int net_deci[5];
    int net_bin[33];
    int msr_bin[33];
	//Variable pour le broadcast
	int broad_bin[33];
	int bin_pass[33];
	//Variable pour le découpage
	int nombre_decoupage;
	int nombre_sousnet;
    saisie: 
        printf("Entrer l'adresse IP et le nombre de reseau(notation CIDR: adresse/reseau)");
        scanf("%s", donner);
        //Verification du donner saisie
        if(donner != NULL)
        {
            //Vérification si il y a une slash
            slash = slash_verification(donner);
            if(slash == 1)
            {
				//Vérification du format de l'adresse IP
                adresse_ip = strtok(donner, "/");
                char_reseau = strtok(NULL, "/");
                point = ip_validation(adresse_ip);
                if(point == 3)
                {
					printf("Adresse IP: %s\n", adresse_ip);
					//Récupération des quatre chiffres
					ip_tok(ip_deci, adresse_ip, ip_char);
					//Vérification des chiffres de l'adresse IP
					valide = verification_ip(ip_deci);
					if(valide == 1)
					{
						//Transformation de l'adresse IP en binaire
						deci_to_bin(ip_deci, ip_bin);
						printf("\nAdresse IP en binaire: ");
						for(i = 31; i>=0; i--)
						{
							printf("%d", ip_bin[i]);
						}
						//Vérification du reseau
						nombre_reseau = atoi(char_reseau);
						if(nombre_reseau >0 && nombre_reseau<33)
						{
							printf("\nNombre reseau = %d", nombre_reseau);
							//Fabrication du binaire du masque de sous reseau
							printf("\nMasque de sous reseau en binaire: ");
							construct_msr(nombre_reseau, msr_bin);
							for(i = 31; i>=0; i--)
							{
								printf("%d", msr_bin[i]);
							} 
							//Fabrication de l'adresse reseau
							construct_reseau(net_bin, ip_bin,msr_bin);
							printf("\nAdresse reseau en binaire: ");
							for(i = 31; i>=0; i--)
							{
								printf("%d", net_bin[i]);
							}
							//Fabrication de l'adresse broadcast
							construct_broadcast(msr_bin, ip_bin, broad_bin, bin_pass);
							printf("\nAdresse broadcast en binaire: ");
							for(i = 31; i>=0; i--)
							{
								printf("%d", broad_bin[i]);
							}
							//Saisie du nombre de découpage
							decoupe: 
								printf("\nEntrer le nombre de découpage\n");
								scanf("%d", &nombre_decoupage);
								nombre_sousnet = 1;
								if(nombre_decoupage>=0 && nombre_decoupage <33)
								{
									//Nombre de machine
									for(i = 0; i<nombre_decoupage; i++)
									{
										nombre_sousnet = nombre_sousnet*2;
									}
									printf("Nombre de machine pour chaque sous reseau: %d", nombre_sousnet);
									//Adresse reseau et broadcast pour chaque sous reseau
								}
								else
								{
									printf("\nNombre de decoupage invalide!! \n");
									goto decoupe;
								}
						}
						else
						{
							printf("\nNombre de reseau invalide!!\n");
							goto saisie;
						}						
					}
					else
					{
						printf("\n INVALIDE ADRESSE IP");
						goto saisie;
					}
				}
				else
				{
					printf("Erreur du format de l'adresse IP\n Format exact: xxx.xxx.xxx.xxx\n");
					goto saisie;
				}
			}
        }
            else
			{
                printf("Erreur!!! Format xxx.xxx.xxx.xxx/nombre reseau\n\n");
                goto saisie;
			}
}
int slash_verification(char* chaine)
{
    int slash = 0;
    int i;
    for(i = 0; chaine[i]!= '\0'; i++)
    {
        if(chaine[i] == '/')
        {
            slash++;
        }
    }
    return slash;
}
void ip_tok(int *adresse, char* chaine, char* chaine1[])
{
	chaine1[0] = strtok(chaine, ".");
	for(int i = 1; i<4; i++)
	{
		chaine1[i] = strtok(NULL, ".");
	}
	for(int i = 0; i<4; i++)
	{
		adresse[i] = atoi(chaine1[i]);
	}
}
int ip_validation(char* ip)
{
	int point = 0;
	for(int i = 0; ip[i]!= '\0'; i++)
	{
		if(ip[i] == '.')
		{
			point++;
		}
	}
	return point;
}
int verification_ip(int* tab)
{
	if((tab[0]>=0 && tab[0]<256) && (tab[1]>=0 && tab[1]<256) && (tab[2]>=0 && tab[2]<256) && (tab[3]>=0 && tab[3]<256))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void deci_to_bin(int *tab, int *binaire)
{
	for(int i = 0; i<32; i++)
	{
		binaire[i] = 0;
	}
	int j = 0;
	for(j = 0; j<8; j++)
	{
		binaire[j] = tab[3] % 2;
		tab[3] = tab[3] / 2;
	}
	for(j = 8; j<16; j++)
	{
		binaire[j] = tab[2] % 2;
		tab[2] = tab[2] / 2;
	}
	for(j = 16; j<24; j++)
	{
		binaire[j] = tab[1] % 2;
		tab[1] = tab[1] / 2;
	}
	for(j=24; j<32; j++)
	{
		binaire[j] = tab[0] % 2;
		tab[0] = tab[0] / 2;
	}
}
void construct_msr(int nombre_reseau, int *msr_bin)
{
	for(int i=0; i<(32-nombre_reseau); i++)
	{
		msr_bin[i] = 0;
	}
	for(int i = 32-nombre_reseau; i<32; i++)
	{
		msr_bin[i] = 1;
	}
}
void construct_reseau(int *net_bin, int *ip_bin, int *msr_bin)
{
	for(int i = 0; i<32; i++)
	{
		if(ip_bin[i] == 1 && msr_bin[i] == 1)
		{
			net_bin[i] = 1;
		}
		else
		{
			net_bin[i] = 0;
		}
	}
}
void construct_broadcast(int *binaire, int *ipbin, int *bin_broad, int *bin_pass)
{
	int i = 0;
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
}