void recupere();
int slash_verification(char* chaine);
void ip_tok(int *adresse, char* chaine, char* chaine1[]);
int ip_validation(char* ip);
int verification_ip(int* tab);
void deci_to_bin(int *tab, int *binaire);
void construct_msr(int nombre_reseau, int *msr_bin);
void construct_reseau(int *net_bin, int *ip_bin, int *msr_bin);
void construct_broadcast(int *binaire, int *ipbin, int *bin_broad, int *bin_pass);
